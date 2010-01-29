#ifndef __YUNI_AUDIO_SOUND3D_H__
# define __YUNI_AUDIO_SOUND3D_H__

# include "../yuni.h"
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
	class Sound3D : public ISound
	{
	public:
		//! The most suitable smart pointer for the class
		typedef SmartPtr<Sound3D> Ptr;
		//! The Threading Policy
		typedef ISound::ThreadingPolicy ThreadingPolicy;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Empty constructor, use default values.
		*/
		Sound3D() {}
		//! Destructor
		virtual ~Sound3D() {}
		//@}

		virtual bool prepare();
		virtual unsigned int buffer() const;

	private:
		//! Forbid default copy constructor
		Sound3D(const Sound3D&);
		//! Forbid default operator=
		Sound3D& operator = (const Sound3D&);

	private:
		//! OpenAL identifier for the buffer
		unsigned int pBufferID;

	}; // class Sound3D





} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_SOUND3D_H__
