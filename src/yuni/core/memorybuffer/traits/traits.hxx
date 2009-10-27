#ifndef __YUNI_CORE_MEMORY_BUFFER_TRAITS_HXX__
# define __YUNI_CORE_MEMORY_BUFFER_TRAITS_HXX__



namespace Yuni
{
namespace Private
{
namespace MemoryBufferImpl
{


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	void Data<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::reserve(Size minCapacity)
	{
		minCapacity += zeroTerminated;
		if (capacity < minCapacity)
		{
			// This loop is a little faster than the following replacement code :
			// capacity = minCapacity + minCapacity % chunkSize;
			do
			{
				// Increase the capacity until we have enough space
				capacity += chunkSize;
			} while (capacity < minCapacity);

			// Realloc the internal buffer
			data = (C*) ::realloc(data, sizeof(C) * capacity);
			// The variable data might be null before calling this method
			// We have to make sure that it is really zero-terminated
			if (ZeroTerminatedT)
				data[size] = C(0);
		}
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT>
	typename Data<C,ChunkSizeT,ZeroTerminatedT,false>::Size
	Data<C,ChunkSizeT,ZeroTerminatedT,false>::assignWithoutChecking(const C* block, Size blockSize)
	{
		// We have to trunk the size if we are outer limits
		// This condition is a little faster than the folowing replacement code :
		// blockSize = Math::Min<Size>(blockSize, capacity - size);
		//
		// We have better performance if the two cases have their own code block
		// (perhaps because of the constant values)
		//
		if (blockSize > capacity)
		{
			// The new blocksize is actually the capacity itself
			// The capacity can not be null
			// Raw copy
			(void)::memcpy(data, block, sizeof(C) * capacity);
			// New size
			size = capacity;
			if (zeroTerminated)
				data[capacity] = C(0);
			return capacity;
		}
		// else
		{
			// Raw copy
			(void)::memcpy(data, block, sizeof(C) * blockSize);
			// New size
			size = blockSize;
			if (zeroTerminated)
				data[size] = C(0);
			return blockSize;
		}
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT>
	typename Data<C,ChunkSizeT,ZeroTerminatedT,false>::Size
	Data<C,ChunkSizeT,ZeroTerminatedT,false>::appendWithoutChecking(const C* block, Size blockSize)
	{
		// We have to trunk the size if we are outer limits
		// This condition is a little faster than the folowing replacement code :
		// blockSize = Math::Min<Size>(blockSize, capacity - size);
		//
		// We have better performance if the two cases have their own code block
		// (perhaps because of the constant values)
		//
		if (blockSize + size > capacity)
		{
			// Computing the new block size to copy
			blockSize = capacity - size;
			// The performance are a bit better if we interupt the process sooner
			if (!blockSize)
				return 0;
			// Raw copy
			(void)::memcpy(data + size, block, sizeof(C) * blockSize);
			// New size
			size = capacity;
			if (zeroTerminated)
				data[capacity] = C(0);
			return blockSize;
		}
		// else
		{
			// Raw copy
			(void)::memcpy(data + size, block, sizeof(C) * blockSize);
			// New size
			size += blockSize;
			if (zeroTerminated)
				data[size] = C(0);
			return blockSize;
		}
	}

	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT>
	inline typename Data<C,ChunkSizeT,ZeroTerminatedT,false>::Size
	Data<C,ChunkSizeT,ZeroTerminatedT,false>::assignWithoutChecking(const C c)
	{
		data[0] = c;
		size = 1;
		if (zeroTerminated)
			data[1] = C(0);
		return 1;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT>
	typename Data<C,ChunkSizeT,ZeroTerminatedT,false>::Size
	Data<C,ChunkSizeT,ZeroTerminatedT,false>::appendWithoutChecking(const C c)
	{
		if (size == capacity)
			return 0;
		// else
		{
			data[size] = c;
			++size;
			if (zeroTerminated)
				data[size] = C(0);
			return 1;
		}
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT>
	void Data<C,ChunkSizeT,ZeroTerminatedT,false>::putc(const C rhs)
	{
		// Making sure that we have enough space
		if (size != capacity)
		{
			// Raw copy
			data[size] = rhs;
			// New size
			++size;
			if (zeroTerminated)
				data[size] = C();
		}
	}




} // namespace MemoryBufferImpl
} // namespace Private
} // namespace Yuni

#endif // __YUNI_CORE_MEMORY_BUFFER_TRAITS_HXX__
