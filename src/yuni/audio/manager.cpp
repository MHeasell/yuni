
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
		{
			ThreadingPolicy::MutexLocker locker(*this);
			// Do not initialize the manager twice
			if (pReady)
				return;
		}
		pAudioLoop.start();
		Yuni::Bind<bool()> callback;
		callback.bind(&Private::Audio::AV::Init);
		pAudioLoop.dispatch(callback);
		callback.bind(&Private::Audio::OpenAL::Init);
		pAudioLoop.dispatch(callback);
		pReady = true;
	}

	void Manager::stop()
	{
		ThreadingPolicy::MutexLocker locker(*this);
		// Do not stop the manager if it was not properly started
		if (!pReady)
			return;

		// Close OpenAL buffers properly
// 		for (BufferMap::iterator it = pBuffers.begin(); it != pBuffers.end(); ++it)
// 		{
// 			delete (it->second);
// 		}
		pBuffers.clear(); // The Buffer destructors will clean stuff up
		// Close OpenAL sources properly
		for (Source::Map::iterator it = pSources.begin(); it != pSources.end(); ++it)
		{
			Private::Audio::OpenAL::DestroySource(it->second->id());
		}
		pSources.clear();
		// Close OpenAL
		Yuni::Bind<bool()> callback;
		callback.bind(&Private::Audio::OpenAL::Close);
		pAudioLoop.dispatch(callback);
		pAudioLoop.stop();
		pReady = false;
	}

	bool Manager::loadSoundWL(const String& filePath)
	{
		std::cout << "Loading file \"" << filePath << "\"..." << std::endl;

		// Try to open the file
		Private::Audio::AudioFile* file = Private::Audio::AV::OpenFile(filePath);
		if (!file)
			return false;

		// Try to get an audio stream from it
		Private::Audio::AudioStream* stream = Private::Audio::AV::GetAudioStream(file, 0);
		if (!stream)
		{
			Private::Audio::AV::CloseFile(file);
			return false;
		}

		// Get info on the audio stream
		int rate;
		int channels;
		int bits;
		if (0 != Private::Audio::AV::GetAudioInfo(stream, rate, channels, bits))
		{
			Private::Audio::AV::CloseFile(file);
			return false;
		}

		// Check the format
		stream->Format = Private::Audio::OpenAL::GetFormat(bits, channels);
		if (0 == stream->Format)
		{
			Private::Audio::AV::CloseFile(file);
			return false;
		}

		// Create the buffer, store it in the map
		pBuffers[filePath] = new Private::Audio::Buffer<>(stream);

		std::cout << "Loading succeeded !" << std::endl;
		return true;
	}


	bool Manager::updateWL()
	{
		Source::Map::iterator end = pSources.end();
		for (Source::Map::iterator it = pSources.begin(); it != end; ++it)
		{
			if (NULL != (it->second))
				!it->second->update();
		}
		return true;
	}




} // namespace Audio
} // namespace Yuni
