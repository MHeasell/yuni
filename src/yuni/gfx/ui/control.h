#ifndef __YUNI_GFX_UI_CONTROL_H__
# define __YUNI_GFX_UI_CONTROL_H__

# include <utility>
# include "../../yuni.h"
# include "component.h"
# include "../rect2D.h"
# include "../point2D.h"
# include "../../threads/mutex.h"


# define YUNI_GFX_UI_BORDER_SPACE_MAX  3.0f


namespace Yuni
{
namespace Gfx
{
namespace UI
{



	/*!
	** \brief Units that can be used to positionate/resize UI controls
	*/
	enum Unit
	{
		//! The standard unit
		unStandard,
		//! Percent
		unPercent
	};


	/*!
	** \brief Control (Visual component)
	*/
	class Control : public Component
	{
	public:
		//! Vector of components
		typedef std::vector< SharedPtr<Control> >  Vector;
		//! List of components
		typedef std::list< SharedPtr<Control> >  List;


		/*!
		** \brief Anchor
		*/
		class Anchor
		{
		public:
			friend class Control;
			enum Type { akLeft = 0, akTop, akRight, akBottom, akEnd };

		public:
			//! \name Constructor & Destructor
			//@{
			/*!
			** \brief Constructor
			*/
			Anchor() : /*pOwner(o), */ pSibling(), pUnit(unPercent), pValue(0.0f) {}
			//! Destructor
			~Anchor() {}
			//@}

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

		}; // class Anchor



	public:
		//! \name Constructor
		//@{

		/*!
		** \brief Default Constructor
		*/
		Control();

		/*!
		** \brief Constructor
		*/
		template<class C> Control(const SharedPtr<C>& prnt);

		//! Destructor
		virtual ~Control();

		//@}


		//! \name Parent
		//@{

		/*!
		** \brief Parent of this component
		*/
		SharedPtr<Control> parent() {return pParent;}

		/*!
		** \brief Assign a new parent
		*/
		bool parent(const SharedPtr<Control>& newParent);

		/*!
		** \brief Detach the component from its parent
		**
		** As this component will no longer belong to any another component, it won't be
		** drawn if it is a visual component. It would be like if the component would not exist.
		*/
		void detachFromParent();

		//@}


		//! \name Layout
		//@{

		/*!
		** \brief All anchors
		*/
		Anchor anchors[Anchor::akEnd];

		//! Get Autosize
		bool autosize();
		//! Set autosize
		void autosize(const bool a);

		/*!
		** \brief Get the bounds values
		*/
		Rect2D<float> bounds();
		/*!
		** \brief Reset the position and the size from bounds values
		*/
		void bounds(Rect2D<float> r);

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


		//! \name Z-Order
		//@{
		//! Send the component to the back
		void sendToBack();
		//! Send the component to the front
		void bringToFront();
		//@}


		//! \name Children
		//@{

		/*!
		** \brief Delete all children
		*/
		void clear();

		//! Get the count of children
		uint32 childrenCount();

		/*!
		** \brief Get a child according its index
		**
		** it is safe to use a out of bounds value. The result will not be valid, that's all.
		**
		** \return A reference to the component, null if it does not exist
		*/
		SharedPtr<Control> child(const uint32 indx);
		/*!
		** \brief Try to find a child according its pointer address
		**
		** \param[in,out] out The component if found, unchanged otherwise
		** \param toFind The pointer to find
		** \param recursive True to Iterate all sub-children
		** \return True if the component was found, false otherwise
		*/
		bool findChildFromPtr(SharedPtr<Control>& out, const void* toFind, const bool recursive = true);

		/*!
		** \brief Try to find a child according its pointer address
		**
		** In this case, we don't really care of the component itself. We are only interrested in
		** if it exists or not.
		**
		** \param toFind The pointer to find
		** \param recursive True to Iterate all sub-children
		** \return True if the component was found, false otherwise
		*/
		bool existsChildFromPtr(const void* toFind, const bool recursive = true);

		/*!
		** \brief Try to find a child according its name
		**
		** \param[in,out] out The component if found, unchanged otherwise
		** \param toFind The pointer to find
		** \param recursive True to Iterate all sub-children
		** \return True if the component was found, false otherwise
		*/
		bool findChildFromName(SharedPtr<Control>& out, const String& toFind, const bool recursive = true);

		//@}


		//! \name Operators
		//@{

		//! Get a child component from its index (null if not found)
		SharedPtr<Control> operator [] (const uint32 indx) {return child(indx);}
		//! Get a child component from its name (null if not foud)
		SharedPtr<Control> operator [] (const String& nm);

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
		/*!
		** \brief Try to find a child according its pointer address (not thread-safe)
		**
		** \param[in,out] out The component if found, unchanged otherwise
		** \param toFind The pointer to find
		** \param recursive True to Iterate all sub-children
		** \return True if the component was found, false otherwise
		*/
		bool findChildFromPtrWL(SharedPtr<Control>& out, const void* toFind, const bool recursive);

		/*!
		** \brief Try to find a child according its pointer address (not thread-safe)
		**
		** In this case, we don't really care of the component itself. We are only interrested in
		** if it exists or not.
		**
		** \param toFind The pointer to find
		** \param recursive True to Iterate all sub-children
		** \return True if the component was found, false otherwise
		*/
		bool existsChildFromPtrWL(const void* toFind, const bool recursive);

		/*!
		** \brief Try to find a child according its name (not thread-safe)
		**
		** \param[in,out] out The component if found, unchanged otherwise
		** \param toFind The pointer to find
		** \param recursive True to Iterate all sub-children
		** \return True if the component was found, false otherwise
		*/
		bool findChildFromStringWL(SharedPtr<Control>& out, const String& toFind, const bool recursive);

		/*!
		** \brief Detach the component from its parent (not thread-safe)
		**
		** As this component will no longer belong to any another component, it won't be
		** drawn if it is a visual component. It would be like if the component would not exist.
		*/
		void detachFromParentWL();

		/*!
		** \brief Invalidate the control
		**
		** If the control is invalidate, that means its caches are invalidate
		** and the control should be redrawn as soon as possible
		*/
		void invalidateWL();

		/*!
		** \brief Event: Called before the component is really destroyed
		** 
		** \return True to continue to broadcast the event to derived classes
		*/
		virtual bool onBeforeDestructionWL();

		/*!
		** \brief Broadcast the event onBeforeDestruction to all children (not thread safe)
		*/
		void broadcastOnBeforeDestructionWL();



		/*!
		** \brief Update internals cached variables (not thread-safe)
		*/
		void internalCachePosSizeUpdateWL();

		void beginUpdateWL();

		void endUpdateWL();

		
	protected:
		//! All children
		Control::Vector pChildren;
		
		//! Parent of this component
		SharedPtr<Control> pParent;

		//! Top-left coordinates
		Point2D<float> pPosition;
		//! Width of the control
		Point2D<float> pSize;

		//! Visible
		bool pVisible;
		//! Enabled
		bool pEnabled;

		//! Is invalidate. If true, that would mean the control should be redrawn as soon as possible
		bool pIsInvalidate;

		//! The cached values for the bounds
		Rect2D<float> pCacheBounds;

	private:
		/*!
		** \brief Send a child component to the back
		** \param c The component
		*/
		void internalChildSendToBack(Control* c);
		/*!
		** \brief Send a child component to the back
		** \param c The component
		*/
		void internalChildBringToFront(Control* c);

		/*!
		** \brief Add a new child in the list
		** \param nc The new child
		*/
		void internalRegisterChild(Control* nc);
		/*!
		** \brief Add a new child in the list
		** \param nc The new child
		*/
		void internalRegisterChild(const SharedPtr<Control>& nc);
		/*!
		** \brief Remove a child from the list according its pointer address
		** \param nc Child to remove
		*/
		void internalUnregisterChild(Control* nc);


	private:
		//!
		bool pAutosize;
		//!
		int pUpdateSessionRefCount;
		//!
		bool pIsInvalidated;

	}; // class Control




} // namespace UI
} // namespace Gfx
} // namespace Yuni


# include "control.hxx"

#endif // __YUNI_GFX_UI_CONTROL_H__
