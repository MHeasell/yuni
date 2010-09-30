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
		//! Empty constructor
		Cairo();
		//! Virtual destructor
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
		virtual void clearColor(const Color::RGB<float>& newColor);

		//! Choose a color with alpha to clear the screen with
		virtual void clearColor(const Color::RGBA<float>& newColor);


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


# include "cairo.hxx"


#endif // __YUNI_GFX_SURFACE_CAIRO_H__
