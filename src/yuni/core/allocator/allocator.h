#ifndef __YUNI_CORE_ALLOCATOR_ALLOCATOR_H__
# define __YUNI_CORE_ALLOCATOR_ALLOCATOR_H__

# include <vector>
# include "chunk.h"

namespace Yuni
{
namespace Core
{
namespace Private
{

	/*!
	** \brief Allocator that works with a fixed given size
	**
	** It can only allocate objects of this size
	** \ingroup Alloc
	*/
	class Allocator
	{
	private:
		//! Type of container used to hold Chunks.
		typedef std::vector<Chunk> ChunkVector;

		//! Iterator through container of Chunks.
		typedef ChunkVector::iterator ChunkIter;

        //! Iterator through const container of Chunks.
        typedef ChunkVector::const_iterator ChunkCIter;

	private:
        //! Fewest # of objects managed by a Chunk.
        static unsigned char pMinObjectsPerChunk;

        //! Most # of objects managed by a Chunk - never exceeds UCHAR_MAX.
        static unsigned char pMaxObjectsPerChunk;

	public:
        //! Constructor
		Allocator();

		//! Destructor
		~Allocator();

		//! Initialize an Allocator by calculating # of blocks per Chunk.
		void initialize(std::size_t blockSize, std::size_t pageSize);

		/*!
		** Returns pointer to allocated memory block of fixed size - or NULL
		** if it failed to allocate.
		*/
		void* allocate(void);

		/*!
		** \brief Deallocate a memory block previously allocated with Allocate.
		** If the block is not owned by this FixedAllocator, it returns false
		** so that SmallObjAllocator can call the default deallocator.  If the
		** block was found, this returns true.
		*/
		bool deallocate(void* ptr, Chunk* hint);

		//! Returns block size with which the Allocator was initialized.
		inline std::size_t blockSize() const { return pBlockSize; }

		/*!
		** Releases the memory used by the empty Chunk.
		** \return True if empty chunk found and released, false if none empty.
		*/
		bool trimEmptyChunk(void);

		/*!
		** Releases unused spots from Chunk list.  This takes constant time
		** with respect to # of Chunks, but actual time depends on underlying
		** memory allocator.
		** \return False if no unused spots, true if some found and released.
		*/
		bool trimChunkList(void);

		/*!
		** \brief Is the block at ptr within a Chunk owned by this Allocator?
		*/
		const Chunk* containsBlock(void* ptr) const;
		inline Chunk* containsBlock(void* ptr)
		{
			return const_cast<Chunk*>(
				const_cast<const Allocator*>(this)->containsBlock(ptr));
		}

	private:
		/*!
		** Deallocates the block at address p, and then handles the internal
        ** bookkeeping needed to maintain class invariants.  This assumes that
		** pDeallocChunk points to the correct chunk.
		*/
		void doDeallocate(void* ptr);

		/*!
		** \brief Create a new empty Chunk and add it to the Chunk list.
		**
		** \return true for success, false for failure.
		*/
		bool createChunk(void);

		/*!
		** \brief Find the Chunk which owns the block at address ptr.
		**
		** Start at pDeallocChunk and search in both forwards and backwards
		** directions from there until you find the Chunk which owns p.
		** \return Pointer to Chunk that owns p, or NULL if no owner found.
		*/
		Chunk* vicinityFind(void* ptr) const;

		//! Private => forbidden
		Allocator(const Allocator&);
		//! Private => forbidden
		Allocator& operator=(const Allocator&);

        //! Number of bytes in a single block within a Chunk.
        std::size_t pBlockSize;
        //! Number of blocks managed by each Chunk.
        unsigned char pNumBlocks;

        //! Container of Chunks.
        ChunkVector pChunks;
        //! Pointer to Chunk used for last or next allocation.
        Chunk* pAllocChunk;
        //! Pointer to Chunk used for last or next deallocation.
        Chunk* pDeallocChunk;
        //! Pointer to the only empty Chunk if there is one, else NULL.
        Chunk* pEmptyChunk;
    };

} // Private
} // Core
} // Yuni

#endif // __YUNI_CORE_ALLOCATOR_SMALLOBJECT_H__
