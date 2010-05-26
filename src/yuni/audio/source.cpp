
#include "../core/math.h"
#include "source.h"
#include "../private/audio/av.h"
#include "../private/audio/openal.h"



namespace Yuni
{
namespace Audio
{
	const float Source::DefaultPitch = 1.0f;
	const float Source::DefaultGain = 1.0f;
	const bool Source::DefaultAttenuation = true;
	const bool Source::DefaultLooping = false;


	bool Source::playSoundDispatched(Private::Audio::Buffer<>::Ptr buffer)
	{
		std::cout << "Beginning playback on source " << pID << "..." << std::endl;
		if (!pReady)
		{
			if (!prepareDispatched())
			{
				std::cerr << "Source preparation failed !" << std::endl;
				return false;
			}
		}

		if (!buffer || !buffer->valid())
		{
			std::cerr << "Invalid Buffer !" << std::endl;
			return false;
		}

		pBuffer = buffer;
		if (!pBuffer->prepareDispatched(pID))
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


	bool Source::updateDispatched()
	{
		if (!pReady)
			return false;
		pPlaying = Private::Audio::OpenAL::IsSourcePlaying(pID);
		if (!pPlaying)
			return false;
		if (pModified)
		{
			if (!Private::Audio::OpenAL::MoveSource(pID, pPosition, pVelocity, pDirection))
			{
				std::cerr << "Source position update failed !" << std::endl;
				return false;
			}
			if (!Private::Audio::OpenAL::ModifySource(pID, DefaultPitch, pGain, DefaultAttenuation, pLoop))
			{
				std::cerr << "Source characteristics update failed !" << std::endl;
				return false;
			}
		}
		if (NULL != pBuffer)
			pBuffer->updateDispatched(pID);
		return true;
	}


	bool Source::prepareDispatched()
	{
		if (pReady)
			return true;

		unsigned int source = Private::Audio::OpenAL::CreateSource(pPosition, pVelocity,
			pDirection, DefaultPitch, pGain, DefaultAttenuation, pLoop);

		pID = source;
		pReady = (source > 0);
		return pReady;
	}




} // namespace Audio
} // namespace Yuni
