
#include "utils.h"


namespace Yuni
{
namespace DBI
{


	bool IsValidIdentifier(AnyString text)
	{
		text.trim();
		if (text.empty() or text.size() > 256)
			return false;

		for (uint i = 0; i != text.size(); ++i)
		{
			char c = text[i];
			if (not String::IsAlpha(c) and not String::IsDigit(c) and c != '_' and c != '.')
				return false;
		}

		if (text.first() == '.' or text.last() == '.')
			return false;

		return true;
	}




} // namespace DBI
} // namespace Yuni

