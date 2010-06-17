#ifndef __YUNI_AUDIO_EMITTER_HXX__
# define __YUNI_AUDIO_EMITTER_HXX__


namespace Yuni
{
namespace Audio
{

	inline Emitter::Emitter(bool loop)
		: pLoop(loop), pGain(DefaultGain), pBuffer(NULL)
		, pReady(false), pPlaying(false), pModified(false)
	{}


	inline Emitter::Emitter(const Gfx::Point3D<>& position, bool loop)
		: pPosition(position), pLoop(loop), pGain(1.0f), pBuffer(NULL)
		, pReady(false), pPlaying(false), pModified(false)
	{}


	inline Emitter::Emitter(const Gfx::Point3D<>& position, const Gfx::Vector3D<>& velocity,
		const Gfx::Vector3D<>& direction, bool loop = false)
		: pPosition(position), pVelocity(velocity), pDirection(direction), pLoop(loop)
		, pGain(1.0f), pBuffer(NULL), pReady(false), pPlaying(false), pModified(false)
	{}


	inline void Emitter::position(const Gfx::Point3D<>& position)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (pPosition != position)
		{
			pPosition = position;
			pModified = true;
		}
	}

	inline Gfx::Point3D<> Emitter::position() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pPosition;
	}

	inline void Emitter::velocity(const Gfx::Vector3D<>& velocity)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (pVelocity != velocity)
		{
			pVelocity = velocity;
			pModified = true;
		}
	}

	inline Gfx::Vector3D<> Emitter::velocity() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pVelocity;
	}

	inline void Emitter::direction(const Gfx::Vector3D<>& direction)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (pDirection != direction)
		{
			pDirection = direction;
			pModified = true;
		}
	}

	inline Gfx::Vector3D<> Emitter::direction() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pDirection;
	}


	inline void Emitter::gain(float newGain)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!Math::Equals(pGain, newGain))
		{
			pGain = newGain;
			pModified = true;
		}
	}

	inline float Emitter::gain() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pGain;
	}


	inline String Emitter::name() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pName;
	}

	template<class StringT>
	inline void Emitter::name(const StringT& name)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		pName = name;
	}


	inline unsigned int Emitter::id() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pID;
	}



} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_EMITTER_HXX__
