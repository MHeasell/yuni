#ifndef __YUNI_AUDIO_OPENAL_H__
# define __YUNI_AUDIO_OPENAL_H__

# include <list>
# include "al.h"
# include "alc.h"

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
		//! \name Enums
		//@{
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
		//@}


	public:
		/*!
		** \brief Initialize OpenAL device and context
		*/
		static bool init();

		/*!
		** \brief Close OpenAL context and device
		*/
		static void close();

		/*!
		** \brief Convert to an OpenAL format
		** \param bits Number of bits per sample
		** \param channels Number of channels
		** \returns An ALenum containing the format, 0 if none found
		*/
		static ALenum getFormat(const ALuint bits, const ALuint channels);

		static bool playSource(ALuint source);

		static void setDistanceModel(DistanceModel model);

		/*!
		** \brief Create OpenAL buffers
		** \param nbBuffers Number of buffers to create
		** \returns An array of IDs of the created buffers
		*/
		static ALuint* createBuffers(ALsizei nbBuffers);

		static void destroyBuffers(ALsizei nbBuffers, ALuint* buffers);

		static void setListener(ALfloat position[3], ALfloat velocity[3],
			ALfloat orientation[6]);

		static void modifySource(ALuint source, float pitch, float gain,
			bool attenuate, bool loop);

		static void moveSource(ALuint source, ALfloat position[3],
			ALfloat velocity[3], ALfloat direction[3]);

		/*!
		** \brief Create an OpenAL source
		** \returns The source's ID, 0 if an error is encountered.
		*/
		static ALuint createSource(ALfloat position[3], ALfloat velocity[3], ALfloat direction[3],
			float pitch, float gain, bool attenuate, bool loop);

		//! Destroy an OpenAL source
		static void destroySource(ALuint source);

		static void bindBufferToSource(ALint buffer, ALuint source);

		static void unbindBufferFromSource(ALuint source);

		static void queueBufferToSource(ALuint buffer, ALuint source);

		static ALuint unqueueBufferFromSource(ALuint source);

	}; // OpenAL

} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_OPENAL_H__
