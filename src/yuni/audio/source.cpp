#include "source.h"

namespace Yuni
{
namespace Audio
{

	bool Source::play(Sound3D& sound)
	{
		if (!pReady)
			if (!prepare())
				return false;
		if (!sound.ready())
			return false;
		OpenAL::bindBufferToSource(sound.buffer(), pID);
		bool started = OpenAL::playSource(pID);
		if (!started)
			OpenAL::unbindBufferFromSource(pID);
	}

	bool Source::play(Music& music)
	{
		if (!pReady)
			if (!prepare())
				return false;
		if (!music.ready())
			return false;
		OpenAL::queueBufferToSource(music.buffer(), pID);
		bool started = OpenAL::playSource(pID);
		if (!started)
			OpenAL::unqueueBufferFromSource(pID); // Ignore return value
	}

	bool Source::prepare()
	{
		if (pReady)
			return true;
		unsigned int source = OpenAL::createSource(pPosition, pVelocity, pDirection,
			1.0f, pGain, true, pLoop);

		pReady = true;
		return true;
	}

} // namespace Audio
} // namespace Yuni
