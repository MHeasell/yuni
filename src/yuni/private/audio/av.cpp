#include <cstdlib>
#include <memory.h>

#include "av.h"

namespace Yuni
{
namespace Private
{
namespace Audio
{


	static uint8* GetVideoBuffer(Stream* stream)
	{
		// Determine required buffer size and allocate buffer
		int numBytes = avpicture_get_size(PIX_FMT_YUV420P, stream->codec->width, stream->codec->height);
		return (uint8*)malloc(numBytes * sizeof(uint8));
	}


	/*!
	** \brief Get the next packet of data
	**
	** Used by get*Data to search for more compressed data, and buffer it in the
	** correct stream. It won't buffer data for streams that the app doesn't have a
	** handle for.
	*/
	static void GetNextPacket(File* file, int streamidx)
	{
		AVPacket packet;
		while (av_read_frame(file->format, &packet) >= 0)
		{
			// Check each stream the user has a handle for, looking for the one
			// this packet belongs to
			for (uint i = 0; i != file->streams.size(); ++i)
			{
				Stream* stream = file->streams[i];
				if (stream->streamIdx != packet.stream_index)
					continue;

				size_t idx = stream->dataSize;

				// Found the stream. Grow the input data buffer as needed to
				// hold the new packet's data. Additionally, some ffmpeg codecs
				// need some padding so they don't overread the allocated
				// buffer
				if (idx + packet.size > stream->dataSizeMax)
				{
					char* temp = (char*)realloc(stream->data, idx + packet.size +
												FF_INPUT_BUFFER_PADDING_SIZE);
					if (!temp)
						break;
					stream->data = temp;
					stream->dataSizeMax = idx + packet.size;
				}

				// Copy the packet and free it
				YUNI_MEMCPY(&stream->data[idx], packet.size, packet.data, packet.size);
				stream->dataSize += packet.size;

				// Return if this stream is what we needed a packet for
				if (streamidx == stream->streamIdx)
				{
					av_free_packet(&packet);
					return;
				}
				break;
			}
			// Free the packet and look for another
			av_free_packet(&packet);
		}
	}

	// New version
	static bool GetNextPacket(Stream* stream, AVPacket& packet)
	{
		do
		{
			// Free old packet
			if (packet.data != nullptr)
				av_free_packet(&packet);

			// Read new packet
			if (av_read_packet(stream->parent->format, &packet) < 0)
				// No more packet to read
				return false;
		} while (packet.stream_index != stream->streamIdx);
		return true;
	}



	bool AV::Init()
	{
		av_register_all();
		# ifdef NDEBUG
		// Silence warning output from the lib
		av_log_set_level(AV_LOG_ERROR);
		# else // NDEBUG
		// Only write output when encountering unrecoverable errors
		av_log_set_level(AV_LOG_FATAL);
		# endif // NDEBUG
		return true;
	}


	File* AV::OpenFile(const AnyString& filename)
	{
		if (filename.empty())
			return nullptr;

		File* file = (File*) calloc(1, sizeof(File));
		if (!file)
			return nullptr;

		# if LIBAVFORMAT_VERSION_MAJOR < 53
		if (av_open_input_file(&file->format, filename.c_str(), nullptr, 0, nullptr))
		# else
		if (avformat_open_input(&file->format, filename.c_str(), nullptr, nullptr))
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
		{
			free(file);
			return nullptr;
		}

		// After opening, we must search for the stream information because not
		// all formats will have it in stream headers (eg. system MPEG streams)
		# if LIBAVFORMAT_VERSION_MAJOR < 53
		if (av_find_stream_info(file->format) < 0)
		# else
		if (avformat_find_stream_info(file->format, nullptr) < 0)
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
		{
			CloseFile(file);
			return nullptr;
		}

		return file;
	}



	void AV::CloseFile(File*& file)
	{
		if (!file)
			return;

		for (uint i = 0; i < file->streams.size(); ++i)
		{
			avcodec_close(file->streams[i]->codec);
			free(file->streams[i]->data);
			free(file->streams[i]->decodedData);
			av_free(file->streams[i]->frame);
		}

		# if LIBAVFORMAT_VERSION_MAJOR < 53
		av_close_input_file(file->format);
		# else
		avformat_close_input(&file->format);
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
		free(file);
		file = nullptr;
	}


	Stream* AV::GetVideoStream(File* file, int streamIndex)
	{
		if (!file)
			return nullptr;

		for (uint i = 0; i < file->format->nb_streams; ++i)
		{
			// Reject streams that are not VIDEO
			# if LIBAVFORMAT_VERSION_MAJOR < 53
			if (file->format->streams[i]->codec->codec_type != CODEC_TYPE_VIDEO)
			# else
			if (file->format->streams[i]->codec->codec_type != AVMEDIA_TYPE_VIDEO)
			# endif // LIBAVFORMAT_VERSION_MAJOR < 53
			{
				continue;
			}

			// Continue until we find the requested stream
			if (streamIndex > 0)
			{
				--streamIndex;
				continue;
			}

			// Check if a handle to this stream already exists
			// and return it if it does
			for (size_t j = 0; j < file->streams.size(); ++j)
			{
				if (file->streams[j]->streamIdx == (int)i)
					return file->streams[j];
			}

			// Doesn't yet exist. Now allocate a new stream object and fill in
			// its info
			Stream* stream = (Stream*)calloc(1, sizeof(*stream));
			if (!stream)
				return nullptr;

			stream->parent = file;
			stream->codec = file->format->streams[i]->codec;
			stream->streamIdx = i;

			// Try to find the codec for the given codec ID, and open it
			AVCodec* codec = avcodec_find_decoder(stream->codec->codec_id);
			if (!codec)
			{
				free(stream);
				return nullptr;
			}

			// Inform the codec that we can handle truncated bitstreams -- i.e.,
			// bitstreams where frame boundaries can fall in the middle of packets
			if (codec->capabilities & CODEC_CAP_TRUNCATED)
				stream->codec->flags |= CODEC_FLAG_TRUNCATED;

			# if LIBAVFORMAT_VERSION_MAJOR < 53
			if (!codec || avcodec_open(stream->codec, codec) < 0)
			# else
			if (!codec || avcodec_open2(stream->codec, codec, NULL) < 0)
			# endif // LIBAVFORMAT_VERSION_MAJOR < 53
			{
				free(stream);
				return nullptr;
			}

			uint64_t frameSize = stream->codec->sample_rate * 2 *
				stream->codec->channels;
			stream->size = frameSize * (file->format->duration / AV_TIME_BASE);

			// Allocate space for the frame data to be stored in
			stream->frame = avcodec_alloc_frame();
			stream->decodedData = GetVideoBuffer(stream);
			if (!stream->frame)
			{
				avcodec_close(stream->codec);
				free(stream);
				return nullptr;
			}

			// Append the new stream object to the stream list.
			file->streams.push_back(stream);
			return stream;
		}
		return nullptr;
	}


	Stream* AV::GetAudioStream(File* file, int streamIndex)
	{
		if (!file)
			return nullptr;

		for (uint i = 0; i < file->format->nb_streams; ++i)
		{
			// Reject streams that are not AUDIO
			# if LIBAVFORMAT_VERSION_MAJOR < 53
			if (file->format->streams[i]->codec->codec_type != CODEC_TYPE_AUDIO)
			# else
			if (file->format->streams[i]->codec->codec_type != AVMEDIA_TYPE_AUDIO)
			# endif // LIBAVFORMAT_VERSION_MAJOR < 53
			{
				continue;
			}

			// Continue until we find the requested stream
			if (streamIndex > 0)
			{
				--streamIndex;
				continue;
			}

			// Check if a handle to this stream already exists
			// and return it if it does
			for (size_t j = 0; j < file->streams.size(); ++j)
			{
				if (file->streams[j]->streamIdx == (int)i)
					return file->streams[j];
			}

			// Doesn't yet exist. Now allocate a new stream object and fill in
			// its info
			Stream* stream = (Stream*)calloc(1, sizeof(*stream));
			if (!stream)
				return nullptr;

			stream->parent = file;
			stream->codec = file->format->streams[i]->codec;
			stream->streamIdx = i;

			// Try to find the codec for the given codec ID, and open it
			AVCodec* codec = avcodec_find_decoder(stream->codec->codec_id);
			# if LIBAVFORMAT_VERSION_MAJOR < 53
			if (!codec || avcodec_open(stream->codec, codec) < 0)
			# else
			if (!codec || avcodec_open2(stream->codec, codec, NULL) < 0)
			# endif // LIBAVFORMAT_VERSION_MAJOR < 53
			{
				free(stream);
				return nullptr;
			}

			uint64_t frameSize = stream->codec->sample_rate * 2 *
				stream->codec->channels;
			stream->size = frameSize * (file->format->duration / AV_TIME_BASE);

			// Allocate space for the decoded data to be stored in before it
			// gets passed to the app
			stream->decodedData = (uint8*)malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE);
			if (!stream->decodedData)
			{
				avcodec_close(stream->codec);
				free(stream);
				return nullptr;
			}

			stream->frame = nullptr;

			// Append the new stream object to the stream list.
			file->streams.push_back(stream);
			return stream;
		}
		return nullptr;
	}


	float AV::GetVideoFrameRate(const Stream* stream)
	{
		# if LIBAVFORMAT_VERSION_MAJOR < 53
		if (!stream || !stream->codec || stream->codec->codec_type != CODEC_TYPE_VIDEO)
		# else
		if (!stream || !stream->codec || stream->codec->codec_type != AVMEDIA_TYPE_VIDEO)
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
			return 0.0f;
		return (float)stream->codec->time_base.den / stream->codec->time_base.num;
	}


	bool AV::GetVideoInfo(const Stream* stream, uint& width, uint& height, uint& depth)
	{
		# if LIBAVFORMAT_VERSION_MAJOR < 53
		if (!stream || !stream->codec || stream->codec->codec_type != CODEC_TYPE_VIDEO)
		# else
		if (!stream || !stream->codec || stream->codec->codec_type != AVMEDIA_TYPE_VIDEO)
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
			return false;

		width = stream->codec->width;
		height = stream->codec->height;
		depth = av_get_bits_per_pixel(&av_pix_fmt_descriptors[stream->codec->pix_fmt]);
		return true;
	}


	bool AV::GetAudioInfo(const Stream* stream, int& rate, int& channels, int& bits)
	{
		# if LIBAVFORMAT_VERSION_MAJOR < 53
		if (!stream || !stream->codec || stream->codec->codec_type != CODEC_TYPE_AUDIO)
		# else
		if (!stream || !stream->codec || stream->codec->codec_type != AVMEDIA_TYPE_AUDIO)
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
			return false;

		rate = stream->codec->sample_rate;
		channels = stream->codec->channels;
		bits = 16;
		return true;
	}


	uint AV::GetStreamDuration(const Stream* stream)
	{
		if (!stream)
			return 0;
		assert(stream->parent);
		assert(stream->parent->format);
		return stream->parent->format->duration / AV_TIME_BASE;
	}


	size_t AV::GetAudioData(Stream* stream, void* data, size_t length)
	{
		size_t dec = 0;

		# if LIBAVFORMAT_VERSION_MAJOR < 53
		if (!stream || stream->codec->codec_type != CODEC_TYPE_AUDIO)
		# else
		if (!stream || stream->codec->codec_type != AVMEDIA_TYPE_AUDIO)
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
			return 0;

		while (dec < length)
		{
			// If there's any pending decoded data, deal with it first
			if (stream->decodedDataSize > 0)
			{
				// Get the amount of bytes remaining to be written, and clamp to
				// the amount of decoded data we have
				size_t rem = length - dec;
				if (rem > stream->decodedDataSize)
					rem = stream->decodedDataSize;

				// Copy the data to the app's buffer and increment
				YUNI_MEMCPY(data, rem, stream->decodedData, rem);
				data = (char*)data + rem;
				dec += rem;

				// If there's any decoded data left, move it to the front of the
				// buffer for next time
				if (rem < stream->decodedDataSize)
					memmove(stream->decodedData, &stream->decodedData[rem],
							stream->decodedDataSize - rem);
				stream->decodedDataSize -= rem;
			}

			// Check if we need to get more decoded data
			if (stream->decodedDataSize == 0)
			{
				size_t insize;
				int size;
				int len;

				insize = stream->dataSize;
				if (0 == insize)
				{
					GetNextPacket(stream->parent, stream->streamIdx);
					// If there's no more input data, break and return what we have
					if (insize == stream->dataSize)
						break;
					insize = stream->dataSize;
					memset(&stream->data[insize], 0, FF_INPUT_BUFFER_PADDING_SIZE);
				}

				// Clear the input padding bits
				// Decode some data, and check for errors
				size = AVCODEC_MAX_AUDIO_FRAME_SIZE;
				AVPacket pkt;
				//AvFrame* decodedFrame = NULL;

				av_init_packet(&pkt);
				pkt.data = (uint8_t*)stream->data;
				pkt.size = insize;

				while ((len = avcodec_decode_audio3(stream->codec,
					(int16_t*)stream->decodedData, &size, &pkt)) == 0)
				{
					if (size > 0)
						break;
					GetNextPacket(stream->parent, stream->streamIdx);
					if (insize == stream->dataSize)
						break;
					insize = stream->dataSize;
					memset(&stream->data[insize], 0, FF_INPUT_BUFFER_PADDING_SIZE);
					pkt.data = (uint8_t*)stream->data;
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
						memmove(stream->data, &stream->data[len], rem);
					stream->dataSize = rem;
				}
				// Set the output buffer size
				stream->decodedDataSize = size;
			}
		}

		// Return the number of bytes we were able to get
		return dec;
	}


	bool AV::GetNextVideoFrame(Stream* stream)
	{
		int frameFinished;
		AVPacket packet;

		while (::av_read_frame(stream->parent->format, &packet) >= 0)
		{
			// Is this a packet from the video stream?
			if (packet.stream_index == stream->streamIdx)
			{
				// Decode video frame
				#if LIBAVCODEC_VERSION_INT > AV_VERSION_INT(52,30,0)
				::avcodec_decode_video2(stream->codec, stream->frame,
					&frameFinished, &packet);
				#else
				::avcodec_decode_video(stream->codec, stream->frame, &frameFinished,
					packet.data, packet.size);
				#endif // LIBAVCODEC_VERSION_INT > AV_VERSION_INT(52,30,0)

				// Did we get a video frame?
				if (frameFinished)
				{
					::avpicture_fill((AVPicture*)stream->frame, stream->decodedData,
						PIX_FMT_YUV420P, stream->codec->width, stream->codec->height);
					::av_free_packet(&packet);
					return true;
				}
			}

			// Free the packet that was allocated by av_read_frame
			::av_free_packet(&packet);
		}
		return false;
	}

// 	bool AV::GetNextVideoFrame(Stream* stream)
// 	{
// 		static int bytesRemaining = 0;
// 		int frameFinished;
// 		uint8* rawData;
// 		int bytesDecoded;
// 		AVPacket packet;

// 		packet.data = nullptr;
// 		# if LIBAVFORMAT_VERSION_MAJOR < 53
// 		if (!stream || stream->codec->codec_type != CODEC_TYPE_VIDEO)
// 		# else
// 		if (!stream || stream->codec->codec_type != AVMEDIA_TYPE_VIDEO)
// 		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
// 			return false;

// 		// Decode packets until we have decoded a complete frame
// 		while (true)
// 		{
// 			// Work on the current packet until we have decoded all of it
// 			while (bytesRemaining > 0)
// 			{
// 				// Decode the next chunk of data
// #if LIBAVCODEC_VERSION_INT > AV_VERSION_INT(52,30,0)
// 				bytesDecoded = avcodec_decode_video2(stream->codec, stream->frame,
// 					&frameFinished, &packet);
// #else
// 				bytesDecoded = avcodec_decode_video(stream->codec, stream->frame,
// 					&frameFinished, packet.data, packet.size);
// #endif // LIBAVCODEC_VERSION_INT > AV_VERSION_INT(52,30,0)

// 				// Was there an error?
// 				if (bytesDecoded < 0)
// 				{
// 					fprintf(stderr, "Error while decoding frame\n");
// 					return false;
// 				}

// 				bytesRemaining -= bytesDecoded;
// 				rawData += bytesDecoded;

// 				// Did we finish the current frame? Then we can return
// 				if (frameFinished)
// 				{
// 					YUNI_MEMCPY(stream->decodedData, bytesDecoded, stream->frame->data, bytesDecoded);
// 					return true;
// 				}
// 			}

// 			// Read the next packet, skipping all packets that aren't for this stream
// 			if (!GetNextPacket(stream, packet))
// 				break;

// 			bytesRemaining = packet.size;
// 			rawData = packet.data;
// 		}

// 		// Decode the rest of the last frame
// #if LIBAVCODEC_VERSION_INT > AV_VERSION_INT(52,30,0)
// 		bytesDecoded = avcodec_decode_video2(stream->codec, stream->frame, &frameFinished,
// 			&packet);
// #else
// 		bytesDecoded = avcodec_decode_video(stream->codec, stream->frame, &frameFinished,
// 			rawData, bytesRemaining);
// #endif // LIBAVCODEC_VERSION_INT > AV_VERSION_INT(52,30,0)

// 		// Free last packet
// 		if (packet.data != nullptr)
// 			av_free_packet(&packet);

// 		return 0 != frameFinished;
// 	}



} // namespace Audio
} // namespace Private
} // namespace Yuni
