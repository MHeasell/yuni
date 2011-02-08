#ifndef __YUNI_UI_LOCAL_STYLE_H__
# define __YUNI_UI_LOCAL_STYLE_H__

namespace Yuni
{
namespace Private
{
namespace UI
{
namespace Local
{


	enum WindowStyle
	{
		wsNone = 0,
		wsModal = 1,
		wsToolWindow = 2,
		wsResizeable = 4,
		wsMinimizable = 8,
		wsMaximizable = 16,
		wsFormMovable = 32,
		wsNoBorder = 64,
		wsNoCaption = 128,
		wsNoCloseButton = 256,
	};



	typedef RGB<float>  Color;


} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni

#endif // __YUNI_UI_LOCAL_STYLE_H__
