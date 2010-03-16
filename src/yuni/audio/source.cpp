
#include "source.h"
#include "../private/audio/openal.h"



namespace Yuni
{
namespace Audio
{


	bool Source::playSound(unsigned int buffer)
	{
		std::cout << "YESSSSSS ! " << buffer << std::endl;
		if (!pReady)
		{
			if (!prepare())
				return false;
		}
		Private::Audio::OpenAL::bindBufferToSource(buffer, pID);
		bool started = Private::Audio::OpenAL::playSource(pID);
		if (!started)
			Private::Audio::OpenAL::unbindBufferFromSource(pID);
		return false;
	}

// 	bool Source::play(Sound3D::Ptr sound)
// 	{
// 		if (!pReady)
// 		{
// 			if (!prepare())
// 				return false;
// 		}
// 		if (!sound->valid())
// 			return false;
// 		Private::Audio::OpenAL::bindBufferToSource(sound->buffer(), pID);
// 		bool started = Private::Audio::OpenAL::playSource(pID);
// 		if (!started)
// 			Private::Audio::OpenAL::unbindBufferFromSource(pID);
// 		return false;
// 	}


// 	bool Source::play(Music::Ptr music)
// 	{
// 		if (!pReady)
// 			if (!prepare())
// 				return false;
// 		if (!music->valid())
// 			return false;
// 		Private::Audio::OpenAL::queueBufferToSource(music->buffer(), pID);
// 		bool started = Private::Audio::OpenAL::playSource(pID);
// 		if (!started)
// 			// Ignore return value
// 			Private::Audio::OpenAL::unqueueBufferFromSource(pID);
// 		return false;
// 	}


	bool Source::prepare()
	{
		if (pReady)
			return true;

		unsigned int source = Private::Audio::OpenAL::createSource(pPosition, pVelocity,
			pDirection, 1.0f, pGain, true, pLoop);

		pID = source;
		pReady = (source > 0);
		return pReady;
	}




} // namespace Audio
} // namespace Yuni
