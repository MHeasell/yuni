#ifndef __YUNI_UI_BUTTON_H__
# define __YUNI_UI_BUTTON_H__

# include "../yuni.h"
# include <map>
# include "../thread/policy.h"
# include "../core/smartptr.h"
# include "../core/string.h"
# include "control.h"

namespace Yuni
{
namespace UI
{

	/*!
	** \brief Base class for all UI controls (viewable components)
	*/
	class Button : public IControl
	{
	public:
   		//! Smart pointer
		typedef IComponent::SmartPtrInfo<Button>::Type Ptr;
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
		Button()
		{}

		/*!
		** \brief Constructor with label
		*/
		template<class StringT>
		explicit Button(const StringT& label) : pLabel(label)
		{}

		/*!
		** \brief Constructor with dimensions
		*/
		template<class StringT>
		Button(const StringT& label, unsigned int width, unsigned int height)
			: IControl(width, height)
		{}

		/*!
		** \brief Full constructor
		*/
		template<class StringT>
		Button(const StringT& label, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
			: IControl(x, y, width, height)
		{}

		/*!
		** \brief Full constructor
		*/
		template<class StringT, class T>
		Button(const StringT& label, Point2D<T>& pos, unsigned int width, unsigned int height)
			: IControl(pos, width, height)
		{}

		//! Virtual destructor
		virtual ~Button() {}
		//@}

	protected:
		//! Text label on the button
		String pLabel;

	}; // class Button





} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_BUTTON_H__
