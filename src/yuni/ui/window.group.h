#ifndef __YUNI_GFX_UI_WINDOW_H__
# define __YUNI_GFX_UI_WINDOW_H__

# include "component.h"



namespace Yuni
{
namespace Gfx
{
namespace UI
{


	class WindowsGroup : public Component
	{
	public:
		WindowsGroup();
		~WindowsGroup();

		SharedPtr<Window> createNewWindow();
		/*!
		** \brief
		*/
		bool acquire(const SharedPtr<Window>& wnd);

	private:
		bool internalAcquire(const SharedPtr<Window>& wnd);
	};


} // namespace UI
} // namespace Gfx
} // namespace Yuni



#endif // __YUNI_GFX_UI_WINDOW_H__
