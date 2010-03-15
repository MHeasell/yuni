#ifndef __YUNI_AUDIO_SOUND_HXX__
# define __YUNI_AUDIO_SOUND_HXX__

# include "../core/traits/cstring.h"

namespace Yuni
{
namespace Audio
{

	inline ISound::ISound()
		:pFile(NULL)
	{
	}

	template<class AnyStringT>
	inline ISound::ISound(const AnyStringT& fileName)
		:pName(filename), pFile(NULL)
	{
	}


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
