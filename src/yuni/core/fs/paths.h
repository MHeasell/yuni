#ifndef __YUNI_CORE_FS_PATHS_H__
# define __YUNI_CORE_FS_PATHS_H__

# include "../../yuni.h"
# include "../string.h"



namespace Yuni
{
namespace Core
{


/*
** \brief Path manipulation functions
** \ingroup PathsAndFiles
*/
namespace Paths
{


	//! \name System-dependant variables
	//@{
	//! The path-separator character according to the platform (ex: `/`)
	//! \ingroup PathsAndFiles
	extern const String::Char Separator;

	//! The path-separator character according to the platform (stored in a string instead of a char)
	//! \ingroup PathsAndFiles
	extern const String::Char* SeparatorAsString;
	//@}





	//! \name Folders handling
	//@{

	/*!
	** \brief Test if a file/folder exists
	** \ingroup PathsAndFiles
	**
	** \param p The folder/filename to test
	** \return True if it exists, false otherwise
	*/
	bool Exists(const String& p);



	/*!
	** \brief Create Path Recursively
	** \ingroup PathsAndFiles
	**
	** \param p The path to create if it does not exist
	** return True if the operation succeeded, false otherwise
	*/
	bool MakeDir(const String& p);



	/*!
	** \brief Retrieve the current directory
	** \ingroup PathsAndFiles
	*/
	String CurrentDirectory();



	/*!
	** \brief Extract the path part of a filename
	** \ingroup PathsAndFiles
	**
	** The path part will be extracted according the system-dependant path-separator
	**
	** \param p The original filename
	** \param systemDependant Consider only the system-dependant path-separator
	** \return The path part of the original filename
	**
	** \code
	**	  std::cout << Paths::ExtractFilePath("/tmp/foo.txt") std::endl; // write `/tmp`
	**	  std::cout << Paths::ExtractFilePath("/tmp/") std::endl; // write `/tmp`
	**	  std::cout << Paths::ExtractFilePath("/tmp") std::endl; // write `/`
	** \endcode
	**
	** \see Paths::Separator
	*/
//	void ExtractFilePath(String& out, const String& p, const bool systemDependant = true);
	String ExtractFilePath(const String& p, const bool systemDependant = true);



	/*!
	** \brief Extract the bare file name
	** \ingroup PathsAndFiles
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
	String ExtractFileName(const String& p, const bool systemDependant = true);
	/*!
	** \brief Extract bare file name for each entry in a list
	** \ingroup PathsAndFiles
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
	void ExtractFileName(String::List& p, const bool systemDependant = true);
	/*!
	** \brief Extract bare file name for each entry in a list
	** \ingroup PathsAndFiles
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
	void ExtractFileName(String::Vector& p, const bool systemDependant = true);



	/*!
	** \brief Extract the bare file name without its extension
	** \ingroup PathsAndFiles
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
	String ExtractFileNameWithoutExtension(const String& p, const bool systemDependant = true);



	/*!
	** \brief Extract the extention of a file name
	** \ingroup PathsAndFiles
	**
	** \param s Filename
	** \param option soIgnoreCase to ensure to have a lowercase string
	** \return The extenion of the filename (with the leading '.') in lowercase, empty if no extension is present
	**
	** \code
	**	 std::cout << Paths::Files::ExtractFileExt("foo.exe") << std::endl; // '.exe'
	**	 std::cout << Paths::Files::ExtractFileExt("/usr/folder.foo/file") << std::endl; // ''
	** \endcode
	*/
	String ExtractFileExt(const String& s, String::CharCase option = String::soIgnoreCase);


	/*!
	** \brief Get if a path is absolute
	** \ingroup PathsAndFiles
	**
	** \param p The path or the filename to test
	** \return True if the path is an absolute path or empty, false otherwise
	*/
	bool IsAbsolute(const String& p);

	//@}




} // namespace Paths
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_FS_PATHS_H__
