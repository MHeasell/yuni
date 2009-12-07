#ifndef __OPENAL_H__
# define __OPENAL_H__

# include <list>
# include "al.h"
# include "alc.h"
# include "types.h"

namespace Yuni
{
namespace Audio
{

	/*!
	** \brief OpenAL wrapper
	*/
	class OpenAL
	{
	public:
		enum DistanceModel
		{
			None,
			InverseDistance,
			InverseDistanceClamped,
			LinearDistance,
			LinearDistanceClamped,
			ExponentDistance,
			ExponentDistanceClamped
		};


	public:
		/*!
		** \brief Initialize OpenAL device and context
		*/
		static bool init()
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

		/*!
		** \brief Close OpenAL context and device
		*/
		static void close()
		{
			ALCcontext* context = alcGetCurrentContext();
			ALCdevice* device = alcGetContextsDevice(context);
			alcMakeContextCurrent(NULL);
			alcDestroyContext(context);
			alcCloseDevice(device);
		}

		/*!
		** \brief Convert to an OpenAL format
		** \param bits Number of bits per sample
		** \param channels Number of channels
		** \returns An ALenum containing the format, 0 if none found
		*/
		static ALenum getFormat(const ALuint bits, const ALuint channels)
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

		static bool playSource(ALuint source)
		{
			alSourcePlay(source);
			if (alGetError() != AL_NO_ERROR)
				return false;
			return true;
		}

		static void setDistanceModel(DistanceModel model)
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

		/*!
		** \brief Create OpenAL buffers
		** \param nbBuffers Number of buffers to create
		** \returns An array of IDs of the created buffers
		*/
		static ALuint* createBuffers(ALsizei nbBuffers)
		{
			ALuint* buffers = (ALuint*)calloc(nbBuffers, sizeof(ALuint));
			alGenBuffers(nbBuffers, buffers);
			return buffers;
		}

		static void destroyBuffers(ALsizei nbBuffers, ALuint* buffers)
		{
			alDeleteBuffers(nbBuffers, buffers);
		}

		static void setListener(ALfloat position[3], ALfloat velocity[3],
			ALfloat orientation[6])
		{
			alListenerfv(AL_POSITION, position);
			alListenerfv(AL_VELOCITY, velocity);
			alListenerfv(AL_ORIENTATION, orientation);
		}

		static void modifySource(ALuint source, float pitch, float gain,
			bool attenuate, bool loop)
		{
			alSourcef(source, AL_PITCH, pitch);
			alSourcef(source, AL_GAIN, gain);
			alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
			if (!attenuate)
				// Disable distance attenuation
				alSourcei(source, AL_ROLLOFF_FACTOR, 0);
		}

		static void moveSource(ALuint source, ALfloat position[3],
			ALfloat velocity[3], ALfloat direction[3])
		{
			// Uncomment this if you want the position / velocity / cone /
			// direction properties to be relative to listener position:
			//alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);
			alSourcefv(source, AL_POSITION, position);
			alSourcefv(source, AL_VELOCITY, velocity);
			alSourcefv(source, AL_DIRECTION, direction);
		}

		// Create an AL source and return its ID. Return a negative value if an error is encountered.
		static int createSource(ALfloat position[3], ALfloat velocity[3],
			ALfloat direction[3], float pitch, float gain, bool attenuate,
			bool loop)
		{
			ALuint source;
			alGenSources(1, &source);
			if (alGetError() != AL_NO_ERROR)
				return -1;

			moveALSource(source, position, velocity, direction);
			modifyALSource(source, pitch, gain, attenuate, loop);
			return (int)source;
		}

		static void destroySource(ALuint source)
		{
			alDeleteSources(1, &source);
		}

		static void bindBufferToSource(ALint buffer, ALuint source)
		{
			alSourcei(source, AL_BUFFER, buffer);
		}

		static void queueBufferToSource(ALint buffer, ALuint source)
		{
			// TODO
		}

		static ALint unqueueBufferFromSource(ALuint source)
		{
			// TODO
		}

	}; // OpenAL

} // namespace Audio
} // namespace Yuni

#endif // __OPENAL_H__
