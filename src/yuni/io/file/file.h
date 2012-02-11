#ifndef __YUNI_IO_FILE_FILE_H__
# define __YUNI_IO_FILE_FILE_H__

# include "../io.h"
# include "openmode.h"



namespace Yuni
{
namespace IO
{

/*!
** \brief File manipulation functions
*/
namespace File
{

	// constants
	enum
	{
		//! The maximum allowed size for a file in memory (Default: 80Mo)
		sizeHardLimit = 83886080u,  // 80Mo = 80 * 1024 * 1024
	};



	/*!
	** \brief Test if a node exists and is actually a file
	**
	** To test if a node exists whatever its nature, you should use
	** IO::Exists() instead.
	**
	** \param filename The folder/filename to test
	** \return True if it exists, false otherwise
	*/
	bool Exists(const StringAdapter& filename);


	/*!
	** \brief Get the size (in bytes) of a file
	**
	** \param filename The filename
	** \param[out] size The size (in bytes) of the file. The value is guaranteed to be set (null) is an error has occured
	** \return True if the operation succeeded, False otherwise
	*/
	bool Size(const StringAdapter& filename, uint64& size);

	/*!
	** \brief Get the size (in bytes) of a file
	**
	** \code
	** #include <yuni/yuni.h>
	** #include <yuni/core/unit/data.h>
	** #include <yuni/io/file.h>
	** #include <iostream>
	**
	** using namespace Yuni;
	** int main()
	** {
	**	Unit::Data::Octet::SIBaseUnit<uint64> size = IO::File::Size("/path/to/my/file");
	**	std::cout << Unit::Data::Octet::Megaoctet<double>(size) << std::endl;
	**	return 0;
	** }
	** \endcode
	**
	** \param filename The filename
	** \return The size (in bytes) of the file. The returned value is guaranteed to be null is an error has occured
	*/
	uint64 Size(const StringAdapter& filename);


	//! \name Date / Time
	//@{
	/*!
	** \brief Get the unix timestamp of the last modification
	*/
	template<class StringT>
	sint64 LastModificationTime(const StringT& filename);
	//@}


	//! \name Load the content of a file
	//@{
	/*!
	** \brief Load the entire content of a file into memory
	**
	** If the file size is greater than \p hardlimit, the content will be truncated (see 'errMemoryLimit').
	** \param[out] out The content of the file
	** \param filename The filename to open
	** \param hardlimit If the size of the file exceeds this limit, it will not be loaded
	** \return errNone if successful
	*/
	template<class StringT1, class StringT2>
	IO::Error LoadFromFile(StringT1& out, const StringT2& filename, const uint64 hardlimit = sizeHardLimit);


	/*!
	** \brief Save the content of a string into a file
	**
	** \param filename The filename to create/overwrite
	** \param content The new content of the file
	** \return True if the operation succeeded, false otherwise
	*/
	template<class StringT, class U> bool SaveToFile(const StringT& filename, const U& content);
	//@}


	/*!
	** \brief Copy a single file
	**
	** \param from The source file
	** \param to The target file
	** \param overwrite Overwrite the target file if already exists
	** \return errNone if the operation succeeded
	*/
	IO::Error Copy(const StringAdapter& from, const StringAdapter& to, bool overwrite = true);


	/*!
	** \brief Delete a file
	**
	** \param filename The file to delete
	*/
	IO::Error Delete(const StringAdapter& filename);


	/*!
	** \brief Create or erase a file
	**
	** \param filename An UTF8 filename
	** \return True if the file has been created or truncated
	*/
	template<class StringT> bool CreateEmptyFile(const StringT& filename);


	/*!
	** \brief Set the content of a file with an arbitrary string
	**
	** \code
	** IO::File::SetContent("/tmp/anyfile.txt", "Hello world !\n");
	** \endcode
	*/
	template<class StringT, class U> bool SetContent(const StringT& filename, const U& content);

	/*!
	** \brief Append the content of an arbitrary string to a file
	**
	** \code
	** IO::File::AppendContent("/tmp/anyfile.txt", "lorem ipsumi\n");
	** \endcode
	*/
	template<class StringT, class U> bool AppendContent(const StringT& filename, const U& content);


	/*!
	** \brief Read a file line by line
	**
	** A simple `cat` :
	** \code
	** IO::File::ReadLineByLine("/tmp/foo.txt", [&] (const String& line)
	** {
	**	std::cout << line << std::endl;
	** });
	** \endcode
	**
	** \param filename A filename
	** \param predicate A functor or a lambda function
	*/
	template<class StringT, class PredicateT>
	bool ReadLineByLine(const StringT& filename, const PredicateT& predicate);






} // namespace File
} // namespace IO
} // namespace Yuni

# include "stream.h"
# include "file.hxx"

#endif // __YUNI_IO_FILE_FILE_H__
