#ifndef __YUNI_AUDIO_SOUND_HXX__
# define __YUNI_AUDIO_SOUND_HXX__


namespace Yuni
{
namespace Audio
{


	inline String ASound::name() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pName;
	}


	template<class AnyStringT>
	inline void ASound::name(const AnyStringT& name)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		pName = name;
	}


	inline bool ASound::valid() const
	{
		return (NULL != pFile);
	}


	inline bool ASound::operator ! () const
	{
		return (NULL == pFile);
	}



} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_SOUND_HXX__
