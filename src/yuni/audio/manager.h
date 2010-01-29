
#ifndef __YUNI_AUDIO_MANAGER_H__
# define __YUNI_AUDIO_MANAGER_H__

# include "../core/string.h"
# include "../thread/policy.h"
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

	public:
		static Manager& Instance();

	private:
		Manager();
		Manager(const Manager&);
		Manager& operator = (const Manager&);

	public:
		void start();
		void stop();

		template<typename AnyStringT>
		bool loadSound(const AnyStringT&);

	private:
		bool loadSoundWL();

	private:
		//! Singleton instance
		static Manager* sInstance;

		//! Event loop for audio events
		Loop pAudioLoop;

		/*!
		** \brief Temporary storage for the string for file loading dispatch
		** \note This is ugly, it should be removed and a better use of bind() should be made.
		*/
		const char* pFilePath;

	}; // class Manager



} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_MANAGER_H__
