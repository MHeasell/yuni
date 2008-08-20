#ifndef __YUNI_APPLICATION_CONSOLE_H__
# define __YUNI_APPLICATION_CONSOLE_H__

# include <yuni/application/abstract.h>



namespace Yuni
{
namespace Application
{


    /*! \class Yuni::Application::Console
    **
    ** \brief Console Application
    **
    ** \code
    ** class HelloWorld
    ** {
    ** public:
    **      HelloWorld(nt argc, char* argv[]) : Yuni::Application::Console(argc, argv) {}
    **      ~HelloWorld() {}
    **
    **      virtual void execute()
    **      {
    **          std::cout << "Hello world" << std::endl;
    **      }
    ** };
    **
    ** int main(int argc, char* argv[])
    ** {
    **      HelloWorld app(argc, argv);
    **      app.execute();
    **      return app.exitCode();
    ** }
    ** \endcode
    */
    class Console : public Application::Abstract
    {
    public:
        /*!
        ** \brief Get the global instance of the console application
        */
        static Console* Instance() {return dynamic_cast<Console*>(Abstract::Instance());}

    public:
        //! \name Constructor & Destructor
        //@{
        /*!
        ** \brief Constructor
        ** \param argc The number of arguments
        ** \param argv All arguments
        */
        Console(int argc, char* argv[]);
        //! Destructor
        virtual ~Console();
        //@}

        /*!
        ** \brief The main routine for the console application
        */
        virtual void execute() = 0;

    }; // class Application::Console



} // namespace Application
} // namespace Yuni

#endif // __YUNI_APPLICATION_CONSOLE_H__
