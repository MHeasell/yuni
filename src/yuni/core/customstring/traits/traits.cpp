
#include "../../../yuni.h"
#include "traits.h"
#include <ctype.h>


namespace Yuni
{
namespace Private
{
namespace CustomStringImpl
{


	bool Equals(const char* const s1, const char* const s2, unsigned int len)
	{
		for (unsigned int i = 0; i != len; ++i)
		{
			if (s1[i] != s2[i])
				return false;
		}
		return true;
	}

	
	bool EqualsInsensitive(const char* const s1, const char* const s2, unsigned int len)
	{
		for (unsigned int i = 0; i != len; ++i)
		{
			if (tolower(s1[i]) != tolower(s2[i]))
				return false;
		}
		return true;
	}


	int Compare(const char* const s1, unsigned int l1, const char* const s2, unsigned int l2)
	{
		const unsigned int l = (l1 < l2) ? l1 : l2;

		for (unsigned int i = 0; i != l; ++i)
		{
			if (s1[i] != s2[i])
				return (((unsigned char)s1[i] < (unsigned char)s2[i]) ? -1 : +1);
		}
		return (l1 == l2) ? 0 : ((l1 < l2) ? -1 : +1);
	}


	int CompareInsensitive(const char* const s1, unsigned int l1, const char* const s2, unsigned int l2)
	{
		const unsigned int l = (l1 < l2) ? l1 : l2;

		for (unsigned int i = 0; i != l; ++i)
		{
			if (tolower(s1[i]) != tolower(s2[i]))
				return ((tolower((unsigned char)s1[i]) < tolower((unsigned char)s2[i])) ? -1 : +1);
		}
		return (l1 == l2) ? 0 : ((l1 < l2) ? -1 : +1);
	}



} // namespace CustomStringImpl
} // namespace Private
} // namespace Yuni


