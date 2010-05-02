#ifndef __YUNI_CORE_CUSTOMSTRING_CUSTOMSTRING_HXX__
# define __YUNI_CORE_CUSTOMSTRING_CUSTOMSTRING_HXX__

# include <ctype.h>



namespace Yuni
{


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::CustomString()
	{}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::~CustomString()
	{}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::CustomString(const NullPtr&)
	{}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::CustomString(const CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>& rhs)
		:AncestorType(rhs)
	{}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::CustomString(const U& rhs)
	{
		assign(rhs);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::CustomString(const char* block,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size blockSize)
	{
		AncestorType::assign(block, blockSize);
	}




	namespace
	{
		template<int ValidT>
		struct TraitsSelectorAssign
		{
			template<class U, class CustomStringT>
			static inline void Perform(const U& u, CustomStringT& customstring)
			{
				customstring.assign(Traits::CString<U>::Perform(u), Traits::Length<U,typename CustomStringT::Size>::Value(u));
			};
		};

		template<> struct TraitsSelectorAssign<0>
		{
			template<class U, class CustomStringT>
			static inline void Perform(const U& u, CustomStringT& customstring)
			{
				typedef typename Static::Remove::Const<U>::Type UType;
				Yuni::Extension::CustomString::Assign<CustomStringT, UType>::Do(customstring, u);
			}
		};

		template<int ValidT>
		struct TraitsSelectorAppend
		{
			template<class U, class CustomStringT>
			static inline void Perform(const U& u, CustomStringT& customstring)
			{
				customstring.append(Traits::CString<U>::Perform(u), Traits::Length<U,typename CustomStringT::Size>::Value(u));
			};
		};

		template<> struct TraitsSelectorAppend<0>
		{
			template<class U, class CustomStringT>
			static inline void Perform(const U& u, CustomStringT& customstring)
			{
				typedef typename Static::Remove::Const<U>::Type UType;
				Yuni::Extension::CustomString::Append<CustomStringT, UType>::Do(customstring, u);
			}
		};

	} // anonymous namespace



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::assign(const U& u)
	{
		TraitsSelectorAssign<Traits::CString<U>::valid && Traits::Length<U>::valid>::
			template Perform<U, CustomStringType>(u, *this);
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::append(const U& u)
	{
		TraitsSelectorAppend<Traits::CString<U>::valid && Traits::Length<U>::valid>::
			template Perform<U, CustomStringType>(u, *this);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::append(const StringT& s,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size size)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);

		AncestorType::append(Traits::CString<StringT>::Perform(s), size);
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::write(const U& u,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size size)
	{
		append(u, size);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::push_back(const U& u)
	{
		append(u);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::push_front(const U& u)
	{
		insert(0, u);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::prepend(const U& u)
	{
		insert(0, u);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::prepend(const U& u,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size size)
	{
		insert(0, Traits::CString<U>::Perform(u), size);
	}





	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::assign(const char* cstr,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size size)
	{
		AncestorType::assign(cstr, size);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::clear()
	{
		AncestorType::clear();
		return *this;
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::reserve(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size minCapacity)
	{
		AncestorType::reserve(minCapacity);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::put(const char c)
	{
		AncestorType::put(c);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::fill(const StringT& pattern)
	{
		typedef typename Static::Remove::Const<StringT>::Type UType;
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CustomString_InvalidTypeForBufferSize);

		if (AncestorType::size)
			Yuni::Extension::CustomString::Fill<CustomString, UType>::Do(AncestorType::data, AncestorType::size, pattern);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::find(const char c) const
	{
		for (Size i = 0; i != AncestorType::size; ++i)
		{
			if (c == AncestorType::data[i])
				return i;
		}
		return npos;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::indexOf(
		typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset, const char c) const
	{
		for (; offset < AncestorType::size; ++offset)
		{
			if (c == AncestorType::data[offset])
				return offset;
		}
		return npos;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::startsWith(const char* cstr,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size len) const
	{
		return (cstr && len && len <= AncestorType::size)
			? (0 == ::memcmp(AncestorType::data, cstr, len))
			: false;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::startsWith(const StringT& s) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CustomString_InvalidTypeForBufferSize);

		return startsWith(Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::Value(s));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::endsWith(const char* cstr,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size len) const
	{
		return (cstr && len && len <= AncestorType::size)
			? (0 == ::memcmp(AncestorType::data + (AncestorType::size - len), cstr, len))
			: false;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::endsWith(const StringT& s) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CustomString_InvalidTypeForBufferSize);

		return endsWith(Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::Value(s));
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::removeLast()
	{
		if (AncestorType::size != 0)
		{
			--(AncestorType::size);
			if (zeroTerminated)
				AncestorType::data[AncestorType::size] = Char();
		}
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	unsigned int
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::countChar(char c) const
	{
		unsigned int count = 0;
		for (Size i = 0; i != AncestorType::size; ++i)
		{
			if (AncestorType::data[i] == c)
				++count;
		}
		return count;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::glob(const StringT& pattern) const
	{
		// TODO This method should be completly removed
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CustomString_InvalidTypeForBufferSize);

		const char* cstr = Traits::CString<StringT>::Perform(pattern);
		Size len = Traits::Length<StringT,Size>::Value(pattern);

		if (len)
		{
			if (AncestorType::size)
			{
				Size e = 0;
				Size prev = npos;
				for (Size i = 0 ; i < AncestorType::size; ++i)
				{
					if ('*' == cstr[e])
					{
						if (e + 1 == len)
							return true;
						while (cstr[e+1] == '*')
							++e;
						if (e + 1 == len)
							return true;

						prev = e;
						if (cstr[e + 1] == AncestorType::data[i])
							e += 2;
					}
					else
					{
						if (cstr[e] == AncestorType::data[i])
							++e;
						else
						{
							if (prev != npos)
								e = prev;
							else
								return false;
						}
					}
				}
				return (e == len);
			}
			return false;
		}
		return empty();
	}





	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::find(const char* cstr,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size len) const
	{
		if (cstr && len && len <= AncestorType::size)
		{
			const Size end = AncestorType::size - len + 1;
			for (Size i = 0; i != end; ++i)
			{
				if (AncestorType::data[i] == *cstr)
				{
					if (!::memcmp(AncestorType::data + i, cstr, len))
						return i;
				}
			}
		}
		return npos;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::indexOf(
		typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset,
		const char* cstr, const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size len) const
	{
		if (cstr && len && len <= AncestorType::size)
		{
			const Size end = AncestorType::size - len + 1;
			for (; offset < end; ++offset)
			{
				if (AncestorType::data[offset] == *cstr)
				{
					if (!::memcmp(AncestorType::data + offset, cstr, len))
						return offset;
				}
			}
		}
		return npos;
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::find(const StringT& s) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CustomString_InvalidTypeForBufferSize);

		// Find the substring
		if (Traits::Length<StringT,Size>::isFixed)
		{
			// We can make some optimisations when the length is known at compile compile time
			// This part of the code should not bring better performances but it should
			// prevent against bad uses of the API, like using a char* for looking for a single char.

			// The value to find is actually empty, npos will be the unique answer
			if (0 == Traits::Length<StringT,Size>::fixedLength)
				return npos;
			// The string is actually a single POD item
			if (1 == Traits::Length<StringT,Size>::fixedLength)
				return find(Traits::CString<StringT>::Perform(s), 1);
			// Researching for the substring with a known length
			return find(Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::fixedLength);
		}
		// A mere CString, with a known length at runtime only
		return find(Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::Value(s));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::indexOf(
		typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset, const StringT& s) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CustomString_InvalidTypeForBufferSize);

		// Find the substring
		if (Traits::Length<StringT,Size>::isFixed)
		{
			// We can make some optimisations when the length is known at compile compile time
			// This part of the code should not bring better performances but it should
			// prevent against bad uses of the API, like using a char* for looking for a single char.

			// The value to find is actually empty, npos will be the unique answer
			if (0 == Traits::Length<StringT,Size>::fixedLength)
				return npos;
			// The string is actually a single POD item
			if (1 == Traits::Length<StringT,Size>::fixedLength)
				return indexOf(offset, Traits::CString<StringT>::Perform(s), 1);
			// Researching for the substring with a known length
			return indexOf(offset, Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::fixedLength);
		}
		// A mere CString, with a known length at runtime only
		return indexOf(offset, Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::Value(s));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::find_first_of(const StringT& s) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CustomString_InvalidTypeForBufferSize);

		// Find the substring
		return find(s);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::consume(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size n)
	{
		erase(0, n);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline U
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::to() const
	{
		typedef typename Static::Remove::Const<U>::Type UType;
		return Yuni::Extension::CustomString::Into<UType>::Perform(*this);
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::to(U& out) const
	{
		typedef typename Static::Remove::Const<U>::Type UType;
		return Yuni::Extension::CustomString::Into<UType>::Perform(*this, out);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::erase(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size len)
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
				// Actually we have to erase a part of the cstr
				(void)::memmove(AncestorType::data + sizeof(Char) * (offset),
								AncestorType::data + sizeof(Char) * (offset + len), sizeof(Char) * (AncestorType::size - offset));
				// Reducing the cstr's size
				AncestorType::size -= len;
			}
			if (zeroTerminated)
				AncestorType::data[AncestorType::size] = Char();
		}
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline char
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::at(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset) const
	{
		return (offset < AncestorType::size) ? AncestorType::data[offset] : Char();
	}




	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::insert(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset, const StringT& s)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CustomString_InvalidTypeForBufferSize);

		if (Traits::Length<StringT,Size>::isFixed)
		{
			// We can make some optimisations when the length is known at compile compile time
			// This part of the code should not bring better performances but it should
			// prevent against bad uses of the API, like using a char* for looking for a single char.

			// The value to find is actually empty, false will be the unique answer
			if (0 == Traits::Length<StringT,Size>::fixedLength)
				return false;
			// The string is actually a single POD item
			if (1 == Traits::Length<StringT,Size>::fixedLength)
				return insert(offset, Traits::CString<StringT>::Perform(s), 1);
			// Researching for the substring with a known length
			return insert(offset, Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::fixedLength);
		}

		return insert(offset, Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::Value(s));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::insert(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset,
		const StringT& s,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size size)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);

		return insert(offset, Traits::CString<StringT>::Perform(s), size);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::insert(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset,
		const char* cstr,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size size)
	{
		if (size > 0)
		{
			if (offset == AncestorType::size)
			{
				append(cstr, size);
				return true;
			}
			else
			{
				// Checking the offset and the size of the given cstr
				if (offset < AncestorType::size)
				{
					AncestorType::insert(offset, cstr, size);
					return true;
				}
			}
		}
		return false;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::insert(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset, const char c)
	{
		if (offset == AncestorType::size)
		{
			append(&c, 1);
			return true;
		}
		else
		{
			// Checking the offset and the size of the given cstr
			if (offset < AncestorType::size)
			{
				AncestorType::insert(offset, &c, 1);
				return true;
			}
		}
		return false;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::overwrite(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset,
		const char* region,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size size)
	{
		if (offset < AncestorType::size && size)
		{
			if (offset + size > AncestorType::size)
				(void)::memcpy(AncestorType::data + offset, region, sizeof(Char) * AncestorType::size - offset);
			else
				(void)::memcpy(AncestorType::data + offset, region, sizeof(Char) * size);
		}
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::overwrite(
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset, const StringT& s)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CustomString_InvalidTypeForBufferSize);

		// Find the substring
		if (Traits::Length<StringT,Size>::isFixed)
		{
			// We can make some optimisations when the length is known at compile compile time
			// This part of the code should not bring better performances but it should
			// prevent against bad uses of the API, like using a char* for looking for a single char.

			// The value to find is actually empty, nothing to do
			if (0 == Traits::Length<StringT,Size>::fixedLength)
				return;
			// The string is actually a single POD item
			if (1 == Traits::Length<StringT,Size>::fixedLength)
				return overwrite(offset, Traits::CString<StringT>::Perform(s), 1);
			// Researching for the substring with a known length
			return overwrite(offset, Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::fixedLength);
		}

		return overwrite(offset, Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::Value(s));
	}




	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::truncate(const Size newSize)
	{
		if (newSize < AncestorType::size)
			AncestorType::size = newSize;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::size() const
	{
		return AncestorType::size;
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::length() const
	{
		return AncestorType::size;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline uint64
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::sizeInBytes() const
	{
		return AncestorType::size * sizeof(Char);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::capacity() const
	{
		return AncestorType::capacity;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline uint64
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::capacityInBytes() const
	{
		return AncestorType::capacity * sizeof(Char);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline const char*
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::data() const
	{
		return AncestorType::data;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline char*
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::data()
	{
		return AncestorType::data;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline const char*
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::c_str() const
	{
		return AncestorType::data;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::empty() const
	{
		return (0 == AncestorType::size);
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::null() const
	{
		return (NULL == AncestorType::data);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::notEmpty() const
	{
		return (0 != AncestorType::size);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::shrink()
	{
		AncestorType::shrink();
	}

		
	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::resize(
		typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size len)
	{
		if (AncestorType::expandable)
		{
			// Dynamic cstr
			AncestorType::reserve(len + AncestorType::zeroTerminated);
			AncestorType::size = len;
		}
		else
		{
			// Static cstr
			if (len <= AncestorType::capacity)
				AncestorType::size = len;
			else
				AncestorType::size = AncestorType::capacity;
		}
		// Zero-Terminated cstrs
		if (zeroTerminated)
			AncestorType::data[AncestorType::size] = Char();
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::trimRight(const char c)
	{
		while (AncestorType::size > 0 && AncestorType::data[AncestorType::size - 1] == c)
			--AncestorType::size;
		if (zeroTerminated)
			AncestorType::data[AncestorType::size] = Char();
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::trimLeft(const char c)
	{
		if (AncestorType::size > 0)
		{
			Size offset = 0;
			while (offset < AncestorType::size && AncestorType::data[offset] == c)
				++offset;
			if (offset)
				erase(0, offset);
		}
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::trimRight(const StringT& whitespaces)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);

		const unsigned int ptrlen = Traits::Length<StringT,Size>::Value(whitespaces);
		if (!ptrlen || empty())
			return;
		const char* ptr = Traits::CString<StringT>::Perform(whitespaces);
		unsigned int i;
		while (AncestorType::size > 0)
		{
			i = 0;
			for (; i != ptrlen; ++i)
			{
				if (ptr[i] == AncestorType::data[AncestorType::size - 1])
				{
					--AncestorType::size;
					break;
				}
			}
			if (ptrlen == i) // nothing has been found. Aborting
				break;
		}
		// Making sure that the string is zero-terminated if required
		if (zeroTerminated)
			AncestorType::data[AncestorType::size] = Char();
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::trimLeft(const StringT& whitespaces)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);

		const unsigned int ptrlen = Traits::Length<StringT,Size>::Value(whitespaces);
		if (!ptrlen || empty())
			return;
		const char* ptr = Traits::CString<StringT>::Perform(whitespaces);
		Size count = 0;
		unsigned int i;
		while (count < AncestorType::size)
		{
			i = 0;
			for (; i != ptrlen; ++i)
			{
				if (ptr[i] == AncestorType::data[count])
				{
					++count;
					break;
				}
			}
			if (ptrlen == i) // nothing has been found. Aborting
				break;
		}
		if (count != 0)
			erase(0, count);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::trim()
	{
		// It seems more interesting to trim from the end first, to reduce the size
		// of the cstr as soon as possible and to reduce the amount of data to move
		// if a region must be removed by trimLeft.
		trimRight(" \t\r\n");
		trimLeft(" \t\r\n");
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::trim(const char c)
	{
		// It seems more interesting to trim from the end first, to reduce the size
		// of the cstr as soon as possible and to reduce the amount of data to move
		// if a region must be removed by trimLeft.
		trimRight(c);
		trimLeft(c);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::trim(const StringT& whitespaces)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CustomString_InvalidTypeForLength);

		// It seems more interesting to trim from the end first, to reduce the size
		// of the cstr as soon as possible and to reduce the amount of data to move
		// if a region must be removed by trimLeft.
		trimRight(whitespaces);
		trimLeft(whitespaces);
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::assignWithoutChecking(
		const char* block,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size blockSize)
	{
		return AncestorType::assignWithoutChecking(block, blockSize);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::appendWithoutChecking(
		const char* block,
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size blockSize)
	{
		return AncestorType::appendWithoutChecking(block, blockSize);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::assignWithoutChecking(const char c)
	{
		return AncestorType::assignWithoutChecking(c);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::appendWithoutChecking(const char c)
	{
		return AncestorType::appendWithoutChecking(c);
	}





	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::format(const StringT& format, ...)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::zeroTerminated, CustomString_FormatMustBeZeroTerminated);

		// Empty the cstr
		clear();
		// Dealing with the variadic arguments
		va_list parg;
		va_start(parg, format);
		vappendFormat(Traits::CString<StringT>::Perform(format), parg);
		va_end(parg);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::appendFormat(const StringT& format, ...)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::zeroTerminated, CustomString_FormatMustBeZeroTerminated);

		// Dealing with the variadic arguments
		va_list parg;
		va_start(parg, format);
		vappendFormat(Traits::CString<StringT>::Perform(format), parg);
		va_end(parg);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::vappendFormat(const char* format, va_list args)
	{
		// Nothing to do if the format is empty
		if (!format || '\0' == *format)
			return;

		// There is no way to know by advance the size occupied by the formatted
		// string
		// Instead of allocating a new temporary cstr, we will directly use
		// this cstr as much as possible.
		//
		// The returned size
		int i;

		if (expandable)
		{
			// Pre-Allocating a minimal amount of free space
			if (AncestorType::capacity - AncestorType::size < 10)
				AncestorType::reserve(AncestorType::size + chunkSize);
			while (true)
			{
				i = Private::CustomStringImpl::vnsprintf<Char>(AncestorType::data + AncestorType::size,
					(AncestorType::capacity - AncestorType::size) * sizeof(Char), format, args);
				if (i == -1)
				{
					AncestorType::reserve(AncestorType::capacity + chunkSize);
					continue;
				}
				else
				{
					if (i < 0)
						return;
				}
				AncestorType::size += (Size) i;
				if (zeroTerminated)
					AncestorType::data[AncestorType::size] = Char();
			}
		}
		else
		{
			// In this case, the cstr can not be expanded
			// We will only try once
			if (AncestorType::capacity != AncestorType::size)
			{
				i = Private::CustomStringImpl::vnsprintf<Char>(AncestorType::data + AncestorType::size,
					(AncestorType::capacity - AncestorType::size) * sizeof(Char), format, args);
				if (i >= 0)
				{
					AncestorType::size += (Size) i;
					if (zeroTerminated)
						AncestorType::data[AncestorType::size] = Char();
				}
			}
		}
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::toLower()
	{
		for (Size i = 0; i < AncestorType::size; ++i)
			AncestorType::data[i] = (Char) tolower(AncestorType::data[i]);
		return *this;
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::toUpper()
	{
		for (Size i = 0; i < AncestorType::size; ++i)
			AncestorType::data[i] = (Char) toupper(AncestorType::data[i]);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<template<class,class> class U, class UType, class Alloc, class StringT>
	void
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::explode(U<UType,Alloc>& out, const StringT& sep,
		bool keepEmptyElements, bool trimElements, bool emptyBefore) const
	{
		// Empty the container
		if (emptyBefore)
			out.clear();
		// String empty
		if (this->notEmpty())
		{
			// Indexes
			Size indx = 0;
			Size len  = 0;
			Size newIndx;

			// Temporary buffer
			CustomStringType segment;

			while (true)
			{
				newIndx = this->find_first_of(sep, indx);
				if (npos == newIndx)
				{
					segment.assign(AncestorType::data[indx], AncestorType::size - indx);
					if (trimElements)
						segment.trim();
					if (segment.notEmpty() || keepEmptyElements)
						out.push_back(segment.to<UType>());
					return;
				}

				if ((len = newIndx - indx) || keepEmptyElements)
				{
					segment.assign(AncestorType::data[indx], len);
					if (trimElements)
						segment.trim();
					if (segment.notEmpty() || keepEmptyElements)
						out.push_back(segment.to<UType>());
				}
				indx = newIndx + 1;
			}
		}
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::convertSlashesIntoBackslashes()
	{
		for (unsigned int i = 0; i != AncestorType::size; ++i)
		{
			if ('/' == AncestorType::data[i])
				AncestorType::data[i] = '\\';
		}
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::convertBackslashesIntoSlashes()
	{
		for (unsigned int i = 0; i != AncestorType::size; ++i)
		{
			if ('\\' == AncestorType::data[i])
				AncestorType::data[i] = '/';
		}
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	void CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::dupplicate(int n)
	{
		if (n > 0 && AncestorType::size > 0)
		{
			if (AncestorType::size == 1)
			{
				// Resize the string
				resize(AncestorType::size * (n + 1));
				// Caraceter copy
				for (unsigned int i = 1; i != AncestorType::size; ++i)
					AncestorType::data[i] = AncestorType::data[0];
			}
			else
			{
				const Size seglen = AncestorType::size;
				Size offset = AncestorType::size;
				// Resize the string
				resize(AncestorType::size * (n + 1));

				while (offset < AncestorType::size)
				{
					if (seglen + offset > AncestorType::size)
						(void)::memcpy(AncestorType::data + offset, AncestorType::data, AncestorType::size - offset);
					else
						(void)::memcpy(AncestorType::data + offset, AncestorType::data, seglen);
					offset += seglen;
				}
			}
		}
	}




	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	int
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Compare(const char* s1, unsigned int l1,
		const char* s2, unsigned int l2)
	{
		const unsigned int l = (l1 < l2) ? l1 : l2;

		for (unsigned int i = 0; i != l; ++i)
		{
			if (s1[i] != s2[i])
				return ((s1[i] < s2[i]) ? -1 : +1);
		}
		return (l1 == l2) ? 0 : ((l1 < l2) ? -1 : +1);
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	int
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::CompareInsensitive(const char* s1, unsigned int l1,
		const char* s2, unsigned int l2)
	{
		const unsigned int l = (l1 < l2) ? l1 : l2;

		for (unsigned int i = 0; i != l; ++i)
		{
			if (tolower(s1[i]) != tolower(s2[i]))
				return ((tolower(s1[i]) < tolower(s2[i])) ? -1 : +1);
		}
		return (l1 == l2) ? 0 : ((l1 < l2) ? -1 : +1);
	}




	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline const char&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator [] (
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset) const
	{
		return AncestorType::data[offset];
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline char&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator [] (
		const typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Size offset)
	{
		return AncestorType::data[offset];
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline const char&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator [] (const int offset) const
	{
		return AncestorType::data[(unsigned int)offset];
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline char&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator [] (const int offset)
	{
		return AncestorType::data[(unsigned int)offset];
	}




	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator != (const StringT& rhs) const
	{
		return !(*this == rhs);
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator ! () const
	{
		return !AncestorType::size;
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator += (const U& rhs)
	{
		append(rhs);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator << (const U& rhs)
	{
		append(rhs);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator = (const CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>& rhs)
	{
		assign(rhs);
		return *this;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class U>
	inline CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator = (const U& rhs)
	{
		assign(rhs);
		return *this;
	}



	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator < (const StringT& rhs) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CustomString_InvalidTypeForBufferSize);

		return Compare(AncestorType::data, AncestorType::size, Traits::CString<StringT>::Perform(rhs),
			Traits::Length<StringT,Size>::Value(rhs)) < 0;
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator > (const StringT& rhs) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CustomString_InvalidTypeForBufferSize);

		return Compare(AncestorType::data, AncestorType::size, Traits::CString<StringT>::Perform(rhs),
			Traits::Length<StringT,Size>::Value(rhs)) > 0;
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator <= (const StringT& rhs) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CustomString_InvalidTypeForBufferSize);

		return Compare(AncestorType::data, AncestorType::size, Traits::CString<StringT>::Perform(rhs),
			Traits::Length<StringT,Size>::Value(rhs)) <= 0;
	}

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator >= (const StringT& rhs) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CustomString_InvalidTypeForBufferSize);

		return Compare(AncestorType::data, AncestorType::size, Traits::CString<StringT>::Perform(rhs),
			Traits::Length<StringT,Size>::Value(rhs)) >= 0;
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	template<class StringT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator == (const StringT& rhs) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CustomString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CustomString_InvalidTypeForBufferSize);

		return (AncestorType::size && AncestorType::size == Traits::Length<StringT,Size>::Value(rhs)) &&
			!::strncmp(AncestorType::data, Traits::CString<StringT>::Perform(rhs), (AncestorType::size) * sizeof(Char));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	inline bool
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator == (const CustomString& rhs) const
	{
		return (AncestorType::size && AncestorType::size == rhs.size()
			&& !::strncmp(AncestorType::data, rhs.data(), AncestorType::size * sizeof(Char)));
	}


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>&
	CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::operator *= (int n)
	{
		dupplicate(n);
		return *this;
	}








} // namespace Yuni

#endif // __YUNI_CORE_CUSTOMSTRING_CUSTOMSTRING_HXX__
