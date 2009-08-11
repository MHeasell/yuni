#ifndef __YUNI_GFX3D_RENDER_RENDERER_H__
# define __YUNI_GFX3D_RENDER_RENDERER_H__

# include "../../yuni.h"
# include "../scene.h"

namespace Yuni
{
namespace Gfx3D
{
namespace Render
{

	/*!
	** \brief The renderer draws frames from a scene and a camera
	**
	** It keeps track of render time, FPS count, and can keep
	** implementation-dependent mesh representations to speed things up.
	*/
	class ARenderer
	{
	public:
		ARenderer() : pPaused(false)
		{}

		virtual void drawFrame(const Yuni::Gfx::Scene& scene) = 0;
		virtual void pause(bool inPause) { pPaused = inPause; }

	private:
		bool pPaused;

	}; // Renderer

} // Render
} // Gfx
} // Yuni

#endif // __YUNI_GFX3D_RENDER_RENDERER_H__
