#ifndef __YUNI_CORE_DICTIONARY_H__
# define __YUNI_CORE_DICTIONARY_H__

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



} // namespace Yuni

#endif // __YUNI_CORE_DICTIONARY_H__
