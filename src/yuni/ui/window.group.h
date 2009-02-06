#ifndef __YUNI_GFX_UI_WINDOW_H__
# define __YUNI_GFX_UI_WINDOW_H__

# include "component.h"



namespace Yuni
{
namespace Gfx
{
namespace UI
{


	/*!
	** \brief
	** \ingroup ui
	**
	** \todo Work in progress
	*/
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
		/*!
		**
		*/
		bool internalAcquire(const SharedPtr<Window>& wnd);

	}; // class WindowsGroup





} // namespace UI
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_UI_WINDOW_H__
