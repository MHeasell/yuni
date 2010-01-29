# include <cstdlib>
# include "openal.h"

namespace Yuni
{
namespace Private
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

	bool OpenAL::close()
	{
		ALCcontext* context = alcGetCurrentContext();
		ALCdevice* device = alcGetContextsDevice(context);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);
		return true;
	}

	ALenum OpenAL::getFormat(unsigned int bits, unsigned int channels)
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

	unsigned int* OpenAL::createBuffers(int nbBuffers)
	{
		unsigned int* buffers = (unsigned int*)calloc(nbBuffers, sizeof(unsigned int));
		alGenBuffers(nbBuffers, buffers);
		return buffers;
	}

	void OpenAL::destroyBuffers(int nbBuffers, unsigned int* buffers)
	{
		alDeleteBuffers(nbBuffers, buffers);
	}

	void OpenAL::setListener(float position[3], float velocity[3], float orientation[6])
	{
		alListenerfv(AL_POSITION, position);
		alListenerfv(AL_VELOCITY, velocity);
		alListenerfv(AL_ORIENTATION, orientation);
	}

	unsigned int OpenAL::createSource(Gfx::Point3D<> position, Gfx::Vector3D<> velocity,
		Gfx::Vector3D<> direction, float pitch, float gain, bool attenuate, bool loop)
	{
		unsigned int source;
		alGenSources(1, &source);
		if (alGetError() != AL_NO_ERROR)
			return 0;

		moveSource(source, position, velocity, direction);
		modifySource(source, pitch, gain, attenuate, loop);
		return source;
	}

	void OpenAL::destroySource(unsigned int source)
	{
		alDeleteSources(1, &source);
	}

	bool OpenAL::playSource(ALuint source)
	{
		alSourcePlay(source);
		if (alGetError() != AL_NO_ERROR)
			return false;
		return true;
	}

	void OpenAL::modifySource(unsigned int source, float pitch, float gain,
		bool attenuate, bool loop)
	{
		alSourcef(source, AL_PITCH, pitch);
		alSourcef(source, AL_GAIN, gain);
		alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
		if (!attenuate)
			// Disable distance attenuation
			alSourcei(source, AL_ROLLOFF_FACTOR, 0);
	}

	void OpenAL::moveSource(unsigned int source, const Gfx::Point3D<>& position,
		const Gfx::Vector3D<>& velocity, const Gfx::Vector3D<>& direction)
	{
		// Uncomment this if you want the position / velocity / cone /
		// direction properties to be relative to listener position:
		//alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);

		float pos[3] = { position.x, position.y, position.z};
		float vel[3] = { velocity.x, velocity.y, velocity.z};
		float dir[3] = { direction.x, direction.y, direction.z};
		alSourcefv(source, AL_POSITION, pos);
		alSourcefv(source, AL_VELOCITY, vel);
		alSourcefv(source, AL_DIRECTION, dir);
	}

	void OpenAL::bindBufferToSource(unsigned int buffer, unsigned int source)
	{
		alSourcei(source, AL_BUFFER, (int)buffer);
	}

	void OpenAL::unbindBufferFromSource(unsigned int source)
	{
		alSourcei(source, AL_BUFFER, 0);
	}

	void OpenAL::queueBufferToSource(unsigned int buffer, unsigned int source)
	{
		alSourceQueueBuffers(source, 1, &buffer);
	}

	unsigned int OpenAL::unqueueBufferFromSource(unsigned int source)
	{
		unsigned int buf;
		alSourceUnqueueBuffers(source, 1, &buf);
		return buf;
	}

} // namespace Audio
} // namespace Private
} // namespace Yuni
