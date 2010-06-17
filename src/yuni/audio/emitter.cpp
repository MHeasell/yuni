
#include "../core/math.h"
#include "emitter.h"
#include "../private/audio/av.h"
#include "../private/audio/openal.h"



namespace Yuni
{
namespace Audio
{
	const float Emitter::DefaultPitch = 1.0f;
	const float Emitter::DefaultGain = 1.0f;
	const bool Emitter::DefaultAttenuation = true;
	const bool Emitter::DefaultLooping = false;

	bool Emitter::playSoundDispatched()
	{
		if (NULL == pBuffer)
			return false;
		return playSoundDispatched(pBuffer);
	}


	bool Emitter::playSoundDispatched(Private::Audio::Buffer<>::Ptr buffer)
	{
		std::cout << "Beginning playback on emitter " << pID << "..." << std::endl;
		if (!pReady)
		{
			if (!prepareDispatched())
				return false;
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
			std::cerr << "Emitter " << pID << " failed playing !" << std::endl;
			Private::Audio::OpenAL::UnqueueBufferFromSource(pID);
			return false;
		}
		std::cout << "Playback started successfully !" << std::endl;
		return true;
	}


	bool Emitter::updateDispatched()
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


	bool Emitter::prepareDispatched()
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
