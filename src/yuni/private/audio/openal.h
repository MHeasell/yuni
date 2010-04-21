#ifndef __YUNI_AUDIO_OPENAL_H__
# define __YUNI_AUDIO_OPENAL_H__

# include "../../yuni.h"
# include <list>
# include "../../core/vector3D.h"
# include "../../core/point3D.h"
# ifdef YUNI_OS_MACOS
#	include <OpenAL/al.h>
#	include <OpenAL/alc.h>
# else
#	include <al.h>
#	include <alc.h>
# endif

namespace Yuni
{
namespace Private
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
		static bool Init();

		/*!
		** \brief Close OpenAL context and device
		*/
		static bool Close();

		/*!
		** \brief Convert to an OpenAL format
		** \param bits Number of bits per sample
		** \param channels Number of channels
		** \returns An ALenum containing the format, 0 if none found
		*/
		static ALenum GetFormat(unsigned int bits, unsigned int channels);

		static void SetDistanceModel(DistanceModel model);

		/*!
		** \brief Create OpenAL buffers
		** \param nbBuffers Number of buffers to create
		** \returns An array of IDs of the created buffers
		*/
		static unsigned int* CreateBuffers(int nbBuffers);

		static void DestroyBuffers(int nbBuffers, unsigned int* buffers);

		static void SetListener(float position[3], float velocity[3], float orientation[6]);

		/*!
		** \brief Create an OpenAL source
		** \returns The source's ID, 0 if an error is encountered.
		*/
		static unsigned int CreateSource(Gfx::Point3D<> position, Gfx::Vector3D<> velocity,
			Gfx::Vector3D<> direction, float pitch, float gain, bool attenuate, bool loop);
		//! Destroy an OpenAL source
		static void DestroySource(unsigned int source);

		static bool PlaySource(unsigned int source);
		static void ModifySource(unsigned int source, float pitch, float gain,
			bool attenuate, bool loop);
		static void MoveSource(unsigned int source, const Gfx::Point3D<>& position,
							   const Gfx::Vector3D<>& velocity, const Gfx::Vector3D<>& direction);

		static void BindBufferToSource(unsigned int buffer, unsigned int source);
		static void UnbindBufferFromSource(unsigned int source);
		static void QueueBufferToSource(unsigned int buffer, unsigned int source);
		static unsigned int UnqueueBufferFromSource(unsigned int source);

	}; // OpenAL

} // namespace Audio
} // namespace Private
} // namespace Yuni

#endif // __YUNI_AUDIO_OPENAL_H__
