
#include "controller.h"


namespace Yuni
{
namespace Gfx
{
namespace UI
{

	Controller* Controller::Instance()
	{
		static Controller singleton;
		return &singleton;
	}


	Controller::Controller()
		:pRoot(new Root())
	{
		pRoot->name("root");
	}

	Controller::~Controller()
	{
	}

	void Controller::clearAllUIControls()
	{
		pMutex.lock();
		pRoot->clear();
		pMutex.unlock();
	}

	SharedPtr<Window> Controller::createNewWindow()
	{
		MutexLocker locker(pMutex);
		// Reference to the new window
		//SharedPtr<Window> wnd(new Window(pRoot));
		return SharedPtr<Window>();
	}


} // namespace UI
} // namespace Gfx
} // namespace Yuni

