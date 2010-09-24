#ifndef __YUNI_UI_CONTROL_CONTAINER_H__
# define __YUNI_UI_CONTROL_CONTAINER_H__

# include "../yuni.h"
# include "../core/smartptr.h"
# include "../thread/policy.h"
# include "control.h"


namespace Yuni
{
namespace UI
{

	/*!
	** \brief Base class for UI controls that can contain other controls
	**
	** Works as a tree, using COM reference counted policy for smart pointers.
	*/
	class IControlContainer : public IControl
	{
	public:
		//! Smart pointer
		typedef IComponent::SmartPtrInfo<IControlContainer>::Type Ptr;
		//! Vector of controls
		typedef std::vector<Ptr> Vector;

		//! Threading Policy
		typedef IComponent::ThreadingPolicy ThreadingPolicy;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Empty constructor
		*/
		IControlContainer()
		{}

		/*!
		** \brief Constructor with dimensions
		*/
		IControlContainer(float width, float height)
			: IControl(width, height)
		{}

		/*!
		** \brief Full constructor
		*/
		IControlContainer(float x, float y, float width, float height)
			: IControl(x, y, width, height)
		{}

		/*!
		** \brief Full constructor
		*/
		template<typename T>
		IControlContainer(Point2D<T>& pos, float width, float height)
			: IControl(pos, width, height)
		{}

		//! Virtual destructor
		virtual ~IControlContainer() {}
		//@}


		//! \name Methods
		//@{
		/*!
		** \brief Resize the window
		**
		** This is implementation-dependent
		*/
		virtual void resize(float, float)
		{
			ThreadingPolicy::MutexLocker lock(*this);
			// TODO: Resize children to fit in the parent's new dimensions
		}
		//@}

	private:
		//! Children controls
		IControl::Vector pChildren;

	}; // class IComponent





} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_CONTROL_CONTAINER_H__
