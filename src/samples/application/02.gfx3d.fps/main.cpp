
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


#ifdef YUNI_OS_WINDOWS
int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, char* cmdLine, int)
{
	int argc;
	char** argv;

	char* arg;
	int index;
	int result;

	// Count the arguments
	argc = 1;
	arg  = cmdLine;
	while (arg[0] != 0)
	{
		while (arg[0] != 0 && arg[0] == ' ')
		{
			arg++;
		}

		if (arg[0] != 0)
		{
			argc++;
			while (arg[0] != 0 && arg[0] != ' ')
			{
				arg++;
			}
		}
	}

	// Tokenize the arguments
	argv = (char**)malloc(argc * sizeof(char*));
	arg = cmdLine;
	index = 1;
	while (arg[0] != 0)
	{
		while (arg[0] != 0 && arg[0] == ' ')
		{
			arg++;
		}

		if (arg[0] != 0)
		{
			argv[index] = arg;
			index++;
			while (arg[0] != 0 && arg[0] != ' ')
			{
				arg++;
			}
        
			if (arg[0] != 0)
			{
				arg[0] = 0;    
				arg++;
			}
		}
	}    

	// Put the program name into argv[0]
	char filename[_MAX_PATH];

	GetModuleFileName(NULL, filename, _MAX_PATH);
	argv[0] = filename;

	// Call the user specified main function    
	result = main(argc, argv);

	free(argv);
	return result;
}
#endif