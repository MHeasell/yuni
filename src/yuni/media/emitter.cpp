
#include "../core/math.h"
#include "../core/system/gettimeofday.h"
#include "emitter.h"
#include "../private/media/av.h"
#include "../private/media/openal.h"
#include <iostream>


namespace Yuni
{
namespace Media
{

	const float Emitter::DefaultPitch = 1.0f;
	const float Emitter::DefaultGain  = 1.0f;




	bool Emitter::attachBufferDispatched(Source::Ptr& buffer)
	{
		// Check buffer validity
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
		return true;
	}


	bool Emitter::detachBufferDispatched()
	{
		if (!pReady || !pBuffer)
			return false;

		stopSourceDispatched();

		Private::Media::OpenAL::UnbindBufferFromSource(pID);
		pBuffer = nullptr;
		return true;
	}


	bool Emitter::playSourceDispatched()
	{
		if (!pBuffer)
			return false;

		pPlaying = Private::Media::OpenAL::PlaySource(pID);
		if (!pPlaying)
		{
			std::cerr << "Emitter " << pID << " failed playing !" << std::endl;
			Private::Media::OpenAL::UnqueueBufferFromSource(pID);
			return false;
		}
		// Store start time
		Yuni::timeval now;
		YUNI_SYSTEM_GETTIMEOFDAY(&now, NULL);
		pStartTime = now.tv_sec;
		return true;
	}


	bool Emitter::playSourceDispatched(Source::Ptr& buffer)
	{
		if (!pReady && !prepareDispatched())
			return false;

		if (!attachBufferDispatched(buffer))
			return false;

		return playSourceDispatched();
	}


	bool Emitter::pauseSourceDispatched()
	{
		if (!pPlaying)
			return false;

		Private::Media::OpenAL::PauseSource(pID);
		return true;
	}


	bool Emitter::stopSourceDispatched()
	{
		if (!pPlaying && !pPaused)
			return false;

		Private::Media::OpenAL::StopSource(pID);
		return true;
	}


	bool Emitter::updateDispatched()
	{
		if (!pReady)
			return false;
		pPlaying = Private::Media::OpenAL::IsSourcePlaying(pID);
		pPaused = Private::Media::OpenAL::IsSourcePaused(pID);
		// If not playing, nothing else to do
		if (!pPlaying)
			return false;
		if (pModified)
		{
			if (!Private::Media::OpenAL::MoveSource(pID, pPosition, pVelocity, pDirection))
			{
				std::cerr << "Source position update failed !" << std::endl;
				return false;
			}
			if (!Private::Media::OpenAL::ModifySource(pID, DefaultPitch, pGain, DefaultAttenuation, pLoop))
			{
				std::cerr << "Source characteristics update failed !" << std::endl;
				return false;
			}
		}
		if (pBuffer)
			pBuffer->updateDispatched(pID);
		return true;
	}


	bool Emitter::prepareDispatched()
	{
		if (pReady)
			return true;

		unsigned int source = Private::Media::OpenAL::CreateSource(pPosition, pVelocity,
			pDirection, DefaultPitch, pGain, DefaultAttenuation, pLoop);

		pID = source;
		pReady = (source > 0);
		return pReady;
	}


	sint64 Emitter::elapsedTime() const
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (!pPlaying)
			return 0;
		ALfloat elapsed;
		::alGetSourcef(pID, AL_SEC_OFFSET, &elapsed);
		return elapsed;
		// Yuni::timeval now;
		// YUNI_SYSTEM_GETTIMEOFDAY(&now, NULL);
		// return now.tv_sec - pStartTime;
	}


} // namespace Media
} // namespace Yuni
