#ifndef __YUNI_AUDIO_MANAGER_H__
# define __YUNI_AUDIO_MANAGER_H__

# include <map>
# include "../core/point3d.h"
# include "../core/vector3d.h"
# include "../core/string.h"
# include "../thread/policy.h"
# include "source.h"
# include "loop.h"



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

		typedef std::map<String, unsigned int> BufferMap;

	public:
		static Manager& Instance();

	private:
		Manager(): pReady(false) {}
		Manager(const Manager&);
		Manager& operator = (const Manager&);

	public:
		void start();
		void stop();

		template<typename AnyStringT>
		bool loadSound(const AnyStringT&);

		template<typename AnyStringT1, typename AnyStringT2>
		bool playSound(const AnyStringT1& source, const AnyStringT2& sound);

		/*!
		** \brief Create a source with default values
		**
		** Position, speed and velocity default to (0,0,0)
		*/
		template<typename AnyStringT>
		bool addSource(const AnyStringT& sourceName, bool loop);

		/*!
		** \brief Create a source with 3D position
		**
		** Speed and velocity default to (0,0,0)
		*/
		template<typename AnyStringT>
		bool addSource(const AnyStringT& sourceName, const Gfx::Point3D<>& position,
			bool loop);

		/*!
		** \brief Constructor with position, velocity and direction
		*/
		template<typename AnyStringT>
		bool addSource(const AnyStringT& sourceName, const Gfx::Point3D<>& position,
			const Gfx::Vector3D<>& velocity, const Gfx::Vector3D<>& direction, bool loop);


	private:
		bool loadSoundWL();

		bool playSoundWL();

		unsigned int createSource();

	private:
		//! Singleton instance
		static Manager* sInstance;

		//! Has the manager been properly started ?
		bool pReady;

		//! Event loop for audio events
		Loop pAudioLoop;

		/*!
		** \brief Temporary storage for the string for file loading dispatch
		** \note This is ugly, it should be removed and a better use of bind() should be made.
		*/
		String pFilePath;

		//! Map of currently registered sources, with string tags as keys
		Source::Map pSources;

		//! Map of currently loaded buffers, with string tags as keys
		BufferMap pBuffers;

	}; // class Manager



} // namespace Audio
} // namespace Yuni

#include "manager.hxx"

#endif // __YUNI_AUDIO_MANAGER_H__
