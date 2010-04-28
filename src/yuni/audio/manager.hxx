#ifndef __YUNI_AUDIO_MANAGER_HXX__
# define __YUNI_AUDIO_MANAGER_HXX__

namespace Yuni
{
namespace Audio
{


	template<typename StringT>
	bool Manager::loadSound(const StringT& filePath)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pReady)
			return false;

		// Create the buffer, store it in the map
		pBuffers[filePath] = new Private::Audio::Buffer<>(NULL);

		Yuni::Bind<bool()> callback;
		callback.bind(this, &Manager::loadSoundDispatched, String(filePath));
		pAudioLoop.dispatch(callback);
		return true;
	}


	template<typename StringT1, typename StringT2>
	bool Manager::playSound(const StringT1& source, const StringT2& sound)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pReady)
			return false;

		String soundStr(sound);
		if (pBuffers.find(soundStr) == pBuffers.end())
		{
			std::cerr << "Manager::playSound : no buffer with name \"" << sound
					  << "\" could be found !" << std::endl;
			return false;
		}
		Private::Audio::Buffer<>::Ptr buffer(pBuffers[soundStr]);

		String sourceStr(source);
		if (pSources.find(sourceStr) == pSources.end())
		{
			std::cerr << "Manager::playSound : no source with name \"" << source
					  << "\" could be found !" << std::endl;
			return false;
		}
		Source::Ptr sourcePtr(pSources[sourceStr]);

		// Here we would like to do as below: a template specialization to avoid the useless
		// String constructor call when StringT == String.
		// However, it would require method template partial specialization :/
		Audio::Loop::RequestType callback;
 		callback.bind(sourcePtr, &Source::playSound, buffer);
		// Dispatching...
 		pAudioLoop.dispatch(callback);

		return true;
	}


	template<typename StringT>
	bool Manager::addSource(const StringT& sourceName, bool loop)
	{
		Source::Ptr newSource(new Source(loop));

		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (!pReady)
				return false;

			pSources[String(sourceName)] = newSource;
		}
		Audio::Loop::RequestType callback;
 		callback.bind(newSource, &Source::prepare);
		// Dispatching...
 		pAudioLoop.dispatch(callback);
		// TODO: Find a way to test the return value

		return true;
	}

	template<>
	inline bool Manager::addSource<String>(const String& sourceName, bool loop)
	{
		Source::Ptr newSource(new Source(loop));

		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (!pReady)
				return false;

			pSources[sourceName] = newSource;
		}
		Audio::Loop::RequestType callback;
 		callback.bind(newSource, &Source::prepare);
		// Dispatching...
 		pAudioLoop.dispatch(callback);
		// TODO: Find a way to test the return value

		return true;
	}

	template<typename StringT>
	bool Manager::addSource(const StringT& sourceName, const Gfx::Point3D<>& position,
		bool loop = false)
	{
		Source::Ptr newSource(new Source(position, loop));
		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (!pReady)
				return false;

			pSources[String(sourceName)] = newSource;
		}
		Audio::Loop::RequestType callback;
 		callback.bind(newSource, &Source::prepare);
		// Dispatching...
 		pAudioLoop.dispatch(callback);

		return true;
	}

	template<typename StringT>
	bool Manager::addSource(const StringT& sourceName, const Gfx::Point3D<>& position,
		const Gfx::Vector3D<>& velocity, const Gfx::Vector3D<>& direction, bool loop = false)
	{
		Source::Ptr newSource(new Source(position, velocity, direction, loop));

		{
			ThreadingPolicy::MutexLocker locker(*this);
			if (!pReady)
				return false;

			pSources[String(sourceName)] = newSource;
		}
		Audio::Loop::RequestType callback;
 		callback.bind(newSource, &Source::prepare);
		// Dispatching...
 		pAudioLoop.dispatch(callback);

		return true;
	}



} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_MANAGER_HXX__
