
#include <yuni/yuni.h>
#include <yuni/application/console.h>
#include <iostream>


/*!
** \brief Our own application class
**
** To make it a simple console application,
** we have it inherit Yuni::Application::Console.
*/
class HelloWorld : public Yuni::Application::Console
{
public:
	//! Constructor
	HelloWorld(int argc, char* argv[])
		:Yuni::Application::Console(argc, argv)
	{}

	//! Destructor
	virtual ~HelloWorld()
	{}

	//! Overload onExecute() to implement our own behaviour
	virtual void onExecute()
	{
		std::cout << "Hello world" << std::endl;
	}
};



int main(int argc, char* argv[])
{
	// Instanciate our app, feeding it the console arguments
	HelloWorld app(argc, argv);

	// Run the onExecute() method to launch the app
	app.onExecute();

	// Exit the app
	return app.exitCode();
}
