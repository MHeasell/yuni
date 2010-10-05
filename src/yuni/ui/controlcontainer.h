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
		IControlContainer();

		/*!
		** \brief Constructor with dimensions
		*/
		IControlContainer(float width, float height);

		/*!
		** \brief Full constructor
		*/
		IControlContainer(float x, float y, float width, float height);

		/*!
		** \brief Full constructor
		*/
		template<class T>
		IControlContainer(const Point2D<T>& pos, float width, float height);

		//! Virtual destructor
		virtual ~IControlContainer();
		//@}


		//! \name Add / remove children
		//@{
		void add(IControl::Ptr& child);
		IControlContainer& operator += (IControl::Ptr& child);
		IControlContainer& operator << (IControl::Ptr& child);

		void remove(IControl::ID child);
		void remove(IControl::Ptr& child);
		IControlContainer& operator -= (IComponent::ID id);
		IControlContainer& operator -= (IControl::Ptr& child);
		//@}


	protected:
		//! \name Methods
		//@{
		/*!
		** \brief Resize the window
		**
		** This is implementation-dependent
		*/
		virtual void resizeWL(float& newWidth, float& newHeight);
		//@}

	private:
		//! Children controls
		IControl::Map pChildren;

	}; // class IControlContainer





} // namespace UI
} // namespace Yuni

# include "controlcontainer.hxx"

#endif // __YUNI_UI_CONTROL_CONTAINER_H__
