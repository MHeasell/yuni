
# include "../private/audio/openal.h"
# include "sound.h"

namespace Yuni
{
namespace Audio
{


	bool Sound::prepareDispatched(uint source)
	{
		if (!pStream || !pStream->size)
			return false;

		pBufferCount = (pStream->size > (maxBufferCount - 1) * bufferSize)
			? static_cast<uint>(maxBufferCount)
			: (static_cast<uint>(pStream->size) / bufferSize + 1);

		if (!Private::Audio::OpenAL::CreateBuffers(pBufferCount, pIDs))
			return false;

		for (uint i = 0; i < pBufferCount; ++i)
		{
			// Make sure we get some data to give to the buffer
			const size_t count = Private::Audio::AV::GetAudioData(pStream, pData.data(), bufferSize);
			if (!count)
				return false;

			// Buffer the data with OpenAL
			if (!Private::Audio::OpenAL::SetBufferData(pIDs[i], pStream->format, pData.data(),
				count, pStream->codec->sample_rate))
				return false;
			// Queue the buffers onto the source
			if (!Private::Audio::OpenAL::QueueBufferToSource(pIDs[i], source))
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
		alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
		if (!processed)
			return true;

		// A buffer has finished playing, unqueue it
		ALuint buffer = Private::Audio::OpenAL::UnqueueBufferFromSource(source);
		// Get the next data to feed the buffer
		size_t count = Private::Audio::AV::GetAudioData(pStream, pData.data(), bufferSize);
		if (!count)
			return false;

		// Buffer the data with OpenAL and queue the buffer onto the source
		if (!Private::Audio::OpenAL::SetBufferData(buffer, pStream->format, pData.data(), count,
			pStream->codec->sample_rate))
			return false;

		return Private::Audio::OpenAL::QueueBufferToSource(buffer, source);
	}


	bool Sound::destroyDispatched(Thread::Signal* signal)
	{
		if (!pStream)
			return false;

		Private::Audio::AV::CloseFile(pStream->parent);
		pStream = nullptr;
		Private::Audio::OpenAL::DestroyBuffers(pBufferCount, pIDs);
		pBufferCount = 0;
		if (signal)
			signal->notify();
		return true;
	}




} // namespace Audio
} // namespace Yuni
