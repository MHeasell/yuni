#ifndef __LIBYUNI_CONFIG_VERSIONS_H__
# define __LIBYUNI_CONFIG_VERSIONS_H__

# define YUNI_NO_THREAD_SAFE // disabling thread-safety
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
namespace VersionInfo
{

	enum CompilerCompliant
	{
		gcc,
		visualstudio,
	};

	enum Mapping
	{
		mappingStandard,
		mappingSVNSources,
	};


	struct Settings
	{
	public:

	public:
		Settings()
			:supportOpenGL(false), supportDirectX(false)
		{}

		bool configFile(String::List& options, bool displayError) const;

		bool parserModulesOptions(String::List& options, bool displayError);

		bool moduleExists(const String& name) const;

	public:
		String compiler;
		Mapping mapping;
		String path;
		String compilationMode;
		String::List modules;
		bool supportOpenGL;
		bool supportDirectX;

		String::List includePath;
		String::List libPath;

		struct ModuleSettings
		{
		public:
			typedef std::map<String, bool> OptionMap;
		public:
			void merge(OptionMap& out, const OptionMap& with) const
			{
				const OptionMap::const_iterator end = with.end();
				for (OptionMap::const_iterator i = with.begin(); i != end; ++i)
					out[i->first] = true;
			}

		public:
			OptionMap cxxFlags;
			OptionMap includes;
			OptionMap frameworks;
			OptionMap libs;
			OptionMap libIncludes;
			OptionMap defines;
			String::List dependencies;
		};
		std::map<String, ModuleSettings> moduleSettings;
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

		VersionInfo::Settings* selected();

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
