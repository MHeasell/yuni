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
	bool QueueService::Emitters::add(const StringT& emitterName)
	{
		return add(String(emitterName));
	}

	template<>
	inline bool QueueService::Emitters::add<String>(const String& emitterName)
	{
		Emitter::Ptr newEmitter(new Emitter());

		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (!pQueueService->pReady)
				return false;

			pEmitters[emitterName] = newEmitter;
		}
		Audio::Loop::RequestType callback;
 		callback.bind(newEmitter, &Emitter::prepareDispatched);
		// Dispatching...
 		pQueueService->pAudioLoop.dispatch(callback);

		return true;
	}

	template<typename StringT, typename StringT2>
	bool QueueService::Emitters::add(const StringT& emitterName, const StringT2& attachedBuffer)
	{
		return add(String(emitterName), String(attachedBuffer));
	}

	template<>
	inline bool QueueService::Emitters::add<String, String>(const String& emitterName,
		const String& attachedBuffer)
	{
		Emitter::Ptr newEmitter(new Emitter());

		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (!pQueueService->pReady)
				return false;

			pEmitters[String(emitterName)] = newEmitter;
		}
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

	template<>
	inline bool QueueService::Emitters::attach<String, String>(const String& name,
		const String& attachedBuffer)
	{
		Emitter::Ptr newEmitter(new Emitter());

		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (!pQueueService->pReady)
				return false;

			pEmitters[name] = newEmitter;
		}
		Audio::Loop::RequestType callback;
 		callback.bind(newEmitter, &Emitter::prepareDispatched);
		// Dispatching...
 		pQueueService->pAudioLoop.dispatch(callback);

		return true;
	}

	template<typename StringT>
	bool QueueService::Emitters::attach(Emitter::Ptr name, const StringT& attachedBuffer)
	{
		return attach(name, String(attachedBuffer));
	}

	template<>
	inline bool QueueService::Emitters::attach<String>(Emitter::Ptr name, const String& attachedBuffer)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		// TODO
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
	inline bool QueueService::Emitters::play(const StringT& name)
	{
		return play(String(name));
	}

	template<>
	inline bool QueueService::Emitters::play<String>(const String& name)
	{
		return play(get(name));
	}

	inline bool QueueService::Emitters::play(Emitter::Ptr& emitter)
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
	bool QueueService::loadSound(const StringT& filePath)
	{
		return loadSound(String(filePath));
	}

	template<>
	bool QueueService::loadSound<String>(const String& filePath)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pReady)
			return false;

		// Create the buffer, store it in the map
		bank.pBuffers[filePath] = new Private::Audio::Buffer<>(NULL);

		Yuni::Bind<bool()> callback;
		callback.bind(this, &QueueService::loadSoundDispatched, filePath);
		pAudioLoop.dispatch(callback);
		return true;
	}


	template<typename StringT1, typename StringT2>
	bool QueueService::playSound(const StringT1& emitterName, const StringT2& sound)
	{
		return playSound(String(emitterName), String(sound));
	}

	template<>
	bool QueueService::playSound<String,String>(const String& emitterName, const String& sound)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pReady)
			return false;

		Private::Audio::Buffer<>::Ptr buffer = bank.get(sound);
		if (!buffer)
		{
			std::cerr << "QueueService::playSound : no buffer with name \"" << sound
					  << "\" could be found !" << std::endl;
			return false;
		}

		Emitter::Ptr emitterPtr = emitter.get(emitterName);
		if (!emitterPtr)
		{
			std::cerr << "QueueService::playSound : no emitter with name \"" << emitterName
					  << "\" could be found !" << std::endl;
			return false;
		}

		Audio::Loop::RequestType callback;
 		callback.bind(emitterPtr, &Emitter::playSoundDispatched, buffer);
		// Dispatching...
 		pAudioLoop.dispatch(callback);

		return true;
	}




} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_QUEUESERVICE_HXX__
