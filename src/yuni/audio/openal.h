#ifndef __YUNI_AUDIO_OPENAL_H__
# define __YUNI_AUDIO_OPENAL_H__

# include <list>
# include "../gfx/vector3D.h"
# include "../gfx/point3D.h"
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
		static ALenum getFormat(unsigned int bits, unsigned int channels);

		static void setDistanceModel(DistanceModel model);

		/*!
		** \brief Create OpenAL buffers
		** \param nbBuffers Number of buffers to create
		** \returns An array of IDs of the created buffers
		*/
		static unsigned int* createBuffers(int nbBuffers);

		static void destroyBuffers(int nbBuffers, unsigned int* buffers);

		static void setListener(float position[3], float velocity[3], float orientation[6]);

		/*!
		** \brief Create an OpenAL source
		** \returns The source's ID, 0 if an error is encountered.
		*/
		static unsigned int createSource(Gfx::Point3D<> position, Gfx::Vector3D<> velocity,
			Gfx::Vector3D<> direction, float pitch, float gain, bool attenuate, bool loop);
		//! Destroy an OpenAL source
		static void destroySource(unsigned int source);

		static bool playSource(unsigned int source);
		static void modifySource(unsigned int source, float pitch, float gain,
			bool attenuate, bool loop);
		static void moveSource(unsigned int source, const Gfx::Point3D<>& position,
							   const Gfx::Vector3D<>& velocity, const Gfx::Vector3D<>& direction);

		static void bindBufferToSource(unsigned int buffer, unsigned int source);
		static void unbindBufferFromSource(unsigned int source);
		static void queueBufferToSource(unsigned int buffer, unsigned int source);
		static unsigned int unqueueBufferFromSource(unsigned int source);

	}; // OpenAL

} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_OPENAL_H__
