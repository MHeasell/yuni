
#include "source.h"
#include "../private/audio/av.h"
#include "../private/audio/openal.h"



namespace Yuni
{
namespace Audio
{


	bool Source::playSound(Private::Audio::Buffer<>::Ptr buffer)
	{
		std::cout << "Beginning playback on source " << pID << "..." << std::endl;
		if (!pReady)
		{
			if (!prepare())
				return false;
		}

		if (!buffer || !buffer->valid())
		{
			std::cout << "Invalid Buffer !" << std::endl;
			return false;
		}

		pBuffer = buffer;
		if (!pBuffer->prepare(pID))
		{
			std::cerr << "Failed loading buffers !" << std::endl;
			return false;
		}

		pPlaying = Private::Audio::OpenAL::PlaySource(pID);
		if (!pPlaying)
		{
			std::cerr << "Source " << pID << " failed playing !" << std::endl;
			Private::Audio::OpenAL::UnqueueBufferFromSource(pID);
			return false;
		}
		std::cout << "Playback started successfully !" << std::endl;
		return true;
	}

	bool Source::update()
	{
		if (!pReady)
			return false;
		pPlaying = Private::Audio::OpenAL::IsSourcePlaying(pID);
		if (!pPlaying)
			return false;
		if (NULL != pBuffer)
			pBuffer->update(pID);
		return true;
	}

	bool Source::prepare()
	{
		if (pReady)
			return true;

		unsigned int source = Private::Audio::OpenAL::CreateSource(pPosition, pVelocity,
			pDirection, 1.0f, pGain, true, pLoop);

		pID = source;
		pReady = (source > 0);
		return pReady;
	}




} // namespace Audio
} // namespace Yuni
