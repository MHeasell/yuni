#include <cstdlib>
#include <memory.h>

#include "av.h"

namespace Yuni
{
namespace Private
{
namespace Audio
{

	namespace // anonymous
	{

		/*!
		** \brief Get the next packet of data
		**
		** Used by get*Data to search for more compressed data, and buffer it in the
		** correct stream. It won't buffer data for streams that the app doesn't have a
		** handle for.
		*/
		void GetNextPacket(AudioFile* file, int streamidx)
		{
			AVPacket packet;
			while (av_read_frame(file->FormatContext, &packet) >= 0)
			{
				AudioStream** iter = file->Streams;
				// Check each stream the user has a handle for, looking for the one
				// this packet belongs to
				for (size_t i = 0; i < file->StreamsSize; ++i, ++iter)
				{
					if ((*iter)->StreamIdx == packet.stream_index)
					{
						size_t idx = (*iter)->DataSize;

						// Found the stream. Grow the input data buffer as needed to
						// hold the new packet's data. Additionally, some ffmpeg codecs
						// need some padding so they don't overread the allocated
						// buffer
						if (idx + packet.size > (*iter)->DataSizeMax)
						{
							char* temp = (char*)realloc((*iter)->Data, idx + packet.size +
														FF_INPUT_BUFFER_PADDING_SIZE);
							if (!temp)
								break;
							(*iter)->Data = temp;
							(*iter)->DataSizeMax = idx + packet.size;
						}

						// Copy the packet and free it
						memcpy(&(*iter)->Data[idx], packet.data, packet.size);
						(*iter)->DataSize += packet.size;

						// Return if this stream is what we needed a packet for
						if (streamidx == (*iter)->StreamIdx)
						{
							av_free_packet(&packet);
							return;
						}
						break;
					}
				}
				// Free the packet and look for another
				av_free_packet(&packet);
			}
		}

	} // namespace anonymous

	bool AV::Init()
	{
	  std::cout << "AV::Init" << std::endl;
		av_register_all();
 		// Silence warning output from the lib
		av_log_set_level(AV_LOG_ERROR);
		return true;
	}


	void AV::CloseFile(AudioFile* file)
	{
	  std::cout << "AV::CloseFile" << std::endl;
		if (!file)
			return;

		for (size_t i = 0; i < file->StreamsSize; ++i)
		{
			avcodec_close(file->Streams[i]->CodecContext);
			free(file->Streams[i]->Data);
			free(file->Streams[i]->DecodedData);
			free(file->Streams[i]);
		}
		free(file->Streams);

		av_close_input_file(file->FormatContext);
		free(file);
	}


	AudioStream* AV::GetAudioStream(AudioFile* file, int streamnum)
	{
		if (!file)
			return NULL;

		for (unsigned int i = 0; i < file->FormatContext->nb_streams; ++i)
		{
			if (file->FormatContext->streams[i]->codec->codec_type != CODEC_TYPE_AUDIO)
				continue;

			if (0 == streamnum)
			{
				// Found the requested stream. Check if a handle to this stream
				// already exists and return it if it does
				for (size_t j = 0; j < file->StreamsSize; ++j)
				{
					if (file->Streams[j]->StreamIdx == (int)i)
						return file->Streams[j];
				}

				// Doesn't yet exist. Now allocate a new stream object and fill in
				// its info
				AudioStream* stream = (AudioStream*)calloc(1, sizeof(*stream));
				if (!stream)
					return NULL;

				stream->parent = file;
				stream->CodecContext = file->FormatContext->streams[i]->codec;
				stream->StreamIdx = i;

				// Try to find the codec for the given codec ID, and open it
				AVCodec* codec = avcodec_find_decoder(stream->CodecContext->codec_id);
				if (!codec || avcodec_open(stream->CodecContext, codec) < 0)
				{
					free(stream);
					return NULL;
				}

				// Allocate space for the decoded data to be stored in before it
				// gets passed to the app
				stream->DecodedData = (char*)malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE);
				if (!stream->DecodedData)
				{
					avcodec_close(stream->CodecContext);
					free(stream);
					return NULL;
				}

				// Append the new stream object to the stream list. The original
				// pointer will remain valid if realloc fails, so we need to use
				// another pointer to watch for errors and not leak memory
				AudioStream** temp = (AudioStream**)realloc(file->Streams, (file->StreamsSize + 1) *
													  sizeof(AudioStream*));
				if (!temp)
				{
					avcodec_close(stream->CodecContext);
					free(stream->DecodedData);
					free(stream);
					return NULL;
				}
				file->Streams = temp;
				file->Streams[file->StreamsSize++] = stream;
				return stream;
			}
			streamnum--;
		}
		return NULL;
	}


	int AV::GetAudioInfo(AudioStream* stream, int *rate, int *channels, int *bits)
	{
		if (!stream || stream->CodecContext->codec_type != CODEC_TYPE_AUDIO)
			return 1;

		if (rate)
			*rate = stream->CodecContext->sample_rate;
		if (channels)
			*channels = stream->CodecContext->channels;
		if (bits)
			*bits = 16;

		return 0;
	}


	int AV::GetAudioData(AudioStream* stream, void *data, int length)
	{
		int dec = 0;

		if (!stream || stream->CodecContext->codec_type != CODEC_TYPE_AUDIO)
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
				memcpy(data, stream->DecodedData, rem);
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
					size_t rem = insize-len;
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
