#ifndef __YUNI_AUDIO_MANAGER_HXX__
# define __YUNI_AUDIO_MANAGER_HXX__

namespace Yuni
{
namespace Audio
{


	template<typename AnyStringT>
	bool Manager::loadSound(const AnyStringT& filePath)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pReady)
			return false;

		Yuni::Bind<bool()> callback;

		callback.bind(this, &Manager::loadSoundWL, String(filePath));
		pAudioLoop.dispatch(callback);
		return true;
	}


	template<typename AnyStringT1, typename AnyStringT2>
	bool Manager::playSound(const AnyStringT1& source, const AnyStringT2& sound)
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
		// String constructor call when AnyStringT == String.
		// However, it would require method template partial specialization :/
		Audio::Loop::RequestType callback;
 		callback.bind(sourcePtr, &Source::playSound, buffer);
		// Dispatching...
 		pAudioLoop.dispatch(callback);

		//pSources[String(source)]->playSound(pBuffers[String(sound)]);
		return true;
	}


	template<typename AnyStringT>
	bool Manager::addSource(const AnyStringT& sourceName, bool loop)
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

	template<typename AnyStringT>
	bool Manager::addSource(const AnyStringT& sourceName, const Gfx::Point3D<>& position,
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

	template<typename AnyStringT>
	bool Manager::addSource(const AnyStringT& sourceName, const Gfx::Point3D<>& position,
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
