#ifndef __YUNI_IO_SEARCHPATH__SEARCH_PATH_H__
# define __YUNI_IO_SEARCHPATH_SEARCH_PATH_H__

# include "../../yuni.h"
# include "../../core/string.h"
# include <map>


namespace Yuni
{
namespace IO
{

	/*!
	** \brief Find files or folders from one or several search paths
	**
	** \code
	** IO::SearchPath searchpath;
	** searchpath.directories.push_back(".");
	** searchpath.extensions.push_back(".dylib");
	** searchpath.extensions.push_back(".a");
	** searchpath.prefixes.push_back("");
	**
	** const String& location = searchpath.find("mylib");
	** if (!location)
	**	std::cerr << "impossible to find something\n";
	** else
	**	std::cout << "found: " << location << std::endl;
	**
	** // finding all matches
	** String::Vector list;
	** if (search.find(list, "mylib"))
	**	std::cerr << "impossible to find something\n";
	** else
	**	std::cout << "found: " << list << std::endl;
	** \endcode
	**
	** \note The cache lookup is disabled by default
	*/
	class SearchPath
	{
	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		SearchPath();
		//! Destructor
		~SearchPath();
		//@}


		//! \name Lookup
		//@{
		/*!
		** \brief Try to find the first filename/folder in the search paths which mathes the criteria
		** \return An absolute filename, or empty if not found
		*/
		bool find(String& out, const StringAdapter& filename) const;

		/*!
		** \brief Find all matching filenames/folders in the search paths which math the criteria
		*/
		bool find(String::Vector& out, const StringAdapter& filename) const;

		/*!
		** \brief Find all matching filenames/folders in the search paths which math the criteria
		*/
		bool find(String::List& out, const StringAdapter& filename) const;
		//@}


		//! \name Cache
		//@{
		//! Get if the cache is used
		bool cacheLookup() const;
		//! Set if the cache should be used
		void cacheLookup(bool enabled);

		/*!
		** \brief Clear the cache
		*/
		void cacheClear();
		//@}


	public:
		//! List of directories where to search of
		String::Vector  directories;
		//! List of extensions
		String::Vector  extensions;
		//! List of prefixes
		String::Vector  prefixes;
		


	private:
		typedef std::map<String, String> CacheStore;
		//! Should we use the cache ?
		bool pCacheLookup;
		//! Cache store
		CacheStore pCache;
		//! Temporary string used for cache lookup
		// (to reduce memory allocation / deallocation)
		mutable String pCacheQuery;

	}; // class SearchPath






} // namespace IO
} // namespace Yuni

# include "searchpath.hxx"

#endif // __YUNI_IO_SEARCHPATH_SEARCH_PATH_H__
