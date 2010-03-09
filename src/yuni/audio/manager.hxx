
namespace Yuni
{
namespace Audio
{


	template<typename AnyStringT>
	bool Manager::loadSound(const AnyStringT& filePath)
	{
		ThreadingPolicy::MutexLocker locker(*this);
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
		Yuni::Bind<bool(Sound::Ptr&)> callback;

		callback.
		return true;
	}

	template<typename AnyStringT>
	void Manager::addSource(const AnyStringT& sourceName, bool loop = false)
	{
		Source::Ptr newSource(new Source(loop));
		pSources[String(sourceName)] = newSource;
		newSource->prepare();
	}

	template<>
	inline void Manager::addSource(const String& sourceName, bool loop)
	{
		Source::Ptr newSource(new Source(loop));
		pSources[sourceName] = newSource;
		newSource->prepare();
	}


	template<typename AnyStringT>
	void Manager::addSource(const AnyStringT& sourceName, const Gfx::Point3D<>& position,
		bool loop = false)
	{
		Source::Ptr newSource(new Source(position, loop));
		pSources[String(sourceName)] = newSource;
		newSource->prepare();
	}

	template<typename AnyStringT>
	void Manager::addSource(const AnyStringT& sourceName, const Gfx::Point3D<>& position,
		const Gfx::Vector3D<>& velocity, const Gfx::Vector3D<>& direction, bool loop = false)
	{
		Source::Ptr newSource(new Source(position, velocity, direction, loop));
		pSources[String(sourceName)] = newSource;
		newSource->prepare();
	}


} // namespace Audio
} // namespace Yuni
