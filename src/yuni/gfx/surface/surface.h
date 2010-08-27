#ifndef __YUNI_GFX_SURFACE_ASURFACE_H__
# define __YUNI_GFX_SURFACE_ASURFACE_H__

# include "../../yuni.h"
# include "../../core/smartptr.h"
# include "../scene.h"
# include "../core/color/rgb.h"
# include "../core/color/rgba.h"

namespace Yuni
{
namespace Gfx
{
namespace Surface
{



	/*!
	** \brief A drawing surface is where we can draw stuff for display
	**
	** This is a common interface to Cairo, OpenGL and DirectX.
	*/
	class ASurface
	{
	public:
		typedef SmartPtr<ASurface> Ptr;

	protected:
		/*!
		** \brief Main constructor
		*/
		ASurface() {}

	public:
		//! \brief Virtual destructor
		virtual ~ASurface() {}

	private:
		ASurface(const ASurface&);

	public:
		//! Initialize the surface
		virtual bool initialize() = 0;

		//! Release the surface (uninitialize)
		virtual void release() = 0;

		//! Resize the viewport
		virtual void resize(unsigned int width, unsigned int height) = 0;

		//! Render a frame
		virtual void drawFrame(const Yuni::Gfx::Scene& scene);

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

		//! Set the default color for clearing the surface
		virtual void clearColor(Color::RGB<uint8>& newColor);

	protected:
		//! Clear the surface to clear color, default color depends on back-end
		virtual void clearScreen() = 0;

	protected:
		bool pPaused;

	}; // ASurface




} // namespace Surface
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_SURFACE_ASURFACE_H__
