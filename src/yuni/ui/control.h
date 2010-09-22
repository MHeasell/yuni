#ifndef __YUNI_UI_CONTROL_H__
# define __YUNI_UI_CONTROL_H__

# include "../yuni.h"
# include <vector>
# include "../thread/policy.h"
# include "../core/smartptr.h"
# include "component.h"

namespace Yuni
{
namespace UI
{

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

		//! Threading Policy
		typedef IComponent::ThreadingPolicy ThreadingPolicy;


	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Empty constructor
		*/
		IControl()
		{}

		/*!
		** \brief Constructor with dimensions
		*/
		IControl(unsigned int width, unsigned int height)
			: IComponent(width, height)
		{}

		/*!
		** \brief Full constructor
		*/
		IControl(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
			: IComponent(x, y, width, height)
		{}

		/*!
		** \brief Full constructor
		*/
		template<typename T>
		IControl(Point2D<T>& pos, unsigned int width, unsigned int height)
			: IComponent(pos, width, height)
		{}

		//! Virtual destructor
		virtual ~IControl() {}
		//@}


	}; // class IControl






} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_CONTROL_H__
