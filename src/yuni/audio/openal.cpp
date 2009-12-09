# include <list>
# include "openal.h"

namespace Yuni
{
namespace Audio
{

	bool OpenAL::init()
	{
		ALCdevice* device = alcOpenDevice(NULL);
		if (!device)
			return false;
		ALCcontext* context = alcCreateContext(device, NULL);
		if (!context)
			return false;
		alcMakeContextCurrent(context);
		// Clear errors
		alGetError();
		return true;
	}

	void OpenAL::close()
	{
		ALCcontext* context = alcGetCurrentContext();
		ALCdevice* device = alcGetContextsDevice(context);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);
	}

	ALenum OpenAL::getFormat(const ALuint bits, const ALuint channels)
	{
		switch (bits)
		{
		case 8:
			if (channels == 1)
				return AL_FORMAT_MONO8;
			if (channels == 2)
				return AL_FORMAT_STEREO8;
			if (alIsExtensionPresent("AL_EXT_MCFORMATS"))
			{
				if (channels == 4)
					return alGetEnumValue("AL_FORMAT_QUAD8");
				if (channels == 6)
					return alGetEnumValue("AL_FORMAT_51CHN8");
			}
			break;
		case 16:
			if (channels == 1)
				return AL_FORMAT_MONO16;
			if (channels == 2)
				return AL_FORMAT_STEREO16;
			if (alIsExtensionPresent("AL_EXT_MCFORMATS"))
			{
				if (channels == 4)
					return alGetEnumValue("AL_FORMAT_QUAD16");
				if (channels == 6)
					return alGetEnumValue("AL_FORMAT_51CHN16");
			}
			break;
		}
		return 0;
	}

	bool OpenAL::playSource(ALuint source)
	{
		alSourcePlay(source);
		if (alGetError() != AL_NO_ERROR)
			return false;
		return true;
	}

	void OpenAL::setDistanceModel(DistanceModel model)
	{
		ALenum modelName;
		switch (model)
		{
		case None:
			modelName = AL_NONE;
			break;
		case InverseDistance:
			modelName = AL_INVERSE_DISTANCE;
			break;
		case InverseDistanceClamped:
			modelName = AL_INVERSE_DISTANCE_CLAMPED;
			break;
		case LinearDistance:
			modelName = AL_LINEAR_DISTANCE;
			break;
		case LinearDistanceClamped:
			modelName = AL_LINEAR_DISTANCE_CLAMPED;
			break;
		case ExponentDistance:
			modelName = AL_EXPONENT_DISTANCE;
			break;
		case ExponentDistanceClamped:
			modelName = AL_EXPONENT_DISTANCE_CLAMPED;
			break;
		default:
			modelName = AL_INVERSE_DISTANCE_CLAMPED;
			break;
		}
		alDistanceModel(modelName);
	}

	ALuint* OpenAL::createBuffers(ALsizei nbBuffers)
	{
		ALuint* buffers = (ALuint*)calloc(nbBuffers, sizeof(ALuint));
		alGenBuffers(nbBuffers, buffers);
		return buffers;
	}

	void OpenAL::destroyBuffers(ALsizei nbBuffers, ALuint* buffers)
	{
		alDeleteBuffers(nbBuffers, buffers);
	}

	void OpenAL::setListener(ALfloat position[3], ALfloat velocity[3],
		ALfloat orientation[6])
	{
		alListenerfv(AL_POSITION, position);
		alListenerfv(AL_VELOCITY, velocity);
		alListenerfv(AL_ORIENTATION, orientation);
	}

	void OpenAL::modifySource(ALuint source, float pitch, float gain,
		bool attenuate, bool loop)
	{
		alSourcef(source, AL_PITCH, pitch);
		alSourcef(source, AL_GAIN, gain);
		alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
		if (!attenuate)
			// Disable distance attenuation
			alSourcei(source, AL_ROLLOFF_FACTOR, 0);
	}

	void OpenAL::moveSource(ALuint source, ALfloat position[3],
		ALfloat velocity[3], ALfloat direction[3])
	{
		// Uncomment this if you want the position / velocity / cone /
		// direction properties to be relative to listener position:
		//alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);
		alSourcefv(source, AL_POSITION, position);
		alSourcefv(source, AL_VELOCITY, velocity);
		alSourcefv(source, AL_DIRECTION, direction);
	}

	ALuint OpenAL::createSource(ALfloat position[3], ALfloat velocity[3], ALfloat direction[3],
		float pitch, float gain, bool attenuate, bool loop)
	{
		ALuint source;
		alGenSources(1, &source);
		if (alGetError() != AL_NO_ERROR)
			return 0;

		moveSource(source, position, velocity, direction);
		modifySource(source, pitch, gain, attenuate, loop);
		return source;
	}

	void OpenAL::destroySource(ALuint source)
	{
		alDeleteSources(1, &source);
	}

	void OpenAL::bindBufferToSource(ALint buffer, ALuint source)
	{
		alSourcei(source, AL_BUFFER, buffer);
	}

	void OpenAL::unbindBufferFromSource(ALuint source)
	{
		alSourcei(source, AL_BUFFER, 0);
	}

	void OpenAL::queueBufferToSource(ALuint buffer, ALuint source)
	{
		alSourceQueueBuffers(source, 1, &buffer);
	}

	ALuint OpenAL::unqueueBufferFromSource(ALuint source)
	{
		ALuint buf;
		alSourceUnqueueBuffers(source, 1, &buf);
		return buf;
	}

} // namespace Audio
} // namespace Yuni
