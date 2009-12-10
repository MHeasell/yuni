#ifndef __YUNI_AUDIO_SOURCE_H__
# define __YUNI_AUDIO_SOURCE_H__

# include "../yuni.h"
# include "../core/string.h"
# include "../core/smartptr.h"
# include "../gfx/point3D.h"
# include "../gfx/vector3D.h"

# include "openal.h"
# include "sound3D.h"
# include "music.h"



namespace Yuni
{
namespace Audio
{

	/*!
	** \brief An audio source is an object from which the sound is played
	**
	** Audio sources can be placed in space, and be moved around.
	*/
	class Source: public Policy::ObjectLevelLockable<Source>
	{
	public:
		//! The most suitable smart pointer for the class
		typedef SmartPtr<Source> Ptr;
		//! Threading Policy
		typedef Policy::ObjectLevelLockable<Source> ThreadingPolicy;

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Shortest constructor
		**
		** Position, speed and direction default to (0,0,0)
		*/
		Source(bool loop = false): pLoop(loop), pReady(false)
		{}

		/*!
		** \brief Constructor with 3D position
		**
		** Speed and velocity default to (0,0,0)
		*/
		Source(const Gfx::Point3D<>& position, bool loop = false)
			: pPosition(position), pLoop(loop), pReady(false)
		{}

		/*!
		** \brief Constructor with position, velocity and direction
		*/
		Source(const Gfx::Point3D<>& position, const Gfx::Vector3D<>& velocity,
			const Gfx::Vector3D<>& direction, bool loop = false)
			: pPosition(position), pVelocity(velocity), pDirection(direction),
			  pLoop(loop), pReady(false)
		{}

		//! Destructor
		~Source() {}
		//@}

		//! Start a 3D sound playback on this source
		bool play(Sound3D::Ptr sound);
		//! Start a music playback on this source
		bool play(Music::Ptr music);

		//! \name Methods
		//@{
		//! Prepare the source for playing
		bool prepare();
		//@}

		//! \name Accessors
		//@{

		void position(const Gfx::Point3D<>& position)
		{
			ThreadingPolicy::MutexLocker locker(*this);
			pPosition = position;
		}
		Gfx::Point3D<> position() const
		{
			ThreadingPolicy::MutexLocker locker(*this);
			return pPosition;
		}

		/*!
		** \brief Set the volume modifier on the source
		**
		** 0.0f for no sound, 1.0f to keep sound as is, > 1.0f to amplify sound
		*/
		void gain(float newGain)
		{
			ThreadingPolicy::MutexLocker locker(*this);
			pGain = newGain;
		}
		//! Get the current volume modifier
		float gain() const
		{
			ThreadingPolicy::MutexLocker locker(*this);
			return pGain;
		}

		String name() const
		{
			ThreadingPolicy::MutexLocker locker(*this);
			return pName;
		}
		void name(const String& name)
		{
			ThreadingPolicy::MutexLocker locker(*this);
			pName = name;
		}

		//@}


	private:
		Source(const Source&);
		Source& operator= (const Source&);

	private:
		//! String identifier for the source
		String pName;
		//! OpenAL identifier for the source
		unsigned int pID;
		//! Position of the source in space
		Gfx::Point3D<> pPosition;
		//! Speed of the source
		Gfx::Vector3D<> pVelocity;
		//! Direction of the movement of the source
		Gfx::Vector3D<> pDirection;
		//! Should the source loop on itself when finished playing?
		bool pLoop;
		//! Volume modifier, 1.0 means no modification
		float pGain;
		//! Is the source ready for use?
		bool pReady;

	}; // class Source




} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_SOURCE_H__
