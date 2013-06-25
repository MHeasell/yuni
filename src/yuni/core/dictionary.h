#ifndef __YUNI_CORE_DICTIONARY_H__
# define __YUNI_CORE_DICTIONARY_H__

# include "../yuni.h"
# include "string.h"
# include <map>
# include <set>
# ifdef YUNI_HAS_STL_UNORDERED_MAP
#	include <unordered_map>
# endif
# ifdef YUNI_HAS_STL_UNORDERED_SET
#	include <unordered_set>
# endif



namespace Yuni
{

	template<class KeyT, class ValueT>
	class Dictionary final
	{
	public:
		//! Un unordered dictionary table
		# ifndef YUNI_HAS_STL_UNORDERED_MAP
		typedef std::map<KeyT, ValueT> Hash;
		# else
		typedef std::unordered_map<KeyT, ValueT> Hash;
		# endif

		//! Un ordered dictionary table
		typedef std::map<KeyT, ValueT> Ordered;

	}; // struct Dictionary



	template<class KeyT>
	class Set final
	{
	public:
		//! Un unordered set table
		# ifndef YUNI_HAS_STL_UNORDERED_MAP
		typedef std::set<KeyT> Hash;
		# else
		typedef std::unordered_set<KeyT> Hash;
		# endif

		//! Un ordered dictionary table
		typedef std::set<KeyT> Ordered;

	}; // struct Set



	//! Convenient typedef for a key/value store
	typedef Dictionary<String, String>::Hash  KeyValueStore;


} // namespace Yuni

#endif // __YUNI_CORE_DICTIONARY_H__
