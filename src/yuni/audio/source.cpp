
#include "source.h"


namespace Yuni
{
namespace Audio
{

	bool Source::play(Sound3D::Ptr sound)
	{
		if (!pReady)
		{
			if (!prepare())
				return false;
		}
		if (!sound->valid())
			return false;
		OpenAL::bindBufferToSource(sound->buffer(), pID);
		bool started = OpenAL::playSource(pID);
		if (!started)
			OpenAL::unbindBufferFromSource(pID);
		return false;
	}


	bool Source::play(Music::Ptr music)
	{
		if (!pReady)
			if (!prepare())
				return false;
		if (!music->valid())
			return false;
		OpenAL::queueBufferToSource(music->buffer(), pID);
		bool started = OpenAL::playSource(pID);
		if (!started)
			OpenAL::unqueueBufferFromSource(pID); // IgnAore return value
		return false;
	}


	bool Source::prepare()
	{
		if (pReady)
			return true;

		unsigned int source = OpenAL::createSource(pPosition, pVelocity, pDirection,
			1.0f, pGain, true, pLoop);

		pReady = true;
		return (pReady);
	}




} // namespace Audio
} // namespace Yuni
