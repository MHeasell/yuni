#ifndef __YUNI_PRIVATE_AUDIO_BUFFER_HXX__
# define __YUNI_PRIVATE_AUDIO_BUFFER_HXX__

# include "openal.h"
# include "buffer.h"

namespace Yuni
{
namespace Private
{
namespace Audio
{

	template<unsigned int BufferSizeT>
	inline Buffer<BufferSizeT>::Buffer(AudioStream* stream)
		:pStream(stream)
	{
		OpenAL::CreateBuffers(BufferCount, pIDs);
	}

	template<unsigned int BufferSizeT>
	inline Buffer<BufferSizeT>::~Buffer()
	{
		OpenAL::DestroyBuffers(BufferCount, pIDs);
	}

	template<unsigned int BufferSizeT>
	bool Buffer<BufferSizeT>::prepare(unsigned int source)
	{
		for (unsigned int i = 0; i < BufferCount; ++i)
		{
			// Make sure we get some data to give to the buffer
			size_t count = AV::GetAudioData(pStream, pData.data(), BufferSize);
			if (!count)
				return false;

			// Buffer the data with OpenAL
			OpenAL::SetBufferData(pIDs[i], pStream->Format, pData.data(), count,
				pStream->CodecContext->sample_rate);
			// Queue the buffers onto the source
			OpenAL::QueueBufferToSource(pIDs[i], source);
		}
		return true;
	}

	template<unsigned int BufferSizeT>
	bool Buffer<BufferSizeT>::update(unsigned int source)
	{
		// Check if a buffer has finished playing
		ALint processed = 0;
		alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
		if (!processed)
			return true;

		// A buffer has finished playing, unqueue it
		ALuint buffer = OpenAL::UnqueueBufferFromSource(source);
		// Get the next data to feed the buffer
		size_t count = AV::GetAudioData(pStream, pData.data(), BufferSize);
		if (!count)
			return false;

		// Buffer the data with OpenAL and queue the buffer onto the source
		OpenAL::SetBufferData(buffer, pStream->Format, pData.data(), count,
			pStream->CodecContext->sample_rate);
		OpenAL::QueueBufferToSource(buffer, source);
		return true;
	}


} // namespace Audio
} // namespace Private
} // namespace Yuni

#endif // __YUNI_PRIVATE_AUDIO_BUFFER_HXX__
