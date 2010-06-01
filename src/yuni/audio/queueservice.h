#ifndef __YUNI_AUDIO_QUEUESERVICE_H__
# define __YUNI_AUDIO_QUEUESERVICE_H__

# include "../yuni.h"
# include <map>
# include "../core/point3d.h"
# include "../core/vector3d.h"
# include "../core/string.h"
# include "../core/smartptr.h"
# include "../thread/policy.h"
# include "../thread/condition.h"
# include "emitter.h"
# include "loop.h"
# include "../private/audio/buffer.h"


namespace Yuni
{
namespace Audio
{

	/*!
	** \brief The audio queue service is the service that manages everything sound-related
	**
	** It takes care of ffmpeg / openal inits.
	** It uses an event loop to solve MT problems.
	*/
	class QueueService: public Policy::ObjectLevelLockable<QueueService>
	{
	public:
		typedef Policy::ObjectLevelLockable<QueueService>  ThreadingPolicy;

	public:
		class Emitters
		{
		private:
			Emitters()
			{}
			Emitters(const Emitters&);

			//! Map of currently registered emitters, with string tags as keys
			Emitter::Map pEmitters;

		public:
			bool create(const String& name);
			bool create(const String& name, const String& attachedBuffer);
			bool attach(const String& name, const String& attachedBuffer);
			bool attach(Emitter::Ptr name, const String& attachedBuffer);
			bool remove(const String& name);
			bool remove(Emitter::Ptr name);

		private:
			friend class QueueService;

			QueueService* pQueueService;
		};

	public:
		QueueService(): pReady(false), pAudioLoop(this)
		{
			emitter.pQueueService = this;
		}

	public:
		//! Control block for emitters
		Emitters emitter;

	public:
		bool start();
		void stop();

		template<typename StringT>
		bool loadSound(const StringT&);

		template<typename StringT1, typename StringT2>
		bool playSound(const StringT1& emitter, const StringT2& sound);

		/*!
		** \brief Create an emitter with default values
		**
		** Position, speed and velocity default to (0,0,0)
		*/
		template<typename StringT>
		bool addEmitter(const StringT& emitterName, bool loop);

		/*!
		** \brief Create an emitter with 3D position
		**
		** Speed and velocity default to (0,0,0)
		*/
		template<typename StringT>
		bool addEmitter(const StringT& emitterName, const Gfx::Point3D<>& position,
			bool loop);

		/*!
		** \brief Constructor with position, velocity and direction
		*/
		template<typename StringT>
		bool addEmitter(const StringT& emitterName, const Gfx::Point3D<>& position,
			const Gfx::Vector3D<>& velocity, const Gfx::Vector3D<>& direction, bool loop);

		/*!
		** \brief Move an emitter to a given position
		*/
		template<typename StringT>
		bool moveEmitter(const StringT& emitterName, const Gfx::Point3D<>& position);

		/*!
		** \brief Move an emitter to a given position, with velocity and direction
		*/
		template<typename StringT>
		bool moveEmitter(const StringT& emitterName, const Gfx::Point3D<>& position,
			const Gfx::Vector3D<>& velocity, const Gfx::Vector3D<>& direction);

	private:
		QueueService(const QueueService&);
		QueueService& operator = (const QueueService&);


	private:
		//! This is meant to aggregate a condition and a boolean for dispatching
		struct InitData
		{
			InitData(Thread::Condition& c, bool& r): condition(c), ready(r) {}

			Thread::Condition& condition;
			bool& ready;
		};

	private:
		/*!
		** \brief Audio initialization
		**
		** \note Dispatched in the audio loop
		*/
		bool initDispatched(InitData& initData);

		/*!
		** \brief Sound loading
		**
		** \note Dispatched in the audio loop
		*/
		bool loadSoundDispatched(const String& filePath);

		/*!
		** \brief Buffer update
		**
		** \note Called in the Audio::Loop::onLoop()
		*/
		bool updateDispatched();

	private:
		//! Static to make sure only one manager is started
		static bool sHasRunningInstance;

		//! Has the manager been properly started ?
		bool pReady;
		//! Event loop for audio events
		Loop pAudioLoop;
		//! Map of currently loaded buffers, with string tags as keys
		Private::Audio::Buffer<>::Map pBuffers;
		//! Map of currently registered emitters, with string tags as keys
		Emitter::Map pEmitters;

	private:
		friend class Loop;
		friend class Emitters;

	}; // class QueueService




} // namespace Audio
} // namespace Yuni

#include "queueservice.hxx"

#endif // __YUNI_AUDIO_QUEUESERVICE_H__
