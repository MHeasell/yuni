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
		:pFile(NULL)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, IString_InvalidTypeForBuffer);

		loadFromFileWL(Traits::CString<UType>::Buffer(fileName));
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

	template<class AnyStringT>
	inline bool ISound::loadFromFile(const AnyStringT& fileName)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, IString_InvalidTypeForBuffer);

		ThreadingPolicy::MutexLocker locker(*this);
		return loadFromFileWL(Traits::CString<UType>::Buffer(fileName));
	}


} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_SOUND_HXX__
