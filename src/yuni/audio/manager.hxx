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

		Yuni::Bind<bool()> callback;

		callback.bind(this, &Manager::loadSoundWL, String(filePath));
		pAudioLoop.dispatch(callback);
		return true;
	}


	template<typename StringT1, typename StringT2>
	bool Manager::playSound(const StringT1& source, const StringT2& sound)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pReady)
			return false;

		Private::Audio::Buffer<>::Ptr buffer(pBuffers[String(sound)]);
		if (NULL == buffer)
		{
			std::cerr << "Manager::playSound : no buffer with name \"" << sound
					  << "\" could be found !" << std::endl;
			return false;
		}

		Source::Ptr sourcePtr(pSources[String(source)]);
		if (NULL == sourcePtr)
		{
			std::cerr << "Manager::playSound : no source with name \"" << source
					  << "\" could be found !" << std::endl;
			return false;
		}

		// Here we would like to do as below: a template specialization to avoid the useless
		// String constructor call when StringT == String.
		// However, it would require method template partial specialization :/
		Audio::Loop::RequestType callback;
 		callback.bind(sourcePtr, &Source::playSound, buffer);
		// Dispatching...
 		pAudioLoop.dispatch(callback);

		//pSources[String(source)]->playSound(pBuffers[String(sound)]);
		return true;
	}


	template<typename StringT>
	bool Manager::addSource(const StringT& sourceName, bool loop)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pReady)
			return false;

		Source::Ptr newSource(new Source(loop));

		Audio::Loop::RequestType callback;
 		callback.bind(newSource, &Source::prepare);
		// Dispatching...
 		pAudioLoop.dispatch(callback);
		// TODO: Find a way to test the return value

		pSources[String(sourceName)] = newSource;
		return true;
	}

	template<>
	inline bool Manager::addSource<String>(const String& sourceName, bool loop)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pReady)
			return false;

		Source::Ptr newSource(new Source(loop));
		Audio::Loop::RequestType callback;
 		callback.bind(newSource, &Source::prepare);
		// Dispatching...
 		pAudioLoop.dispatch(callback);
		// TODO: Find a way to test the return value

		pSources[sourceName] = newSource;
		return true;
	}

	template<typename StringT>
	bool Manager::addSource(const StringT& sourceName, const Gfx::Point3D<>& position,
		bool loop = false)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pReady)
			return false;

		Source::Ptr newSource(new Source(position, loop));
		Audio::Loop::RequestType callback;
 		callback.bind(newSource, &Source::prepare);
		// Dispatching...
 		pAudioLoop.dispatch(callback);

		pSources[String(sourceName)] = newSource;
		return true;
	}

	template<typename StringT>
	bool Manager::addSource(const StringT& sourceName, const Gfx::Point3D<>& position,
		const Gfx::Vector3D<>& velocity, const Gfx::Vector3D<>& direction, bool loop = false)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pReady)
			return false;

		Source::Ptr newSource(new Source(position, velocity, direction, loop));
		Audio::Loop::RequestType callback;
 		callback.bind(newSource, &Source::prepare);
		// Dispatching...
 		pAudioLoop.dispatch(callback);

		pSources[String(sourceName)] = newSource;
		return true;
	}



} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_MANAGER_HXX__
