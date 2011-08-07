#ifndef __YUNI_DOCMAKE_MAKE_H__
# define __YUNI_DOCMAKE_MAKE_H__

# include <yuni/yuni.h>
# include <yuni/core/string.h>
# include "sqlite/sqlite3.h"


namespace Yuni
{
namespace Tool
{
namespace DocMake
{


	class Program
	{
	public:
		/*!
		** \brief Default constructor
		*/
		Program();

		bool parseCommandLine(int argc, char** argv);

		void findAllSourceFiles();

	public:
		//! The input folder
		static String input;
		//! The htdocs folder
		static String htdocs;
		//! The index filename
		static String indexFilename;
		static unsigned int nbJobs;
		bool printVersion;
		static bool debug;
		static bool verbose;
		static bool clean;
		static bool shortUrl;

	}; // class Make





} // namespace DocMake
} // namespace Tool
} // namespace Yuni

#endif // __YUNI_DOCMAKE_MAKE_H__
