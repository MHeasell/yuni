
namespace Yuni
{
namespace Core
{

	inline SmallObjAllocator& SmallObjAllocator::Instance()
	{
		static SmallObjAllocator* instance = NULL;
		if (!instance)
			instance = new SmallObjAllocator();
		return *instance;
	}

	SmallObjAllocator::SmallObjAllocator()
		:pPool(NULL)
	{
		const std::size_t allocCount = getOffset(YUNI_MAX_SMALL_OBJECT_SIZE, YUNI_OBJECT_ALIGNMENT);
		pPool = new Private::Allocator[allocCount];
		for (std::size_t i = 0; i < allocCount; ++i)
			pPool[i].initialize((i + 1) * YUNI_OBJECT_ALIGNMENT, YUNI_CHUNK_SIZE);
	}


	SmallObjAllocator::~SmallObjAllocator()
	{
		delete[] pPool;
	}

	void* SmallObjAllocator::allocate(std::size_t numBytes)
	{
		// Fallback on default allocator
		if (numBytes > YUNI_MAX_SMALL_OBJECT_SIZE)
			return ::operator new(numBytes);

		if (0 == numBytes)
			numBytes = 1;

		const std::size_t index = getOffset(numBytes, YUNI_OBJECT_ALIGNMENT) - 1;
		Private::Allocator& allocator = pPool[index];
		void* place = allocator.allocate();

		if ((NULL == place) && trimExcessMemory())
			place = allocator.allocate();
 		return place;
	}

	void SmallObjAllocator::deallocate(void* ptr, std::size_t numBytes)
	{
		if (NULL == ptr)
			return;
		// Fallback on default deallocator
		if (numBytes > YUNI_MAX_SMALL_OBJECT_SIZE)
		{
			::operator delete(ptr);
			return;
		}

		if (0 == numBytes)
			numBytes = 1;
		const std::size_t index = getOffset(numBytes, YUNI_OBJECT_ALIGNMENT) - 1;
		Private::Allocator& allocator = pPool[index];
		allocator.deallocate(ptr, NULL);
	}

	void SmallObjAllocator::deallocate(void* ptr)
	{
		if (NULL == ptr)
			return;
		Private::Allocator* allocator = NULL;
		const std::size_t allocCount = getOffset(YUNI_MAX_SMALL_OBJECT_SIZE, YUNI_OBJECT_ALIGNMENT);
		Private::Chunk* chunk = NULL;

		// Search for the correct allocator
		// (the one allocating objects of this size)
		for (std::size_t size = 0; size < allocCount; ++size)
		{
			chunk = pPool[size].containsBlock(ptr);
			if (NULL != chunk)
			{
				allocator = &pPool[size];
				break;
			}
		}
		// Fallback on default deallocator
		if (NULL == allocator)
		{
			::operator delete(ptr);
			return;
		}

		allocator->deallocate(ptr, chunk);
	}

	bool SmallObjAllocator::trimExcessMemory()
	{
		bool found = false;
		const std::size_t allocCount = getOffset(YUNI_MAX_SMALL_OBJECT_SIZE, YUNI_OBJECT_ALIGNMENT);
		std::size_t i;

		for (i = 0; i < allocCount; ++i)
			if (pPool[i].trimEmptyChunk())
				found = true;
		for (i = 0; i < allocCount; ++i)
			if (pPool[i].trimChunkList())
				found = true;
 
		return found;
	}

} // Core
} // Yuni
