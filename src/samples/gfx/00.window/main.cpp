
#include <yuni/yuni.h>
#include <yuni/ui/ui.h>
#include <yuni/application/gfx3d.h>


using namespace Yuni;


class SampleApp : public Application::Gfx3D
{
public:
	SampleApp(int argc, char* argv[])
		// Propagate the command line arguments to the application
		: Application::Gfx3D(argc, argv)
	{}


private:
	// Overridden from Application::Gfx3D
	virtual void onBeforeCreateDevice()
	{
		// Set the application title
		title("Sample application");

		// Set the UI
		UI::Desktop::Ptr ui = createUI();
		desktop = ui;

		// Create a device that uses Cairo rendering
		Gfx::Device::Ptr newDevice = new Gfx::Device();
		newDevice->type(Gfx::Device::Cairo);
		reset(newDevice);
	}


	// Overridden from Application::Gfx3D
	virtual void onAfterCreateDevice(const bool success)
	{
		// Check for success
		if (!success)
		{
			// Complain
			std::cerr << "Oh my god, device creation failed !" << std::endl;
		}
		// No need to force application termination here, the program will exit on its own
	}


	UI::Desktop::Ptr createUI() const
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

};

int main(int argc, char* argv[])
{
	SampleApp app(argc, argv);
	app.execute();
	return app.exitCode();
}
