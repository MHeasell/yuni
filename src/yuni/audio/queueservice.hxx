#ifndef __YUNI_AUDIO_QUEUESERVICE_HXX__
# define __YUNI_AUDIO_QUEUESERVICE_HXX__


namespace Yuni
{
namespace Audio
{


	inline bool QueueService::running() const
	{
		ThreadingPolicy::MutexLocker locker(*this);

		return pReady && pAudioLoop.running();
	}


	inline bool QueueService::playing() const
	{
		ThreadingPolicy::MutexLocker locker(*this);

		Emitter::Map::const_iterator end = emitter.pEmitters.end();
		for (Emitter::Map::const_iterator it = emitter.pEmitters.begin(); it != end; ++it)
			if (it->second->playing())
				return true;
		return false;
	}



	inline Emitter::Ptr QueueService::Emitters::get(const StringAdapter& name)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		Emitter::Map::iterator it = pEmitters.find(name);
		if (it == pEmitters.end())
			return nullptr;
		return it->second;
	}


	inline Sound::Ptr QueueService::Bank::get(const StringAdapter& name)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		Sound::Map::iterator it = pBuffers.find(name);
		if (it == pBuffers.end())
			return nullptr;
		return it->second;
	}




	inline bool QueueService::Emitters::add(const StringAdapter& emitterName)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (!pQueueService->pReady)
			return false;

		// Create the emitter and add it
		Emitter::Ptr newEmitter(new Emitter());
		pEmitters[emitterName] = newEmitter;

		Audio::Loop::RequestType callback;
 		callback.bind(newEmitter, &Emitter::prepareDispatched);
		// Dispatching...
 		pQueueService->pAudioLoop.dispatch(callback);

		return true;
	}


	inline bool QueueService::Emitters::attach(const StringAdapter& emitterName,
		const StringAdapter& bufferName)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pQueueService->pReady)
			return false;

		Emitter::Ptr emitter = get(emitterName);
		if (!emitter)
			return false;

		Sound::Ptr buffer = pBank->get(bufferName);
		if (!buffer)
			return false;

		Audio::Loop::RequestType callback;
 		callback.bind(emitter, &Emitter::attachBufferDispatched, buffer);
		// Dispatching...
 		pQueueService->pAudioLoop.dispatch(callback);

		return true;
	}


	inline bool QueueService::Emitters::attach(Emitter::Ptr emitter, const StringAdapter& bufferName)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pQueueService->pReady)
			return false;

		if (!emitter)
			return false;

		Sound::Ptr buffer = pBank->get(bufferName);
		if (!buffer)
			return false;

		Audio::Loop::RequestType callback;
 		callback.bind(emitter, &Emitter::attachBufferDispatched, buffer);
		// Dispatching...
 		pQueueService->pAudioLoop.dispatch(callback);

		return true;
	}


	inline void QueueService::Emitters::detach(const StringAdapter& name)
	{
		return detach(get(name));
	}


	inline void QueueService::Emitters::detach(Emitter::Ptr emitter)
	{
		if (!emitter)
			return;

		Audio::Loop::RequestType callback;
 		callback.bind(emitter, &Emitter::detachBufferDispatched);
		// Dispatching...
 		pQueueService->pAudioLoop.dispatch(callback);
	}



	inline bool QueueService::Emitters::move(const StringAdapter& emitterName,
		const Point3D<>& position)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		Emitter::Map::iterator it = pEmitters.find(emitterName);
		if (it == pEmitters.end())
			return false;
		it->second->position(position);
		return true;
	}


	inline bool QueueService::Emitters::move(const StringAdapter& emitterStr, const Point3D<>& position,
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


	inline sint64 QueueService::Emitters::elapsedTime(const StringAdapter& name)
	{
		return elapsedTime(get(name));
	}

	inline sint64 QueueService::Emitters::elapsedTime(Emitter::Ptr emitter)
	{
		if (!emitter)
			return 0;

		return emitter->elapsedTime();
	}


	inline bool QueueService::Emitters::play(const StringAdapter& name)
	{
		return play(get(name));
	}

	inline bool QueueService::Emitters::play(Emitter::Ptr emitter)
	{
		if (!emitter)
			return false;
		Audio::Loop::RequestType callback;
 		callback.bind(emitter, &Emitter::playSoundDispatched);
		// Dispatching...
 		pQueueService->pAudioLoop.dispatch(callback);
		return true;
	}


	inline bool QueueService::Emitters::stop(const StringAdapter& name)
	{
		return stop(get(name));
	}

	inline bool QueueService::Emitters::stop(const Emitter::Ptr& emitter)
	{
		if (!emitter)
			return false;
		// TODO
		return false;
	}




	inline void QueueService::Bank::clear()
	{
		ThreadingPolicy::MutexLocker locker(*this);

		Yuni::Bind<bool()> callback;
		Sound::Map::iterator bEnd = pBuffers.end();
		for (Sound::Map::iterator it = pBuffers.begin(); it != bEnd; ++it)
		{
			callback.bind(it->second, &Sound::destroyDispatched);
			pQueueService->pAudioLoop.dispatch(callback);
		}
		pBuffers.clear();
	}


	inline bool QueueService::Bank::load(const StringAdapter& filePath)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (!pQueueService->pReady)
			return false;

		// Create the buffer, store it in the map
		pBuffers[filePath] = new Sound(NULL);

		Yuni::Bind<bool()> callback;
		callback.bind(pQueueService, &QueueService::loadSoundDispatched, filePath);
		pQueueService->pAudioLoop.dispatch(callback);
		return true;
	}


	inline bool QueueService::Bank::unload(const StringAdapter& name)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (!pQueueService->pReady)
			return false;

		Sound::Ptr buffer = get(name);
		if (!buffer)
			return false;

		Yuni::Bind<bool()> callback;
		callback.bind(buffer, &Sound::destroyDispatched);
		pQueueService->pAudioLoop.dispatch(callback);
		pBuffers.erase(name);
		return true;
	}


	inline unsigned int QueueService::Bank::duration(const StringAdapter& name)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (!pQueueService->pReady)
			return 0;

		Sound::Ptr buffer = get(name);
		if (!buffer)
			return 0;

		return buffer->duration();
	}



} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_QUEUESERVICE_HXX__
