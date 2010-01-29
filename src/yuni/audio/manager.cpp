
#include "../private/audio/av.h"
#include "../private/audio/openal.h"
#include "manager.h"

namespace Yuni
{
namespace Audio
{

	Manager* Manager::sInstance;

	Manager& Manager::Instance()
	{
		if (!sInstance)
			sInstance = new Manager();
		return *sInstance;
	}


	void Manager::start()
	{
		pAudioLoop.start();
		Yuni::Bind<bool()> callback;
		callback.bind(&Private::Audio::AV::init);
		pAudioLoop.dispatch(callback);
		callback.bind(&Private::Audio::OpenAL::init);
		pAudioLoop.dispatch(callback);
	}

	void Manager::stop()
	{
		Yuni::Bind<bool()> callback;
		callback.bind(&Private::Audio::OpenAL::close);
		pAudioLoop.dispatch(callback);
		pAudioLoop.stop();
	}

	template<typename AnyStringT>
	bool Manager::loadSound(const AnyStringT& filePath)
	{
		ThreadingPolicy::MutexLocker locker(*this);
		Yuni::Bind<bool()> callback;
		callback.bind(this, &Manager::loadSoundWL);
		pFilePath = filePath.CStr();
		pAudioLoop.dispatch(callback);
		return true;
	}

	bool Manager::loadSoundWL()
	{
		// Try to open the file
		Private::Audio::AudioFile* file = Private::Audio::AV::openFile(pFilePath);
		if (!file)
			return false;

		// Try to get an audio stream from it
		Private::Audio::AudioStream* stream = Private::Audio::AV::getAudioStream(file, 0);
		if (!stream)
		{
			Private::Audio::AV::closeFile(file);
			return false;
		}

		// Get info on the audio stream
		int rate;
		int channels;
		int bits;
		if (0 != Private::Audio::AV::getAudioInfo(stream, &rate, &channels, &bits))
		{
			Private::Audio::AV::closeFile(file);
			return false;
		}

		// Check the format
		ALenum format = Private::Audio::OpenAL::getFormat(bits, channels);
		if (0 == format)
		{
			Private::Audio::AV::closeFile(file);
			return false;
		}

		return true;
	}

} // namespace Audio
} // namespace Yuni
