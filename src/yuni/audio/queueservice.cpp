
#include <cassert>
#include "../private/audio/av.h"
#include "../private/audio/openal.h"
#include "queueservice.h"

namespace Yuni
{
namespace Audio
{

	bool QueueService::sHasRunningInstance = false;


	bool QueueService::start()
	{
		ThreadingPolicy::MutexLocker locker(*this);
		// Do not initialize the manager twice
		if (pReady || sHasRunningInstance)
			return false;

		pAudioLoop.start();
		Thread::Condition condition;
		InitData initData(condition, pReady);
		Bind<bool()> callback;
		callback.bind(this, &QueueService::initDispatched, initData);
		condition.lock();
		pAudioLoop.dispatch(callback);

		// Wait for the initDispatched to finish
		condition.waitUnlocked();
		condition.unlock();

		if (pReady)
		{
			sHasRunningInstance = true;
			return true;
		}
		return false;
	}

	void QueueService::stop()
	{
		ThreadingPolicy::MutexLocker locker(*this);
		// Do not stop the manager if it was not properly started
		if (!pReady)
			return;

		// Close OpenAL buffers properly
		Private::Audio::Buffer<>::Map::iterator bEnd = pBuffers.end();
		for (Private::Audio::Buffer<>::Map::iterator it = pBuffers.begin(); it != bEnd; ++it)
		{
			it->second->destroyDispatched();
		}
		pBuffers.clear();

		// Close OpenAL emitters properly
		Emitter::Map::iterator sEnd = pEmitters.end();
		for (Emitter::Map::iterator it = pEmitters.begin(); it != sEnd; ++it)
		{
			Private::Audio::OpenAL::DestroySource(it->second->id());
		}
		pEmitters.clear();
		// Close OpenAL
		Yuni::Bind<bool()> callback;
		callback.bind(&Private::Audio::OpenAL::Close);
		pAudioLoop.dispatch(callback);
		pAudioLoop.stop();
		pReady = false;
		sHasRunningInstance = false;
	}


	bool QueueService::initDispatched(InitData& data)
	{
  		data.condition.lock();
		data.condition.unlock();
		data.ready = Private::Audio::AV::Init() && Private::Audio::OpenAL::Init();

		data.condition.notify();
		return data.ready;
	}


	bool QueueService::loadSoundDispatched(const String& filePath)
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
		std::cout << "Sound is " << bits << " bits " << (channels > 1 ? "stereo " : "mono ")
				  << rate << "Hz" << std::endl;

		// Associate the buffer with the stream
		{
			ThreadingPolicy::MutexLocker locker(*this);
			assert(pBuffers.find(filePath) != pBuffers.end());
			pBuffers[filePath]->stream(stream);
		}

		std::cout << "Loading succeeded !" << std::endl;
		return true;
	}


	bool QueueService::updateDispatched()
	{
		Emitter::Map::iterator end = pEmitters.end();
		for (Emitter::Map::iterator it = pEmitters.begin(); it != end; ++it)
			it->second->updateDispatched();
		return true;
	}




} // namespace Audio
} // namespace Yuni
