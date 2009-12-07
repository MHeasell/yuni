#ifndef __YUNI_CORE_MEMORY_BUFFER_TRAITS_TRAITS_H__
# define __YUNI_CORE_MEMORY_BUFFER_TRAITS_TRAITS_H__

# include <stdlib.h>
# include <string.h>
# include <wchar.h>
# include "../../math/math.h"



namespace Yuni
{
namespace Private
{
namespace MemoryBufferImpl
{



	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool Expandable>
	struct Data
	{
	public:
		typedef unsigned int Size;
		enum
		{
			chunkSize = ChunkSizeT,
			zeroTerminated = (ZeroTerminatedT ? 1 : 0),
			expandable = 1,
		};
	public:
		Data()
			:size(0), capacity(0), data(NULL)
		{}

		Data(const Data& rhs)
			:size(rhs.size), capacity(rhs.size), data(NULL)
		{
			if (size)
			{
				capacity += zeroTerminated;
				data = (C*)::malloc(sizeof(C) * capacity);
				(void)::memcpy(data, rhs.data, sizeof(C) * size);
				if (zeroTerminated)
					data[size] = C();
			}
		}

		~Data()
		{
			// Release the internal buffer if allocated
			::free(data);
		}

		void clear()
		{
			if (zeroTerminated)
			{
				if (size)
				{
					size = 0;
					data[0] = C();
				}
			}
			else
			{
				size = 0;
			}
		}

		Size assignWithoutChecking(const C* block, const Size blockSize)
		{
			// Making sure that we have enough space
			reserve(blockSize + zeroTerminated);
			// Raw copy
			(void)::memcpy(data, block, blockSize);
			// New size
			size = blockSize;
			if (zeroTerminated)
				data[size] = C();
			return blockSize;
		}


		Size appendWithoutChecking(const C* block, const Size blockSize)
		{
			// Making sure that we have enough space
			reserve(size + blockSize + zeroTerminated);
			// Raw copy
			(void)::memcpy(data + size, block, blockSize);
			// New size
			size += blockSize;
			if (zeroTerminated)
				data[size] = C();
			return blockSize;
		}

		Size assignWithoutChecking(const C c)
		{
			// Making sure that we have enough space
			reserve(1 + zeroTerminated);
			// Raw copy
			data[0] = c;
			// New size
			size = 1;
			if (zeroTerminated)
				data[1] = C();
			return 1;
		}


		Size appendWithoutChecking(const C c)
		{
			// Making sure that we have enough space
			reserve(size + 1 + zeroTerminated);
			// Raw copy
			data[size] = c;
			// New size
			++size;
			if (zeroTerminated)
				data[size] = C();
			return 1;
		}


		Size assign(const C* block, const Size blockSize)
		{
			return (block && blockSize) ? assignWithoutChecking(block, blockSize) : 0;
		}


		Size append(const C* block, const Size blockSize)
		{
			return (block && blockSize) ? appendWithoutChecking(block, blockSize) : 0;
		}

		void put(const C rhs)
		{
			// Making sure that we have enough space
			reserve(size + 1 + zeroTerminated);
			// Raw copy
			data[size] = rhs;
			// New size
			++size;
			if (zeroTerminated)
				data[size] = C();
		}


		void reserve(Size minCapacity);

		void insert(Size offset, const C* buffer, const Size len)
		{
			// Reserving enough space to insert the buffer
			reserve(len + size + zeroTerminated);
			// Move the existing block of data
			(void)::memmove(data + sizeof(C) * (offset + len), data + sizeof(C) * (offset), sizeof(C) * (size - offset));
			// Copying the given buffer
			(void)::memcpy(data + sizeof(C) * (offset), buffer, sizeof(C) * len);
			// Updating the size
			size += len;
			// zero-terminated
			if (zeroTerminated)
				data[size] = C();
		}

	protected:
		Size size;
		Size capacity;
		C* data;
	}; // class Data





	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT>
	struct Data<C, ChunkSizeT, ZeroTerminatedT, false>
	{
	public:
		typedef unsigned int Size;
		enum
		{
			chunkSize = ChunkSizeT,
			capacity = ChunkSizeT,
			zeroTerminated = (ZeroTerminatedT ? 1 : 0),
			expandable = 0,
		};

	public:
		Data()
			:size(0)
		{
			// The buffer must be properly initialized
			if (zeroTerminated)
				data[0] = C();
		}

		Data(const Data& rhs)
			:size(rhs.size)
		{
			(void)::memcpy(data, rhs.data, sizeof(C) * (size + zeroTerminated));
		}

		void clear()
		{
			size = 0;
			if (zeroTerminated)
				data[0] = C();
		}

		Size assignWithoutChecking(const C* block, Size blockSize);

		Size appendWithoutChecking(const C* block, Size blockSize);

		Size assignWithoutChecking(const C c);

		Size appendWithoutChecking(const C c);


		Size assign(const C* block, const Size blockSize)
		{
			return (block && blockSize) ? assignWithoutChecking(block, blockSize) : 0;
		}

		Size append(const C* block, const Size blockSize)
		{
			return (block && blockSize) ? appendWithoutChecking(block, blockSize) : 0;
		}

		void put(const C rhs);

		static void reserve(const Size)
		{
			// Do nothing
		}

		void insert(Size offset, const C* buffer, Size len)
		{
			if (offset + len >= capacity)
			{
				// The new buffer will take the whole space
				(void)::memcpy(data + sizeof(C) * (offset), buffer, sizeof(C) * (capacity - offset));
				size = capacity;
				if (zeroTerminated)
					data[capacity] = C();
				return;
			}
			if (size + len <= capacity)
			{
				// Move the existing block of data
				(void)::memmove(data + sizeof(C) * (offset + len), data + sizeof(C) * (offset), sizeof(C) * (size - offset));
				// Copying the given buffer
				(void)::memcpy(data + sizeof(C) * (offset), buffer, sizeof(C) * len);
				// Updating the size
				size += len;
				// zero-terminated
				if (zeroTerminated)
					data[size] = C();
			}
			else
			{
				// Move the existing block of data
				(void)::memmove(data + sizeof(C) * (offset + len), data + sizeof(C) * (offset), sizeof(C) * (capacity - offset - len));
				// Copying the given buffer
				(void)::memcpy(data + sizeof(C) * (offset), buffer, sizeof(C) * len);
				// Updating the size
				size = capacity;
				// zero-terminated
				if (zeroTerminated)
					data[capacity] = C();
			}
		}

	protected:
		Size size;
		C data[capacity + zeroTerminated];

	}; // class Data;






} // namespace MemoryBufferImpl
} // namespace Private
} // namespace Yuni

# include "traits.hxx"

#endif // __YUNI_CORE_MEMORY_BUFFER_TRAITS_TRAITS_H__
