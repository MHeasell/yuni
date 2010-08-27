#ifndef __YUNI_GFX_SURFACE_CAIRO_H__
# define __YUNI_GFX_SURFACE_CAIRO_H__

# include "../api/cairo.h"
# include "surface.h"

namespace Yuni
{
namespace Gfx
{
namespace Surface
{



	/*!
	** \brief A Cairo surface for 2D vector-based drawing
	*/
	class Cairo: public ASurface
	{
	protected:
		//! Initalize Cairo surface
		virtual bool initialize();

		//! Release surface
		virtual void release();

		//! Resize the surface
		virtual void resize(unsigned int width, unsigned int height);

		//! Choose a color to clear the screen with
		virtual void clearColor(Color::RGB<uint8>& newColor);

		//! Clear the screen to black
		virtual void clearScreen();


	protected:
		//! Cairo context
		cairo_t* context;

		//! Cairo surface
		cairo_surface_t* surface;


	}; // Cairo



} // namespace Surface
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_SURFACE_CAIRO_H__
