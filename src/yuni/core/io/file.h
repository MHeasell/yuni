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
	** \param filename The filename
	** \param[out] size The size (in bytes) of the file. 0 if any errors has occured
	** \return True if the operation succeeded, False otherwise
	*/
	template<class AnyStringT> bool Size(const AnyStringT& filename, uint64& size);

	/*!
	** \brief Get the size of a file
	**
	** \ingroup IOFile
	** \param filename The filename
	** \param[out] size The size (in bytes) of the file. 0 if any errors has occured
	** \return The size in bytes of the file, 0 when the operation fails
	*/
	template<class AnyStringT> uint64 Size(const AnyStringT& filename);




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
	** \param[out] out The content of the file
	** \param filename The filename to open
	** \param hardlimit If the size of the file exceeds this limit, it will not be loaded
	** \return True if the operation succeeded.
	*/
	template<class C, int ChunkT, class AnyStringT>
	bool LoadContent(const StringBase<C,ChunkT>& out, const AnyStringT& filename, const uint64 hardlimit = sizeHardLimit);


	/*!
	** \brief Save the content of a string into a file
	**
	** \ingroup IOFile
	** \param filename The filename to create/overwrite
	** \param content The new content of the file
	** \return True if the operation succeeded, false otherwise
	*/
	template<class AnyStringT, class U> bool SaveToFile(const AnyStringT& filename, const U& content);
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
	** \brief Create or erase a file
	**
	** \param filename An UTF8 filename
	** \return True if the file has been created or truncated
	*/
	template<class AnyStringT> bool CreateEmptyFile(const AnyStringT& filename);


	/*!
	** \brief Set the content of a file with an arbitrary string
	**
	** \code
	** Core::IO::File::SetContent("/tmp/anyfile.txt", "Hello world !\n");
	** \endcode
	*/
	template<class AnyStringT, class U> bool SetContent(const AnyStringT& filename, const U& content);

	/*!
	** \brief Append the content of an arbitrary string to a file
	**
	** \code
	** Core::IO::File::AppendContent("/tmp/anyfile.txt", "lorem ipsumi\n");
	** \endcode
	*/
	template<class AnyStringT, class U> bool AppendContent(const AnyStringT& filename, const U& content);






} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

# include "io.h"
# include "file/stream.h"
# include "file/file.hxx"

#endif // __YUNI_CORE_FS_FILES_H__
