#ifndef __YUNI_PRIVATE_MEDIA_STREAM_HXX__
# define __YUNI_PRIVATE_MEDIA_STREAM_HXX__

#include "openal.h"
#include "../../core/math.h"

namespace Yuni
{
namespace Private
{
namespace Media
{


	template<StreamType TypeT>
	Stream<TypeT>::Stream(File* parent, AVFormatContext* format, AVCodecContext* codecCtx, uint index):
		pCodec(codecCtx),
		pFormat(format),
		pIndex(index),
		pALFormat(0),
		pSize(0),
		pCrtPts(AV_NOPTS_VALUE),
		pData(nullptr),
		pDataSize(0),
		pDataSizeMax(0),
		pDecodedData(nullptr),
		pDecodedDataSize(0),
		pFrame(nullptr),
		pParent(parent)
	{
		if (!pParent)
		{
			pCodec = nullptr;
			return;
		}

		// Try to find the codec for the given codec ID, and open it
		AVCodec* codec = ::avcodec_find_decoder(pCodec->codec_id);
		# if LIBAVFORMAT_VERSION_MAJOR < 53
		if (!codec || ::avcodec_open(pCodec, codec) < 0)
		# else
		if (!codec || ::avcodec_open2(pCodec, codec, NULL) < 0)
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
		{
			pCodec = nullptr;
			return;
		}

		if (IsAudio)
			pALFormat = Private::Media::OpenAL::GetFormat(16,  pCodec->channels);
	}


	template<StreamType TypeT>
	Stream<TypeT>::~Stream()
	{
		if (pCodec)
			::avcodec_close(pCodec);
		::free(pData);
		::free(pDecodedData);
		if (pFrame)
			::av_free(pFrame);
	}


	template<StreamType TypeT>
	template<uint SizeT>
	inline uint Stream<TypeT>::nextBuffer(CString<SizeT, false>& buffer)
	{
		YUNI_STATIC_ASSERT(IsAudio, nextBufferNotAccessibleInVideo);

		if (!pDecodedData)
		{
			uint64 frameSize = rate() * 2 * channels();
			pSize = frameSize * pFormat->duration / AV_TIME_BASE;

			// Allocate space for the decoded data to be stored in
			pDecodedData = (uint8*)::malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE);
		}

		uint dec = 0;
		char* data = buffer.data();
		while (dec < SizeT)
		{
			// If there's any pending decoded data, deal with it first
			if (pDecodedDataSize > 0)
			{
				// Get the amount of bytes remaining to be written, and clamp to
				// the amount of decoded data we have
				size_t rem = SizeT - dec;
				if (rem > pDecodedDataSize)
					rem = pDecodedDataSize;

				// Copy the data to the app's buffer and increment
				YUNI_MEMCPY(data, rem, pDecodedData, rem);
				data = (char*)data + rem;
				dec += rem;

				// If there's any decoded data left, move it to the front of the
				// buffer for next time
				if (rem < pDecodedDataSize)
					::memmove(pDecodedData, &pDecodedData[rem], pDecodedDataSize - rem);
				pDecodedDataSize -= rem;
			}

			// Check if we need to get more decoded data
			if (pDecodedDataSize == 0)
			{
				size_t insize = pDataSize;
				if (0 == insize)
				{
					pParent->getNextPacket<stAudio>(this);
					// If there's no more input data, break and return what we have
					if (insize == pDataSize)
						break;
					insize = pDataSize;
					::memset(&pData[insize], 0, FF_INPUT_BUFFER_PADDING_SIZE);
				}

				// Clear the input padding bits
				// Decode some data, and check for errors
				int size = AVCODEC_MAX_AUDIO_FRAME_SIZE;
				AVPacket pkt;
				//AvFrame* decodedFrame = NULL;

				::av_init_packet(&pkt);
				pkt.data = (uint8_t*)pData;
				pkt.size = insize;

				int len;
				while ((len = ::avcodec_decode_audio3(pCodec,
					(int16_t*)pDecodedData, &size, &pkt)) == 0)
				{
					if (size > 0)
						break;
					pParent->getNextPacket<stAudio>(this);
					if (insize == pDataSize)
						break;
					insize = pDataSize;
					::memset(&pData[insize], 0, FF_INPUT_BUFFER_PADDING_SIZE);
					pkt.data = (uint8_t*)pData;
					pkt.size = insize;
				}

				if (len < 0)
					break;

				if (len > 0)
				{
					// If any input data is left, move it to the start of the
					// buffer, and decrease the buffer size
					size_t rem = insize - len;
					if (rem)
						memmove(pData, &pData[len], rem);
					pDataSize = rem;
				}
				// Set the output buffer size
				pDecodedDataSize = size;
			}
		}

		// Return the number of bytes we were able to get
		return dec;
	}


	template<StreamType TypeT>
	uint Stream<TypeT>::readFrame()
	{
		AVPacket packet;
		int frameFinished = 0;
		int bytesRead = 0;

		// We should not have to clean the frame here, but it's a security
		// pFrame should be nullptr when entering here
		if (pFrame)
			::av_free(pFrame);

		pFrame = ::avcodec_alloc_frame();

		while (!frameFinished)
		{
			// Read a packet
			if (::av_read_frame(pFormat, &packet) != 0)
			{
				::av_free(pFrame);
				pFrame = nullptr;
				break;
			}
			// Ignore packets from other streams
			if ((uint)packet.stream_index != pIndex)
				continue;

			if (IsVideo)
			{
				pCrtPts = 0;
				// If we can decode it
				#if LIBAVCODEC_VERSION_INT > AV_VERSION_INT(52,30,0)
				if ((bytesRead = ::avcodec_decode_video2(pCodec, pFrame, &frameFinished, &packet)) >= 0)
				#else
				if ((bytesRead = ::avcodec_decode_video(pCodec, pFrame, &frameFinished, packet.data, packet.size)) >= 0)
				#endif
				{
					// If the frame is finished (should be in one shot for video stream)
					if (frameFinished)
					{
						if (AV_NOPTS_VALUE == packet.dts && pFrame->opaque
							&& AV_NOPTS_VALUE != *(uint64_t*)pFrame->opaque)
							pCrtPts = *(uint64_t*)pFrame->opaque;
						else if (AV_NOPTS_VALUE != packet.dts)
							pCrtPts = packet.dts;
						else
							pCrtPts = 0.0;
						pCrtPts *= ::av_q2d(pCodec->time_base);
						break;
					}
				}
			}
			else // IsAudio
			{
				// If we can decode it
				#if LIBAVCODEC_VERSION_INT > AV_VERSION_INT(52,30,0)
				if ((bytesRead = ::avcodec_decode_audio4(pCodec, pFrame, &frameFinished, &packet)) >= 0)
				#else
				if ((bytesRead = ::avcodec_decode_audio3(pCodec, pFrame, &frameFinished, packet.data, packet.size)) >= 0)
				#endif
				{
					// If the frame is finished (should be in one shot for video stream)
					if (frameFinished)
					{
						pFrame->pts = packet.dts;
						break;
					}
				}
			}
		}

		// free packet
		::av_free_packet(&packet);
		return bytesRead;
	}


	template<StreamType TypeT>
	inline Frame::Ptr Stream<TypeT>::nextFrame()
	{
		//YUNI_STATIC_ASSERT(IsVideo, nextFrameNotAccessibleInAudio);
		readFrame();
		// TODO : Give the real frame index
		Frame::Ptr frame = new Frame(0u, pCrtPts);
		frame->setData(pFrame);
		pFrame = nullptr;
		return frame;
	}


	// template<StreamType TypeT>
	// inline uint8* Stream<TypeT>::nextBuffer(uint& count)
	// {
	// 	YUNI_STATIC_ASSERT(IsAudio, nextBufferNotAccessibleInVideo);
	// 	count = readFrame();
	// count = ::av_samples_get_buffer_size(NULL, stream->CodecCtx->channels,
    //                                           stream->Frame->nb_samples,
    //                                           stream->CodecCtx->sample_fmt, 1);
	// 	return pFrame->data[0];
	// }


	template<StreamType TypeT>
	inline uint Stream<TypeT>::index() const
	{
		return pIndex;
	}


	template<StreamType TypeT>
	inline uint Stream<TypeT>::duration() const
	{
		assert(pParent);
		return pParent->duration();
	}


	template<StreamType TypeT>
	inline uint Stream<TypeT>::width() const
	{
		YUNI_STATIC_ASSERT(IsVideo, NotAccessibleInAudio);
		return pCodec->width;
	}


	template<StreamType TypeT>
	inline uint Stream<TypeT>::height() const
	{
		YUNI_STATIC_ASSERT(IsVideo, NotAccessibleInAudio);
		return pCodec->height;
	}


	template<StreamType TypeT>
	inline uint Stream<TypeT>::depth() const
	{
		YUNI_STATIC_ASSERT(IsVideo, NotAccessibleInAudio);
		return ::av_get_bits_per_pixel(&::av_pix_fmt_descriptors[pCodec->pix_fmt]);
	}


	template<StreamType TypeT>
	inline float Stream<TypeT>::fps() const
	{
		YUNI_STATIC_ASSERT(IsVideo, NotAccessibleInAudio);
		assert(pCodec);
		float variable = (float)pFormat->streams[pIndex]->avg_frame_rate.num / pFormat->streams[pIndex]->avg_frame_rate.den;
		float constant = (float)pCodec->time_base.den / (pCodec->time_base.num * pCodec->ticks_per_frame);
		return Math::Min(variable, constant);
	}


	template<StreamType TypeT>
	inline uint Stream<TypeT>::rate() const
	{
		YUNI_STATIC_ASSERT(IsAudio, NotAccessibleInVideo);
		assert(pCodec);
		return pCodec->sample_rate;
	}


	template<StreamType TypeT>
	inline uint Stream<TypeT>::channels() const
	{
		YUNI_STATIC_ASSERT(IsAudio, NotAccessibleInVideo);
		assert(pCodec);
		return pCodec->channels;
	}


	template<StreamType TypeT>
	inline uint Stream<TypeT>::bits() const
	{
		YUNI_STATIC_ASSERT(IsAudio, NotAccessibleInVideo);
		assert(pCodec);
		// Internal FFMpeg format is always 16 bits
		return 16;
	}


	template<StreamType TypeT>
	inline StreamType Stream<TypeT>::type() const
	{
		return TypeT;
	}



} // namespace Media
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_MEDIA_STREAM_HXX__