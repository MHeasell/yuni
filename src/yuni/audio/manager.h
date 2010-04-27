#ifndef __YUNI_AUDIO_MANAGER_H__
# define __YUNI_AUDIO_MANAGER_H__

# include "../yuni.h"
# include <map>
# include "../core/point3d.h"
# include "../core/vector3d.h"
# include "../core/string.h"
# include "../core/smartptr.h"
# include "../thread/policy.h"
# include "source.h"
# include "loop.h"
# include "../private/audio/buffer.h"


namespace Yuni
{
namespace Audio
{


	/*!
	** \brief The audio manager is a singleton that manages everything sound-related
	**
	** It takes care of ffmpeg / openal inits.
	** It uses an event loop to solve MT problems.
	*/
	class Manager: public Policy::ObjectLevelLockable<Manager>
	{
	public:
		typedef Policy::ObjectLevelLockable<Manager>  ThreadingPolicy;

	public:
		Manager(): pReady(false), pAudioLoop(this)
		{}

	private:
		Manager(const Manager&);
		Manager& operator = (const Manager&);

	public:
		void start();
		void stop();

		template<typename StringT>
		bool loadSound(const StringT&);

		template<typename StringT1, typename StringT2>
		bool playSound(const StringT1& source, const StringT2& sound);

		/*!
		** \brief Create a source with default values
		**
		** Position, speed and velocity default to (0,0,0)
		*/
		template<typename StringT>
		bool addSource(const StringT& sourceName, bool loop);

		/*!
		** \brief Create a source with 3D position
		**
		** Speed and velocity default to (0,0,0)
		*/
		template<typename StringT>
		bool addSource(const StringT& sourceName, const Gfx::Point3D<>& position,
			bool loop);

		/*!
		** \brief Constructor with position, velocity and direction
		*/
		template<typename StringT>
		bool addSource(const StringT& sourceName, const Gfx::Point3D<>& position,
			const Gfx::Vector3D<>& velocity, const Gfx::Vector3D<>& direction, bool loop);


	private:
		bool loadSoundWL(const String& filePath);

		bool playSoundWL();

		bool updateWL();

		unsigned int createSource();

	private:
		//! Static to make sure only one manager is started
		static bool sHasRunningInstance;

		//! Has the manager been properly started ?
		bool pReady;
		//! Event loop for audio events
		Loop pAudioLoop;
		//! Map of currently registered sources, with string tags as keys
		Source::Map pSources;
		//! Map of currently loaded buffers, with string tags as keys
		Private::Audio::Buffer<>::Map pBuffers;

	private:
		friend class Loop;

	}; // class Manager




} // namespace Audio
} // namespace Yuni

#include "manager.hxx"

#endif // __YUNI_AUDIO_MANAGER_H__
