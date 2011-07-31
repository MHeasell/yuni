#ifndef __YUNI_STM_SWAP_FILE_H__
# define __YUNI_STM_SWAP_FILE_H__

# include "../../yuni.h"
# include "header.h"


namespace Yuni
{
namespace STM
{
namespace Tablespace
{

	class Tablespace
	{
	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		Tablespace();
		//! Destructor
		~Tablespace();
		//@}

		//! The current size (in bytes) of the tablespace
		uint64 size() const {return pHeader.size() * pHeader.count();}
		//! The capacity of the tablespace (in bytes)
		uint64 capacity() const {return pBlockCount * pBlockSize;}

		//! Block size (in bytes)
		unsigned int blockSize() const {return pBlockSize;}

		//! The total of blocks in the tablespace
		unsigned int blockCount() const {return pBlockCount;}

	private:
		Header pHeader;

	}; // class Tablespace



} // namespace Tablespace
} // namespace STM
} // namespace Yuni

#endif // __YUNI_STM_SWAP_FILE_H__
