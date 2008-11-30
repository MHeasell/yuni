#ifndef __YUNI_HASH_KEY_H__
# define __YUNI_HASH_KEY_H__

# include "../yuni.h"
# include "../toolbox/string.h"
# include "std.hashmap.h"



namespace Yuni
{
namespace Hash
{


	class Key
	{
	public:
		//! Default Constructor
		Key() : pID(0) {}
		//! Constructor with a given unique ID
		Key(const size_t i) : pID(i) {}

		/*!
		** \brief Get the unique ID
		*/
		const size_t uid() const {return pID;}

	protected:
		size_t pID;

	}; // class Hash::Key


} // namespace Hash
} // namespace Yuni




/*!
** \internal __gnu_cxx is deprecated in C++0x
*/

# ifdef YUNI_OS_GNU_HASH_MAP
#	define YUNI_OS_HASH_MAP_INHERIT
#	define YUNI_OS_HASH_MAP_FUN hash
namespace __gnu_cxx
# else
#	define YUNI_OS_HASH_MAP_FUN hash_compare
#	define YUNI_OS_HASH_MAP_INHERIT  : public stdext::hash_compare <std::string>
namespace stdext
# endif
{

	template<>
	class YUNI_OS_HASH_MAP_FUN <Yuni::Hash::Key> YUNI_OS_HASH_MAP_INHERIT
	{
	public:
		size_t operator()(const Yuni::Hash::Key& __s) const
		{ return __s.uid(); }

		bool operator () (const Yuni::Hash::Key& lhs, const Yuni::Hash::Key& rhs) const
		{ return lhs.uid() < rhs.uid(); }
	};


	template <>
	class YUNI_OS_HASH_MAP_FUN <Yuni::String> YUNI_OS_HASH_MAP_INHERIT
	{
	public:
		size_t operator () (const Yuni::String& str) const
		{
			YUNI_OS_HASH_MAP_FUN <char const *> h;
			return (h(str.c_str()));
		}

		bool operator () (const Yuni::String& lhs, const Yuni::String& rhs) const
		{ return lhs < rhs; }
	};

} // namespace YuniSTLExt


#endif // __YUNI_HASH_KEY_H__
