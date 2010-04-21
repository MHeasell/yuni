#ifndef __YUNI_AUDIO_SOURCE_HXX__
# define __YUNI_AUDIO_SOURCE_HXX__


namespace Yuni
{
namespace Audio
{

	inline Source::Source(bool loop)
		: pLoop(loop), pReady(false), pPlaying(false)
	{}


	inline Source::Source(const Gfx::Point3D<>& position, bool loop)
		: pPosition(position), pLoop(loop), pReady(false), pPlaying(false)
	{}


	inline Source::Source(const Gfx::Point3D<>& position, const Gfx::Vector3D<>& velocity,
		const Gfx::Vector3D<>& direction, bool loop = false)
		:pPosition(position), pVelocity(velocity), pDirection(direction),
		 pLoop(loop), pReady(false), pPlaying(false)
	{}


	inline void Source::position(const Gfx::Point3D<>& position)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		pPosition = position;
	}

	inline Gfx::Point3D<> Source::position() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pPosition;
	}


	inline void Source::gain(float newGain)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		pGain = newGain;
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

	template<class AnyStringT>
	inline void Source::name(const AnyStringT& name)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		pName = name;
	}


	inline unsigned int Source::id() const
	{
		return pID;
	}



} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_SOURCE_HXX__
