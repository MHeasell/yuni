#ifndef __YUNI_CORE_ALLOCATOR_SMALLOBJALLOCATOR_H__
# define __YUNI_CORE_ALLOCATOR_SMALLOBJALLOCATOR_H__

# include <cstddef>
# include "../../threads/policy.h"
# include "allocator.h"

# ifndef YUNI_CHUNK_SIZE
#	define YUNI_CHUNK_SIZE 4096
# endif

# ifndef YUNI_MAX_SMALL_OBJECT_SIZE
#	define YUNI_MAX_SMALL_OBJECT_SIZE 256
# endif

# ifndef YUNI_OBJECT_ALIGNMENT
#	define YUNI_OBJECT_ALIGNMENT 4
# endif

namespace Yuni
{
namespace Core
{

	/*!
	** \brief Singleton used for all small object allocations / deallocations
	**
	** \ingroup Alloc
	*/
	class SmallObjAllocator
	{
	public:
		static SmallObjAllocator& Instance();

	public:
		//! Destructor
		~SmallObjAllocator();

		/*!
		** \brief Do an allocation of given size
		** \param size Size of data to allocate
		** \returns Allocated pointer
		*/
		void* allocate(std::size_t numBytes);

		/*!
		** \brief Deallocate given pointer of given size
		** \param ptr Pointer to deallocate
		** \param size Size of deallocated data
		*/
		void deallocate(void* ptr, std::size_t numBytes);
		void deallocate(void* ptr);

	private:
		//! Private => forbidden
		SmallObjAllocator();
		//! Private => forbidden
		SmallObjAllocator(const SmallObjAllocator&);
		//! Private => forbidden
		SmallObjAllocator& operator = (const SmallObjAllocator&);

		//! Calculate an offset using a given number of bytes and the alignment value
		std::size_t getOffset(std::size_t numBytes, std::size_t alignment)
		{
			const std::size_t alignExtra = alignment - 1;
			return (numBytes + alignExtra) / alignment;
		}

		/*!
		** \brief Releases empty Chunks from memory.
		** \return True if any memory released, or false if none released.
		*/
		bool trimExcessMemory();

	private:
		//! Pointer to array of fixed-size allocators.
		Private::Allocator* pPool;
	};

} // Core
} // Yuni

# include "smallobjallocator.hxx"

#endif // __YUNI_CORE_ALLOCATOR_SMALLOBJALLOCATOR_H__
