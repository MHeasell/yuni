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
# include "../thread/signal.h"
# include "emitter.h"
# include "loop.h"
# include "sound.h"


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
			//! Get an emitter
			Emitter::Ptr get(const StringAdapter& name);

			//! Add an emitter
			bool add(const StringAdapter& name);

			//! Attach an emitter to a buffer
			bool attach(const StringAdapter& name, const StringAdapter& attachedBuffer);
			//! Attach an emitter to a buffer
			bool attach(Emitter::Ptr name, const StringAdapter& attachedBuffer);

			//! Modify an emitter's data
			bool modify(const StringAdapter& name, bool loop);
			//! Modify an emitter's data
			bool modify(Emitter::Ptr name, bool loop);

			//! Move an emitter around
			bool move(const StringAdapter& name, const Point3D<>& position);
			//! Move an emitter around
			bool move(Emitter::Ptr emitter, const Point3D<>& position);
			//! Move an emitter around
			bool move(const StringAdapter& name, const Point3D<>& position,
				const Vector3D<>& velocity, const Vector3D<>& direction);
			//! Move an emitter around
			bool move(Emitter::Ptr emitter, const Point3D<>& position,
				const Vector3D<>& velocity, const Vector3D<>& direction);

			//! Get elapsed playback time on an emitter
			sint64 elapsedTime(const StringAdapter& name);
			//! Get elapsed playback time on an emitter
			sint64 elapsedTime(Emitter::Ptr emitter);

			//! Start playback on an emitter
			bool play(const StringAdapter& name);
			//! Start playback on an emitter
			bool play(Emitter::Ptr emitter);

			//! Stop playback on an emitter
			bool stop(const StringAdapter& name);
			//! Stop playback on an emitter
			bool stop(const Emitter::Ptr& emitter);

			//! Remove an emitter
			bool remove(const StringAdapter& name);
			//! Remove an emitter
			bool remove(Emitter::Ptr name);

		private:
			//! Friend declaration
			friend class QueueService;

			//! Associated queue service
			QueueService* pQueueService;
			//! Associated bank
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
			//! \name Constructors
			//@{
			//! Empty constructor
			Bank()
			{}

			//! Copy constructor
			Bank(const Bank&);
			//@}

		public:
			//! Clear the bank, free the loaded buffers
			void clear();

			/*!
			** \brief Load sound file from given path
			**
			** \param name Path to file, used from now on as an identifier for the sound
			*/
			bool load(const StringAdapter& name);

			/*!
			** \brief Load sound file from given path
			**
			** \param name Path to file, used from now on as an identifier for the sound
			*/
			bool unload(const StringAdapter& name);

			//! Get the duration of a loaded sound
			unsigned int duration(const StringAdapter& name);


		private:
			//! Get a sound from the bank
			Sound::Ptr get(const StringAdapter& name);

		private:
			//! Friend declaration
			friend class QueueService;
			//! Friend declaration
			friend class QueueService::Emitters;

			//! Map of currently loaded buffers, with string tags as keys
			Sound::Map pBuffers;

			//! Associated queue service
			QueueService* pQueueService;
		};




	public:
		//! \name Constructor and destructor
		//@{
		//! Constructor
		QueueService(): pReady(false), pAudioLoop(this)
		{
			bank.pQueueService = this;
			emitter.pQueueService = this;
			emitter.pBank = &bank;
		}
		//! Destructor
		~QueueService()
		{
			if (pReady)
				stop();
		}
		//@}

	public:
		/*!
		** \brief Start the audio service
		*/
		bool start();

		/*!
		** \brief Stop the audio service
		*/
		void stop();

		/*!
		** \brief Is the audio service running ?
		*/
		bool running() const;

		/*!
		** \brief Is there at least one emitter playing ?
		*/
		bool playing() const;

	public:
		//! Control block for emitters
		Emitters emitter;
		//! Control block for audio buffers
		Bank bank;

	private:
		//! \name Private operations
		//@{
		/*!
		** \brief Copy constructor
		*/
		QueueService(const QueueService&);

		/*!
		** \brief Assignment
		*/
		QueueService& operator = (const QueueService&);
		//@}


	private:
		//! This is meant to aggregate a condition and a boolean for dispatching
		struct InitData
		{
			InitData(Thread::Signal& s, bool& r): signal(s), ready(r) {}

			Thread::Signal& signal;
			bool& ready;
		};

		//! This is meant to aggregate a condition with the emitter
		struct EmitterPositionData
		{
			EmitterPositionData(Thread::Signal& s, float& f): signal(s), data(f) {}

			Thread::Signal& signal;
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
		//! Friend declaration
		friend class Loop;
		//! Friend declaration
		friend class Emitters;
		//! Friend declaration
		friend class Bank;

	}; // class QueueService




} // namespace Audio
} // namespace Yuni

#include "queueservice.hxx"

#endif // __YUNI_AUDIO_QUEUESERVICE_H__
