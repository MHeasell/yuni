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
		typedef SmartPtr<Sound3D> Ptr;
		//@}

	public:
		/*!
		** \brief Empty constructor, use default values.
		*/
		Sound3D() {}

	private:
		//! Forbid default copy constructor
		Sound3D(const Sound3D&) {}
		//! Forbid default operator=
		Sound3D& operator= (const Sound3D&) {}

	};

} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_SOUND3D_H__
