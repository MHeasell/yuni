
#include "../system/windows.hdr.h"
#include "file.h"
#ifndef YUNI_OS_WINDOWS
# include <dlfcn.h>
#endif
#include <stdio.h>
#include "../fs/paths.h"



#ifdef YUNI_OS_WINDOWS
# define YUNI_DYNLIB_DLOPEN(X)      ::LoadLibrary(TEXT(X))
#else
# define YUNI_DYNLIB_DLOPEN(X,M)    ::dlopen(X,M)
#endif

#ifdef YUNI_OS_WINDOWS
# define YUNI_DYNLIB_DLCLOSE(X)     ::FreeLibrary(X)
#else
# define YUNI_DYNLIB_DLCLOSE(X)     ::dlclose(X)
#endif

#ifdef YUNI_OS_WINDOWS
# define YUNI_DYNLIB_DLSYM(X, Y)    ::GetProcAddress(X,Y)
#else
# define YUNI_DYNLIB_DLSYM(X, Y)    ::dlsym(X,Y)
#endif


namespace Yuni
{
namespace DynamicLibrary
{


	// Implementation of the static variable
	const File::Handle File::NullHandle = NULL;



	void File::wrapperDlClose(const File::Handle h)
	{
		YUNI_DYNLIB_DLCLOSE(h);
	}


	Symbol::Handle File::wrapperDlSym(const File::Handle h, const char* name)
	{
		return (Symbol::Handle)(YUNI_DYNLIB_DLSYM(h, name));
	}



	namespace /* Anonymous namespace */
	{
		/*!
		** \brief Try to find a file from a list of paths, a filename and a prefix
		**
		** \internal The template parameter is only here to preserve compile-time type
		**  informations (it prevents against recomputing the length of the string
		**  or to allocate data if using a String). The class String has special
		**  template specializations for this kind of type (char[N])
		**
		** \param searchPaths List of paths where to look for the library
		** \param[out] s A temporary string, where to write the absolute filename
		** \param prefix The prefix to use for the filename
		** \return True if the filename in `s` exists and should be loaded, False otherwise
		**/
		template<typename P>
		inline bool FindExistingLibrary(const String::Vector& searchPaths, String& s, const String& filename, P prefix)
		{
			# define TEST_THEN_LOAD(EXT) \
				s.clear(); \
				s << (*i) << Toolbox::Paths::Separator << prefix << filename << EXT; \
				if (Toolbox::Paths::Exists(s)) \
					return true

			const String::Vector::const_iterator end = searchPaths.end();
			for (String::Vector::const_iterator i = searchPaths.begin(); i != end; ++i)
			{
				# ifdef YUNI_OS_DARWIN
				TEST_THEN_LOAD(".dylib");
				TEST_THEN_LOAD(".bundle");
				# endif

				# ifdef YUNI_OS_AIX
				TEST_THEN_LOAD(".a");
				# endif
				# ifdef YUNI_OS_HPUX
				TEST_THEN_LOAD(".sl");
				# endif

				# ifdef YUNI_OS_WINDOWS
				TEST_THEN_LOAD(".dll");
				# else
				TEST_THEN_LOAD(".so");
				# endif
			}
			return false;
			# undef TEST_THEN_LOAD
		}
	} // Anonymous namespace


	bool File::load(const String& filename, const File::Relocation r, const File::Visibility v)
	{
		// No filename
		if (!filename.empty())
		{
			// If the file name is absolute, there is no need for research
			if (Toolbox::Paths::IsAbsolute(filename))
				return loadFromRawFilename(filename.c_str(), r, v);

			// A temporary string, where to write the absolute filename
			String s;
			// Avoid multiple memory allocations
			s.reserve(FILENAME_MAX);

			// Search paths
			String::Vector searchPaths;

			// On the most OS, libraries have the prefix `lib`
			# ifndef YUNI_OS_WINDOWS
			if (FindExistingLibrary(searchPaths, s, filename, "lib"))
				return loadFromRawFilename(s.c_str(), r, v);
			# endif
			// But sometimes not
			if (FindExistingLibrary(searchPaths, s, filename, ""))
				return loadFromRawFilename(s.c_str(), r, v);
		}
		// Make sure the library has been unloaded
		// This unloading would have been done by `loadFromRawFilename()` if
		// something was found
		unload();
		// We have found nothing :(
		return false;

	}


	void File::unload()
	{
		if (loaded())
		{
			YUNI_DYNLIB_DLCLOSE(pHandle);
			pHandle = NullHandle;
			pFilename.clear();
		}
	}






	# ifdef YUNI_OS_WINDOWS

	// Specific implementation for the Windows platform
	bool File::loadFromRawFilename(const char* filename, const File::Relocation, const File::Visibility)
	{
		// Unload the library if already loaded
		unload();

		if (filename)
		{
			// Loading
			pHandle = YUNI_DYNLIB_DLOPEN(filename);
			if (NullHandle != pHandle)
			{
				pFilename = filename;
				return true;
			}
		}
		return false;
	}

	# else

	// Specific implementation for the Unix platforms
	bool File::loadFromRawFilename(const char* filename,
		const File::Relocation r,
		const File::Visibility v)
	{
		// Unload the library if already loaded
		unload();

		if (filename)
		{
			// The mode
			int mode = ((relocationLazy == r) ? RTLD_LAZY : RTLD_NOW);
			if (visibilityDefault != v)
				mode |= ((visibilityGlobal == v) ? RTLD_GLOBAL : RTLD_LOCAL);
			// Loading
			pHandle = YUNI_DYNLIB_DLOPEN(filename, mode);
			if (NullHandle != pHandle)
			{
				pFilename = filename;
				return true;
			}
		}
		return false;
	}

	# endif







} // namespace DynamicLibrary
} // namespace Yuni

