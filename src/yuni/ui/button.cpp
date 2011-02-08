
#include "button.h"

namespace Yuni
{
namespace UI
{


	Button::Button()
	{
		pClass = "button";
	}


	Button::Button(const IControl::Ptr& parent)
		: IControl(parent)
	{
		pClass = "button";
	}


	Button::~Button()
	{
		destroyBoundEvents();
	}



} // namespace UI
} // namespace Yuni

