#ifndef __YUNI_AUDIO_EMITTER_H__
# define __YUNI_AUDIO_EMITTER_H__

# include <map>
# include "../yuni.h"
# include "../core/string.h"
# include "../core/point3D.h"
# include "../core/vector3D.h"
# include "../core/system/windows/gettimeofday.h"
# include "../private/audio/buffer.h"


namespace Yuni
{
namespace Audio
{

	/*!
	** \brief An audio emitter is an object from which the sound is played
	**
	** Audio emitters can be placed in space, and be moved around.
	*/
	class Emitter: public Policy::ObjectLevelLockable<Emitter>
	{
	public:
		//! The most suitable smart pointer for the class
		typedef SmartPtr<Emitter> Ptr;
		//! Threading Policy
		typedef Policy::ObjectLevelLockable<Emitter> ThreadingPolicy;
		//! Map
		typedef std::map<String, Ptr> Map;

	public:
		//! Default values
		static const float DefaultPitch;
		static const float DefaultGain;
		static const bool DefaultAttenuation;
		static const bool DefaultLooping;

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Shortest constructor
		**
		** Position, speed and direction default to (0,0,0)
		*/
		Emitter(bool loop = DefaultLooping);

		/*!
		** \brief Constructor with 3D position
		**
		** Speed and velocity default to (0,0,0)
		*/
		Emitter(const Gfx::Point3D<>& position, bool loop);

		/*!
		** \brief Constructor with position, velocity and direction
		*/
		Emitter(const Gfx::Point3D<>& position, const Gfx::Vector3D<>& velocity,
			const Gfx::Vector3D<>& direction, bool loop);

		/*!
		** \brief Destructor
		*/
		~Emitter() {}
		//@}


		//! \name Methods
		//@{
		//! Attach a buffer to the emitter
		bool attachBufferDispatched(Private::Audio::Buffer<>::Ptr buffer);

		//! Prepare the emitter for playing
		bool prepareDispatched();

		//! Play the sound
		bool playSoundDispatched();
		//! Play the sound
		bool playSoundDispatched(Private::Audio::Buffer<>::Ptr buffer);

		//! Update buffers if necessary
		bool updateDispatched();
		//@}


		//! \name Accessors
		//@{
		void position(const Gfx::Point3D<>& position);
		Gfx::Point3D<> position() const;

		void velocity(const Gfx::Vector3D<>& position);
		Gfx::Vector3D<> velocity() const;

		void direction(const Gfx::Vector3D<>& position);
		Gfx::Vector3D<> direction() const;

		/*!
		** \brief Set the volume modifier on the emitter
		** \param newGain 0.0f for no sound, 1.0f to keep sound as is, > 1.0f to amplify sound
		*/
		void gain(float newGain);
		//! Get the current volume modifier
		float gain() const;

		/*!
		** \brief Get the elapsed playback time (in seconds)
		** \returns Time elapsed since the emitter started playback. 0 if not playing.
		*/
		float elapsedTime() const;

		String name() const;
		template<class StringT> void name(const StringT& name);

		unsigned int id() const;
		//@}


	private:
		Emitter(const Emitter&);
		Emitter& operator= (const Emitter&);

	private:
		//! String identifier for the emitter
		String pName;
		//! OpenAL identifier for the emitter
		unsigned int pID;
		//! Position of the emitter in space
		Gfx::Point3D<> pPosition;
		//! Speed of the emitter
		Gfx::Vector3D<> pVelocity;
		//! Direction of the movement of the emitter
		Gfx::Vector3D<> pDirection;
		//! Should the emitter loop on itself when finished playing?
		bool pLoop;
		//! Volume modifier, 1.0 means no modification
		float pGain;
		//! Current playback position
		Yuni::timeval pStartTime;
		//! Buffer used for playing. NULL if none
		Private::Audio::Buffer<>::Ptr  pBuffer;

		//! Is the emitter ready for use?
		bool pReady;
		//! Is the emitter currently playing?
		bool pPlaying;
		//! Has the emitter's values been modified ?
		bool pModified;

	}; // class Emitter




} // namespace Audio
} // namespace Yuni

# include "emitter.hxx"

#endif // __YUNI_AUDIO_EMITTER_H__
