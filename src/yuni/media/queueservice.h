#ifndef __YUNI_MEDIA_QUEUESERVICE_H__
# define __YUNI_MEDIA_QUEUESERVICE_H__

# include "../yuni.h"
# include "../core/string.h"
# include "emitter.h"
# include "loop.h"
# include "source.h"


namespace Yuni
{
namespace Media
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
		class Library;

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
			Emitter::Ptr get(const AnyString& name);

			//! Add an emitter
			bool add(const AnyString& name);

			//! Attach an emitter to a buffer
			bool attach(const AnyString& name, const AnyString& attachedBuffer);
			//! Attach an emitter to a buffer
			bool attach(Emitter::Ptr emitter, const AnyString& attachedBuffer);
			//! Attach an emitter to a buffer
			bool attach(Emitter::Ptr emitter, Source::Ptr attachedBuffer);

			//! Detach an emitter from any buffer
			void detach(const AnyString& name);
			//! Detach an emitter from any buffer
			void detach(Emitter::Ptr name);

			//! Modify an emitter's data
			bool modify(const AnyString& name, bool loop);
			//! Modify an emitter's data
			bool modify(Emitter::Ptr name, bool loop);

			//! Move an emitter around
			bool move(const AnyString& name, const Point3D<>& position);
			//! Move an emitter around
			bool move(Emitter::Ptr emitter, const Point3D<>& position);
			//! Move an emitter around
			bool move(const AnyString& name, const Point3D<>& position,
				const Vector3D<>& velocity, const Vector3D<>& direction);
			//! Move an emitter around
			bool move(Emitter::Ptr emitter, const Point3D<>& position,
				const Vector3D<>& velocity, const Vector3D<>& direction);

			//! Get elapsed playback time on an emitter
			sint64 elapsedTime(const AnyString& name);
			//! Get elapsed playback time on an emitter
			sint64 elapsedTime(Emitter::Ptr emitter);

			//! Get whether an emitter is playing
			bool playing(const AnyString& name);
			//! Get whether an emitter is playing
			bool playing(Emitter::Ptr emitter);

			//! Get whether an emitter is paused
			bool paused(const AnyString& name);
			//! Get whether an emitter is paused
			bool paused(Emitter::Ptr emitter);

			//! Start playback on an emitter
			bool play(const AnyString& name);
			//! Start playback on an emitter
			bool play(Emitter::Ptr emitter);

			//! Pause playback on an emitter
			bool pause(const AnyString& name);
			//! Pause playback on an emitter
			bool pause(Emitter::Ptr emitter);

			//! Stop playback on an emitter
			bool stop(const AnyString& name);
			//! Stop playback on an emitter
			bool stop(const Emitter::Ptr& emitter);

			//! Remove an emitter
			bool remove(const AnyString& name);
			//! Remove an emitter
			bool remove(Emitter::Ptr name);

		private:
			//! Friend declaration
			friend class QueueService;

			//! Associated queue service
			QueueService* pQueueService;
			//! Associated library
			Library* pLibrary;
		};




		/*!
		** \brief The Library contains the media buffers currently loaded in the queue service
		**
		** It can be accessed through: queueService.library
		*/
		class Library: public Policy::ObjectLevelLockable<Library>
		{
		public:
			typedef Policy::ObjectLevelLockable<Library>  ThreadingPolicy;

		private:
			//! \name Constructors
			//@{
			//! Empty constructor
			Library()
			{}

			//! Copy constructor
			Library(const Library&);
			//@}

		public:
			//! Clear the library, free the loaded buffers
			void clear();

			/*!
			** \brief Load media file from given path
			**
			** \param name Path to file, used from now on as an identifier for the source
			*/
			bool load(const AnyString& name);

			/*!
			** \brief Load media file from given path
			**
			** \param name Path to file, used from now on as an identifier for the source
			*/
			bool unload(const AnyString& name);

			//! Get the duration of a loaded source
			uint duration(const AnyString& name);

			//! Get elapsed time (current playing time) in the source
			float elapsedTime(const AnyString& name);

		private:
			//! Get a source from the library
			Source::Ptr get(const AnyString& name);

		private:
			//! Friend declaration
			friend class QueueService;
			//! Friend declaration
			friend class QueueService::Emitters;

			//! Map of currently loaded buffers, with string tags as keys
			Source::Map pBuffers;

			//! Associated queue service
			QueueService* pQueueService;
		};




	public:
		//! \name Constructor and destructor
		//@{
		//! Constructor
		QueueService();

		//! Destructor
		~QueueService();
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
		Library library;

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
		** \brief Media initialization
		**
		** \note Dispatched in the media loop
		*/
		bool initDispatched(InitData& initData);

		/*!
		** \brief Source loading
		**
		** \note Dispatched in the media loop
		*/
		bool loadSourceDispatched(const String& filePath);

		/*!
		** \brief Buffer update
		**
		** \note Called in the Media::Loop::onLoop()
		*/
		bool updateDispatched();

	private:
		//! Static to make sure only one manager is started
		static Atomic::Int<32> sHasRunningInstance;

		//! Has the manager been properly started ?
		bool pReady;
		//! Event loop for media events
		Loop pMediaLoop;

	private:
		//! Friend declaration
		friend class Loop;
		//! Friend declaration
		friend class Emitters;
		//! Friend declaration
		friend class Library;

	}; // class QueueService




} // namespace Media
} // namespace Yuni

#include "queueservice.hxx"

#endif // __YUNI_MEDIA_QUEUESERVICE_H__
