
# include "../private/media/openal.h"
# include "source.h"
# include "../private/media/frame.h"

namespace Yuni
{
namespace Media
{

	uint Source::fillBuffer()
	{
		pData.clear();
		uint size = 0;
		while (size < minBufferSize)
		{
			// Make sure we get some data to give to the buffer
			Private::Media::Frame::Ptr frame = pAStream->nextFrame();
			if (!frame)
				return 0;
			uint count = frame->audioSize();
			if (!count)
				return 0;
			count = Math::Min(count, (uint)maxBufferSize - size);
			pData.append((const char*)frame->audioData(), count);
			size += count;
		}
		return size;
	}


	void Source::fillQueue()
	{
		for (uint i = pFrames.size(); i < bestQueueSize; )
		{
			Private::Media::Frame::Ptr frame = pVStream->nextFrame();
			if (!frame)
				return;

			if (frame->valid())
			{
				pFrames.push_back(frame);
				++i;
			}
		}
	}


	bool Source::prepareDispatched(uint source)
	{
		if (!pAStream && !pVStream)
			return false;

		// Audio
		if (nullptr != pAStream)
		{
			pBufferCount = maxBufferCount;

			if (!Private::Media::OpenAL::CreateBuffers(pBufferCount, pIDs))
				return false;

			for (uint i = 0; i < pBufferCount; ++i)
			{
				uint size = fillBuffer();
				if (!size)
					return false;

				// Buffer the data with OpenAL
				if (!Private::Media::OpenAL::SetBufferData(pIDs[i], pAStream->alFormat(),
					pData.data(), size, pAStream->rate()))
					return false;
				// Queue the buffers onto the source
				if (!Private::Media::OpenAL::QueueBufferToSource(pIDs[i], source))
					return false;
			}
		}

		// Video
		if (nullptr != pVStream)
		{
			fillQueue();
		}

		return true;
	}


	bool Source::updateDispatched(uint source)
	{
		if (!pAStream && !pVStream)
			return false;

		// Audio
		if (nullptr != pAStream)
		{
			// Check if a buffer has finished playing
			ALint processed = 0;
			::alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
			::alGetSourcei(source, AL_SAMPLE_OFFSET, (int*)&pSamplesCurrent);
			if (!processed)
				return true;

			// A buffer has finished playing, unqueue it
			ALuint buffer = Private::Media::OpenAL::UnqueueBufferFromSource(source);
			pSamplesCurrent = 0;
			int bufferSize;
			::alGetBufferi(buffer, AL_SIZE, &bufferSize);
			pSamplesRead += bufferSize * pAStream->channels() * pAStream->bits();
			// Get the next data to feed the buffer
			uint size = fillBuffer();
			if (!size)
				return false;

			// Buffer the data with OpenAL and queue the buffer onto the source
			if (!Private::Media::OpenAL::SetBufferData(buffer, pAStream->alFormat(), pData.data(),
				size, pAStream->rate()))
				return false;
			if (!Private::Media::OpenAL::QueueBufferToSource(buffer, source))
				return false;
		}

		// Video
		if (nullptr != pVStream)
		{
			if (nullptr != pAStream && Private::Media::OpenAL::IsSourcePlaying(source))
			{
				// Try to sync with audio
				ALfloat elapsed;
				::alGetSourcef(source, AL_SEC_OFFSET, &elapsed);
				while (!pFrames.empty() && elapsed > pFrames.front()->timestamp())
				{
					pFrames.pop_front();
					if (pFrames.empty())
						fillQueue();
				}
			}

			if (pFrames.empty())
				// Failed to load anymore
				return false;
		}

		return true;
	}


	bool Source::destroyDispatched(Thread::Signal* signal)
	{
		if (!pAStream && !pVStream)
			return false;

		pFrames.clear();
		if (pAStream)
		{
			delete pAStream->parent();
			Private::Media::OpenAL::DestroyBuffers(pBufferCount, pIDs);
			pBufferCount = 0;
		}
		else
			delete pVStream->parent();
		pAStream = nullptr;
		pVStream = nullptr;
		if (signal)
			signal->notify();
		return true;
	}




} // namespace Media
} // namespace Yuni
