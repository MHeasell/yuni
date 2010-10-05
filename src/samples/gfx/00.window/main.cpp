
#include <yuni/yuni.h>
#include <yuni/application/gfx3d.h>
#include <yuni/gfx/device.h>


using namespace Yuni;


class SampleApp : public Application::Gfx3D
{
public:
	SampleApp(int argc, char* argv[])
		: Application::Gfx3D(argc, argv)
	{
		// Get the engine
		Gfx::Engine* engine = Gfx::Engine::Instance();
		// Set the application title
		engine->applicationTitle("Sample application");
		// Set the UI
		UI::Desktop::Ptr ui = CreateUI();
		engine->desktop(ui);
		// Create a device that uses Cairo rendering
		Gfx::Device::Ptr dev = new Gfx::Device();
		dev->type(Gfx::Device::Cairo);
		// Reset engine with our new device
		engine->reset(dev);
	}

	UI::Desktop::Ptr CreateUI() const
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

		UI::Desktop::Ptr desktop = new UI::Desktop();
		(*desktop) += editor;
		//(*desktop) += mygame;

		return desktop;
	}

};

int main(int argc, char* argv[])
{
	SampleApp app(argc, argv);
	app.execute();
	return app.exitCode();
}
