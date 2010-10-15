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
		Button();

		/*!
		** \brief Constructor with parent
		*/
		Button(const IControl::Ptr& parent);

		/*!
		** \brief Constructor with label
		*/
		template<class StringT>
		explicit Button(const StringT& label);

		/*!
		** \brief Constructor with parent and label
		*/
		template<class StringT>
		Button(const IControl::Ptr& parent, const StringT& label);

		/*!
		** \brief Constructor with dimensions
		*/
		template<class StringT>
		Button(const StringT& label, float width, float height);

		/*!
		** \brief Constructor with parent and dimensions
		*/
		template<class StringT>
		Button(const IControl::Ptr& parent, const StringT& label, float width, float height);

		/*!
		** \brief Full constructor
		*/
		template<class StringT>
		Button(const StringT& label, float x, float y, float width, float height);

		/*!
		** \brief Full constructor with parent
		*/
		template<class StringT>
		Button(const IControl::Ptr& parent, const StringT& label, float x, float y,
			float width, float height);

		/*!
		** \brief Full constructor
		*/
		template<class StringT, class T>
		Button(const StringT& label, Point2D<T>& pos, float width, float height);

		/*!
		** \brief Full constructor with parent
		*/
		template<class StringT, class T>
		Button(const IControl::Ptr& parent, const StringT& label, Point2D<T>& pos,
			float width, float height);


		//! Virtual destructor
		virtual ~Button();
		//@}

	protected:
		//! Text label on the button
		String pLabel;

	}; // class Button





} // namespace UI
} // namespace Yuni

# include "button.hxx"

#endif // __YUNI_UI_BUTTON_H__
