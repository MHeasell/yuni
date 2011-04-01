#ifndef __YUNI_UI_LOCAL_CONTROLS_SURFACE_H__
# define __YUNI_UI_LOCAL_CONTROLS_SURFACE_H__

# include "../../../yuni.h"
# include "../../../core/rect2D.h"


namespace Yuni
{
namespace Private
{
namespace UI
{
namespace Local
{

	/*!
	** \brief Abstract surface for rendering
	*/
    class Surface
	{
	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		Surface() {}
		//! Destructor
		virtual ~Surface() {}
		//@}

		//! Initialize the surface
		virtual bool initialize() = 0;

		//! Destroy the surface
		virtual void destroy() = 0;

		//! Refresh the surface
		virtual void refresh() = 0;

	protected:
		/*!
		** \brief Rectangle in which the surface is drawn
		**
		** \note Position is relative to parent
		*/
		Rect2D<float> pRect;

	}; // class Surface




} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni

#endif // __YUNI_UI_LOCAL_CONTROLS_SURFACE_H__
