
#include "queueservice.h"
#include <cassert>
#include "../core/point3D.h"
#include "../core/vector3D.h"
#include "../thread/signal.h"
#include "../private/media/av.h"
#include "../private/media/file.h"
#include "../private/media/openal.h"

namespace Yuni
{
namespace Media
{

	Atomic::Int<32> QueueService::sHasRunningInstance = 0;


	QueueService::QueueService() :
		pReady(false),
		pMediaLoop(this)
	{
		library.pQueueService = this;
		emitter.pQueueService = this;
		emitter.pLibrary = &library;
	}


	QueueService::~QueueService()
	{
		if (pReady)
			stop();
	}


	bool QueueService::start()
	{
		ThreadingPolicy::MutexLocker locker(*this);
		// Do not initialize the manager twice
		if (pReady || sHasRunningInstance)
			return false;

		pMediaLoop.start();

		// Init media from the media loop
		{
			Thread::Signal signal;
			InitData initData(signal, pReady);
			Bind<bool()> callback;
			callback.bind(this, &QueueService::initDispatched, (InitData&)initData);
			pMediaLoop.dispatch(callback);
			// Wait for the initDispatched to finish
			signal.wait();
		}

		if (pReady)
		{
			sHasRunningInstance = 1;
			return true;
		}
		return false;
	}


	void QueueService::stop()
	{
		ThreadingPolicy::MutexLocker locker(*this);
		// Do not stop the manager if it was not properly started
		if (!pReady)
			return;

		pMediaLoop.beginClose();

		// Close OpenAL buffers properly
		library.clear();

		// Close OpenAL emitters properly
		{
			Emitter::Map::iterator sEnd = emitter.pEmitters.end();
			for (Emitter::Map::iterator it = emitter.pEmitters.begin(); it != sEnd; ++it)
			{
				Private::Media::OpenAL::DestroySource(it->second->id());
			}
		}
		emitter.pEmitters.clear();
		// Close OpenAL
		Yuni::Bind<bool()> callback;
		callback.bind(&Private::Media::OpenAL::Close);
		pMediaLoop.dispatch(callback);
		pMediaLoop.endClose();
		pReady = false;
		sHasRunningInstance = 0;
	}


	bool QueueService::initDispatched(InitData& data)
	{
		data.ready = Private::Media::AV::Init() && Private::Media::OpenAL::Init();
		// The variable must be considered as destroyed as soon as the method
		// 'notify()' is called
		bool ready = data.ready;
		data.signal.notify();
		return ready;
	}


	bool QueueService::loadSoundDispatched(const String& filePath)
	{
		// Try to open the file
		Private::Media::File* file = new Private::Media::File(filePath);
		if (!file->valid())
		{
			delete file;
			return false;
		}

		// Try to get an audio stream from it
		Private::Media::Stream<Private::Media::stAudio>::Ptr stream =
			file->getStream<Private::Media::stAudio>();
		if (!stream)
		{
			delete file;
			return false;
		}

		// Check the format
		if (!stream->valid())
		{
			delete file;
			return false;
		}
		//std::cout << "Sound is " << bits << " bits " << (channels > 1 ? "stereo " : "mono ")
		//	  << rate << "Hz" << std::endl;

		// Associate the buffer with the stream
		{
			ThreadingPolicy::MutexLocker locker(*this);
			Sound::Ptr buffer = library.get(filePath);
			assert(nullptr != buffer);
			buffer->stream(stream);
		}

		return true;
	}


	bool QueueService::updateDispatched()
	{
		const Emitter::Map::iterator end = emitter.pEmitters.end();
		for (Emitter::Map::iterator it = emitter.pEmitters.begin(); it != end; ++it)
			(it->second)->updateDispatched();
		return true;
	}


	bool QueueService::playing() const
	{
		ThreadingPolicy::MutexLocker locker(*this);

		Emitter::Map::const_iterator end = emitter.pEmitters.end();
		for (Emitter::Map::const_iterator it = emitter.pEmitters.begin(); it != end; ++it)
		{
			if (it->second->playing())
				return true;
		}
		return false;
	}



	///////////////////////////////// Emitters


	Emitter::Ptr QueueService::Emitters::get(const AnyString& name)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		Emitter::Map::iterator it = pEmitters.find(name);
		if (it == pEmitters.end())
			return nullptr;
		return it->second;
	}


	bool QueueService::Emitters::add(const AnyString& emitterName)
	{
		Emitter::Ptr newEmitter(new Emitter());

		ThreadingPolicy::MutexLocker locker(*this);

		if (!pQueueService->pReady)
			return false;

		// Create the emitter and add it
		pEmitters[emitterName] = newEmitter;

		Media::Loop::RequestType callback;
 		callback.bind(newEmitter, &Emitter::prepareDispatched);
		// Dispatching...
 		pQueueService->pMediaLoop.dispatch(callback);

		return true;
	}


	bool QueueService::Emitters::attach(const AnyString& emitterName,
		const AnyString& bufferName)
	{
		Sound::Ptr buffer = pLibrary->get(bufferName);
		if (!buffer)
			return false;

		ThreadingPolicy::MutexLocker locker(*this);
		{
			if (!pQueueService->pReady)
				return false;

			Emitter::Map::iterator it = pEmitters.find(emitterName);
			if (it == pEmitters.end())
				return false;
			Emitter::Ptr emitter = it->second;

			Media::Loop::RequestType callback;
			callback.bind(emitter, &Emitter::attachBufferDispatched, buffer);
			// Dispatching...
			pQueueService->pMediaLoop.dispatch(callback);
		}
		return true;
	}


	bool QueueService::Emitters::attach(Emitter::Ptr emitter, const AnyString& bufferName)
	{
		if (!emitter || !bufferName)
			return false;

		Sound::Ptr buffer = pLibrary->get(bufferName);
		if (!buffer)
			return false;

		ThreadingPolicy::MutexLocker locker(*this);
		{
			if (!pQueueService->pReady)
				return false;

			Media::Loop::RequestType callback;
			callback.bind(emitter, &Emitter::attachBufferDispatched, buffer);
			// Dispatching...
			pQueueService->pMediaLoop.dispatch(callback);
		}
		return true;
	}


	bool QueueService::Emitters::attach(Emitter::Ptr emitter, Sound::Ptr buffer)
	{
		if (!emitter || !buffer)
			return false;

		ThreadingPolicy::MutexLocker locker(*this);
		{
			if (!pQueueService->pReady)
				return false;

			Media::Loop::RequestType callback;
			callback.bind(emitter, &Emitter::attachBufferDispatched, buffer);
			// Dispatching...
	 		pQueueService->pMediaLoop.dispatch(callback);
		}
		return true;
	}


	void QueueService::Emitters::detach(const AnyString& name)
	{
		return detach(get(name));
	}


	void QueueService::Emitters::detach(Emitter::Ptr emitter)
	{
		if (!emitter)
			return;

		Media::Loop::RequestType callback;
 		callback.bind(emitter, &Emitter::detachBufferDispatched);
		// Dispatching...
 		pQueueService->pMediaLoop.dispatch(callback);
	}



	bool QueueService::Emitters::move(const AnyString& emitterName,
		const Point3D<>& position)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		Emitter::Map::iterator it = pEmitters.find(emitterName);
		if (it == pEmitters.end())
			return false;
		it->second->position(position);
		return true;
	}


	bool QueueService::Emitters::move(const AnyString& emitterStr, const Point3D<>& position,
		const Vector3D<>& velocity, const Vector3D<>& direction)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		Emitter::Map::iterator it = pEmitters.find(emitterStr);
		if (it == pEmitters.end())
			return false;

 		it->second->position(position);
 		it->second->velocity(velocity);
 		it->second->direction(direction);
		return true;
	}


	bool QueueService::Emitters::playing(const AnyString& name)
	{
		return playing(get(name));
	}


	bool QueueService::Emitters::playing(Emitter::Ptr emitter)
	{
		if (!emitter)
			return false;
		return emitter->playing();
	}


	bool QueueService::Emitters::paused(const AnyString& name)
	{
		return paused(get(name));
	}


	bool QueueService::Emitters::paused(Emitter::Ptr emitter)
	{
		if (!emitter)
			return false;
		return emitter->paused();
	}


	bool QueueService::Emitters::play(Emitter::Ptr emitter)
	{
		if (!emitter)
			return false;
		Media::Loop::RequestType callback;
 		callback.bind(emitter, &Emitter::playSoundDispatched);
		// Dispatching...
 		pQueueService->pMediaLoop.dispatch(callback);
		return true;
	}


	bool QueueService::Emitters::pause(Emitter::Ptr emitter)
	{
		if (!emitter)
			return false;
		Media::Loop::RequestType callback;
 		callback.bind(emitter, &Emitter::pauseSoundDispatched);
		// Dispatching...
 		pQueueService->pMediaLoop.dispatch(callback);
		return true;
	}


	bool QueueService::Emitters::stop(const Emitter::Ptr& emitter)
	{
		if (!emitter)
			return false;
		Media::Loop::RequestType callback;
 		callback.bind(emitter, &Emitter::stopSoundDispatched);
		// Dispatching...
 		pQueueService->pMediaLoop.dispatch(callback);
		return true;
	}



	////////////////////////// Library

	Sound::Ptr QueueService::Library::get(const AnyString& name)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		Sound::Map::iterator it = pBuffers.find(name);
		if (it == pBuffers.end())
			return nullptr;
		return it->second;
	}


	void QueueService::Library::clear()
	{
		ThreadingPolicy::MutexLocker locker(*this);

		{
			Thread::Signal signal;
			Yuni::Bind<bool()> callback;
			Sound::Map::iterator bEnd = pBuffers.end();
			for (Sound::Map::iterator it = pBuffers.begin(); it != bEnd; ++it)
			{
				// We have to pass a pointer here, otherwise bind() will call the copy ctor
				callback.bind(it->second, &Sound::destroyDispatched, &signal);
				pQueueService->pMediaLoop.dispatch(callback);
				signal.wait();
				signal.reset();
			}
		}
		pBuffers.clear();
	}


	bool QueueService::Library::load(const AnyString& filePath)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (!pQueueService->pReady)
			return false;

		// Create the buffer, store it in the map
		pBuffers[filePath] = new Sound();

		Yuni::Bind<bool()> callback;
		callback.bind(pQueueService, &QueueService::loadSoundDispatched, filePath);
		pQueueService->pMediaLoop.dispatch(callback);
		return true;
	}


	bool QueueService::Library::unload(const AnyString& name)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (!pQueueService->pReady)
			return false;

		Sound::Map::iterator it = pBuffers.find(name);
		if (pBuffers.end() == it)
			return false;

		{
			Thread::Signal signal;
			Yuni::Bind<bool()> callback;

			callback.bind(it->second, &Sound::destroyDispatched, &signal);
			pQueueService->pMediaLoop.dispatch(callback);
			signal.wait();
		}
		// Wait for data to be properly unloaded before removing from the list
		pBuffers.erase(it);

		return true;
	}


	unsigned int QueueService::Library::duration(const AnyString& name)
	{
		Sound::Ptr buffer = get(name);
		if (!buffer)
			return 0;

		ThreadingPolicy::MutexLocker locker(*this);
		if (!pQueueService->pReady)
			return 0;
		return buffer->duration();
	}


	bool QueueService::running() const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pReady && pMediaLoop.running();
	}






} // namespace Media
} // namespace Yuni
