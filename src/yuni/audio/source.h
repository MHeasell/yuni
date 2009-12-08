#ifndef __YUNI_AUDIO_SOURCE_H__
# define __YUNI_AUDIO_SOURCE_H__

# include "../core/smartptr.h"
# include "../gfx/point3D.h"
# include "../gfx/vector3D.h"

namespace Yuni
{
namespace Audio
{
	/*!
	** \brief An audio source is an object from which the sound is played
	**
	** Audio sources can be placed in space, and be moved around.
	*/
	class Source
	{
	public:
		typedef SmartPtr<Source> Ptr;

	public:
		/*!
		** \brief Empty constructor
		**
		** Position and speed default to (0,0,0)
		*/
		Source() {}

	private:
		Gfx::Point3D pPosition;
		Gfx::Vector3D pVelocity;
		Gfx::Vector3D pDirection;

	}; // Source

} // namespace Audio
} // namespace Yuni

#endif // __YUNI_AUDIO_SOURCE_H__
