
#include <yuni/yuni.h>
#include <yuni/ui/control.h>
#include <yuni/ui/window.h>
#include <yuni/core/smartptr.h>

using namespace Yuni;


int main(void)
{
	SharedPtr<Gfx::UI::Control> nullPtr(NULL);
	SmartPtr<Gfx::UI::Window> wnd(new Gfx::UI::Window(nullPtr));
	wnd->beginUpdate();
	wnd->bounds(Gfx::Rect2D<float>(1.0f, 1.0f, 10.f, 4.0f));
	wnd->endUpdate();
	return 0;
}
