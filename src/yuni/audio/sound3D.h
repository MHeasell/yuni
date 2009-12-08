#ifndef __YUNI_AUDIO_SOUND3D_H__
# define __YUNI_AUDIO_SOUND3D_H__

# include "sound.h"

namespace Yuni
{
namespace Audio
{
	/*!
	** \brief A 3D sound is a sound that has a position in space.
	**
	** Implicitly, it means the sound will be affected by attenuation
	** relative to distance.
	*/
	class Sound3D
	{
	public:
		//! \name Typedefs
		//@{
		typedef SmartPtr<Sound> Ptr;
		//@}

	public:
		/*!
		** \brief Empty constructor, use default values.
		*/
		Sound() {}

	private:
		//! Forbid default copy constructor
		Sound(const Music&) {}
		//! Forbid default operator=
		Sound& operator= (Music&) {}

	public:
		//! \name Accessors
		//@{
		const String& name() { return pName; }
		void name(const String& name) { pName = name; }
		//@}

	protected:
		//! String identifier for the sound
		String pName;

	};

} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_SOUND_H__
