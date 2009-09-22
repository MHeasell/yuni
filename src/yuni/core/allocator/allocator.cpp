
# include <climits>
# include "../stl/algorithm.h"
# include "allocator.h"

namespace Yuni
{
namespace Core
{
namespace Private
{

	Allocator::Allocator()
		:pBlockSize(0), pNumBlocks(0), pChunks(0),
		 pAllocChunk(NULL), pDeallocChunk(NULL), pEmptyChunk(NULL)
	{
	}

	Allocator::~Allocator()
	{
	}

	void Allocator::initialize(std::size_t blockSize, std::size_t pageSize)
	{
		pBlockSize = blockSize;

		std::size_t numBlocks = pageSize / blockSize;
		if (numBlocks > pMaxObjectsPerChunk)
			numBlocks = pMaxObjectsPerChunk;
		else if (numBlocks < pMinObjectsPerChunk)
			numBlocks = pMinObjectsPerChunk;

		pNumBlocks = static_cast<unsigned char>(numBlocks);
	}

	void* Allocator::allocate()
	{
		if ((NULL == pAllocChunk) || pAllocChunk->isFull())
		{
			if (NULL != pEmptyChunk)
			{
				pAllocChunk = pEmptyChunk;
				pEmptyChunk = NULL;
			}
			else
			{
				for (ChunkIter it(pChunks.begin()); ; ++it)
				{
					if (pChunks.end() == it)
					{
						if (!createChunk())
							return NULL;
						break;
					}
					if (!it->isFull())
					{
                       pAllocChunk = &*it;
					   break;
					}
				}
			}
		}
		else if (pAllocChunk == pEmptyChunk)
			// Detach pEmptyChunk from pAllocChunk, because after
			// calling pAllocChunk->allocate(pBlockSize); the chunk
			// is no longer empty.
			pEmptyChunk = NULL;

		void* place = pAllocChunk->allocate(pBlockSize);

		return place;
	}

	bool Allocator::deallocate(void* ptr, Chunk* hint)
	{
		Chunk* foundChunk = (NULL == hint) ? vicinityFind(ptr) : hint;
		if (NULL == foundChunk)
			return false;

		pDeallocChunk = foundChunk;
		doDeallocate(ptr);
		return true;
  }

	bool Allocator::trimEmptyChunk( void )
	{
		// Either pEmptyChunk is NULL, or it points to an empty Chunk.
		if (NULL == pEmptyChunk)
			return false;

		// Make sure the empty chunk is at the end
		Chunk* lastChunk = &pChunks.back();
		if (lastChunk != pEmptyChunk)
			// If not, swap the two chunks
			std::swap(*pEmptyChunk, *lastChunk);

		// Free the empty chunk
		lastChunk->release();
		pChunks.pop_back();

		// Check if it was the last chunk
		if (pChunks.empty())
		{
			pAllocChunk = NULL;
			pDeallocChunk = NULL;
		}
		else
		{
			// If our last alloc/last dealloc pointers pointed on this chunk,
			// reinitialize them to the front/back chunks.
			if (pDeallocChunk == pEmptyChunk)
				pDeallocChunk = &pChunks.front();
			if (pAllocChunk == pEmptyChunk )
				pAllocChunk = &pChunks.back();
		}

		// We just destroyed the empty chunk, no chunk is empty anymore
		pEmptyChunk = NULL;
		return true;
	}

	bool Allocator::trimChunkList()
	{
		if (pChunks.size() == pChunks.capacity())
			return false;
		// Use the "make-a-temp-and-swap" trick to remove excess capacity.
		ChunkVector(pChunks).swap(pChunks);
		return true;
	}

	const Chunk* Allocator::containsBlock(void* ptr) const
	{
		const std::size_t chunkLength = pNumBlocks * pBlockSize;
		// Loop on chunks
		for (ChunkCIter it(pChunks.begin()); it != pChunks.end(); ++it)
		{
			const Chunk& chunk = *it;
			// If we find the containing chunk
			if (chunk.containsBlock(ptr, chunkLength))
				// Return it
				return &chunk;
		}
		// Otherwise return null
		return NULL;
	}

	Chunk* Allocator::vicinityFind(void* ptr) const
	{
		if (pChunks.empty())
			return NULL;

		const std::size_t chunkLength = pNumBlocks * pBlockSize;
		Chunk* low = pDeallocChunk;
		Chunk* high = pDeallocChunk + 1;
		const Chunk* lowBound = &pChunks.front();
		const Chunk* highBound = &pChunks.back() + 1;

		// Special case: pDeallocChunk is the last in the array
		if (high == highBound)
			high = NULL;

		while (1)
		{
			if (low)
			{
				if (low->containsBlock(ptr, chunkLength))
					return low;
				if (low == lowBound)
				{
					low = NULL;
					if (NULL == high)
						break;
				}
				else
					--low;
			}

			if (high)
			{
				if (high->containsBlock(ptr, chunkLength))
					return high;
				if (++high == highBound)
				{
					high = NULL;
					if (NULL == low)
						break;
				}
			}
		}

		return NULL;
	}

	void Allocator::doDeallocate(void* ptr)
	{
		// Call into the chunk, will adjust the inner list but won't release memory
		pDeallocChunk->deallocate(ptr, pBlockSize);

		if (pDeallocChunk->hasAvailable(pNumBlocks))
		{
			// pDeallocChunk is empty, but a Chunk is only released if there
			// are 2 empty chunks.
			// Since pEmptyChunk may only point to a previously cleared Chunk,
			// if it points to something else besides pDeallocChunk,
			// then Allocator currently has 2 empty Chunks.
			if (NULL != pEmptyChunk)
			{
				// If last Chunk is empty, just change what pDeallocChunk
				// points to, and release the last.  Otherwise, swap an empty
				// Chunk with the last, and then release it.
				Chunk* lastChunk = &pChunks.back();
				if (lastChunk == pDeallocChunk)
					pDeallocChunk = pEmptyChunk;
				else if (lastChunk != pEmptyChunk)
					std::swap(*pEmptyChunk, *lastChunk);
				lastChunk->release();
				pChunks.pop_back();
				if ((pAllocChunk == lastChunk) || pAllocChunk->isFull())
					pAllocChunk = pDeallocChunk;
			}
			pEmptyChunk = pDeallocChunk;
		}
	}

	bool Allocator::createChunk()
	{
		bool allocated = false;
		// Exceptions are disabled
		//try
		{
			std::size_t size = pChunks.size();
			// Calling pChunks.reserve *before* creating and initializing the new
			// Chunk means that nothing is leaked by this function in case an
			// exception is thrown from reserve.
			if (pChunks.capacity() == size)
			{
				if (0 == size)
					size = 4;
				pChunks.reserve(size * 2);
			}
			Chunk newChunk;
			allocated = newChunk.initialize(pBlockSize, pNumBlocks);
			if (allocated)
				pChunks.push_back(newChunk);
		}
		//catch(...)
		//{
		//	allocated = false;
		//}
		if (!allocated)
			return false;

		pAllocChunk = &pChunks.back();
		pDeallocChunk = &pChunks.front();
		return true;
	}

	unsigned char Allocator::pMinObjectsPerChunk = 8;
	unsigned char Allocator::pMaxObjectsPerChunk = UCHAR_MAX;

} // namespace Private
} // namespace Core
} // namespace Yuni
