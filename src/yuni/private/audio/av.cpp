#include <cstdlib>
#include <memory.h>

#include "av.h"

namespace Yuni
{
namespace Private
{
namespace Audio
{

	/*!
	** \brief Get the next packet of data
	**
	** Used by get*Data to search for more compressed data, and buffer it in the
	** correct stream. It won't buffer data for streams that the app doesn't have a
	** handle for.
	*/
	static void GetNextPacket(AudioFile* file, int streamidx)
	{
		AVPacket packet;
		while (av_read_frame(file->formatContext, &packet) >= 0)
		{
			// Check each stream the user has a handle for, looking for the one
			// this packet belongs to

			for (uint i = 0; i != file->streams.size(); ++i)
			{
				AudioStream* stream = file->streams[i];
				if (stream->StreamIdx != packet.stream_index)
					continue;

				size_t idx = stream->DataSize;

				// Found the stream. Grow the input data buffer as needed to
				// hold the new packet's data. Additionally, some ffmpeg codecs
				// need some padding so they don't overread the allocated
				// buffer
				if (idx + packet.size > stream->DataSizeMax)
				{
					char* temp = (char*)realloc(stream->Data, idx + packet.size +
												FF_INPUT_BUFFER_PADDING_SIZE);
					if (!temp)
						break;
					stream->Data = temp;
					stream->DataSizeMax = idx + packet.size;
				}

				// Copy the packet and free it
				YUNI_MEMCPY(&stream->Data[idx], packet.size, packet.data, packet.size);
				stream->DataSize += packet.size;

				// Return if this stream is what we needed a packet for
				if (streamidx == stream->StreamIdx)
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


	AudioFile* AV::OpenFile(const AnyString& filename)
	{
		if (filename.empty())
			return nullptr;

		AudioFile* file = (AudioFile*) calloc(1, sizeof(AudioFile));
		if (!file)
			return nullptr;

		# if LIBAVFORMAT_VERSION_MAJOR < 53
		if (not av_open_input_file(&file->formatContext, filename.c_str(), NULL, 0, NULL))
		# else
		if (not avformat_open_input(&file->formatContext, filename.c_str(), NULL, NULL))
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
		{
			// After opening, we must search for the stream information because not
			// all formats will have it in stream headers (eg. system MPEG streams)
			# if LIBAVFORMAT_VERSION_MAJOR < 53
			if (av_find_stream_info(file->formatContext) >= 0)
			# else
			if (avformat_find_stream_info(file->formatContext, NULL) >= 0)
			# endif // LIBAVFORMAT_VERSION_MAJOR < 53
				return file;

			# if LIBAVFORMAT_VERSION_MAJOR < 53
			av_close_input_file(file->formatContext);
			# else
			avformat_close_input(&file->formatContext);
			# endif // LIBAVFORMAT_VERSION_MAJOR < 53
		}

		free(file);
		return nullptr;
	}



	void AV::CloseFile(AudioFile*& file)
	{
		if (!file)
			return;

		uint size = file->streamsSize;
		for (uint i = 0; i < size; ++i)
		{
			avcodec_close(file->streams[i]->CodecContext);
			free(file->streams[i]->Data);
			free(file->streams[i]->DecodedData);
		}

		# if LIBAVFORMAT_VERSION_MAJOR < 53
		av_close_input_file(file->formatContext);
		# else
		avformat_close_input(&file->formatContext);
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
		free(file);
		file = nullptr;
	}


	AudioStream* AV::GetAudioStream(AudioFile* file, int streamIndex)
	{
		if (!file)
			return nullptr;

		for (uint i = 0; i < file->formatContext->nb_streams; ++i)
		{
			// Reject streams that are not AUDIO
			# if LIBAVFORMAT_VERSION_MAJOR < 53
			if (file->formatContext->streams[i]->codec->codec_type != CODEC_TYPE_AUDIO)
			# else
			if (file->formatContext->streams[i]->codec->codec_type != AVMEDIA_TYPE_AUDIO)
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
			for (size_t j = 0; j < file->streamsSize; ++j)
			{
				if (file->streams[j]->StreamIdx == (int)i)
					return file->streams[j];
			}

			// Doesn't yet exist. Now allocate a new stream object and fill in
			// its info
			AudioStream* stream = (AudioStream*)calloc(1, sizeof(*stream));
			if (!stream)
				return nullptr;

			stream->parent = file;
			stream->CodecContext = file->formatContext->streams[i]->codec;
			stream->StreamIdx = i;

			// Try to find the codec for the given codec ID, and open it
			AVCodec* codec = avcodec_find_decoder(stream->CodecContext->codec_id);
			# if LIBAVFORMAT_VERSION_MAJOR < 53
			if (!codec || avcodec_open(stream->CodecContext, codec) < 0)
			# else
			if (!codec || avcodec_open2(stream->CodecContext, codec, NULL) < 0)
			# endif // LIBAVFORMAT_VERSION_MAJOR < 53
			{
				free(stream);
				return nullptr;
			}

			uint64_t frameSize = stream->CodecContext->sample_rate * 2 *
				stream->CodecContext->channels;
			stream->Size = frameSize * (file->formatContext->duration / AV_TIME_BASE);

			// Allocate space for the decoded data to be stored in before it
			// gets passed to the app
			stream->DecodedData = (char*)malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE);
			if (!stream->DecodedData)
			{
				avcodec_close(stream->CodecContext);
				free(stream);
				return nullptr;
			}

			// Append the new stream object to the stream list.
			file->streamsSize++;
			file->streams.push_back(stream);
			return stream;
		}
		return nullptr;
	}


	int AV::GetAudioInfo(AudioStream* stream, int& rate, int& channels, int& bits)
	{
		# if LIBAVFORMAT_VERSION_MAJOR < 53
		if (!stream || stream->CodecContext->codec_type != CODEC_TYPE_AUDIO)
		# else
		if (!stream || stream->CodecContext->codec_type != AVMEDIA_TYPE_AUDIO)
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
			return 1;

		rate = stream->CodecContext->sample_rate;
		channels = stream->CodecContext->channels;
		bits = 16;

		return 0;
	}


	uint AV::GetStreamDuration(const AudioStream* stream)
	{
		if (!stream)
			return 0;
		assert(stream->parent);
		assert(stream->parent->formatContext);
		return stream->parent->formatContext->duration / AV_TIME_BASE;
	}


	size_t AV::GetAudioData(AudioStream* stream, void *data, size_t length)
	{
		size_t dec = 0;

		# if LIBAVFORMAT_VERSION_MAJOR < 53
		if (!stream || stream->CodecContext->codec_type != CODEC_TYPE_AUDIO)
		# else
		if (!stream || stream->CodecContext->codec_type != AVMEDIA_TYPE_AUDIO)
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
			return 0;

		while (dec < length)
		{
			// If there's any pending decoded data, deal with it first
			if (stream->DecodedDataSize > 0)
			{
				// Get the amount of bytes remaining to be written, and clamp to
				// the amount of decoded data we have
				size_t rem = length - dec;
				if (rem > stream->DecodedDataSize)
					rem = stream->DecodedDataSize;

				// Copy the data to the app's buffer and increment
				YUNI_MEMCPY(data, rem, stream->DecodedData, rem);
				data = (char*)data + rem;
				dec += rem;

				// If there's any decoded data left, move it to the front of the
				// buffer for next time
				if (rem < stream->DecodedDataSize)
					memmove(stream->DecodedData, &stream->DecodedData[rem],
							stream->DecodedDataSize - rem);
				stream->DecodedDataSize -= rem;
			}

			// Check if we need to get more decoded data
			if (stream->DecodedDataSize == 0)
			{
				size_t insize;
				int size;
				int len;

				insize = stream->DataSize;
				if (0 == insize)
				{
					GetNextPacket(stream->parent, stream->StreamIdx);
					// If there's no more input data, break and return what we have
					if (insize == stream->DataSize)
						break;
					insize = stream->DataSize;
					memset(&stream->Data[insize], 0, FF_INPUT_BUFFER_PADDING_SIZE);
				}

				// Clear the input padding bits
				// Decode some data, and check for errors
				size = AVCODEC_MAX_AUDIO_FRAME_SIZE;
				AVPacket pkt;
				//AvFrame* decodedFrame = NULL;

				av_init_packet(&pkt);
				pkt.data = (uint8_t*)stream->Data;
				pkt.size = insize;

				while ((len = avcodec_decode_audio3(stream->CodecContext,
					(int16_t*)stream->DecodedData, &size, &pkt)) == 0)
				{
					if (size > 0)
						break;
					GetNextPacket(stream->parent, stream->StreamIdx);
					if (insize == stream->DataSize)
						break;
					insize = stream->DataSize;
					memset(&stream->Data[insize], 0, FF_INPUT_BUFFER_PADDING_SIZE);
					pkt.data = (uint8_t*)stream->Data;
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
						memmove(stream->Data, &stream->Data[len], rem);
					stream->DataSize = rem;
				}
				// Set the output buffer size
				stream->DecodedDataSize = size;
			}
		}

		// Return the number of bytes we were able to get
		return dec;
	}





} // namespace Audio
} // namespace Private
} // namespace Yuni
