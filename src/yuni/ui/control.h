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
		// TODO use a smart pointer here to avoid race conditions
		IControl(IControlContainer* parent);

		/*!
		** \brief Constructor with dimensions
		*/
		IControl(float width, float height);

		/*!
		** \brief Constructor with dimensions and parent
		*/
		IControl(IControlContainer* parent, float width, float height);

		/*!
		** \brief Full constructor
		*/
		IControl(float x, float y, float width, float height);

		/*!
		** \brief Full constructor with parent
		*/
		// TODO use a smart pointer here to avoid race conditions
		IControl(IControlContainer* parent, float x, float y, float width, float height);

		/*!
		** \brief Full constructor
		*/
		template<typename T>
		IControl(Point2D<T>& pos, float width, float height);

		/*!
		** \brief Full constructor with parent
		*/
		template<class T>
		// TODO use a smart pointer here to avoid race conditions
		IControl(IControlContainer* parent, const Point2D<T>& pos, float width, float height);


		//! Virtual destructor
		virtual ~IControl();
		//@}


		//! Get the parent
		// TODO returns a smart pointer here to avoid race conditions
		IControlContainer* parent();

		//! Set the parent
		void parent(IControlContainer* newParent);

		//! Is there a parent ?
		bool hasParent() const;

		//! Depth in the UI tree, 0 if root.
		size_t depth() const;


	protected:
		//! Set the parent (without locking)
		// TODO use a smart pointer here to avoid race conditions
		void parentWL(IControlContainer* newParent);

	protected:
		/*!
		** \brief Parent component. Null by default
		**
		** A normal pointer is used here, because the reference count is held by the
		** object itself and it would bring a circular reference if the smart pointer
		** were used.
		*/
		IControlContainer* pParent;

		//! Depth in the UI tree : 0 if no parent, parent level + 1 otherwise
		size_t pDepth;

	}; // class IControl




} // namespace UI
} // namespace Yuni

# include "control.hxx"

#endif // __YUNI_UI_CONTROL_H__
