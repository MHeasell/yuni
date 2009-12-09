#ifndef __YUNI_CORE_DYNAMICLIBRARY_FILE_H__
# define __YUNI_CORE_DYNAMICLIBRARY_FILE_H__

/*!
** \file file.h
** Header for Yuni::DynamicLibrary::File, a class for manipulating Executable Object Files
*/

# include "../../yuni.h"
# include <stdlib.h>
# include "../string.h"
# include "symbol.h"
//# include "../function.h"



// Determining the handle type for the current Operating system
# ifdef YUNI_OS_WINDOWS
#	define YUNI_DYNAMICLIBRARY_OS_HANDLE  HINSTANCE
# else
#	define YUNI_DYNAMICLIBRARY_OS_HANDLE  void*
# endif




namespace Yuni
{

/*!
** \brief Tools for manipulating Dynamic libraries (Executable Object files)
*/
namespace DynamicLibrary
{


	/*!
	** \brief An Executable Object file
	**
	** Here is an example of a typical use of a dynamic library. Assuming we have
	** the following shared library :
	** \code
	** #include <yuni/yuni.h> // For `YUNI_LIB_EXPORT`, which is OS Dependant
	** #include <string.h>    // For `strlen()`
	**
	** extern "C" YUNI_LIB_EXPORT const char* myname(void)
	** {
	** 	return "The 'my' library";
	** }
	**
	** extern "C" YUNI_LIB_EXPORT int mylength(const char* s)
	** {
	** 	return s ? strlen(s) : 0;
	** }
	** \endcode
	**
	** We could safely use it in this way, which is the simplest one :
	** \code
	** #include <iostream>
	** #include <yuni/core/dynamiclibrary.h>
	**
	**
	** int main(void)
	** {
	** 		// Our dynamic library
	** 		// (might be `mylib.so` on Unix, `my.dynlib` on Darwin, or `my.dll` on Windows)
	** 		// The current path (`./`) is by default in the search paths
	** 		Yuni::DynamicLibrary::File lib("my");
	**
	** 		// Binding with a C function, which has only one argument and an `int`
	** 		// as its returned type
	** 		Yuni::Function::F1<int, const char*> f = lib["mylength"];
	**
	** 		// Calling the exported function
	** 		// It is safe to directly call the function like this.
	** 		// The default constructor of the returned type is used if the library
	** 		// has not been successfully loaded.
	** 		int result = f("Hello world");
	**
	** 		std::cout << "Library loaded : " << (lib.loaded() ? "Yes" : "No") << std::endl;
	** 		std::cout << "Returned Value : " << result << std::endl;
	**
	**		// Extra: Displaying the name of our library
	** 		Yuni::Function::F0<const char*> libname = lib["myname"];
	**		const char* s = libname();
	**		std::cout << "Library name: " << (s ? s : "(null)") << std::endl;
	** }
	** \endcode
	*/
	class File
	{
	public:
		//! OS Dependant Handle of a shared library
		typedef YUNI_DYNAMICLIBRARY_OS_HANDLE Handle;
		//! An invalid handle
		static const Handle NullHandle;

		/*!
		** \brief Relocation options
		**
		** When an object is brought into the address space of a process, it may
		** contain references to symbols whose addresses are not known until the
		** object is loaded. These references shall be relocated before the
		** symbols can be accessed (man dlopen).
		**
		** These options are actually ignored on Windows.
		*/
		enum Relocation
		{
			/*!
			** \brief Relocations shall be performed at an implementation-defined
			** time (see RTLD_LAZY, Unix only)
			*/
			relocationLazy,
			/*!
			** brief All necessary relocations shall be performed when the object
			** is first loaded (see RTLD_NOW, Unix only)
			*/
			relocationNow
		};

		/*!
		** \brief Scope of visibility options
		*/
		enum Visibility
		{
			/*!
			** \brief OS Dependant default implementation
			*/
			visibilityDefault,
			/*!
			** \brief  The object’s symbols shall be made available for the
			** relocation processing of any other object (Unix only)
			*/
			visibilityGlobal,
			/*!
			** \brief The object’s symbols shall not be made available for the
			** relocation processing of any other object (Unix only)
			*/
			visibilityLocal
		};


	public:
		//! \name Constructor & DEstructor
		//@{
		/*!
		** \brief Default constructor
		*/
		File();

		/*!
		** \brief Constructor - Load an dynamic library
		**
		** \param filename Filename of the library to load
		** \param r The relocation mode (no effect on Windows)
		** \param v The visibility mode (no effect on Windows)
		*/
		File(const char* filename, const Relocation r = relocationLazy,
			const Visibility v = visibilityDefault);
		File(const String& filename, const Relocation r = relocationLazy,
			const Visibility v = visibilityDefault);

		/*!
		** \brief Destructor
		**
		** The library will be automatically unloaded if needed.
		*/
		~File();
		//@}


		//! \name Loading / Unloading
		//@{
		/*!
		** \brief Load a dynamic library from its filename
		**
		** The filename may be modified, according the current operating system.
		** A prefix and/or a suffix may be added to suit to the OS.
		**
		** The prefix : `lib` may be added as prefix on Unix platforms
		** The suffixes :
		**  - Mac OS : .dylib, .bundle, .so
		**  - Unix/Linux : .so
		**  - AIX : .a
		**  - HP-UX : .sl, .so
		**  - Windows : .dll
		**
		** The library will be searched in all system-specific library locations
		** (e.g. LD_LIBRARY_PATH on Unix), then in all given search paths, unless
		** the file name has an absolute path.
		**
		** If a library is already loaded, it will be unloaded first.
		**
		** \param filename The absolute or relative filename to the library
		** \param r The relocation mode (no effect on Windows)
		** \param v The visibility mode (no effect on Windows)
		** \return True if the library has been loaded
		*/
		bool load(const String& filename, const Relocation r = relocationLazy,
			const Visibility v = visibilityDefault);

		/*!
		** \brief Load a dynamic library from its filename
		**
		** No operation will be made on the filename, contrary to
		** load() where a suffic and/or a prefix might be added.
		**
		** If a library is already loaded, it will be unloaded first.
		**
		** \param filename The absolute or relative filename to the library
		** \param r The relocation mode (no effect on Windows)
		** \param v The visibility mode (no effect on Windows)
		** \return True if the library has been loaded
		*/
		bool loadFromRawFilename(const char* filename, const Relocation r = relocationLazy,
			const Visibility v = visibilityDefault);
		bool loadFromRawFilename(const String& filename, const Relocation r = relocationLazy,
			const Visibility v = visibilityDefault);

		/*!
		** \brief Unload the dynamic library
		**
		** Nothing will be done if the library is not already loaded
		*/
		void unload();

		/*!
		** \brief Get if the dynamic library is loaded
		*/
		bool loaded() const;

		/*!
		** \brief Get the filename of the loaded library
		** \return The full filename of the library, or empty if not loaded
		*/
		const String& filename() const;
		//@}

		//! \name Symbols
		//@{
		/*!
		** \brief Get if a symbol exists in the library
		**
		** \param name Name of the exported symbol
		** \return True if the library is loaded and the symbol exists, False otherwise
		*/
		bool hasSymbol(const String& name) const;
		bool hasSymbol(const char* name) const;

		/*!
		** \brief Try to resolve the address of an exported symbol by the library
		**
		** \code
		** Yuni::DynamicLibrary::File lib;
		** if (lib.load("my"))
		** {
		** 		// The shared library has been loaded
		** 		// We can try to resolve a symbol
		** 		Yuni::DynamicLibrary::Symbol s = lib.resolve("myentry");
		** 		if (s.valid())
		** 		{
		** 			// The symbol has been found, let's continue
		** 			// ...
		** 		}
		** 		else
		** 		{
		** 			// The symbol has not been found in the library
		** 		}
		** }
		** \endcode
		**
		** \param name Name of the exported symbol
		** \return The Symbol. Use Symbol::valid() or Symbol::null() to know if
		** the result is valid
		*/
		Symbol resolve(const char* name) const;
		Symbol resolve(const String& name) const;
		//@}

		//! \name Handle
		//@{
		/*!
		** \brief Get the OS Dependant handle of the dynamic library
		*/
		Handle handle() const;
		//@}

		//! \name Operators
		//@{
		/*!
		** \brief The operator []
		** \see resolve()
		*/
		Symbol operator [] (const char* name) const;
		/*!
		** \brief The operator []
		** \see resolve()
		*/
		Symbol operator [] (const String& name) const;
		//@}


	private:
		//! Wrapper on dlclose()
		static void wrapperDlClose(const Handle h);
		//! Wrapper on dlsym()
		static Symbol::Handle wrapperDlSym(const Handle h, const char* name);


	private:
		//! Handle of the dynamic library
		Handle pHandle;
		//! The full filename of the library
		String pFilename;

	}; // class DynamicLibrary




} // namespace DynamicLibrary
} // namespace Yuni

# include "file.hxx"

# undef YUNI_DYNAMICLIBRARY_OS_HANDLE

#endif // __YUNI_CORE_DYNAMICLIBRARY_FILE_H__
