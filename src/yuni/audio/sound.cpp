
#include "sound.h"
#include "openal.h"


namespace Yuni
{
namespace Audio
{


	ASound::ASound()
		:pFile(NULL)
	{
		// Do nothing
	}


	bool ASound::loadFromFile()
	{
		// Locking
		ThreadingPolicy::MutexLocker locker(*this);

		// Try to open the file
		AudioFile* file = AV::openFile(pFilePath);
		if (!file)
			return false;

		// Try to get an audio stream from it
		AudioStream* stream = AV::getAudioStream(file, 0);
		if (!stream)
		{
			AV::closeFile(file);
			return false;
		}

		// Get info on the audio stream
		int rate;
		int channels;
		int bits;
		if (0 != AV::getAudioInfo(stream, &rate, &channels, &bits))
		{
			AV::closeFile(file);
			return false;
		}

		// Check the format
		ALenum format = OpenAL::getFormat(bits, channels);
		if (0 == format)
		{
			AV::closeFile(file);
			return false;
		}

		return true;
	}




} // namespace Audio
} // namespace Yuni
