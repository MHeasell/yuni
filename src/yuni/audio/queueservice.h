#ifndef __YUNI_AUDIO_QUEUESERVICE_H__
# define __YUNI_AUDIO_QUEUESERVICE_H__

# include "../yuni.h"
# include <map>
# include "../core/atomic/int.h"
# include "../core/point3D.h"
# include "../core/vector3D.h"
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
		//! The threading policy
		typedef Policy::ObjectLevelLockable<QueueService>  ThreadingPolicy;

	public:

		//! Forward declaration
		class Bank;

		/*!
		** \brief This is the the access to all the emitters for this queue service
		**
		** All the emitters are managed here.
		** It can be accessed through: queueService.emitter
		*/
		class Emitters: public Policy::ObjectLevelLockable<Emitters>
		{
		public:
			typedef Policy::ObjectLevelLockable<Emitters>  ThreadingPolicy;

		private:
			Emitters()
			{}
			Emitters(const Emitters&);

			//! Map of currently registered emitters, with string tags as keys
			Emitter::Map pEmitters;

		public:
			template<typename StringT>
			Emitter::Ptr get(const StringT& name);

			template<typename StringT>
			bool add(const StringT& name);

			template<typename StringT, typename StringT2>
			bool attach(const StringT& name, const StringT2& attachedBuffer);
			template<typename StringT>
			bool attach(Emitter::Ptr name, const StringT& attachedBuffer);

			template<typename StringT>
			bool modify(const StringT& name, bool loop);
			bool modify(Emitter::Ptr name, bool loop);

			template<typename StringT>
			bool move(const StringT& name, const Gfx::Point3D<>& position);
			bool move(Emitter::Ptr emitter, const Gfx::Point3D<>& position);
			template<typename StringT>
			bool move(const StringT& name, const Gfx::Point3D<>& position,
				const Gfx::Vector3D<>& velocity, const Gfx::Vector3D<>& direction);
			bool move(Emitter::Ptr emitter, const Gfx::Point3D<>& position,
				const Gfx::Vector3D<>& velocity, const Gfx::Vector3D<>& direction);

			template<typename StringT>
			sint64 elapsedTime(const StringT& name);
			sint64 elapsedTime(Emitter::Ptr emitter);

			template<typename StringT>
			bool play(const StringT& name);
			bool play(Emitter::Ptr emitter);

			template<typename StringT>
			bool stop(const StringT& name);
			bool stop(Emitter::Ptr& emitter);

			template<typename StringT>
			bool remove(const StringT& name);
			bool remove(Emitter::Ptr name);

		private:
			friend class QueueService;

			QueueService* pQueueService;
			Bank* pBank;
		};




		/*!
		** \brief The bank contains the audio buffers currently loaded in the queue service
		**
		** It can be accessed through: queueService.bank
		*/
		class Bank: public Policy::ObjectLevelLockable<Bank>
		{
		public:
			typedef Policy::ObjectLevelLockable<Bank>  ThreadingPolicy;

		private:
			Bank()
			{}
			Bank(const Bank&);

			//! Map of currently loaded buffers, with string tags as keys
			Private::Audio::Buffer<>::Map pBuffers;

		public:
			void clear();

			template<typename StringT>
			bool load(const StringT& name);


		private:
			template<typename StringT>
			Private::Audio::Buffer<>::Ptr get(const StringT& name);

		private:
			friend class QueueService;
			friend class QueueService::Emitters;

			QueueService* pQueueService;
		};




	public:
		QueueService(): pReady(false), pAudioLoop(this)
		{
			bank.pQueueService = this;
			emitter.pQueueService = this;
			emitter.pBank = &bank;
		}
		~QueueService()
		{
			if (pReady)
				stop();
		}

	public:
		//! Control block for emitters
		Emitters emitter;
		//! Control block for audio buffers
		Bank bank;

	public:
		bool start();
		void stop();


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

		//! This is meant to aggregate a condition with the emitter
		struct EmitterPositionData
		{
			EmitterPositionData(Thread::Condition& c, float& f): condition(c), data(f) {}

			Thread::Condition& condition;
			float& data;
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
		static Atomic::Int<32> sHasRunningInstance;

		//! Has the manager been properly started ?
		bool pReady;
		//! Event loop for audio events
		Loop pAudioLoop;

	private:
		friend class Loop;
		friend class Emitters;
		friend class Bank;

	}; // class QueueService




} // namespace Audio
} // namespace Yuni

#include "queueservice.hxx"

#endif // __YUNI_AUDIO_QUEUESERVICE_H__
