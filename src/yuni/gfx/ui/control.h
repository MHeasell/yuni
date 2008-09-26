#ifndef __YUNI_GFX_UI_CONTROL_H__
# define __YUNI_GFX_UI_CONTROL_H__

# include <utility>
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

	enum Unit
	{
		unStandard,
		unPercent
	};


	/*!
	** \brief Control (Visual component)
	*/
	class Control : public Component
	{
	public:
		/*!
		** \brief Anchor
		*/
		class Anchor
		{
		public:
			friend class Control;
			enum Type { akLeft = 0, akTop, akRight, akBottom, akEnd };

		public:
			Anchor(Control* o) : pOwner(o), pSibling(), pUnit(unPercent), pValue(0.0f) {}
			~Anchor();

			//! Get the sibling
			SharedPtr<Control> sibling();
			//! Set the sibling
			template<class C> void sibling(const SharedPtr<C>& s);

			/*!
			** \brief Set the border space
			** \param v The value of the border space
			** \param u The unit of the border space value
			*/
			void borderSpace(const float v, const Unit& u = unPercent);
			//! Get the border space
			std::pair<float, Unit> borderSpace();

			//! Get the border space unit only
			Unit borderSpaceUnit();
			//! Set the border space unit only
			void borderSpaceUnit(const Unit& u);

			//! Get the border space value only
			float borderSpaceValue();
			//! Set the border space value only
			void borderSpaceValue(const float v);

		private:
			void resetSiblingWL();

		private:
			//! Mutex from
			Control* pOwner;
			//! 
			SharedPtr<Control> pSibling;
			//! Unit type
			Unit pUnit;
			//! 
			float pValue;
		};


	public:
		//! \name Constructor
		//@{

		/*!
		** \brief Constructor
		*/
		template<class C> Control(const SharedPtr<C>& prnt)
			:Component(prnt), pPosition(), pSize(50, 50), pScale(1.0f), pVisible(true),
			pEnabled(true), pIsInvalidate(true), pUpdateSessionRefCount(0), pIsInvalidated(false)
		{
			internalCachePosSizeUpdateWL();
		}

		//! Destructor
		virtual ~Control();

		/*!
		** \brief All anchors
		*/
		Anchor anchors[Anchor::akEnd];

		//@}

		//! \name Bounds
		//@{
		/*!
		** \brief Get the bounds values
		*/
		Rect2D<float> bounds();
		/*!
		** \brief Reset the position and the size from bounds values
		*/
		void bounds(Rect2D<float> r);
		//@}

		//! \name Point2D<float>
		//@{
		//! Get the current position
		Point2D<float> position();
		/*!
		** \brief Set the current position
		** \param np THe new position
		*/
		void position(const Point2D<float>& np);
		/*!
		** \brief Set the current position
		** \param x The new X-coordinate
		** \param y The new Y-coordinate
		*/
		void position(const float x, const float y);
		//@}

		//! \name Dimensions
		//@{
		//! Get the current dimension
		Point2D<float> dimensions();
		/*!
		** \brief Set the dimension
		**
		** \param w The new width of the control
		** \param h The new height of the control
		*/
		void dimensions(const float w, const float h);
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
		bool isVisible(const Rect2D<float>& limits);
		//! Set the visibility of the control
		void visible(const bool v);
		//@}



		//! \name Updates
		//@{

		/*!
		** \brief Begin an update of this component
		**
		** It helps to maintain performance by preventing the control (and its children)
		** from drawing until the EndUpdate method is called.
		**
		** \see endUpdate()
		*/
		void beginUpdate();

		/*!
		** \brief End an update of this component
		**
		** \see beginUpdate()
		*/
		void endUpdate();

		/*!
		** \brief Invalidate the state of the control
		**
		** If the control is invalidate, that means its caches are invalidate
		** and the control should be redrawn as soon as possible
		*/
		void invalidate();

		//@}


	protected:
		virtual bool onBeforeDestructionWL();
		virtual void invalidateWL();

		/*!
		** \brief Update internals cached variables (not thread-safe)
		*/
		void internalCachePosSizeUpdateWL();

		void beginUpdateWL();

		void endUpdateWL();

	protected:
		//! Top-left coordinates
		Point2D<float>  pPosition;
		//! Width of the control
		Point2D<float> pSize;
		//! Scale
		float pScale;
		//! Visible
		bool pVisible;
		//! Enabled
		bool pEnabled;
		//! Is invalidate. If true, that would mean the control should be redrawn as soon as possible
		bool pIsInvalidate;

		//! The cached values for the bounds
		Rect2D<float> pCacheBounds;

	private:
		int pUpdateSessionRefCount;
		bool pIsInvalidated;

	}; // class Control




} // namespace UI
} // namespace Gfx
} // namespace Yuni


# include "control.hxx"

#endif // __YUNI_GFX_UI_CONTROL_H__
