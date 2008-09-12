
#include <yuni/yuni.h>
#include <yuni/application/gfx3d.h>
#include <iostream>


//
// Our own application class
// To make it a simple console application,
// we have it inherit Yuni::Application::Gfx3D.
//
class HelloWorld : public Yuni::Application::Gfx3D
{
public:
	// Our constructor
	HelloWorld(int argc, char* argv[])
		:Yuni::Application::Gfx3D(argc, argv)
	{}

	virtual ~HelloWorld()
	{}

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
