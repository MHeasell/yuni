#ifndef __YUNI_APPLICATION_CONSOLE_H__
# define __YUNI_APPLICATION_CONSOLE_H__

# include <yuni/application/abstract.h>



namespace Yuni
{
namespace Application
{

    class Console : public Application::Abstract
    {
    public:
        /*!
        ** \brief Get the global instance of the console application
        */
        static Console& Instance();

    public:
        Console(int argc, char* argv[]);
        virtual ~Console();

    }; // class Application::Console



} // namespace Application
} // namespace Yuni

#endif // __YUNI_APPLICATION_CONSOLE_H__
