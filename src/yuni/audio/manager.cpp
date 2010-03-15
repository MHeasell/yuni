
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
		pReady = true;
	}

	void Manager::stop()
	{
		// Close OpenAL buffers properly
		for (BufferMap::iterator it = pBuffers.begin(); it != pBuffers.end(); ++it)
		{
			Private::Audio::OpenAL::destroyBuffers(1, &(it->second));
		}
		pBuffers.clear();
		// Close OpenAL sources properly
		for (Source::Map::iterator it = pSources.begin(); it != pSources.end(); ++it)
		{
			Private::Audio::OpenAL::destroySource(it->second->ID());
		}
		pSources.clear();
		// Close OpenAL
		Yuni::Bind<bool()> callback;
		callback.bind(&Private::Audio::OpenAL::close);
		pAudioLoop.dispatch(callback);
		pAudioLoop.stop();
		pReady = false;
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

		// Create the buffer, store it in the map
		pBuffers[pFilePath] = *Private::Audio::OpenAL::createBuffers(1);

		return true;
	}

} // namespace Audio
} // namespace Yuni
