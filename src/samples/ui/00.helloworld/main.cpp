
#include <yuni/yuni.h>
#include <yuni/gfx/ui/control.h>
#include <yuni/gfx/ui/window.h>

using namespace Yuni;


int main(void)
{
	SharedPtr<Gfx::UI::Window> wnd(new Gfx::UI::Window());
	/*
	wnd->beginUpdate();
	wnd->bounds(1.0f, 1.0f, 10.f, 4.0f);
	w*/nd->endUpdate();
	return 0;
}
