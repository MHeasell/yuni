#ifndef __YUNI_APPLICATION_AAPPLICATION_H__
# define __YUNI_APPLICATION_AAPPLICATION_H__

# include "../yuni.h"
# include "../thread/policy.h"
# include "../core/getopt.h"
# include "../core/getopt/parser.h"


namespace Yuni
{
namespace Application
{


	class AApplication : public Policy::ObjectLevelLockable<AApplication>
	{
	public:
		//! The Threading Policy
		typedef Policy::ObjectLevelLockable<AApplication>  ThreadingPolicy;
		//! Pointer
		typedef AApplication* Ptr;
		//! Path
		typedef StringBase<char, 1024> PathType;

	public:
		/*!
		** \brief Get the global instance of the application
		*/
		static AApplication::Ptr Instance();


	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Constructor
		*/
		AApplication(int argc, char* argv[]);
		//! Destructor
		virtual ~AApplication();
		//@}


		//! \name Paths & Filenames
		//@{
		/*!
		** \brief The absolute filename of the application
		*/
		const PathType& exeName() const;

		/*!
		** \brief The absolute root folder of the application
		*/
		const PathType& rootFolder() const;
		//@}


		//! \name Exit status
		//@{
		/*!
		** \brief Get if the application should stop as soon as possible
		*/
		bool terminated() const;

		/*!
		** \brief Indicate that the application should stop as soon as possible
		**
		** \param ex The new exit code value
		*/
		void terminate(const int ex = 0);

		/*!
		** \brief Get the exit code to use
		*/
		int exitCode() const;
		//@}


		//! \name Execute
		//@{
		/*!
		** \brief Execute the application
		*/
		void execute();
		//@}


		/*!
		** \brief Default command line options
		**
		** ReImplement this method to configure your own command line options.
		** \param parser A GetOpt parser
		** \param argc The number of arguments
		** \param argv A null-terminated list of arguments (in UTF8)
		*/
		virtual void arguments(int argc, char** argv);

		virtual void onExecute() = 0;

	private:
		//! The private default constructor
		AApplication() {}
		//! The private copy constructor
		AApplication(const AApplication&);
		//! The private copy operator
		AApplication& operator = (const AApplication&);

	private:
		//! The global instance
		static AApplication::Ptr pGlobalInstance;

	private:
		//! Indicates if the application should stop as soon as possible
		ThreadingPolicy::Volatile<bool>::Type pTerminated;
		//! The full filename of the application
		PathType pExeName;
		//! The root folder of the application
		PathType pRootFolder;
		//! Exit code
		int pExitCode;

	}; // class AApplication






} // namespace Application
} // namespace Yuni

# include "application.hxx"

#endif // __YUNI_APPLICATION_AAPPLICATION_H__
