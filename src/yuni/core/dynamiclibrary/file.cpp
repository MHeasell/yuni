
#include "../system/windows.hdr.h"
#include "file.h"
#ifndef YUNI_OS_WINDOWS
# include <dlfcn.h>
#else
# include "../../core/string/wstring.h"
#endif
#include <stdio.h>
#include "../../io/file.h"
#include "../../io/directory.h"



#ifdef YUNI_OS_WINDOWS
# define YUNI_DYNLIB_DLOPEN(X)      ::LoadLibraryW(X)
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



	namespace // Anonymous namespace
	{

		/*!
		** \brief Try to find a file from a single path, a filename and a prefix
		**
		** \param[out] s A temporary string, where to write the absolute filename
		** \param prefix The prefix to use for the filename
		** \return True if the filename in `s` exists and should be loaded, False otherwise
		**/
		template<class StringT>
		inline bool FindLibraryFile(StringT& out, /*const StringT2& path,*/ const StringAdapter& filename, const char* prefix)
		{
			# define TEST_THEN_LOAD(EXT) \
				out.clear(); \
				/*if (!path.empty()) */ \
					/*out << path << IO::Separator; */ \
				out << prefix << filename << EXT; \
				if (IO::File::Exists(out)) \
					return true

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

			return false;
			# undef TEST_THEN_LOAD
		}


		/*!
		** \brief Try to find a file from a list of paths, a filename and a prefix
		**
		** \param[out] s A temporary string, where to write the absolute filename
		** \param prefix The prefix to use for the filename
		** \return True if the filename in `s` exists and should be loaded, False otherwise
		**/
		inline bool FindLibrary(String& out, const StringAdapter& filename)
		{
			return (FindLibraryFile(out, filename, "lib") || FindLibraryFile(out, filename, ""));
		}

	} // Anonymous namespace


	File::File(const StringAdapter& filename, const Relocation r, const Visibility v) :
		pHandle(NullHandle)
	{
		(void)loadFromFile(filename, r, v);
	}


	File::File() :
		pHandle(NullHandle)
	{}


	File::~File()
	{
		if (NullHandle != pHandle)
			wrapperDlClose(pHandle);
	}




	bool File::loadFromFile(const StringAdapter& filename, const File::Relocation r, const File::Visibility v)
	{
		// No filename
		if (!filename.empty())
		{
			// If the file name is absolute, there is no need for research
			if (IO::IsAbsolute(filename))
				return loadFromRawFilename(filename, r, v);

			// A temporary string, where to write the absolute filename
			String s;
			s.reserve(512);

			// Search paths
			// TODO : find a far more efficient way for doing this
			if (FindLibrary(s, filename))
				return loadFromRawFilename(s, r, v);
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
	bool File::loadFromRawFilename(const StringAdapter& filename, const File::Relocation, const File::Visibility)
	{
		// Unload the library if already loaded
		unload();

		if (filename.notEmpty())
		{
			// Loading
			WString<true> buffer(filename);
			if (buffer.empty())
				return false;

			pHandle = YUNI_DYNLIB_DLOPEN(buffer.c_str());
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
	bool File::loadFromRawFilename(const StringAdapter& filename, const File::Relocation r, const File::Visibility v)
	{
		// Unload the library if already loaded
		unload();

		if (filename.notEmpty())
		{
			// The mode
			int mode = ((relocationLazy == r) ? RTLD_LAZY : RTLD_NOW);
			if (visibilityDefault != v)
				mode |= ((visibilityGlobal == v) ? RTLD_GLOBAL : RTLD_LOCAL);
			// Loading
			pHandle = YUNI_DYNLIB_DLOPEN(filename.c_str(), mode);
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

