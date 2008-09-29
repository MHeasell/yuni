
# include "../../yuni.h"
# include "window.h"



namespace Yuni
{
namespace Gfx
{
namespace UI
{

	Window::Window(const SharedPtr<Control>& prnt)
		:Control(prnt), pCaption()
	{}

	Window::~Window()
	{
		if (pState != csDestroying)
			onBeforeDestruction();
		clear();
	}


	String Window::caption()
	{
		MutexLocker locker(pMutex);
		return pCaption;
	}

	void Window::caption(const String& c)
	{
		pMutex.lock();
		pCaption = c;
		internalInvalidate();
		pMutex.unlock();
	}

	
	bool Window::onBeforeDestructionWL()
	{
		return Control::onBeforeDestructionWL();
	}


} // namespace UI
} // namespace Gfx
} // namespace Yuni

