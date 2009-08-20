
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
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>



#ifndef S_ISDIR
#	define S_ISDIR(mode) ( (mode & S_IFMT) == S_IFDIR)
#endif


/* Make lstat work even with -ansi mode - and under Windows */
#ifdef ANT_WINDOWS
#	define YUNI_INTERNAL_LSTAT(path, sb) stat(path, sb)
#else
#	define YUNI_INTERNAL_LSTAT(path, sb) stat(path, sb)
#endif



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


	String ExtractFileNameWithoutExtension(const String& p, const bool systemDependant)
	{
		String::size_type pos = (systemDependant)
			? p.find_last_of(Separator)
			: p.find_last_of("\\/");
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



	String ExtractFileExt(const String& s, String::CharCase option)
	{
		String::size_type n = s.find_last_of(".\\/");
		if (n == String::npos || '.' != s[n])
			return String();
		return (String::soIgnoreCase == option) ? String(s, n).toLower() : String(s, n);
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
		struct stat s;
		return (stat(p.c_str(), &s) == 0);
		# endif
	}


	bool MakeDir(const char path[], unsigned int mode)
	{
		if (NULL == path || '\0' == *path)
			return true;

		char buffer[FILENAME_MAX];
		strncpy(buffer, path, sizeof(buffer));
		char* pt = buffer;
		char tmp;
		while (1)
		{
			if ('\\' == *pt || '/' == *pt || '\0' == *pt)
			{
				tmp = *pt;
				*pt = '\0';
				if ('\0' != buffer[0] && '\0' != buffer[1] && '\0' != buffer[2])
				{
					# ifdef YUNI_OS_WINDOWS
					(void)mode; // to avoid a compiler warning
					if (mkdir(buffer) < 0 && errno != EEXIST && errno != EISDIR && errno != ENOSYS)
					# else
					if (mkdir(buffer, mode) < 0 && errno != EEXIST && errno != EISDIR && errno != ENOSYS)
					# endif
					{
						return false;
					}
				}
				if ('\0' == tmp)
					break;
				*pt = tmp;
			}
			++pt;
		}
		return true;
	}



	String MakeAbsolute(const String& p)
	{
		return MakeAbsolute(p, CurrentDirectory());
	}

	String MakeAbsolute(const String& p, const String& currentDirectory)
	{
		if (Core::Paths::IsAbsolute(p))
			return p;
		String ret = currentDirectory;
		ret << Separator << p;
		ret.removeTrailingSlash();
		return ret;
	}


	namespace
	{
		bool RmDirInternal(const char path[])
		{
			DIR* dp;
			struct dirent* ep;
			char buffer[FILENAME_MAX];
			struct stat st;

			if (NULL != (dp = opendir(path)))
			{
				while (NULL != (ep = readdir(dp)))
				{
					sprintf(buffer, "%s/%s", path, ep->d_name);
					if (0 == stat(buffer, &st))
					{
						if (S_ISDIR(st.st_mode))
						{
							if (strcmp(".", (ep->d_name)) != 0 && strcmp("..", (ep->d_name)) != 0)
							{
								if (!RmDirInternal(buffer))
									return false;
								if (rmdir(buffer))
									return false;
							}
						}
						else
							unlink(buffer);
					}
				}
				(void)closedir(dp);
			}
			return (0 == rmdir(path));
		}

	} // anonymous namespace



	bool RmDir(const char path[])
	{
		return (NULL == path || '\0' == *path)
			? true : RmDirInternal(path);
	}


	bool RecursiveCopy(const char* src, const char* dst)
	{
		DIR *dirp;
		struct dirent *dp;
		struct stat sb;
		char buf[FILENAME_MAX];
		int fd, fd2;
		mode_t mode;

		if (YUNI_INTERNAL_LSTAT(src, &sb))
			return 0;

		/* src is a file */
		if (!S_ISDIR((mode = sb.st_mode)))
		{
			if (!YUNI_INTERNAL_LSTAT(dst, &sb) && S_ISDIR(sb.st_mode))
			{
				const char *p = strrchr(src, '/');
				/* src => dst/src */
				sprintf(buf, "%s/%s", dst, (p?p+1:src));

				RecursiveCopy(src, buf);
				return 1;
			}

			//LogNotice("Copying `%s`", ShortPath(src, buf, 60));
			/* src => dst */
			if ((fd = open(src, O_RDONLY)) < 0)
				return 0;

			if ((fd2 = open(dst, O_CREAT|O_TRUNC|O_WRONLY, mode & 0777)) < 0)
			{
				close(fd);
				return 0;
			}

			size_t len, len2;
			while ((len = read(fd, buf, FILENAME_MAX)) > 0)
			{
				while (len && (len2 = write(fd2, buf, len)) > 0)
					len -= len2;
			}
			close(fd);
			close(fd2);

			return 1;
		}

		/* src is a directory */

		if (YUNI_INTERNAL_LSTAT(dst, &sb))
		{
			if (!MakeDir(dst))
				return 0;
		}
		else
		{
			/* if dst already exists and it's a file, try to remove it */
			if (!S_ISDIR(sb.st_mode))
			{
				if (remove(dst) || !MakeDir(dst))
					return false;
			}
		}

		if ((dirp = opendir(src)) == NULL)
			return false;

		char buf2[FILENAME_MAX];
		while ((dp = readdir(dirp)) != NULL)
		{
			/* do not copy hidden files */
			if (dp->d_name[0] == '.')
				continue;
			sprintf(buf, "%s/%s", src, dp->d_name);
			sprintf(buf2, "%s/%s", dst, dp->d_name);
			RecursiveCopy(buf, buf2);
		}
		closedir(dirp);

		return true;
	}



} // namespace Paths
} // namespace Core
} // namespace Yuni

