#ifndef __YUNI_AUDIO_QUEUESERVICE_HXX__
# define __YUNI_AUDIO_QUEUESERVICE_HXX__


namespace Yuni
{
namespace Audio
{


	template<typename StringT>
	Emitter::Ptr QueueService::Emitters::get(const StringT& name)
	{
		return get(String(name));
	}


	template<>
	inline Emitter::Ptr QueueService::Emitters::get<String>(const String& name)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		Emitter::Map::iterator it = pEmitters.find(name);
		if (it == pEmitters.end())
			return Emitter::Ptr(NULL);
		return it->second;
	}


	template<typename StringT>
	Private::Audio::Buffer<>::Ptr QueueService::Bank::get(const StringT& name)
	{
		return get(String(name));
	}

	template<>
	inline Private::Audio::Buffer<>::Ptr QueueService::Bank::get<String>(const String& name)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		Private::Audio::Buffer<>::Map::iterator it = pBuffers.find(name);
		if (it == pBuffers.end())
			return Private::Audio::Buffer<>::Ptr(NULL);
		return it->second;
	}




	template<typename StringT>
	bool QueueService::Emitters::add(const StringT& emitterName)
	{
		return add(String(emitterName));
	}

	template<>
	inline bool QueueService::Emitters::add<String>(const String& emitterName)
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


	template<typename StringT, typename StringT2>
	bool QueueService::Emitters::attach(const StringT& name, const StringT2& attachedBuffer)
	{
		return attach(String(name), String(attachedBuffer));
	}

	template<typename StringT>
	bool QueueService::Emitters::attach(Emitter::Ptr name, const StringT& attachedBuffer)
	{
		return attach(name, String(attachedBuffer));
	}

	template<>
	inline bool QueueService::Emitters::attach<String, String>(const String& emitterName,
		const String& bufferName)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pQueueService->pReady)
			return false;

		Emitter::Ptr emitter = get(emitterName);
		if (!emitter)
			return false;

		Private::Audio::Buffer<>::Ptr buffer = pBank->get(bufferName);
		if (!buffer)
			return false;

		Audio::Loop::RequestType callback;
 		callback.bind(emitter, &Emitter::attachBufferDispatched, buffer);
		// Dispatching...
 		pQueueService->pAudioLoop.dispatch(callback);

		return true;
	}


	template<>
	inline bool QueueService::Emitters::attach<String>(Emitter::Ptr emitter, const String& bufferName)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pQueueService->pReady)
			return false;

		if (!emitter)
			return false;

		Private::Audio::Buffer<>::Ptr buffer = pBank->get(bufferName);
		if (!buffer)
			return false;

		Audio::Loop::RequestType callback;
 		callback.bind(emitter, &Emitter::attachBufferDispatched, buffer);
		// Dispatching...
 		pQueueService->pAudioLoop.dispatch(callback);

		return true;
	}


	template<typename StringT>
	bool QueueService::Emitters::move(const StringT& emitterName, const Gfx::Point3D<>& position)
	{
		return move(String(emitterName), position);
	}

	template<>
	inline bool QueueService::Emitters::move<String>(const String& emitterName,
		const Gfx::Point3D<>& position)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		Emitter::Map::iterator it = pEmitters.find(emitterName);
		if (it == pEmitters.end())
			return false;
		it->second->position(position);
		return true;
	}


	template<typename StringT>
	bool QueueService::Emitters::move(const StringT& emitterStr, const Gfx::Point3D<>& position,
		const Gfx::Vector3D<>& velocity, const Gfx::Vector3D<>& direction)
	{
		return move(String(emitterStr), position, velocity, direction);
	}

	template<>
	inline bool QueueService::Emitters::move<String>(const String& emitterStr, const Gfx::Point3D<>& position,
		const Gfx::Vector3D<>& velocity, const Gfx::Vector3D<>& direction)
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


	template<typename StringT>
	inline sint64 QueueService::Emitters::elapsedTime(const StringT& name)
	{
		return elapsedTime(get(String(name)));
	}

	template<>
	inline sint64 QueueService::Emitters::elapsedTime<String>(const String& name)
	{
		return elapsedTime(get(name));
	}

	inline sint64 QueueService::Emitters::elapsedTime(Emitter::Ptr emitter)
	{
		if (!emitter)
			return 0;

		return emitter->elapsedTime();
	}


	template<typename StringT>
	inline bool QueueService::Emitters::play(const StringT& name)
	{
		return play(get(String(name)));
	}

	template<>
	inline bool QueueService::Emitters::play<String>(const String& name)
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
	}


	template<typename StringT>
	inline bool QueueService::Emitters::stop(const StringT& name)
	{
		return stop(String(name));
	}

	template<>
	inline bool QueueService::Emitters::stop<String>(const String& name)
	{
		return stop(get(name));
	}

	inline bool QueueService::Emitters::stop(Emitter::Ptr& emitter)
	{
		if (!emitter)
			return false;
		// TODO
	}




	inline void QueueService::Bank::clear()
	{
		ThreadingPolicy::MutexLocker locker(*this);

		Private::Audio::Buffer<>::Map::iterator bEnd = pBuffers.end();
		for (Private::Audio::Buffer<>::Map::iterator it = pBuffers.begin(); it != bEnd; ++it)
		{
			it->second->destroyDispatched();
		}
		pBuffers.clear();
	}


	template<typename StringT>
	inline bool QueueService::Bank::load(const StringT& filePath)
	{
		return load(String(filePath));
	}

	template<>
	inline bool QueueService::Bank::load<String>(const String& filePath)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (!pQueueService->pReady)
			return false;

		// Create the buffer, store it in the map
		pBuffers[filePath] = new Private::Audio::Buffer<>(NULL);

		Yuni::Bind<bool()> callback;
		callback.bind(pQueueService, &QueueService::loadSoundDispatched, filePath);
		pQueueService->pAudioLoop.dispatch(callback);
		return true;
	}




} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_QUEUESERVICE_HXX__
