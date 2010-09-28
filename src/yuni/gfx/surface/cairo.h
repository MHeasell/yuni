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
	class Cairo: public ISurface
	{
	public:
		Cairo();
		virtual ~Cairo();

	public:
		//! Initalize Cairo surface
		virtual bool initialize();

		//! Release surface
		virtual void release();

		//! Resize the surface
		virtual void resize(float width, float height);

		//! Refresh view
		virtual bool refresh();

		//! Choose a color to clear the screen with
		virtual void clearColor(const Color::RGB<uint8>& newColor);


	protected:
		//! Clear the screen to black
		virtual void clearScreen();


	protected:
		//! Cairo context
		cairo_t* pContext;

		//! Cairo surface
		cairo_surface_t* pSurface;


	}; // Cairo



} // namespace Surface
} // namespace Gfx
} // namespace Yuni


#endif // __YUNI_GFX_SURFACE_CAIRO_H__
