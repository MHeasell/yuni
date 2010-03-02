
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


	template<typename AnyStringT>
	bool playSound(const AnyStringT& source, const AnyStringT& sound)
	{
		return true;
	}



} // namespace Audio
} // namespace Yuni
