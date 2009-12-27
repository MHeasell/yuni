#ifndef __YUNI_APPLICATION_CONSOLE_H__
# define __YUNI_APPLICATION_CONSOLE_H__

# include "application.h"



namespace Yuni
{
namespace Application
{


	/*!
	** \brief Console Application
	**
	** \code
	** class HelloWorld : public Yuni::Application::Console
	** {
	** public:
	**	  HelloWorld(nt argc, char* argv[]) : Yuni::Application::Console(argc, argv) {}
	**	  virtual ~HelloWorld() {}
	**
	**	  virtual void execute()
	**	  {
	**		  std::cout << "Hello world" << std::endl;
	**	  }
	** };
	**
	** int main(int argc, char* argv[])
	** {
	**	  HelloWorld app(argc, argv);
	**	  app.execute();
	**	  return app.exitCode();
	** }
	** \endcode
	*/
	class Console : public Application::AApplication
	{
	public:
		//! Ancestor type
		typedef Application::AApplication  AncestorType;
		//! The Threading Policy
		typedef AncestorType::ThreadingPolicy ThreadingPolicy;
		//! Pointer
		typedef Console* Ptr;

	public:
		/*!
		** \brief Get the global instance of the console application
		*/
		static Console::Ptr Instance() {return dynamic_cast<Console*>(AApplication::Instance());}

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
		virtual void onExecute() = 0;

	}; // class Application::Console






} // namespace Application
} // namespace Yuni

#endif // __YUNI_APPLICATION_CONSOLE_H__
