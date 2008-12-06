
#include "../../system/windows.hdr.h"
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
namespace Paths
{
	



	bool IsAbsolute(const String& p)
	{
		# ifdef YUNI_OS_WINDOWS
		return (p.empty() || (p.size() > 2 && ':' == p[1] && '\\' == p[2]));
		# else
		return (p.empty() || '/' == p[0]);
		# endif
	}
	

	String CurrentDirectory()
	{
		# ifdef YUNI_OS_WINDOWS
		char* c = _getcwd(NULL, 0);
		# else
		char* c = getcwd(NULL, 0);
		# endif
		if (NULL != c)
		{
			String ret(c);
			free(c);
			return String(ret);
		}
		return String();
	}


	String ExtractFilePath(const String& p, const bool systemDependant)
	{
		String::Vector parts;
		if (systemDependant)
			p.split(parts, SeparatorAsString, false);
		else
			p.split(parts, "\\/", false);
		
		String ret;
		String::Vector::size_type n = parts.size();
		--n;
		for (String::Vector::size_type i = 0; i != n; ++i)
		{
			if (parts[i] != ".")
				ret << parts[i] << Separator;
		}
		return ret;
	}

	String ExtractFileName(const String& p, const bool systemDependant)
	{
		String::size_type pos;
		if (systemDependant)
			pos = p.find_last_of(Separator);
		else
			pos = p.find_last_of("\\/");
		if (String::npos == pos)
			return p;
		return p.substr(pos + 1);
	}

	void ExtractFileName(String::List& p, const bool systemDependant)
	{
		for (String::List::iterator i = p.begin(); i != p.end(); i++)
			*i = ExtractFileName( *i, systemDependant );
	}

	void ExtractFileName(String::Vector& p, const bool systemDependant)
	{
		for (String::Vector::iterator i = p.begin(); i != p.end(); i++)
			*i = ExtractFileName( *i, systemDependant );
	}

	String ExtractFileNameWithoutExtension(const String& p)
	{
		String::size_type pos = p.find_last_of(Separator);
		String::size_type n = p.find_last_of('.');
		if (String::npos == n && String::npos == pos)
			return p;
		if (n == pos)
			return "";
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
			return "";
		return String(s, n).toLower();
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
		struct _stat s;
		if ('\\' != p[p.size() -1])
			return (_stat(p.c_str(), &s) == 0);
		return (_stat(String(p, 0, p.size() - 1).c_str(), &s) == 0);
		# else
		struct stat s;
		return (stat(p.c_str(), &s) == 0);
		# endif
	}

	bool MakeDir(const String& p)
	{
		if (p.empty())
			return true;
		String::Vector parts;
		p.split(parts, SeparatorAsString, false);
		String pth;

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
} // namespace TA3D

