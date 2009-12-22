#ifndef __YUNI_GFX_RENDER_RENDERER_H__
# define __YUNI_GFX_RENDER_RENDERER_H__

# include "../../yuni.h"
# include "../../core/smartptr.h"
# include "../scene.h"


namespace Yuni
{
namespace Gfx
{
namespace Render
{

	/*!
	** \brief The renderer draws frames from a scene and a camera
	**
	** It keeps track of render time, FPS count, and can keep
	** implementation-dependent mesh representations to speed things up.
	** This is also a way to define a common interface to OpenGL and DirectX.
	*/
	class ARenderer
	{
	public:
		typedef SmartPtr<ARenderer> Ptr;

	protected:
		/*!
		** \brief Main constructor
		**
		** Initialize the FPS counter with a one-second interval
		*/
		ARenderer()	: pPaused(false) {}

	public:
		//! \brief Virtual destructor
		virtual ~ARenderer() {}

	private:
		ARenderer(const ARenderer&);

	public:
		//! Initialize the renderer
		virtual bool initialize() = 0;

		//! Release the renderer (uninitialize)
		virtual void release() = 0;

		//! Resize the viewport
		virtual void resize(unsigned int width, unsigned int height) = 0;

		//! Render a frame
		virtual void drawFrame(const Yuni::Gfx::Scene& scene);

		//! Pause / Unpause rendering
		virtual void pause(bool inPause) { pPaused = inPause; }

		//! Get the number of frames rendered in the last second
		unsigned int instantFPS()
		{
			// TODO FPS counter missing
			return 0;
		}

		//! Get the mean number of frames per second since start of rendering
		unsigned int meanFPS()
		{
			// TODO FPS counter missing
			return 0;
		}

	private:
		//! Clear the screen to black
		virtual void clearScreen() = 0;

		//! Reset the view matrices
		virtual void resetView() = 0;

		//! Apply view translation
		virtual void applyTranslation(const Vector3D<float>& translation) = 0;

		//! Apply view rotation
		virtual void applyRotation(const Vector3D<float>& rotation) = 0;

		//! Draw some triangles
		virtual void drawTriangles(const Mesh::TriangleList& triangles) = 0;

		//! TEMPORARY
		virtual void testDraw() = 0;

	protected:
		bool pPaused;

	}; // ARenderer




} // namespace Render
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_RENDER_RENDERER_H__
