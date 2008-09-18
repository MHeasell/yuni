#ifndef __YUNI_GFX_UI_CONTROL_H__
# define __YUNI_GFX_UI_CONTROL_H__

# include "../../yuni.h"
# include "component.h"
# include "../rect2D.h"
# include "../point2D.h"


namespace Yuni
{
namespace Gfx
{
namespace UI
{


	class Control : public Component
	{
	public:
		//! \name Constructor
		//@{

		/*!
		** \brief
		*/
		template<class C> Control(const SharedPtr<C>& prnt)
			:Component(prnt), pLeft(20), pTop(20), pWidth(50), pHeight(50), pVisible(true),
			pEnabled(true), pIsInvalidated(true)
		{
			internalCachePosSizeUpdate();
		}

		//! Destructor
		virtual ~Control();

		//@}

		//! \name Bounds
		//@{

		/*!
		** \brief Get the bounds values
		*/
		Rect2D<int> bounds();

		/*!
		** \brief Reset the position and the size from bounds values
		*/
		void bounds(Rect2D<int> r);

		//@}

		//! \name Position
		//@{

		//! Get the current position
		Point2D<int> position();

		/*!
		** \brief Set the current position
		** \param np THe new position
		*/
		void position(const Point2D<int>& np);

		/*!
		** \brief Set the current position
		** \param x The new X-coordinate
		** \param y The new Y-coordinate
		*/
		void position(const int x, const int y);

		//@}

		//! \name Dimensions
		//@{
		//! Get the current dimension
		Point2D<int> dimensions();
		//! Set the dimension
		void dimensions(const int w, const int h);
		//@}

		//! \name Enable
		//@{
		//! Get if the control is enabled
		bool enabled();
		//! Set if the control is enabled
		void enabled(const bool e);
		//@}

		//! \name Visible
		//@{

		//! Get if the control should be visible (property)
		bool visible();

		//! Get if the control will be visible with a given rectangle
		bool isVisible(const Rect2D<int>& limits);

		//! Set the visibility of the control
		void visible(const bool v);

		//@}


		void invalidate();

	protected:
		void internalInvalidate();

	private:
		/*!
		** \brief Update internals cached variables (not thread-safe)
		*/
		void internalCachePosSizeUpdate();

	private:
		int pLeft;
		int pTop;
		int pWidth;
		int pHeight;
		bool pVisible;
		bool pEnabled;
		bool pIsInvalidated;

		Rect2D<int> pCacheBounds;

	}; // class Control




} // namespace UI
} // namespace Gfx
} // namespace Yuni


#endif // __YUNI_GFX_UI_CONTROL_H__
