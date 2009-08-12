#ifndef __YUNI_GFX3D_RENDER_RENDERER_H__
# define __YUNI_GFX3D_RENDER_RENDERER_H__

# include "../../yuni.h"
# include "../scene.h"
# include "fpscounter.h"

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
		/*!
		** \brief Main constructor
		**
		** Initialize the FPS counter with a one-second interval
		*/
		ARenderer()	: pPaused(false)
		{}
		//! \brief Virtual destructor
		virtual ~ARenderer()
		{}

		//! Render a frame
		virtual void drawFrame(const Yuni::Gfx::Scene& scene) = 0;

		//! Pause / Unpause rendering
		virtual void pause(bool inPause) { pPaused = inPause; }

		//! Get the number of frames rendered in the last second
		unsigned int instantFPS()
		{
			return pCounter.instantFPS();
		}

		//! Get the mean number of frames per second since start of rendering
		unsigned int meanFPS()
		{
			return pCounter.meanFPS();
		}

	protected:
		bool pPaused;
		FPSCounter pCounter;

	}; // ARenderer

} // Render
} // Gfx
} // Yuni

#endif // __YUNI_GFX3D_RENDER_RENDERER_H__
