
#include <yuni/yuni.h>
#include <yuni/application/gfx3d.h>
#include <yuni/gfx/engine.h>
#include <iostream>

using namespace Yuni;


/*!
** \brief Our own application class
**
** To make it a graphical application with 3D support,
** we have it inherit Yuni::Application::Gfx3D.
*/
class HelloWorld : public Application::Gfx3D
{
public:
	HelloWorld(int argc, char* argv[])
		:Application::Gfx3D(argc, argv)
	{
		// We connect our own method to the event
		Gfx::Engine::Instance()->onFPSChanged.connect(this, &HelloWorld::onFPSChanged);
	}

	virtual ~HelloWorld()
	{
		// It is advised to disconnect all events at this stage
		destroyingObserver();
	}

	void onFPSChanged(int fps)
	{
		// The FPS count has changed
		// We will set the application title according to the new value
		this->title(String() << "Hello World ! - " << fps << " fps");
	}
};



int main(int argc, char* argv[])
{
	// Instanciate our app, feeding it the console arguments
	HelloWorld app(argc, argv);

	// Run the execute() method to launch the app
	app.execute();

	// Exit the app
	return app.exitCode();
}
