#ifndef __YUNI_AUDIO_SOURCE_HXX__
# define __YUNI_AUDIO_SOURCE_HXX__


namespace Yuni
{
namespace Audio
{

	inline Source::Source(bool loop)
		: pLoop(loop), pGain(DefaultGain), pBuffer(NULL)
		, pReady(false), pPlaying(false), pModified(false)
	{}


	inline Source::Source(const Gfx::Point3D<>& position, bool loop)
		: pPosition(position), pLoop(loop), pGain(1.0f), pBuffer(NULL)
		, pReady(false), pPlaying(false), pModified(false)
	{}


	inline Source::Source(const Gfx::Point3D<>& position, const Gfx::Vector3D<>& velocity,
		const Gfx::Vector3D<>& direction, bool loop = false)
		: pPosition(position), pVelocity(velocity), pDirection(direction), pLoop(loop)
		, pGain(1.0f), pBuffer(NULL), pReady(false), pPlaying(false), pModified(false)
	{}


	inline void Source::position(const Gfx::Point3D<>& position)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (pPosition != position)
		{
			pPosition = position;
			pModified = true;
		}
	}

	inline Gfx::Point3D<> Source::position() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pPosition;
	}


	inline void Source::gain(float newGain)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!Math::Equals(pGain, newGain))
		{
			pGain = newGain;
			pModified = true;
		}
	}

	inline float Source::gain() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pGain;
	}


	inline String Source::name() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pName;
	}

	template<class StringT>
	inline void Source::name(const StringT& name)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		pName = name;
	}


	inline unsigned int Source::id() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pID;
	}



} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_SOURCE_HXX__
