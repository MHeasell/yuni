#ifndef __YUNI_AUDIO_QUEUESERVICE_HXX__
# define __YUNI_AUDIO_QUEUESERVICE_HXX__


namespace Yuni
{
namespace Audio
{


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

		Sound::Map::iterator bEnd = pBuffers.end();
		for (Sound::Map::iterator it = pBuffers.begin(); it != bEnd; ++it)
		{
			it->second->destroyDispatched();
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

	inline unsigned int QueueService::Bank::duration(const StringAdapter& name)
	{
		Sound::Ptr buffer = get(name);
		if (!buffer)
			return false;

		return buffer->duration();
	}



} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_QUEUESERVICE_HXX__
