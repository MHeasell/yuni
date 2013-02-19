#ifndef __YUNI_PRIVATE_MEDIA_FILE_HXX__
# define __YUNI_PRIVATE_MEDIA_FILE_HXX__

namespace Yuni
{
namespace Private
{
namespace Media
{


	template<StreamType TypeT>
	inline typename Stream<TypeT>::Ptr File::addStream(uint index)
	{
		typedef Stream<TypeT> MyStream;

		// Loop on streams in the file
		for (uint i = 0; i < pFormat->nb_streams; ++i)
		{
			// Reject streams that are not the requested codec type
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
		typename Stream<TypeT>::Map& cache = getCache<TypeT>();
		typename Stream<TypeT>::Map::iterator it = cache.find(index);
		if (cache.end() != it)
			return it->second;

		return addStream<TypeT>(index);
	}


	template<StreamType TypeT>
	inline AVPacket* File::getNextPacket(Stream<TypeT>* stream)
	{
		AVPacket* packet = new AVPacket();
		// Get a packet
		while (::av_read_frame(pFormat, packet) >= 0)
		{
			// Search for the corresponding stream in the video stream cache
			auto vIt = pVStreams.find((uint)packet->stream_index);
			if (pVStreams.end() != vIt)
			{
				// This is a stream we handle, so enqueue the packet
				vIt->second->pPackets.push_back(packet);

				// Return if this stream is what we needed a packet for
				if (TypeT == stVideo && vIt->second->index() == stream->index())
					return packet;

				// Packet was stored, get another one
				packet = new AVPacket();
				continue;
			}
			else
			{
				// Search for the corresponding stream in the audio stream cache
				auto aIt = pAStreams.find((uint)packet->stream_index);
				if (pAStreams.end() != aIt)
				{
					// This is a stream we handle, so enqueue the packet
					aIt->second->pPackets.push_back(packet);

					// Return if this stream is what we needed a packet for
					if (TypeT == stAudio && aIt->second->index() == stream->index())
						return packet;

					// Packet was stored, get another one
					packet = new AVPacket();
					continue;
				}
			}

			// Unmanaged packet, free it and look for another one
			::av_free_packet(packet);
		}
		delete packet;
		return nullptr;
	}


	template<>
	inline bool File::isSameType<stVideo>(MediaType type) const
	{
		# if LIBAVFORMAT_VERSION_MAJOR < 53
		return CODEC_TYPE_VIDEO == type;
		# else
		return AVMEDIA_TYPE_VIDEO == type;
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
	}

	template<>
	inline bool File::isSameType<stAudio>(MediaType type) const
	{
		# if LIBAVFORMAT_VERSION_MAJOR < 53
		return CODEC_TYPE_AUDIO == type;
		# else
		return AVMEDIA_TYPE_AUDIO == type;
		# endif // LIBAVFORMAT_VERSION_MAJOR < 53
	}

	template<StreamType TypeT>
	inline bool File::isSameType(MediaType type) const
	{
		YUNI_STATIC_ASSERT(false, InvalidStreamType);
		return false;
	}


	template<>
	inline Stream<stVideo>::Map& File::getCache<stVideo>()
	{
		return pVStreams;
	}

	template<>
	inline Stream<stAudio>::Map& File::getCache<stAudio>()
	{
		return pAStreams;
	}

	template<StreamType TypeT>
	inline typename Stream<TypeT>::Map& File::getCache()
	{
		YUNI_STATIC_ASSERT(false, InvalidStreamType);
		return pVStreams;
	}




} // namespace Media
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_MEDIA_FILE_HXX__
