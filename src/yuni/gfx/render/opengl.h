#ifndef __YUNI_GFX3D_RENDER_OPENGL_H__
# define __YUNI_GFX3D_RENDER_OPENGL_H__

# include "renderer.h"

namespace Yuni
{
namespace Gfx3D
{
	/*!
	** \brief OpenGL implementation of a renderer
	**
	** For the moment, this is a naive unoptimized implementation.
	*/
	class OpenGL
	{
	public:
		void drawFrame(const Scene& scene);

	}; // OpenGL

} // Gfx3D
} // Yuni

#endif // __YUNI_GFX3D_RENDER_OPENGL_H__
