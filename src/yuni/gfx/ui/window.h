#ifndef __YUNI_GFX_UI_WINDOW_H__
# define __YUNI_GFX_UI_WINDOW_H__


namespace Yuni
{
namespace Gfx
{
namespace UI
{


	class Window : public Control
	{
	public:
		Window(const SharedPtr<Window>& prnt);
		~Window();

		String caption();
		void caption(const String& c);
	
	};


} // namespace UI
} // namespace Gfx
} // namespace Yuni


#endif // __YUNI_GFX_UI_WINDOW_H__
