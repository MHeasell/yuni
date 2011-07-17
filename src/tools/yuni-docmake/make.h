#ifndef __YUNI_DOCMAKE_MAKE_H__
# define __YUNI_DOCMAKE_MAKE_H__

# include <yuni/yuni.h>
# include <yuni/core/string.h>
# include "sqlite/sqlite3.h"


class Make 
{
public:
	/*!
	** \brief Default constructor
	*/
	Make();

	bool parseCommandLine(int argc, char** argv);

	void findAllSourceFiles();

public:
	Yuni::String input;
	Yuni::String htdocs;
	static unsigned int nbJobs;
	bool printVersion;
	static bool debug;
	static bool verbose;
	static bool clean;
	static bool shortUrl;

}; // class Make



#endif // __YUNI_DOCMAKE_MAKE_H__
