#ifndef __YUNI_APPLICATION_ABSTRACT_H__
# define __YUNI_APPLICATION_ABSTRACT_H__

# include "../yuni.h"
# include "../misc/string.h"


namespace Yuni
{
namespace Application
{


	class YUNI_EXPORT Abstract
	{
	public:
		/*!
		** \brief Get the global instance of the application
		*/
		static Abstract* Instance();

	public:
		//! \name Constructor & Destructor
		//@{
		//! Constructor
		Abstract(int argc, char* argv[]);
		//! Destructor
		virtual ~Abstract();
		//@}

		/*!
		** \brief Get if the application should stop as soon as possible
		*/
		bool terminated() const {return pTerminated;}
		/*!
		** \brief Indicate that the application should stop as soon as possible
		**
		** \param ex The new exit code value
		*/
		void terminate(const sint8 ex = 0) {pTerminated = true; pExitCode = ex;}

		/*!
		** \brief Get the full filename of the application
		*/
		const String& exeName() const {return pExeName;}

		/*!
		** \brief Get the root folder of the application
		*/
		const String& rootFolder() const {return pRootFolder;}

		/*!
		** \brief Get the exit code to use
		*/
		sint8 exitCode() const {return pExitCode;}

	private:
		/*!
		** \brief Parse the command line
		** \return True to stop the application
		*/
		bool parseCommandLine(int argc, char* argv[]);

	private:
		//! Indicates if the application should stop as soon as possible
		bool pTerminated;
		//! The full filename of the application
		String pExeName;
		//! The root folder of the application
		String pRootFolder;
		//! Exit code
		sint8 pExitCode;

	}; // class Application::Abstract






} // namespace Application
} // namespace Yuni


#endif // __YUNI_APPLICATION_ABSTRACT_H__
