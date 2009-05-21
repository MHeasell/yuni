
#include "../system/windows.hdr.h"
#ifndef YUNI_OS_WINDOWS
#	include <stdlib.h>
#	include <unistd.h>
#else
#	include <direct.h>
#endif
#include <sys/stat.h>
#include <fstream>
#include "paths.h"



namespace Yuni
{
namespace Core
{
namespace Paths
{

	# ifdef YUNI_OS_WINDOWS
	const String::Char Separator = '\\';
	# else
	const String::Char Separator = '/';
	# endif

	//! The path-separator character according to the platform (stored in a string instead of a char)
	//! \ingroup PathsAndFiles
	# ifdef YUNI_OS_WINDOWS
	const String::Char* SeparatorAsString = "\\";
	# else
	const String::Char* SeparatorAsString = "/";
	# endif




	bool IsAbsolute(const String& p)
	{
		# ifdef YUNI_OS_WINDOWS
		return (p.empty() || (p.size() > 2 && ':' == p[1] && '\\' == p[2]));
		# else
		return (p.empty() || '/' == p.first());
		# endif
	}


	String CurrentDirectory()
	{
		char path[FILENAME_MAX];
		memset(path, 0, FILENAME_MAX);
		# ifdef YUNI_OS_WINDOWS
		const char* p = _getcwd(path, FILENAME_MAX - 2);
		# else
		const char* p = getcwd(path, FILENAME_MAX - 2);
		# endif
		return String(p);
	}


	void ExtractFilePath(String& out, const String& p, const bool systemDependant)
	{
		out.clear();
		const String::size_type pos = (systemDependant)
			? p.find_last_of(Separator)
			: p.find_last_of("\\/");
		if (String::npos != pos)
		{
			if (!pos)
				out.append(p[pos]);
			else
				out.append(p, 0, pos - 1);
		}
	}

	String ExtractFilePath(const String& p, const bool systemDependant)
	{
		if (p.notEmpty())
		{
			const String::size_type pos = (systemDependant)
				? p.find_last_of(Separator)
				: p.find_last_of("\\/");
			return (String::npos == pos) ? String() : String(p, 0, pos + 1);
		}
		return String();
	}



	String ExtractFileName(const String& p, const bool systemDependant)
	{
		if (p.notEmpty())
		{
			const String::size_type pos = (systemDependant)
				? p.find_last_of(Separator)
				: p.find_last_of("\\/");
			return (String::npos == pos) ? p : String(p, pos + 1);
		}
		return String();
	}

	void ExtractFileName(String::List& p, const bool systemDependant)
	{
		String tmp;
		for (String::List::iterator i = p.begin(); i != p.end(); i++)
		{
			tmp.assign(ExtractFileName(*i, systemDependant));
			*i = tmp;
		}
	}

	void ExtractFileName(String::Vector& p, const bool systemDependant)
	{
		String tmp;
		for (String::Vector::iterator i = p.begin(); i != p.end(); i++)
		{
			tmp.assign(ExtractFileName(*i, systemDependant));
			*i = tmp;
		}
	}


	String ExtractFileNameWithoutExtension(const String& p)
	{
		String::size_type pos = p.find_last_of(Separator);
		String::size_type n = p.find_last_of('.');
		if (String::npos == n && String::npos == pos)
			return p;
		if (n == pos)
			return String();
		if (n == String::npos && n > pos + 1)
		{
			if (String::npos == pos)
				return p;
			return p.substr(pos + 1);
		}
		if (pos == String::npos)
			return p.substr(0, n);
		return p.substr(pos + 1, n - pos - 1);
	}



	String ExtractFileExt(const String& s)
	{
		String::size_type n = s.find_last_of(".\\/");
		if (n == String::npos || '.' != s[n])
			return String();
		return String(s, n);
	}


	bool Exists(const String& p)
	{
		if (p.empty())
			return false;
		# ifdef YUNI_OS_WINDOWS
		// ugly workaround with stat under Windows
		// FIXME: Find a better way to find driver letters
		if (p.size() == 2 && ':' == p[1])
			return true;
		# endif

		# ifdef YUNI_OS_WINDOWS
		struct _stat s;
		if ('\\' == p.last())
		{
			return (_stat(String(p, p.size() - 1).c_str(), &s) == 0);
		}
		return (_stat(p.c_str(), &s) == 0);
		# else
		printf("mmmmmmmmmmmmmmmmdddddddddddddddddddddddddddddddd \n");
		struct stat s;
		return (stat(p.c_str(), &s) == 0);
		# endif
	}

	bool MakeDir(const String& p)
	{
		if (p.empty())
			return true;
		String::Vector parts;
		p.explode(parts, Separator, false);
		String pth;
		pth.reserve(p.size());

		for (String::Vector::const_iterator i = parts.begin(); i != parts.end(); ++i)
		{
			pth += *i;
			# ifndef YUNI_OS_WINDOWS
			pth += Separator;
			# endif
			if (!Exists(pth))
			{
				# ifdef YUNI_OS_WINDOWS
				if (_mkdir(pth.c_str()))
				# else
				if (mkdir(pth.c_str(), 01755))
				# endif
				{
					// Impossible to create the folder
					return false;
				}
			}
			# ifdef YUNI_OS_WINDOWS
			pth += Separator;
			# endif
		}
		return true;
	}



} // namespace Paths
} // namespace Core
} // namespace Yuni

