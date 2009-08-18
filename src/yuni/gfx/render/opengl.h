#ifndef __YUNI_GFX_RENDER_OPENGL_H__
# define __YUNI_GFX_RENDER_OPENGL_H__

# include "renderer.h"

namespace Yuni
{
namespace Gfx
{
namespace Render
{

	/*!
	** \brief OpenGL implementation of a renderer
	**
	** For the moment, this is a naive unoptimized implementation.
	*/
	class OpenGL: public ARenderer
	{
	public:
		void drawFrame(const Yuni::Gfx::Scene& scene);

	}; // OpenGL

} // Render
} // Gfx
} // Yuni

#endif // __YUNI_GFX_RENDER_OPENGL_H__
