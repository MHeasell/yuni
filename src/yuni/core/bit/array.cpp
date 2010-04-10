
#include "array.h"


namespace Yuni
{
namespace Core
{
namespace Bit
{

	bool Array::any() const
	{
		for (unsigned int i = 0; i != pBuffer.size(); ++i)
		{
			if (pBuffer[i] != 0)
				return true;
		}
		return false;
	}

	bool Array::none() const
	{
		for (unsigned int i = 0; i != pBuffer.size(); ++i)
		{
			if (pBuffer[i] != 0)
				return false;
		}
		return true;
	}


	bool Array::all() const
	{
		for (unsigned int i = 0; i != pBuffer.size(); ++i)
		{
			if ((unsigned char)pBuffer[i] != 0xFF)
				return false;
		}
		return true;
	}





} // namespace Bit
} // namespace Core
} // namespace Yuni


