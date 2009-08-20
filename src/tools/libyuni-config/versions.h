#ifndef __LIBYUNI_CONFIG_VERSIONS_H__
# define __LIBYUNI_CONFIG_VERSIONS_H__

# include <yuni/yuni.h>
# include <yuni/core/string.h>
# include <yuni/core/version/version.h>
# include <map>


# ifdef YUNI_OS_WINDOWS
#	define YUNI_LIBCONFIG_DEFAULT_COMPILER "vs9"
# else
#	if defined(YUNI_OS_SUNOS) || defined(YUNI_OS_SOLARIS)
#		define YUNI_LIBCONFIG_DEFAULT_COMPILER "suncc"
#	else
#		define YUNI_LIBCONFIG_DEFAULT_COMPILER "gcc"
#	endif
# endif



namespace Yuni
{
namespace LibConfig
{

namespace Compiler
{
	struct Settings
	{
		struct flags
		{
			//! Cxx flags
			String::List cxx;
			String::List defines;
			String::List libs;
		};
		struct path
		{
			String::List include;
			String::List libs;
		};

		std::map<String,String> additionalFiles;
	};

} // namespace Compiler

namespace VersionInfo
{

	enum Mapping
	{
		mappingStandard,
		mappingSVNSources,
	};


	struct Settings
	{
	public:
		Settings()
			:supportOpenGL(false), supportDirectX(false)
		{}

		String compiler;
		Mapping mapping;
		String path;
		String compilationMode;
		String::List modules;
		bool supportOpenGL;
		bool supportDirectX;

		String::List includePath;
		String::List libPath;

		//! Compiler options for a given module and a given compiler name
		std::map<String, std::map<String, Compiler::Settings> > compilation;
	};


	class List
	{
	public:
		typedef std::map<Version, VersionInfo::Settings>  InternalList;
		typedef InternalList::reverse_iterator iterator;
		typedef InternalList::const_reverse_iterator const_iterator;

	public:
		List() {}

		const String& compiler() const {return pCompiler;}
		void compiler(const String& c) {pCompiler = c;}
		
		void checkRootFolder(const String& root);

		void findFromPrefixes(const String::List& prefix);

		void print();

		void printWithInfos();

	private:
		void loadFromPath(const String& path);

	private:
		String pCompiler;
		InternalList pList;
	};


} // namespace VersionInfo
} // namespace LibConfig
} // namespace Yuni

#endif // __LIBYUNI_CONFIG_VERSIONS_H__
