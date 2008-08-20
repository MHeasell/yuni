
#include <yuni/yuni.h>
#include <yuni/application/console.h>
#include <iostream>


//
// Our own application class
// To make it a simple console application,
// we have it inherit Yuni::Application::Console.
//
class HelloWorld : public Yuni::Application::Console
{
public:
    // Our constructor
    HelloWorld(int argc, char* argv[])
        :Yuni::Application::Console(argc, argv)
    {}

    virtual ~HelloWorld()
    {}

    // Overload execute() to implement our own behaviour
    virtual void execute()
    {
        std::cout << "Hello world" << std::endl;
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
