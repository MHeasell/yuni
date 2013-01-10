#ifndef __YUNI_PRIVATE_AUDIO_FILE_HXX__
# define __YUNI_PRIVATE_AUDIO_FILE_HXX__

namespace Yuni
{
namespace Private
{
namespace Audio
{


	template<StreamType TypeT>
	inline typename Stream<TypeT>::Ptr File::addStream(uint index)
	{
		typedef Stream<TypeT> MyStream;

		for (uint i = 0; i < pFormat->nb_streams; ++i)
		{
			// Reject streams that are not VIDEO
			if (!isSameType<TypeT>(pFormat->streams[i]->codec->codec_type))
				continue;

			// Continue until we find the requested stream
			if (index > 0)
			{
				--index;
				continue;
			}

			// Allocate a new stream object and fill in its info
			typename MyStream::Ptr stream = new MyStream(this, pFormat, pFormat->streams[i]->codec, i);
			if (!stream)
				// The new stream is destroyed here by the SmartPtr
				return nullptr;

			// Check that the codec was properly loaded
			if (!stream->valid())
			{
				// The new stream is destroyed here by the SmartPtr
				continue;
			}

			// Append the new stream object to the stream list.
			getCache<TypeT>()[stream->index()] = stream;
			return stream;
		}
		return nullptr;
	}


	template<StreamType TypeT>
	inline typename Stream<TypeT>::Ptr File::getStream(uint index)
	{
		assert(pFormat);
		auto& cache = getCache<TypeT>();
		auto it = cache.find(index);
		if (cache.end() != it)
			return it->second;

		return addStream<TypeT>(index);
	}


	template<StreamType TypeT>
	inline void File::getNextPacket(Stream<TypeT>* stream)
	{
		AVPacket packet;
		while (::av_read_frame(pFormat, &packet) >= 0)
		{
			// Check each stream the user has a handle for, looking for the one
			// this packet belongs to
			auto& cache = getCache<TypeT>();
			auto end = cache.end();
			for (auto it = cache.begin(); it != end; ++it)
			{
				typename Stream<TypeT>::Ptr crtStream = it->second;
				if (crtStream->index() != (uint)packet.stream_index)
					continue;

				size_t idx = crtStream->pDataSize;

				// Found the stream. Grow the input data buffer as needed to
				// hold the new packet's data. Additionally, some ffmpeg codecs
				// need some padding so they don't overread the allocated
				// buffer
				if (idx + packet.size > crtStream->pDataSizeMax)
				{
					char* temp = (char*)realloc(crtStream->pData, idx + packet.size +
												FF_INPUT_BUFFER_PADDING_SIZE);
					if (!temp)
						break;
					crtStream->pData = temp;
					crtStream->pDataSizeMax = idx + packet.size;
				}

				// Copy the packet and free it
				YUNI_MEMCPY(&crtStream->pData[idx], packet.size, packet.data, packet.size);
				crtStream->pDataSize += packet.size;

				// Return if this stream is what we needed a packet for
				if (crtStream->index() == stream->index())
				{
					::av_free_packet(&packet);
					return;
				}
				break;
			}
			// Free the packet and look for another
			::av_free_packet(&packet);
		}
	}


	template<>
	inline bool File::isSameType<stVideo>(AVMediaType type) const
	{
		# if LIBAVFORMAT_VERSION_MAJOR < 53
		return CODEC_TYPE_VIDEO == type;
		# else
		return AVMEDIA_TYPE_VIDEO == type;
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
	}

	template<>
	inline bool File::isSameType<stAudio>(AVMediaType type) const
	{
		# if LIBAVFORMAT_VERSION_MAJOR < 53
		return CODEC_TYPE_AUDIO == type;
		# else
		return AVMEDIA_TYPE_AUDIO == type;
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
	}

	template<StreamType TypeT>
	inline bool File::isSameType(AVMediaType type) const
	{
		YUNI_STATIC_ASSERT(false, InvalidStreamType);
		return false;
	}


	template<>
	inline typename Stream<stVideo>::Map& File::getCache<stVideo>()
	{
		return pVStreams;
	}

	template<>
	inline typename Stream<stAudio>::Map& File::getCache<stAudio>()
	{
		return pAStreams;
	}

	template<StreamType TypeT>
	inline typename Stream<TypeT>::Map& File::getCache()
	{
		YUNI_STATIC_ASSERT(false, InvalidStreamType);
		return pVStreams;
	}



} // namespace Audio
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_AUDIO_FILE_HXX__