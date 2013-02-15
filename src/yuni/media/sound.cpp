
# include "../private/media/openal.h"
# include "sound.h"
# include "../private/media/frame.h"

namespace Yuni
{
namespace Media
{

	uint Sound::fillBuffer()
	{
		pData.clear();
		uint size = 0;
		while (size < minBufferSize)
		{
			// Make sure we get some data to give to the buffer
			Private::Media::Frame::Ptr frame = pStream->nextFrame();
			uint count = frame->audioSize();
			if (!count)
				return 0;
			count = Math::Min(count, (uint)maxBufferSize - size);
			pData.append((const char*)frame->audioData(), count);
			size += count;
		}
		return size;
	}


	bool Sound::prepareDispatched(uint source)
	{
		if (!pStream)
			return false;

		pBufferCount = maxBufferCount;

		if (!Private::Media::OpenAL::CreateBuffers(pBufferCount, pIDs))
			return false;

		for (uint i = 0; i < pBufferCount; ++i)
		{
			uint size = fillBuffer();
			if (!size)
				return false;

			// Buffer the data with OpenAL
			if (!Private::Media::OpenAL::SetBufferData(pIDs[i], pStream->alFormat(),
				pData.data(), size, pStream->rate()))
				return false;
			// Queue the buffers onto the source
			if (!Private::Media::OpenAL::QueueBufferToSource(pIDs[i], source))
				return false;
		}
		return true;
	}


	bool Sound::updateDispatched(uint source)
	{
		if (!pStream)
			return false;

		// Check if a buffer has finished playing
		ALint processed = 0;
		::alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
		if (!processed)
			return true;

		// A buffer has finished playing, unqueue it
		ALuint buffer = Private::Media::OpenAL::UnqueueBufferFromSource(source);
		// Get the next data to feed the buffer
		uint size = fillBuffer();
		if (!size)
			return false;

		// Buffer the data with OpenAL and queue the buffer onto the source
		if (!Private::Media::OpenAL::SetBufferData(buffer, pStream->alFormat(), pData.data(),
			size, pStream->rate()))
			return false;

		return Private::Media::OpenAL::QueueBufferToSource(buffer, source);
	}


	bool Sound::destroyDispatched(Thread::Signal* signal)
	{
		if (!pStream)
			return false;

		delete pStream->parent();
		pStream = nullptr;
		Private::Media::OpenAL::DestroyBuffers(pBufferCount, pIDs);
		pBufferCount = 0;
		if (signal)
			signal->notify();
		return true;
	}




} // namespace Media
} // namespace Yuni
