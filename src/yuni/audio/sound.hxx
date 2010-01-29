#ifndef __YUNI_AUDIO_SOUND_HXX__
# define __YUNI_AUDIO_SOUND_HXX__


namespace Yuni
{
namespace Audio
{


	inline String ISound::name() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pName;
	}


	template<class AnyStringT>
	inline void ISound::name(const AnyStringT& name)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		pName = name;
	}


	inline bool ISound::valid() const
	{
		return (NULL != pFile);
	}


	inline bool ISound::operator ! () const
	{
		return (NULL == pFile);
	}



} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_SOUND_HXX__
