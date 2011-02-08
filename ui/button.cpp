
#include "button.h"

namespace Yuni
{
namespace UI
{

	inline Button::Button()
	{
		pClass = "button";
	}


	Button::Button(const IControl::Ptr& parent)
		: IControl(parent)
	{
		pClass = "button";
	}


	inline Button::~Button()
	{
		destroyBoundEvents();
	}



} // namespace UI
} // namespace Yuni

