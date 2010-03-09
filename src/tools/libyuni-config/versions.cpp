
#include "versions.h"
#include <yuni/core/io/directory.h>
#include <yuni/core/io/file.h>


#define SEP Core::IO::Separator


namespace Yuni
{
namespace LibConfig
{
namespace VersionInfo
{


	void List::checkRootFolder(const String& root)
	{
		String yuniMarker;
		yuniMarker << root << SEP << "mark-for-yuni-sources";

		if (Core::IO::File::Exists(yuniMarker))
		{
			if (pOptDebug)
				std::cout << "[debug] found special marker `" << yuniMarker << "`" << std::endl;

			# ifdef YUNI_OS_WINDOWS
			loadFromPath(root + "\\..\\..\\..");
			# else
			loadFromPath(root + "/../../..");
			# endif
			return;
		}

		# ifdef YUNI_OS_WINDOWS
		// For dealing with the paths like 'Debug/libyuni-config.exe'
		if (Core::IO::File::Exists(String() << root << "\\..\\mark-for-yuni-sources"))
			loadFromPath(root + "\\..\\..\\..\\..");
		# endif
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

	void List::loadFromPath(const String& folder)
	{
		String path;
		Core::IO::Normalize(path, folder);
		if (pOptDebug)
			std::cout << "[debug] :: reading `" << path << "`" << std::endl;

		VersionInfo::Settings info;
		info.mapping = mappingStandard;
		String s(path);
		s << SEP << "yuni.version";
		if (!Core::IO::File::Exists(s))
		{
			s = path;
			s << SEP << "include" << SEP << "yuni" << SEP << "yuni.version";
			if (!Core::IO::File::Exists(s))
			{
				info.mapping = mappingSVNSources;
				s.clear() << path << SEP << "src/yuni/yuni.version";
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
				value.trim();
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
				{
					if (value.notEmpty())
						info.includePath.push_back(value);
				}
				if (key == "path.lib")
				{
					if (value.notEmpty())
						info.libPath.push_back(value);
				}
			}
			if (!version.null() && !info.modules.empty())
			{
				info.path = path;
				info.compiler = pCompiler;
				pList[version] = info;

				if (pOptDebug)
					std::cout << "[debug]  - found installation `" << path << "` (" << version << ")" << std::endl; 
			}
		}
	}


	void List::compiler(const String& c)
	{
		pCompiler = c;
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
				std::cout << "    modules : [core]";
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



	VersionInfo::Settings* List::selected()
	{
		if (pList.empty())
			return NULL;
		InternalList::iterator i = pList.begin();
		return &i->second;
	}



	bool Settings::configFile(String::List& options, bool displayError) const
	{
		if (compiler.empty())
		{
			if (displayError)
				std::cout << "Error: unknown compiler\n";
			return false;
		}
		String out;
		out << this->path << SEP;
		switch (mapping)
		{
			case mappingSVNSources:
				out << "src" << SEP << "yuni" << SEP;
				break;
			case mappingStandard:
				// Nothing to do
				break;
		}
		out << "yuni.config." << this->compiler;

		if (!Core::IO::File::Exists(out))
		{
			if (displayError)
				std::cout << "Error: impossible to open the config file '" << out << "'\n";
			return false;
		}
		if (!Core::IO::File::Load(options, out))
		{
			if (displayError)
				std::cout << "Error: Impossible to read '" << out << "'\n";
			return false;
		}
		return true;
	}



	bool Settings::parserModulesOptions(String::List& options, bool displayError)
	{
		// Cleanup if needed
		moduleSettings.clear();
		// End of the list
		const String::List::const_iterator end = options.end();
		// Key
		String key;
		// Value
		String value;
		// Module name
		String modName;
		// Group
		String group;
		// normalized path
		String norm;

		// The default compiler is gcc
		CompilerCompliant compliant = gcc;
		// Checking for Visual Studio
		if (compiler.notEmpty() && compiler.at(0) == 'v' && compiler.at(1) == 's')
			compliant = visualstudio;

		// For each entry in the ini file
		for (String::List::const_iterator i = options.begin(); i != end; ++i)
		{
			i->extractKeyValue(key, value);
			if (key.empty() || key.first() == '[')
				continue;
			value.trim();
			if (!value)
				continue;

			// Reset
			modName.clear();
			group.clear();

			// Splitting
			const String::Size p = key.find(':');
			if (p == String::npos)
				continue;
			group.assign(key, p);
			modName.assign(key, p + 1, key.size());
			if (!group || !modName)
				continue;

			SettingsPerModule& s = moduleSettings[modName];

			if (group == "path.include")
			{
				Core::IO::Normalize(norm, value);
				switch (compliant)
				{
					case gcc          : s.includes[String() << "-I" << norm] = true; break;
					case visualstudio : s.includes[String() << "/I" << norm] = true; break;
				}
				continue;
			}

			if (group == "lib,rawcommand")
			{
				s.libs[value] = true;
				continue;
			}

			if (group == "path.lib")
			{
				Core::IO::Normalize(norm, value);
				switch (compliant)
				{
					case gcc          : s.libIncludes[String() << "-L" << norm] = true; break;
					case visualstudio : s.libIncludes[String() << "/LIBPATH:" << norm] = true; break;
				}
				continue;
			}

			if (group == "lib")
			{
				Core::IO::Normalize(norm, value);
				switch (compliant)
				{
					case gcc          : s.libs[String() << "-l" << norm] = true; break;
					case visualstudio : s.libs[String() << norm] = true; break;
				}
				continue;
			}

			if (group == "cxxflag")
			{
				s.cxxFlags[value] = true;
				continue;
			}

			if (group == "define")
			{
				switch (compliant)
				{
					case gcc          : s.defines[String() << "-D" << value] = true; break;
					case visualstudio : s.defines[String() << "/D" << value] = true; break;
				}
				continue;
			}
			if (group == "dependency")
			{
				s.dependencies.push_back(value);
				continue;
			}

			if (group == "framework")
			{
				s.frameworks[String() << "-framework \"" << value << "\""] = true;
				continue;
			}

			if (displayError)
				std::cout << "Error: unknown key in the config file: '" << key << "'\n";
			return false;
		}
		return true;
	}



	void Settings::SettingsPerModule::merge(OptionMap& out, const OptionMap& with) const
	{
		const OptionMap::const_iterator end = with.end();
		for (OptionMap::const_iterator i = with.begin(); i != end; ++i)
			out[i->first] = true;
	}





} // namespace VersionInfo
} // namespace LibConfig
} // namespace Yuni

