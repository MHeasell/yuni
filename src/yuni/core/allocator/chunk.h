#ifndef __YUNI_CORE_ALLOCATOR_CHUNK_H__
# define __YUNI_CORE_ALLOCATOR_CHUNK_H__

namespace Yuni
{
namespace Core
{
namespace Private
{
	// Forward declaration
	class Allocator;

	/*!
	** \brief A chunk is a memory unit used to factor calls to new/delete.
	**
	** \ingroup Alloc
	*/
	class Chunk
	{
	private:
		//! Friend declaration. Only Allocator can access Chunk's data
		friend class Allocator;

		/*!
		** \brief Initializes a just-constructed Chunk.
		** \param blockSize Number of bytes per block.
		** \param blocks Number of blocks per Chunk.
		** \return True for success, false for failure.
		*/
		bool initialize(std::size_t blockSize, unsigned char blocks);

		/*!
		** \brief Allocate a block within the Chunk.
		**
		** Does not actually "allocate" by calling malloc, new, or any other
		** function, but merely adjusts some internal indices to indicate an
		** already allocated block is no longer available.
		** @return Pointer to a block within the Chunk.
		*/
		void* allocate(std::size_t blockSize);

		/*!
		** \brief Deallocate a block within the Chunk.
		**
		** Does not actually "deallocate" by calling free, delete, or other
		** function, but merely adjusts some internal indices to indicate a
		** block is now available.
		*/
		void deallocate(void* p, std::size_t blockSize);

		/*!
		** \brief Resets the Chunk back to pristine values.
		**
		** The available count is set back to zero, and the first available
		** index is set to the first block. The stealth indices inside each
		** block are set to point to the next block. This assumes the Chunk's
		** data was already using init.
		*/
		void reset( std::size_t blockSize, unsigned char blocks );

		//! Releases the allocated block of memory.
		void release();

		//! Returns true if this Chunk contains exactly numBlocks blocks.
		bool hasAvailable(unsigned char numBlocks) const
		{
			return pBlocksAvailable == numBlocks;
		}


		//! Returns true if block in ptr is inside this Chunk.
		bool containsBlock(void* ptr, std::size_t chunkLength) const
		{
			unsigned char* pc = static_cast<unsigned char*>(ptr);
			return (pData <= pc) && (pc < pData + chunkLength);
		}

		//! Is the chunk full? (no more allocation possible)
		bool isFull() const
		{
			return 0 == pBlocksAvailable;
		}

	private:
		/// Pointer to array of allocated blocks.
		unsigned char* pData;
		/// Index of first empty block.
		unsigned char pFirstAvailableBlock;
		/// Count of available blocks.
		unsigned char pBlocksAvailable;
	};

} // Private
} // Core
} // Yuni

#endif // __YUNI_CORE_ALLOCATOR_CHUNK_H__
