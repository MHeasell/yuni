#ifndef __YUNI_MEDIA_SOUND_HXX__
# define __YUNI_MEDIA_SOUND_HXX__


namespace Yuni
{
namespace Media
{


	inline Sound::Sound() :
		pStream(nullptr),
		pBufferCount(0)
	{
	}


	inline Sound::~Sound()
	{
	}


	inline uint Sound::duration() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		if (!pStream)
			return 0u;
		return pStream->duration();
	}



} // namespace Media
} // namespace Yuni

#endif // __YUNI_MEDIA_SOUND_HXX__
