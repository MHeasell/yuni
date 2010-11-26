#ifndef __YUNI_PRIVATE_UI_LOCAL_SURFACE_CAIRO_H__
# define __YUNI_PRIVATE_UI_LOCAL_SURFACE_CAIRO_H__

# include "../../../gfx/api/cairo.h"
# include "surface.h"

namespace Yuni
{
namespace Private
{
namespace UI
{
namespace Local
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

		//! Choose a color to clear the screen with (defaults to red)
		virtual void clearColor(const Yuni::Color::RGB<float>& newColor);

		//! Choose a color with alpha to clear the screen with (defaults to red)
		virtual void clearColor(const Yuni::Color::RGBA<float>& newColor);


	protected:
		//! Clear the screen to a given color
		virtual void clearScreen();

		//! Clear only a given rectangle to a given color
		virtual void clearRectangle(float left, float top, float width, float height);


	protected:
		//! Cairo context
		cairo_t* pContext;

		//! Cairo surface
		cairo_surface_t* pSurface;

		//! Color used for clearing the screen
		Yuni::Color::RGBA<float> pClearColor;

	}; // class Cairo



} // namespace Surface
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni


# include "cairo.hxx"


#endif // __YUNI_PRIVATE_UI_LOCAL_SURFACE_CAIRO_H__
