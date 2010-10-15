#ifndef __YUNI_UI_BUTTON_HXX__
# define __YUNI_UI_BUTTON_HXX__


namespace Yuni
{
namespace UI
{


	inline Button::Button()
	{
		pClass = "button";
	}


	inline Button::Button(const IControl::Ptr& parent)
			: IControl(parent)
	{
		pClass = "button";
	}


	template<class StringT>
	inline Button::Button(const StringT& label)
		: pLabel(label)
	{
		pClass = "button";
	}


	template<class StringT>
	inline Button::Button(const IControl::Ptr& parent, const StringT& label)
		: IControl(parent), pLabel(label)
	{
		pClass = "button";
	}


	template<class StringT>
	inline Button::Button(const StringT& label, float width, float height)
		: IControl(width, height), pLabel(label)
	{
		pClass = "button";
	}


	template<class StringT>
	inline Button::Button(const IControl::Ptr& parent, const StringT& label, float width,
		float height)
		: IControl(parent, width, height), pLabel(label)
	{
		pClass = "button";
	}


	template<class StringT>
	inline Button::Button(const StringT& label, float x, float y, float width, float height)
		: IControl(x, y, width, height), pLabel(label)
	{
		pClass = "button";
	}


	template<class StringT>
	inline Button::Button(const IControl::Ptr& parent, const StringT& label, float x, float y,
		float width, float height)
		: IControl(parent, x, y, width, height), pLabel(label)
	{
		pClass = "button";
	}


	template<class StringT, class T>
	inline Button::Button(const StringT& label, Point2D<T>& pos, float width, float height)
		: IControl(pos, width, height), pLabel(label)
	{
		pClass = "button";
	}


	template<class StringT, class T>
	inline Button::Button(const IControl::Ptr& parent, const StringT& label, Point2D<T>& pos,
		float width, float height)
		: IControl(parent, pos, width, height), pLabel(label)
	{
		pClass = "button";
	}


	inline Button::~Button()
	{
		destroyBoundEvents();
	}



} // namespace UI
} // namespace Yuni


#endif // __YUNI_UI_BUTTON_HXX__
