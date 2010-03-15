
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

		callback.bind(this, &Manager::loadSoundWL);
		pFilePath = filePath;
		pAudioLoop.dispatch(callback);
		return true;
	}


	template<typename AnyStringT1, typename AnyStringT2>
	bool Manager::playSound(const AnyStringT1& source, const AnyStringT2& sound)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pReady)
			return false;
		Yuni::Bind<bool()> callback;

		// Here we would like to do as below: a template specialization to avoid the useless
		// String constructor call when AnyStringT == String.
		// However, it would require method template partial specialization :/
// 		callback.bind(pSources[String(source)], &Source::playSound, pBuffers[sound]);
// 		pAudioLoop.dispatch(callback);
		pSources[String(source)]->playSound(pBuffers[String(sound)]);
		return true;
	}

	template<typename AnyStringT>
	bool Manager::addSource(const AnyStringT& sourceName, bool loop = false)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		if (!pReady)
			return false;

		Source::Ptr newSource(new Source(loop));
		if (!newSource->prepare())
			return false;
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
		if (!newSource->prepare())
			return false;
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
		if (!newSource->prepare())
			return false;
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
		if (!newSource->prepare())
			return false;
		pSources[String(sourceName)] = newSource;
		return true;
	}


} // namespace Audio
} // namespace Yuni
