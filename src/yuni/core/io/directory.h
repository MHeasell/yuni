#ifndef __YUNI_CORE_IO_DIRECTORY_H__
# define __YUNI_CORE_IO_DIRECTORY_H__

# include "private.h"


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
	** \param p The directory to test
	** \return True if it exists, false otherwise
	*/
	bool Exists(const char* p);
	template<typename C, int N> bool Exists(const StringBase<C,N>& p);
	//@}



	//! \name Current Directory
	//@{
	/*!
	** \brief Retrieve the current directory
	**
	** \ingroup IODirectory
	*/
	String Current();

	/*!
	** \brief Retrieve the current directory and write the result in a given string
	**
	** \ingroup IODirectory
	** \param[out] out Var where to write the current directory
	*/
	void Current(String& out);
	//@}



	//! \name Create a directory
	//@{
	/*!
	** \brief Create a directory recursively
	**
	** \ingroup IODirectory
	** \param p The path to create if it does not exist
	** \param mode Access permissions (not used on the MS Windows platforms)
	** \return True if the operation succeeded, false otherwise
	*/
	bool Make(const char* p, unsigned int mode = 0755);
	// Yuni::String version
	template<int N> bool Make(const StringBase<char,N>& p, unsigned int mode = 0755);
	//@}


	//! \name Remove a directory
	/*!
	** \brief Recursively delete a directory
	**
	** \ingroup IODirectory
	** \param p The path to delete
	** \return True if the operation succeeded False otherwise
	*/
	bool Remove(const char* p);
	// Yuni::String version
	template<int N> bool Remove(const StringBase<char,N>& p);
	//@}


	//! \name Copy a Directory
	//@{
	/*!
	** \brief Copy a directory
	**
	** \ingroup IODirectory
	** \param src The source folder
	** \param dst The target folder
	** \return True if the operation succeeded False otherwise
	*/
	bool Copy(const char* src, const char* dst);
	// Yuni::String version
	template<int N, int M>
	bool Copy(const StringBase<char,N>& src, const StringBase<char,M>& dst);
	//@}





} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Yuni

# include "directory/directory.hxx"
# include "io.h"

#endif // __YUNI_CORE_IO_DIRECTORY_H__
