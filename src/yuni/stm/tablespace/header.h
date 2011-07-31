#ifndef __YUNI_STM_TABLESPACE_INFO_H__
# define __YUNI_STM_TABLESPACE_INFO_H__

# include "../../yuni.h"


namespace Yuni
{
namespace STM
{
namespace Tablespace
{


	class Header
	{
	public:
		unsigned int size() const {return pBlockSize;}

		unsigned int count() const {return pBlockCapacity - pBlockFree;}

		unsigned int capacity() const {return pBlockCapacity;}

		unsigned int free() const {return pBlockFree;}

	private:
		unsigned int pBlockSize;
		unsigned int pBlockCapacity;
		unsigned int pBlockFree;

	};



} // namespace Tablespace
} // namespace STM
} // namespace Yuni

#endif // __YUNI_STM_TABLESPACE_INFO_H__
