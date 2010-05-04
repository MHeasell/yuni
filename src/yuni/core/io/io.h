#ifndef __YUNI_CORE_IO_IO_H__
# define __YUNI_CORE_IO_IO_H__

# include "../../yuni.h"
# include "../string.h"


namespace Yuni
{
namespace Core
{
/*
** \brief Low-level routines for file and directory support
** \ingroup IO
*/
namespace IO
{

	//! \name System-dependant variables
	//@{
	/*!
	** \brief The path-separator character according to the platform (ex: `/`)
	**
	** \ingroup IO
	*/
	extern const String::Char Separator; // '/'

	/*!
	** \brief The path-separator character according to the platform (stored in a string instead of a char)
	**
	** \ingroup IO
	*/
	extern const String::Char* SeparatorAsString; // "/"

	/*!
	** \brief Constant acoording a type
	**
	** These variables are identical to SeparatorAsString and Separator
	** but are charactere-type dependant.
	** \ingroup IO
	*/
	template<typename C /* = char*/> struct Constant;
	template<>
	struct Constant<char>
	{
		// The complete specialization with wchar_t is in directory.hxx

		//! The path-separator character according to the platform (ex: `/`)
		static const char  Separator; // '/';
		//! The path-separator character according to the platform (stored in a string instead of a char)
		static const char* SeparatorAsString; // "/"
		//! All path-separator characters, for all platforms
		static const char* AllSeparators; // "\\/"

		//! Dot
		static const char  Dot; // '.';

	}; // class Constant<char>
	//@}



	/*!
	** \brief Flow control used in the IO module
	*/
	enum Flow
	{
		//! Abort the whole process
		flowAbort = 0,
		//! Continue
		flowContinue = 1,
		//! Skip the current item
		flowSkip = 2,
	};




	/*!
	** \brief Extract the path part of a filename
	** \ingroup IO
	**
	** The path part will be extracted according the system-(un)dependant path-separator
	** \code
	**	  std::cout << Core::IO::Filename::ExtractFilePath("/tmp/foo.txt") std::endl; // write `/tmp`
	** \endcode
	**
	** \param p The original filename
	** \param systemDependant Consider only the system-dependant path-separator
	** \return The path part of the original filename
	*/
	template<typename C, int N>
	StringBase<C,N> ExtractFilePath(const StringBase<C,N>& p, const bool systemDependant = true);
	template<typename C>
	StringBase<C> ExtractFilePath(const C* p, const bool systemDependant = true);



	/*!
	** \brief Extract the bare file name
	**
	** \ingroup IO
	**
	** The file name will be extracted according the last occurence
	** of the system-dependant path-separator (if systemDependant = true)
	**
	** \param p The original filename
	** \param systemDependant Consider only the system-dependant path-separator
	** \return The bare filename from the original one
	**
	** \see Paths::Separator
	*/
	template<typename C, int N>
	StringBase<C,N> ExtractFileName(const StringBase<C,N>& p, const bool systemDependant = true);
	template<typename C>
	StringBase<C> ExtractFileName(const C* p, const bool systemDependant = true);

	/*!
	** \brief Extract bare file name for each entry in a list
	**
	** \ingroup IO
	**
	** The file name will be extracted according the last occurence
	** of the system-dependant path-separator (if systemDependant = true).
	**
	** Each entry in the list will be replaced by the new value according `ExtractFileName(const String&, const bool)`.
	**
	** \param[in,out] p The list to process
	** \param systemDependant Consider only the system-dependant path-separator
	**
	** \see ExtractFileName(const String&, const bool)
	** \see Paths::Separator
	*/
	template<typename C, int N, template<class> class Alloc>
	void ExtractFileName(std::list<StringBase<C,N>, Alloc<StringBase<C, N> > >& p, const bool systemDependant = true);

	/*!
	** \brief Extract bare file name for each entry in a list
	**
	** \ingroup IO
	**
	** The file name will be extracted according the last occurence
	** of the system-dependant path-separator (if systemDependant = true).
	**
	** Each entry in the list will be replaced by the new value according `ExtractFileName(const String&, const bool)`.
	**
	** \param[in,out] p The list to process
	** \param systemDependant Consider only the system-dependant path-separator
	**
	** \see ExtractFileName(const String&, const bool)
	** \see Paths::Separator
	*/
	template<typename C, int N, template<class> class Alloc>
	void ExtractFileName(std::vector<StringBase<C,N>, Alloc<StringBase<C, N> > >& p, const bool systemDependant = true);


	/*!
	** \brief Extract the bare file name without its extension
	**
	** \ingroup IO
	**
	** The file name will be extracted according the last occurence
	** of the system-dependant path-separator (if systemDependant = true).
	**
	** \param p The original file name
	** \param systemDependant Consider only the system-dependant path-separator
	** \return The bare file name without its extension
	**
	** \see Paths::Separator
	*/
	template<typename C, int N>
	StringBase<C,N> ExtractFileNameWithoutExtension(const StringBase<C,N>& p, const bool systemDependant = true);


	/*!
	** \brief Extract the extention of a file name
	**
	** \ingroup IO
	**
	** \param out Variable where the result will be appended
	** \param filename The original filename
	** \param dot True to include the dot when extracting the extension
	** \return True if an extension has been found
	*/
	template<class StringT1, class StringT2>
	bool ExtractExtension(StringT1& out, const StringT2& filename, bool dot = true);


	/*!
	** \brief Get if a path is absolute
	**
	** \ingroup IO
	**
	** \param filename The path or the filename to test
	** \return True if the given filename is an absolute path, false otherwise (or empty)
	*/
	template<class StringT> bool IsAbsolute(const StringT& filename);


	/*!
	** \brief Make a path absolute
	**
	** \ingroup IO
	**
	** The current directory will be used when the given path is not absolute.
	**
	** \param p Any path to make absolute
	** \return `p` or an absolute path
	*/
	template<typename C, int N>
	StringBase<C,N> MakeAbsolute(const StringBase<C,N>& p);

	/*!
	** \brief Make a path absolute
	**
	** \ingroup IO
	**
	** The current directory is used when the given path is not absolute.
	**
	** \param p Any path to make absolute
	** \param currentDirectory A custom current directory to use instead of CurrentDirectory()
	** \return `p` or an absolute path
	*/
	template<typename C, int N, typename U>
	StringBase<C,N> MakeAbsolute(const StringBase<C,N>& p, const U& currentDirectory);


	/*!
	** \brief Replace the extension
	**
	** \ingroup IO
	** \code
	** std::string s = "file.avi";
	** Yuni::Core::IO::ReplaceExtension(s, ".mpeg");
	** std::cout << s << std::endl; // file.mpeg
	** \endcode
	**
	** \param[in,out] filename     The original filename
	** \param         newExtension The new extension (dot included, ex: `.ota`)
	** \return True if the extension has been replaced (means `found and replaced`)
	*/
	template<class StringT1, class StringT2>
	bool ReplaceExtension(StringT1& filename, const StringT2& newExtension);


	/*!
	** \brief Test if a node exists (whatever its type)
	** \ingroup IO
	**
	** \param p The file/directory to test
	** \return True if it exists, false otherwise
	*/
	// const char*
	template<class StringT> bool Exists(const StringT& filename);


	/*!
	** \brief Normalize a filename
	**
	** The input can be a Windows-style or a Unix-style path, with mixed slasles and anti-slashes.
	** This routine removes dot segments (`.` and `..`) from a given filename (when
	** possible).
	** Any final slash or anti-slash will be kept.
	**
	** \bug The relative filename like C:..\folder1\folder2 are not handled properly
	**
	** \param[out] out      A string (any class compliant to std::string) where to write the result
	** \param      in       A path/filename to normalize
	** \param      inLength Length of #in (optional, -1 for autodetection)
	*/
	template<class StringT1, class StringT2>
	void Normalize(StringT1& out, const StringT2& in, unsigned int inLength = (unsigned int)-1);








} // namespace IO
} // namespace Core
} // namespace Yuni

# include "directory.h"
# include "io.hxx"

#endif // __YUNI_CORE_IO_IO_H__
