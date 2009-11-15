#ifndef __YUNI_CORE_MEMORY_BUFFER_MEMORY_BUFFER_HXX__
# define __YUNI_CORE_MEMORY_BUFFER_MEMORY_BUFFER_HXX__


namespace Yuni
{
namespace Core
{


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::MemoryBuffer()
	{}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::MemoryBuffer(const MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>& rhs)
		:AncestorType(rhs)
	{}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::MemoryBuffer(const U& rhs)
	{
		Private::MemoryBufferImpl::Assign<MemoryBufferType, typename Static::Remove::Const<U>::Type>::Do(*this, rhs);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::MemoryBuffer(const C* block, const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size blockSize)
	{
		AncestorType::assign(block, blockSize);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline void MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::assign(const U& rhs)
	{
		Private::MemoryBufferImpl::Assign<MemoryBuffer, typename Static::Remove::Const<U>::Type>::Do(*this, rhs);
		return *this;
	}

	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline void MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::append(const U& rhs)
	{
		Private::MemoryBufferImpl::Append<MemoryBuffer, typename Static::Remove::Const<U>::Type>::Do(*this, rhs);
		return *this;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	void MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::fill(const U& pattern)
	{
		if (AncestorType::size)
		{
			Private::MemoryBufferImpl::Fill<MemoryBuffer, typename Static::Remove::Const<U>::Type>
				::Do(AncestorType::data, AncestorType::size, pattern);
		}
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::find(const C buffer) const
	{
		for (Size i = 0; i != AncestorType::size; ++i)
		{
			if (buffer == AncestorType::data[i])
				return i;
		}
		return npos;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::find(const C* buffer,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size len) const
	{
		if (buffer && len && len <= AncestorType::size)
		{
			const Size end = AncestorType::size - len + 1;
			for (Size i = 0; i != end; ++i)
			{
				if (AncestorType::data[i] == *buffer)
				{
					if (!::memcmp(AncestorType::data + i, buffer, len))
						return i;
				}
			}
		}
		return npos;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::find_first_of(const U& u) const
	{
		return find(u);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::erase(
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size offset,
		const typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size len)
	{
		// Only valid if the offset is strictly less than the current size
		if (offset < AncestorType::size && len)
		{
			// If the number of items to erase is greater than the current size
			// then all characters after 'offset' are dead
			if (offset + len > AncestorType::size)
				AncestorType::size = offset;
			else
			{
				// Actually we have to erase a part of the buffer
				(void)::memmove(AncestorType::data + sizeof(C) * (offset),
								AncestorType::data + sizeof(C) * (offset + len), sizeof(C) * (AncestorType::size - offset));
				// Reducing the buffer's size
				AncestorType::size -= len;
			}
			if (zeroTerminated)
				AncestorType::data[AncestorType::size] = C();
		}
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::truncate(const Size newSize)
	{
		if (newSize < AncestorType::size)
			AncestorType::size = newSize;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::size() const
	{
		return AncestorType::size;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::capacity() const
	{
		return AncestorType::capacity;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline const C*
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::data() const
	{
		return AncestorType::data;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline C*
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::data()
	{
		return AncestorType::data;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline void
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::resize(inline typename MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::Size len)
	{
		if (AncestorType::expandable)
		{
			// Dynamic buffer
			AncestorType::reserve(len + AncestorType::zeroTerminated);
			AncestorType::size = len;
		}
		else
		{
			// Static buffer
			AncestorType::size = (len <= AncestorType::chunkSize) ? len : AncestorType::chunkSize;
		}
		// Zero-Terminated buffers
		if (zeroTerminated)
			AncestorType::data[AncestorType::size] = C();
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline bool
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::operator != (const U& rhs) const
	{
		return !(*this == rhs);
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline bool
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::operator ! () const
	{
		return !AncestorType::size;
	}



	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>&
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::operator += (const U& rhs)
	{
		Private::MemoryBufferImpl::Append<MemoryBuffer, U>::Do(*this, rhs);
		return *this;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>&
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::operator << (const U& rhs)
	{
		Private::MemoryBufferImpl::Append<MemoryBuffer, U>::Do(*this, rhs);
		return *this;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	inline MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>&
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::operator = (const MemoryBuffer& rhs)
	{
		Private::MemoryBufferImpl::Assign<MemoryBuffer, typename Static::Remove::Const<C>::Type>::Do(*this, rhs);
		return *this;
	}


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	template<class U>
	inline MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>&
	MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>::operator = (const U& rhs)
	{
		Private::MemoryBufferImpl::Assign<MemoryBuffer, typename Static::Remove::Const<U>::Type>::Do(*this, rhs);
		return *this;
	}





} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_MEMORY_BUFFER_MEMORY_BUFFER_HXX__
