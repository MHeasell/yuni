#ifndef __YUNI_CORE_IO_DIRECTORY_H__
# define __YUNI_CORE_IO_DIRECTORY_H__

# include "../../yuni.h"
# include "../string.h"


namespace Yuni
{
namespace Core
{
namespace IO
{

/*
** \brief Directory manipulation functions
**
** \ingroup IODirectory
*/
namespace Directory
{

	//! \name Exists
	//@{
	/*!
	** \brief Test if a node exists and is actually a directory
	**
	** \ingroup IODirectory
	**
	** To test if a node exists whatever its nature, you should use
	** Core::IO::Filesystem::Exists() instead.
	**
	** \param path The directory to test
	** \return True if it exists, false otherwise
	*/
	template<class StringT> bool Exists(const StringT& path);
	//@}


	/*!
	** \brief Routines about current directories
	*/
	namespace Current
	{
		/*!
		** \brief Get the current directory
		**
		** \param clearBefore True to clean @out before
		*/
		template<class StringT> void Get(StringT& out, bool clearBefore = true);

		/*!
		** \brief Get the current directory
		**
		** Performance Tip: Perfer Get(String&) which avoid several string copy
		*/
		String Get();

		/*!
		** \brief Set the current directory
		** \return True if the operation succeeded
		*/
		template<class StringT> bool Set(const StringT& path);

	} // anonymous Current



	//! \name Create a directory
	//@{
	/*!
	** \brief Create a directory recursively
	**
	** \ingroup IODirectory
	** \param p The path to create if it does not exist
	** \param mode Access permissions (ignored on the MS Windows platforms)
	** \return True if the operation succeeded, false otherwise
	*/
	template<class StringT>
	bool Make(const StringT& path, unsigned int mode = 0755);
	//@}


	//! \name Remove a directory
	//@{
	/*!
	** \brief Recursively delete a directory and its content
	**
	** \ingroup IODirectory
	** \param p The path to delete
	** \return True if the operation succeeded False otherwise
	*/
	template<class StringT> bool Remove(const StringT& path);
	//@}


	//! \name Copy a Directory
	//@{
	/*!
	** \brief Copy a directory and its content to another location
	**
	** \ingroup IODirectory
	**
	** \param src The source folder
	** \param dst The target folder
	** \return True if the operation succeeded False otherwise
	*/
	template<class StringT1, class StringT2> bool Copy(const StringT1& src, const StringT2& dst);
	//@}





} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Yuni

# include "directory/directory.hxx"
# include "io.h"

#endif // __YUNI_CORE_IO_DIRECTORY_H__
