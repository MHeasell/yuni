
#include "sound.h"
#include "../private/audio/openal.h"


namespace Yuni
{
namespace Audio
{


	bool ISound::loadFromFile()
	{
		// Locking
		ThreadingPolicy::MutexLocker locker(*this);

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

