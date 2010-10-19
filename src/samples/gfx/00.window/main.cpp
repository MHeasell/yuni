
#include <yuni/yuni.h>
#include <yuni/ui/ui.h>
#include <yuni/application/gfx3d.h>


using namespace Yuni;


UI::Desktop::Ptr createUI()
{
	UI::Application::Ptr editor = new
		UI::Application("com.example.my.3d.editor", "3D Editor");
	//UI::Application::Ptr mygame = new
	//	UI::Application("com.example.my.appl.id", "My Game");

	UI::Window::Ptr wndMain = new UI::Window("3D Editor - Main window");
	//UI::Window::Ptr wndMain = new UI::Window(nullptr,
	//	"mainform", "3D Editor - Main window");
	UI::Button::Ptr btn = new UI::Button(wndMain.pointer(), "Ok");
	(*editor) += wndMain;

	// UI::Window::Ptr wndGame = new UI::Window("formID", nullptr,
	//	"My Game - Another window");
	// UI::Label::Ptr lbl = new UI::Label("lbl", wndGame, "Lorem ipsum");
	// lbl->align = UI::alClient;
	//(*mygame) += wndGame;

	UI::Desktop::Ptr newDesktop = new UI::Desktop();
	(*newDesktop) += editor;
	//(*newDesktop) += mygame;

	return newDesktop;
}



int main(int argc, char* argv[])
{
	UI::IQueueService* ws = new UI::WindowSystem::Native();
	ws->desktop = createUI();
	ws->start();
	return 0;
}
