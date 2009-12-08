#ifndef __YUNI_AUDIO_MUSIC_H__
# define __YUNI_AUDIO_MUSIC_H__

# include "../core/string.h"

namespace Yuni
{
namespace Audio
{
	/*!
	** \brief A music is a sound meant to be played as ambience
	*/
	class Music: public Sound
	{
	public:
		typedef SmartPtr<Music> Ptr;

	public:
		Music() {}

	private:
		Music(const Music&) {}
		Music& operator= (Music&) {}

	}; // Music

} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_MUSIC_H__
