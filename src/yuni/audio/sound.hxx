#ifndef __YUNI_AUDIO_SOUND_HXX__
# define __YUNI_AUDIO_SOUND_HXX__


namespace Yuni
{
namespace Audio
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



} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_SOUND_HXX__
