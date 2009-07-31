
#include <cstdlib>
#include "chunk.h"

namespace Yuni
{
namespace Core
{
namespace Private
{
	bool Chunk::initialize(std::size_t blockSize, unsigned char blocks)
	{
		const std::size_t allocSize = blockSize * blocks;

		// malloc can't throw, so its only way to indicate an error is to return
		// a NULL pointer, so we have to check for that.
		pData = static_cast<unsigned char*>(::std::malloc(allocSize));
		if (NULL == pData)
			return false;

		reset(blockSize, blocks);
		return true;
	}

	void Chunk::reset(std::size_t blockSize, unsigned char blocks)
	{
		pFirstAvailableBlock = 0;
		pBlocksAvailable = blocks;

		// Set up the linked list of blocks
		unsigned char i = 0;
		for (unsigned char* p = pData; i != blocks; p += blockSize)
			*p = ++i;
	}

	void Chunk::release()
	{
		::std::free(static_cast<void*>(pData));
	}

	void* Chunk::allocate(std::size_t blockSize)
	{
		if (isFull())
			return NULL;

		unsigned char* result = pData + (pFirstAvailableBlock * blockSize);
		pFirstAvailableBlock = *result;
		--pBlocksAvailable;

		return result;
	}

	void Chunk::deallocate(void* p, std::size_t blockSize)
	{
		unsigned char* toRelease = static_cast<unsigned char*>(p);
		unsigned char index =
			static_cast<unsigned char>((toRelease - pData) / blockSize);

		*toRelease = pFirstAvailableBlock;
		pFirstAvailableBlock = index;
		++pBlocksAvailable;
	}

} // Private
} // Core
} // Yuni
