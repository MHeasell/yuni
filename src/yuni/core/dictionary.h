#ifndef __YUNI_CORE_DICTIONARY_H__
# define __YUNI_CORE_DICTIONARY_H__

# include "../yuni.h"
# include "string.h"
# include <map>
# include <set>


namespace Yuni
{

	template<class KeyT, class ValueT>
	struct Dictionary
	{
		//! Un unordered dictionary table
		typedef std::map<KeyT, ValueT> Hash;

		//! Un ordered dictionary table
		typedef std::map<KeyT, ValueT> Ordered;

	}; // struct Dictionary



	template<class KeyT>
	struct Set
	{
	public:
		//! Un unordered set table
		typedef std::set<KeyT> Hash;

		//! Un ordered dictionary table
		typedef std::set<KeyT> Ordered;

	}; // struct Set



	//! Convenient typedef for a key/value store
	typedef Dictionary<String, String>::Hash  KeyValueStore;


} // namespace Yuni

#endif // __YUNI_CORE_DICTIONARY_H__
