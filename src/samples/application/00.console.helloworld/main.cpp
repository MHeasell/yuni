
#include <yuni/yuni.h>
#include <yuni/application/console.h>
#include <iostream>


//
// Our own application class
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

    virtual void execute()
    {
        std::cout << "Hello world" << std::endl;
    }
};



int main(int argc, char* argv[])
{
    // Our app
    HelloWorld app(argc, argv);

    // Run our app
    app.execute();

    // Exiting
    return app.exitCode();
}
