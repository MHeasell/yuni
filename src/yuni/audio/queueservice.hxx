#ifndef __YUNI_AUDIO_QUEUESERVICE_HXX__
# define __YUNI_AUDIO_QUEUESERVICE_HXX__


namespace Yuni
{
namespace Audio
{


	template<typename StringT>
	bool QueueService::loadSound(const StringT& filePath)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pReady)
			return false;

		// Create the buffer, store it in the map
		pBuffers[filePath] = new Private::Audio::Buffer<>(NULL);

		Yuni::Bind<bool()> callback;
		callback.bind(this, &QueueService::loadSoundDispatched, String(filePath));
		pAudioLoop.dispatch(callback);
		return true;
	}


	template<typename StringT1, typename StringT2>
	bool QueueService::playSound(const StringT1& emitter, const StringT2& sound)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pReady)
			return false;

		String soundStr(sound);
		if (pBuffers.find(soundStr) == pBuffers.end())
		{
			std::cerr << "QueueService::playSound : no buffer with name \"" << sound
					  << "\" could be found !" << std::endl;
			return false;
		}
		Private::Audio::Buffer<>::Ptr buffer(pBuffers[soundStr]);

		String emitterStr(emitter);
		if (pEmitters.find(emitterStr) == pEmitters.end())
		{
			std::cerr << "QueueService::playSound : no emitter with name \"" << emitter
					  << "\" could be found !" << std::endl;
			return false;
		}
		Emitter::Ptr emitterPtr(pEmitters[emitterStr]);

		// Here we would like to do as below: a template specialization to avoid the useless
		// String constructor call when StringT == String.
		// However, it would require method template partial specialization :/
		Audio::Loop::RequestType callback;
 		callback.bind(emitterPtr, &Emitter::playSoundDispatched, buffer);
		// Dispatching...
 		pAudioLoop.dispatch(callback);

		return true;
	}


	template<typename StringT>
	bool QueueService::addEmitter(const StringT& emitterName, bool loop)
	{
		return addEmitter(String(emitterName), loop);
	}

	template<>
	inline bool QueueService::addEmitter<String>(const String& emitterName, bool loop)
	{
		Emitter::Ptr newEmitter(new Emitter(loop));

		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (!pReady)
				return false;

			pEmitters[emitterName] = newEmitter;
		}
		Audio::Loop::RequestType callback;
 		callback.bind(newEmitter, &Emitter::prepareDispatched);
		// Dispatching...
 		pAudioLoop.dispatch(callback);

		return true;
	}

	template<typename StringT>
	bool QueueService::addEmitter(const StringT& emitterName, const Gfx::Point3D<>& position,
		bool loop = false)
	{
		Emitter::Ptr newEmitter(new Emitter(position, loop));
		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (!pReady)
				return false;

			pEmitters[String(emitterName)] = newEmitter;
		}
		Audio::Loop::RequestType callback;
 		callback.bind(newEmitter, &Emitter::prepareDispatched);
		// Dispatching...
 		pAudioLoop.dispatch(callback);

		return true;
	}

	template<typename StringT>
	bool QueueService::addEmitter(const StringT& emitterName, const Gfx::Point3D<>& position,
		const Gfx::Vector3D<>& velocity, const Gfx::Vector3D<>& direction, bool loop = false)
	{
		Emitter::Ptr newEmitter(new Emitter(position, velocity, direction, loop));

		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (!pReady)
				return false;

			pEmitters[String(emitterName)] = newEmitter;
		}
		Audio::Loop::RequestType callback;
 		callback.bind(newEmitter, &Emitter::prepareDispatched);
		// Dispatching...
 		pAudioLoop.dispatch(callback);

		return true;
	}


	template<typename StringT>
	bool QueueService::moveEmitter(const StringT& emitterName, const Gfx::Point3D<>& position)
	{
		String emitterStr = emitterName;
		return moveEmitter(emitterStr, position);
	}

	template<>
	inline bool QueueService::moveEmitter<String>(const String& emitterStr, const Gfx::Point3D<>& position)
	{
		Emitter::Map::iterator it = pEmitters.find(emitterStr);
		if (it == pEmitters.end())
			return false;
 		it->second->position(position);
		return true;
	}




} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_QUEUESERVICE_HXX__
