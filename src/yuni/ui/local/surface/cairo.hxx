
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



	inline Cairo::Cairo()
		: pContext(NULL), pSurface(NULL)
	{
	}


	inline Cairo::~Cairo()
	{
	}


	inline void Cairo::resize(float, float)
	{
	}


	inline void Cairo::clearColor(const Yuni::Color::RGB<float>& c)
	{
		pClearColor = c;
	}


	inline void Cairo::clearColor(const Yuni::Color::RGBA<float>& c)
	{
		pClearColor = c;
	}


	inline void Cairo::clearScreen()
	{
		// Save current operator settings
		cairo_save(pContext);
		// Set the color
		cairo_set_source_rgba(pContext, pClearColor.red, pClearColor.green, pClearColor.blue,
			pClearColor.alpha);
		// Change the operator from OVER to SOURCE
		cairo_set_operator(pContext, CAIRO_OPERATOR_SOURCE);
		// Paint the whole surface
		cairo_paint(pContext);
		// Restore settings
		cairo_restore(pContext);
	}

	inline void Cairo::clearRectangle(float left, float top, float width, float height)
	{
		// Save current operator settings
		cairo_save(pContext);
		// Set the color
		cairo_set_source_rgba(pContext, pClearColor.red, pClearColor.green, pClearColor.blue,
			pClearColor.alpha);
		// Change the operator from OVER to SOURCE
		cairo_set_operator(pContext, CAIRO_OPERATOR_SOURCE);
		// Define a Rectangle path
		cairo_rectangle(pContext, left, top, width, height);
		// Fill the path
		cairo_fill(pContext);
		// Restore settings
		cairo_restore(pContext);
	}



} // namespace Surface
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni
