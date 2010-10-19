#ifndef __YUNI_UI_CONTROL_H__
# define __YUNI_UI_CONTROL_H__

# include "../yuni.h"
# include <vector>
# include <map>
# include "../thread/policy.h"
# include "../core/smartptr.h"
# include "component.h"

namespace Yuni
{
namespace UI
{

	//! Forward declaration
	class IControlContainer;


	/*!
	** \brief Base class for all UI controls (viewable components)
	*/
	class IControl : public IComponent
	{
	public:
		//! Smart pointer
		typedef IComponent::SmartPtrInfo<IControl>::Type Ptr;
		//! Vector of controls
		typedef std::vector<Ptr> Vector;
		//! Map of controls
		typedef std::map<IComponent::ID, Ptr> Map;
		//! Sorted (by depth in UI tree) map of controls
		typedef std::map<size_t, Map> DepthSortedMap;

		//! Threading Policy
		typedef IComponent::ThreadingPolicy ThreadingPolicy;


	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Empty constructor
		*/
		IControl();

		/*!
		** \brief Constructor with parent
		*/
		IControl(IControl::Ptr parent);

		/*!
		** \brief Constructor with dimensions
		*/
		IControl(float width, float height);

		/*!
		** \brief Constructor with dimensions and parent
		*/
		IControl(IControl::Ptr parent, float width, float height);

		/*!
		** \brief Full constructor
		*/
		IControl(float x, float y, float width, float height);

		/*!
		** \brief Full constructor with parent
		*/
		IControl(IControl::Ptr parent, float x, float y, float width, float height);

		/*!
		** \brief Full constructor
		*/
		template<typename T>
		IControl(Point2D<T>& pos, float width, float height);

		/*!
		** \brief Full constructor with parent
		*/
		template<class T>
		IControl(IControl::Ptr parent, const Point2D<T>& pos, float width, float height);


		//! Virtual destructor
		virtual ~IControl();
		//@}


		//! Create a new locally unique ID, asking the parent for it.
		virtual IComponent::ID createIdentifierWL() const;

		//! Get the parent
		IControl::Ptr parent() const;

		//! Set the parent
		void parent(IControl::Ptr newParent);

		//! Get the children
		const IControl::Map& children() const;

		//! Is there a parent ?
		bool hasParent() const;

		//! Depth in the UI tree, 0 if root.
		unsigned int depth() const;

		//! Catch the focus
		virtual void focus() {}

		//! Enable / disable the control
		void enabled(bool e);
		bool enabled() const;

		// Set visibility of the control
		void visible(bool e);
		bool visible() const;

	protected:
		//! Set the parent (without locking)
		virtual void parentWL(const IControl::Ptr& newParent);

		//! Detach from the tree
		virtual void detachWL();

		//! Add a child
		virtual void addChildWL(const IControl::Ptr& child);
		//! Remove a child
		virtual bool removeChildWL(const IControl::Ptr& child);


	protected:
		/*!
		** \brief Parent control. Null by default
		**
		** A normal pointer is used here, because the reference count is held by the
		** object itself and it would bring a circular reference if the smart pointer
		** were used.
		*/
		IControlContainer* pParent;

		/*!
		** \brief Children controls
		**
		** Always empty for controls that are not control containers.
		*/
		IControl::Map pChildren;

		//! Depth in the UI tree : 0 if no parent, parent level + 1 otherwise
		unsigned int pDepth;

	}; // class IControl




} // namespace UI
} // namespace Yuni

# include "control.hxx"

#endif // __YUNI_UI_CONTROL_H__
