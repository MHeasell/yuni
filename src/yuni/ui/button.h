#ifndef __YUNI_UI_BUTTON_H__
# define __YUNI_UI_BUTTON_H__

# include "../yuni.h"
# include <map>
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
	template<template<class> class TP = Policy::ObjectLevelLockable>
	class Button : public IControl<Button, TP>
	{
	public:
		//! Smart pointer
		typedef SmartPtr<Button> Ptr;

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
		Button(String label) : pLabel(label)
		{}

		/*!
		** \brief Constructor with dimensions
		*/
		Button(String label, unsigned int width, unsigned int height)
			: IControl(width, height)
		{}

		/*!
		** \brief Full constructor
		*/
		template<typename T, typename U>
		Button(String label, T x, U y, unsigned int width, unsigned int height)
			: IControl(x, y, width, height)
		{}

		/*!
		** \brief Full constructor
		*/
		template<typename T>
		Button(String label, Point2D<T>& pos, unsigned int width, unsigned int height)
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
