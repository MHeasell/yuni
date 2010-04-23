#ifndef __YUNI_AUDIO_SOURCE_H__
# define __YUNI_AUDIO_SOURCE_H__

# include <map>
# include "../yuni.h"
# include "../core/string.h"
# include "../core/point3D.h"
# include "../core/vector3D.h"
# include "../private/audio/buffer.h"


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
		//! Map
		typedef std::map<String, Ptr> Map;

	public:
		//! \name Constructors & Destructor
		//@{

		/*!
		** \brief Shortest constructor
		**
		** Position, speed and direction default to (0,0,0)
		*/
		Source(bool loop = false);

		/*!
		** \brief Constructor with 3D position
		**
		** Speed and velocity default to (0,0,0)
		*/
		Source(const Gfx::Point3D<>& position, bool loop);

		/*!
		** \brief Constructor with position, velocity and direction
		*/
		Source(const Gfx::Point3D<>& position, const Gfx::Vector3D<>& velocity,
			const Gfx::Vector3D<>& direction, bool loop);

		/*!
		** \brief Destructor
		*/
		~Source() {}
		//@}


		//! \name Methods
		//@{
		//! Prepare the source for playing
		bool prepare();

		//! Play the sound
		bool playSound(Private::Audio::Buffer<>::Ptr buffer);

		//! Update buffers if necessary
		bool update();
		//@}


		//! \name Accessors
		//@{

		void position(const Gfx::Point3D<>& position);
		Gfx::Point3D<> position() const;

		/*!
		** \brief Set the volume modifier on the source
		** \param newGain 0.0f for no sound, 1.0f to keep sound as is, > 1.0f to amplify sound
		*/
		void gain(float newGain);
		//! Get the current volume modifier
		float gain() const;

		String name() const;
		template<class AnyStringT> void name(const AnyStringT& name);

		unsigned int id() const;
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
		//! Buffer used for playing. NULL if none
		Private::Audio::Buffer<>::Ptr  pBuffer;
		//! Is the source ready for use?
		bool pReady;
		//! Is the source currently playing?
		bool pPlaying;

	}; // class Source




} // namespace Audio
} // namespace Yuni

# include "source.hxx"

#endif // __YUNI_AUDIO_SOURCE_H__
