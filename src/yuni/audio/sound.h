#ifndef __YUNI_AUDIO_SOUND_H__
# define __YUNI_AUDIO_SOUND_H__

# include "openal.h"
# include "av.h"
# include "../core/smartptr.h"

namespace Yuni
{
namespace Audio
{
	/*!
	** \brief A sound is any kind of audio content that can be played by Yuni.
	*/
	class Sound: ThreadingPolicy<Sound>
	{
	public:
		//! \name Typedefs
		//@{
		typedef SmartPtr<Sound> Ptr;

		typedef Policy::ObjectLevelLockable<Sound> ThreadingPolicy;
		//@}

	public:
		/*!
		** \brief Empty constructor, use default values.
		*/
		Sound() {}

	private:
		//! Forbid default copy constructor
		Sound(const Sound&) {}
		//! Forbid default operator=
		Sound& operator= (const Sound&) {}

	public:
		//! \name Accessors
		//@{
		const String& name() { return pName; }
		void name(const String& name) { pName = name; }
		//@}

	protected:
		//! String identifier for the sound
		String pName;

	}; // Sound

} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_SOUND_H__
