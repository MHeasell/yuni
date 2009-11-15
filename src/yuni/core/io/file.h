#ifndef __YUNI_CORE_FS_FILES_H__
# define __YUNI_CORE_FS_FILES_H__

# include "io.h"
# include "file/openmode.h"



namespace Yuni
{
namespace Core
{
namespace IO
{

/*!
** \brief File manipulation functions
** \ingroup IOFile
*/
namespace File
{


	/*!
	**
	** \ingroup IOFile
	*/
	enum
	{
		//! The maximum allowed size for a file in memory (Default: 80Mo)
		sizeHardLimit = 83886080u,  // 80Mo = 80 * 1024 * 1024
	};

	

	/*!
	** \brief Test if a node exists and is actually a file
	**
	** \ingroup IOFile
	**
	** To test if a node exists whatever its nature, you should use
	** Core::IO::Exists() instead.
	**
	** \tparam Any standard that can be converted into a const char*
	** \param p The folder/filename to test
	** \return True if it exists, false otherwise
	*/
	template<class C> bool Exists(const C& p);


	/*!
	** \brief Get the size of a file
	**
	** \ingroup IOFile
	**
	** \param filename The file
	** \param[out] size The size of the file. 0 if any errors has occured
	** \return True if the operation succeeded, False otherwise
	*/
	bool Size(const char* filename, uint64& size);
	bool Size(const String& filename, uint64& size);



	//! \name Load the content of a file
	//@{
	/*!
	** \brief Open and Read the content of a file and write it into an 1D array
	**
	** \ingroup IOFile
	**
	** \param[out] out The content of the file
	** \param filename Filename to open
	** \param emptyListBefore Empty the list before any operation
	** \param sizeLimit Do not load files with a size > to this value. The value `0` disables this feature.
	** \return True if the operation succeeded, False otherwise
	*/
	// const char*
	bool Load(String::Vector& out, const char* filename, const bool emptyListBefore = true,
			const uint32 sizeLimit = sizeHardLimit);
	bool Load(String::List& out, const char* filename, const bool emptyListBefore = true,
			const uint32 sizeLimit = sizeHardLimit);
	// Yuni::String
	template<int N>
	bool Load(String::Vector& out, const StringBase<char,N>& filename, const bool emptyListBefore = true,
			const uint32 sizeLimit = sizeHardLimit);
	template<int N>
	bool Load(String::List& out, const StringBase<char,N>& filename, const bool emptyListBefore = true,
			const uint32 sizeLimit = sizeHardLimit);


	/*!
	** \brief Load the entire content of a file into memory
	**
	** \ingroup IOFile
	**
	** \param filename The filename to open
	** \param hardlimit If the size of the file exceeds this limit, it will not be loaded
	** \return The content of the file, null terminated in any cases, NULL if size > hardlimit or if any error has occurred.
	** If not NULL, this value must be deleted with the keyword `delete[]`
	*/
	char* LoadContentInMemory(const String& filename, const uint64 hardlimit = sizeHardLimit);

	/*!
	** \brief Load the entire content of a file into memory
	** \ingroup IOFile
	**
	** \param filename The filename to open
	** \param[out] size The size of the file
	** \param hardlimit If the size of the file exceeds this limit, it will not be loaded 
	** \return The content of the file, null terminated in any cases, NULL if size > hardlimit or if any error has occurred.
	** If not NULL, this value must be deleted with the keyword `delete[]`
	*/
	char* LoadContentInMemory(const String& filename, uint64& size, const uint64 hardlimit = sizeHardLimit);

	/*!
	** \brief Save the content of a string into a file
	** \ingroup IOFile
	**
	** \param filename The filename to create/overwrite
	** \param content The new content of the file
	** \return True if the operation succeeded, false otherwise
	*/
	bool SaveToFile(const String& filename, const String& content);
	//@}


	/*!
	** \brief Copy a single file
	** \ingroup IOFile
	**
	** \param from The source file
	** \param to The target file
	** \param overwrite Overwrite the target file if already exists
	** \return True if the operation succeeded (or if the target file already exists and `overwrite` = false), false otherwise
	*/
	bool Copy(const String& from, const String& to, const bool overwrite = true);



	/*!
	** \brief Remove dot segments in an unix filename
	** \ingroup IOFile
	**
	** This routine removes dot segments (`.` and `..`) from a given filename.
	** However, in the case of a relative filename (ex: `../path/to/file`) the
	** first dot segments (`..` only) can not be removed to preserve the meaning
	** of the data.
	** Any final slash will be removed.
	**
	** \param filename The filename
	** \return A new string string with dot segments removed
	*/
	String RemoveDotSegmentsFromUnixFilename(const String& filename);


	/*!
	** \brief Create or erase a file
	**
	** \param filename An UTF8 filename
	*/
	template<class C> bool CreateEmptyFile(const C& filename);


	/*!
	** \brief Set the content of a file with an arbitrary string
	**
	** \code
	** Core::IO::File::SetContent("/tmp/anyfile.txt", "Hello world !\n");
	** \endcode
	*/
	template<class C1, class C2> bool SetContent(const C1& filename, const C2& content);

	/*!
	** \brief Append the content of an arbitrary string to a file
	**
	** \code
	** Core::IO::File::AppendContent("/tmp/anyfile.txt", "lorem ipsumi\n");
	** \endcode
	*/
	template<class C1, class C2> bool AppendContent(const C1& filename, const C2& content);






} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

# include "io.h"
# include "file/stream.h"
# include "file/file.hxx"

#endif // __YUNI_CORE_FS_FILES_H__
