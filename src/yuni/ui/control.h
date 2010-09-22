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
	template<class T,                                                // The original type
		template<class> class TP     = Policy::ObjectLevelLockable,  // The threading policy
		>
	class IControl : public IComponent<T, TP>
	{
	public:
		//! Smart pointer
		typedef SmartPtr<IControl> Ptr;
		//! Vector of controls
		typedef std::vector<IControl> Vector;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Empty constructor
		*/
		IControl() : IComponent()
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
		template<typename T, typename U>
		IControl(T x, U y, unsigned int width, unsigned int height)
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
