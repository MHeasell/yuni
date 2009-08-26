
#define YUNI_NO_THREAD_SAFE // disabling thread-safety
#include "versions.h"
#include <yuni/core/io/directory.h>
#include <yuni/core/io/file.h>


namespace Yuni
{
namespace LibConfig
{
namespace VersionInfo
{


	void List::checkRootFolder(const String& root)
	{
		if (Core::IO::File::Exists(String() << root << Core::IO::Separator << "mark-for-yuni-sources"))
		{
			# ifdef YUNI_OS_WINDOWS
			loadFromPath(root + "\\..\\..\\..");
			# else
			loadFromPath(root + "/../../..");
			# endif
		}
	}


	void List::findFromPrefixes(const String::List& prefix)
	{
		if (!prefix.empty())
		{
			const String::List::const_iterator end = prefix.end();
			for (String::List::const_iterator i = prefix.begin(); i != end; ++i)
				loadFromPath(*i);
		}
	}

	void List::loadFromPath(const String& path)
	{
		VersionInfo::Settings info;
		info.mapping = mappingStandard;
		String s(path);
		s << Core::IO::Separator << "yuni.version";
		if (!Core::IO::File::Exists(s))
		{
			s = path;
			s << Core::IO::Separator << "include" << Core::IO::Separator
				<< "yuni" << Core::IO::Separator << "yuni.version";
			if (!Core::IO::File::Exists(s))
			{
				info.mapping = mappingSVNSources;
				s = path;
				s << Core::IO::Separator << "src/yuni/yuni.version";
				if (!Core::IO::File::Exists(s))
					return;
			}
		}
		String::List list;
		if (Core::IO::File::Load(list, s, false) && !list.empty())
		{
			String key;
			String value;

			Version version;
			const String::List::const_iterator end = list.end();
			for (String::List::const_iterator i = list.begin(); i != end; ++i)
			{
				i->extractKeyValue(key, value);
				if (key.empty() || key == "[")
					continue;
				if (key == "version.hi")
					version.hi = value.to<unsigned int>();
				if (key == "version.lo")
					version.lo = value.to<unsigned int>();
				if (key == "version.rev")
					version.revision = value.to<unsigned int>();
				if (key == "version.target")
					info.compilationMode = value;
				if (key == "modules.available")
					value.explode(info.modules, ";\"', \t", false);
				if (key == "support.opengl")
					info.supportOpenGL = value.to<bool>();
				if (key == "support.directx")
					info.supportDirectX = value.to<bool>();
				if (key == "redirect")
					loadFromPath(value);
				if (key == "path.include")
					info.includePath.push_back(value);
				if (key == "path.lib")
					info.libPath.push_back(value);
			}
			if (!version.null() && !info.modules.empty())
			{
				info.path = path;
				info.compiler = pCompiler;
				pList[version] = info;
			}
		}
	}


	void List::print()
	{
		if (!pList.empty())
		{
			const const_iterator end = pList.rend();
			for (const_iterator i = pList.rbegin(); i != end; ++i)
			{
				std::cout << i->first;
				if (i->second.mapping == mappingSVNSources)
					std::cout << " (svn-sources)";
				std::cout << "\n";
			}
		}
	}

	void List::printWithInfos()
	{
		if (!pList.empty())
		{
			const const_iterator end = pList.rend();
			for (const_iterator i = pList.rbegin(); i != end; ++i)
			{
				std::cout << i->first << " " << i->second.compilationMode;
				if (i->second.mapping == mappingSVNSources)
					std::cout << " (svn-sources)";
				std::cout << "\n";
				std::cout << "    path    : " << i->second.path << "\n";
				std::cout << "    modules :";
				const String::List::const_iterator mend = i->second.modules.end();
				for (String::List::const_iterator j = i->second.modules.begin(); j != mend; ++j)
					std::cout << " " << *j;
				std::cout << "\n";
				std::cout << "    OpenGL  : " << (i->second.supportOpenGL ? "Yes" : "No") << "\n";
				# ifdef YUNI_OS_WINDOWS
				std::cout << "    DirectX : " << (i->second.supportDirectX ? "Yes" : "No") << "\n";
				# endif
			}
		}
	}



} // namespace VersionInfo
} // namespace LibConfig
} // namespace Yuni

