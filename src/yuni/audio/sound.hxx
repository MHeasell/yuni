#ifndef __YUNI_AUDIO_SOUND_HXX__
# define __YUNI_AUDIO_SOUND_HXX__


namespace Yuni
{
namespace Audio
{


	inline Sound::Sound(StreamPtr stream) :
		pStream(stream), pBufferCount(0)
	{
	}


	inline Sound::~Sound()
	{
	}


	inline uint Sound::duration() const
	{
		ThreadingPolicy::MutexLocker lock(*this);
		return Private::Audio::AV::GetDuration(pStream);
	}



} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_SOUND_HXX__
