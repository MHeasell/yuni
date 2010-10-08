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
		IControl(IControlContainer* parent, const Point2D<T>& pos, float width, float height);


		//! Virtual destructor
		virtual ~IControl();
		//@}


		//! Get the parent
		IControlContainer* parent();

		//! Set the parent
		void parent(IControlContainer* newParent);

		//! Is there a parent ?
		bool hasParent() const;

		//! Depth in the UI tree, 0 if root.
		size_t depth() const;


	protected:
		/*!
		** \brief Parent component. Null by default
		**
		** A normal pointer is used here, because we do not have the full
		** class implementation. This is not a problem, because if the
		** parent is destroyed, the child will be destroyed too so the
		** pointer will not be dangling.
		*/
		IControlContainer* pParent;

		/*!
		** \brief Depth in the UI tree : 0 if no parent, parent level + 1 otherwise
		*/
		size_t pDepth;


	}; // class IControl




} // namespace UI
} // namespace Yuni

# include "control.hxx"

#endif // __YUNI_UI_CONTROL_H__
