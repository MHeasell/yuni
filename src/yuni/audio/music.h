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
		Music() {}

	private:
		Music(const Music&) {}
		Music& operator= (Music&) {}

	public:
		const String& name() { return pName; }
		void name(const String& name) { pName = name; }

	private:
		//! String identifier for the sound
		String pName;

	}; // Music

} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_MUSIC_H__
