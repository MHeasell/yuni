#ifndef __YUNI_CORE_STRING_STRING_HXX__
# define __YUNI_CORE_STRING_STRING_HXX__

# include <iostream>
# include <ctype.h>
# include <cassert>
# ifdef YUNI_HAS_VA_COPY
#	include <stdarg.h>
# endif // YUNI_HAS_VA_COPY



namespace Yuni
{

	//! Returns a non-null terminated C-String
	char* NullTerminatedCString();


	template<uint ChunkSizeT, bool ExpandableT>
	inline int CString<ChunkSizeT,ExpandableT>::ToLower(int c)
	{
		return (static_cast<uint>(c) - 'A' < 26)
			? c | 32
			: c;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline int CString<ChunkSizeT,ExpandableT>::ToUpper(int c)
	{
		return (static_cast<uint>(c) - 'a' < 26)
			? c & 0x5f
			: c;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool CString<ChunkSizeT,ExpandableT>::IsSpace(int c)
	{
		return (c == ' ') || (static_cast<uint>(c) - '\t' < 5);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool CString<ChunkSizeT,ExpandableT>::IsDigit(int c)
	{
		return static_cast<uint>(c) - '0' < 10;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool CString<ChunkSizeT,ExpandableT>::IsDigitNonZero(int c)
	{
		return static_cast<uint>(c) - '1' < 9;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool CString<ChunkSizeT,ExpandableT>::IsAlpha(int c)
	{
		return (static_cast<uint>(c) | 32) - 'a' < 26;
	}



	template<uint ChunkSizeT, bool ExpandableT>
	inline CString<ChunkSizeT,ExpandableT>::CString()
	{}


	template<uint ChunkSizeT, bool ExpandableT>
	inline CString<ChunkSizeT,ExpandableT>::CString(const YuniNullPtr&)
	{}


	template<uint ChunkSizeT, bool ExpandableT>
	inline CString<ChunkSizeT,ExpandableT>::~CString()
	{}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class ModelT, bool ConstT, class ModelT2, bool ConstT2>
	inline
	CString<ChunkSizeT,ExpandableT>::CString(
		const IIterator<ModelT,ConstT>& begin, const IIterator<ModelT2,ConstT2>& end)
	{
		assign(begin, end);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class ModelT, bool ConstT, class ModelT2, bool ConstT2, class StringT>
	inline
	CString<ChunkSizeT,ExpandableT>::CString(
		const IIterator<ModelT,ConstT>& begin, const IIterator<ModelT2,ConstT2>& end, const StringT& separator)
	{
		assign(begin, end, separator);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline
	CString<ChunkSizeT,ExpandableT>::CString(const CString<ChunkSizeT,ExpandableT>& rhs) :
		AncestorType(rhs)
	{}


	template<uint ChunkSizeT, bool ExpandableT>
	inline CString<ChunkSizeT,ExpandableT>::CString(const char* text)
	{
		assign(text);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<uint SizeT, bool ExpT>
	inline CString<ChunkSizeT,ExpandableT>::CString(const CString<SizeT, ExpT>& rhs)
	{
		assign(rhs);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class U>
	inline CString<ChunkSizeT,ExpandableT>::CString(const U& rhs)
	{
		assign(rhs);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline
	CString<ChunkSizeT,ExpandableT>::CString(size_t n, char c)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		// Resizing the buffer to `n`
		resize(n);
		// Note: the string may have a fixed-length capacity
		(void)::memset(AncestorType::data, c, AncestorType::size * sizeof(Char));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline
	CString<ChunkSizeT,ExpandableT>::CString(size_t n, unsigned char c)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		// Resizing the buffer to `n`
		resize(n);
		// Note: the string may have a fixed-length capacity
		(void)::memset(AncestorType::data, static_cast<char>(c), AncestorType::size * sizeof(Char));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<uint SizeT, bool ExpT>
	CString<ChunkSizeT,ExpandableT>::CString(const CString<SizeT,ExpT>& s, Size offset, Size n)
	{
		if (offset < s.size())
		{
			Size length = s.size() - offset;
			if (length > n)
				length = n;
			if (!adapter)
				AncestorType::assign((const char* const) s.c_str() + offset, length);
			else
				adapt(s.c_str() + offset, length);
		}
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<uint SizeT, bool ExpT>
	CString<ChunkSizeT,ExpandableT>::CString(const CString<SizeT,ExpT>& s, Size offset)
	{
		if (offset < s.size())
		{
			if (!adapter)
				AncestorType::assign((const char* const) s.c_str() + offset, s.size() - offset);
			else
				adapt(s.c_str() + offset, s.size() - offset);
		}
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class TraitsT, class AllocT>
	CString<ChunkSizeT,ExpandableT>::CString(const std::basic_string<char,TraitsT,AllocT>& string)
	{
		assign(string);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class TraitsT, class AllocT>
	CString<ChunkSizeT,ExpandableT>::CString(const std::basic_string<char,TraitsT,AllocT>& s,
		Size offset, Size n)
	{
		if (offset < s.size())
		{
			Size length = s.size() - offset;
			if (length > n)
				length = n;
			if (!adapter)
				AncestorType::assign((const char* const) s.c_str() + offset, length);
			else
				adapt(s.c_str() + offset, length);
		}
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class TraitsT, class AllocT>
	CString<ChunkSizeT,ExpandableT>::CString(const std::basic_string<char,TraitsT,AllocT>& s, Size offset)
	{
		if (offset < s.size())
		{
			if (!adapter)
				AncestorType::assign((const char* const) s.c_str() + offset, s.size() - offset);
			else
				adapt(s.c_str() + offset, s.size() - offset);
		}
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline
	CString<ChunkSizeT,ExpandableT>::CString(const char* const cstring, Size blockSize)
	{
		if (!adapter)
			AncestorType::assign(cstring, blockSize);
		else
			adapt(cstring, blockSize);
	}




	namespace
	{
		template<bool ValidT, bool AdapterT>
		struct TraitsSelectorAssign
		{
			template<class U, class CStringT>
			static inline void Perform(const U& u, CStringT& string)
			{
				string.assign(Traits::CString<U>::Perform(u), Traits::Length<U,typename CStringT::Size>::Value(u));
			};
		};

		template<> struct TraitsSelectorAssign<true, true>
		{
			template<class U, class CStringT>
			static inline void Perform(const U& u, CStringT& string)
			{
				string.adapt(Traits::CString<U>::Perform(u), Traits::Length<U,typename CStringT::Size>::Value(u));
			};
		};


		template<bool AdapterT> struct TraitsSelectorAssign<false, AdapterT>
		{
			template<class U, class CStringT>
			static inline void Perform(const U& u, CStringT& string)
			{
				YUNI_STATIC_ASSERT(!AdapterT, CString_Adapter_ReadOnly);
				typedef typename Static::Remove::Const<U>::Type UType;
				Yuni::Extension::CString::Assign<CStringT, UType>::Perform(string, u);
			}
		};

		template<bool ValidT>
		struct TraitsSelectorAppend
		{
			template<class U, class CStringT>
			static inline void Perform(const U& u, CStringT& string)
			{
				string.append(Traits::CString<U>::Perform(u), Traits::Length<U,typename CStringT::Size>::Value(u));
			};
		};

		template<> struct TraitsSelectorAppend<false>
		{
			template<class U, class CStringT>
			static inline void Perform(const U& u, CStringT& string)
			{
				typedef typename Static::Remove::Const<U>::Type UType;
				Yuni::Extension::CString::Append<CStringT, UType>::Perform(string, u);
			}
		};

	} // anonymous namespace



	template<uint ChunkSizeT, bool ExpandableT>
	template<class U>
	inline
	void CString<ChunkSizeT,ExpandableT>::assign(const U& u)
	{
		TraitsSelectorAssign<
			(Traits::CString<U>::valid && Traits::Length<U>::valid),             // Standard CString ?
			(0 != CString<ChunkSizeT,ExpandableT>::adapter) // Adapter ?
			>::
			template Perform<U, CStringType>(u, *this);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class U>
	inline
	void CString<ChunkSizeT,ExpandableT>::append(const U& u)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		TraitsSelectorAppend<Traits::CString<U>::valid && Traits::Length<U>::valid>::
			template Perform<U, CStringType>(u, *this);
	}



	template<class T>
	struct AppendIterator
	{
		template<class StringT, class IteratorT, class IteratorT2>
		static void Perform(StringT& s, const IteratorT& begin, const IteratorT2& end)
		{
			for (IteratorT i = begin; i != end; ++i)
				s << *i;
		}

		template<class StringT, class IteratorT, class IteratorT2, class SeparatorT>
		static void Perform(StringT& s, const IteratorT& begin, const IteratorT2& end, const SeparatorT& separator)
		{
			if (begin != end)
			{
				s << *begin;
				IteratorT i = begin;
				++i;
				for (; i != end; ++i)
					s << separator << *i;
			}
		}

		template<class StringT, class IteratorT, class IteratorT2, class SeparatorT, class EnclosureT>
		static void Perform(StringT& s, const IteratorT& begin, const IteratorT2& end, const SeparatorT& separator,
			const EnclosureT& enclosure)
		{
			if (begin != end)
			{
				s << enclosure << *begin << enclosure;
				IteratorT i = begin;
				++i;
				for (; i != end; ++i)
					s << separator << enclosure << *i << enclosure;
			}
		}

	}; // class AppendIterator




	template<uint ChunkSizeT, bool ExpandableT>
	template<class ModelT, bool ConstT, class ModelT2, bool ConstT2>
	inline void
	CString<ChunkSizeT,ExpandableT>::assign(const IIterator<ModelT,ConstT>& begin,
		const IIterator<ModelT2,ConstT2>& end)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		typedef typename IIterator<ModelT,ConstT>::value_type  HeldType;
		clear();
		AppendIterator<HeldType>::Perform(*this, begin, end);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class ModelT, bool ConstT, class ModelT2, bool ConstT2, class StringT>
	inline void
	CString<ChunkSizeT,ExpandableT>::assign(const IIterator<ModelT,ConstT>& begin,
		const IIterator<ModelT2,ConstT2>& end, const StringT& separator)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		typedef typename IIterator<ModelT,ConstT>::value_type  HeldType;
		clear();
		AppendIterator<HeldType>::Perform(*this, begin, end, separator);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class ModelT, bool ConstT, class ModelT2, bool ConstT2, class StringT, class EnclosureT>
	inline void
	CString<ChunkSizeT,ExpandableT>::assign(const IIterator<ModelT,ConstT>& begin,
		const IIterator<ModelT2,ConstT2>& end, const StringT& separator, const EnclosureT& enclosure)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		typedef typename IIterator<ModelT,ConstT>::value_type  HeldType;
		clear();
		AppendIterator<HeldType>::Perform(*this, begin, end, separator, enclosure);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class ModelT, bool ConstT, class ModelT2, bool ConstT2>
	inline void
	CString<ChunkSizeT,ExpandableT>::append(const IIterator<ModelT,ConstT>& begin,
		const IIterator<ModelT2,ConstT2>& end)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		typedef typename IIterator<ModelT,ConstT>::value_type  HeldType;
		AppendIterator<HeldType>::Perform(*this, begin, end);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class ModelT, bool ConstT, class ModelT2, bool ConstT2, class StringT>
	inline void
	CString<ChunkSizeT,ExpandableT>::append(const IIterator<ModelT,ConstT>& begin,
		const IIterator<ModelT2,ConstT2>& end, const StringT& separator)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		typedef typename IIterator<ModelT,ConstT>::value_type  HeldType;
		AppendIterator<HeldType>::Perform(*this, begin, end, separator);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class ModelT, bool ConstT, class ModelT2, bool ConstT2, class StringT, class EnclosureT>
	inline void
	CString<ChunkSizeT,ExpandableT>::append(const IIterator<ModelT,ConstT>& begin,
		const IIterator<ModelT2,ConstT2>& end, const StringT& separator, const EnclosureT& enclosure)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		typedef typename IIterator<ModelT,ConstT>::value_type  HeldType;
		AppendIterator<HeldType>::Perform(*this, begin, end, separator, enclosure);
	}



	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline void
	CString<ChunkSizeT,ExpandableT>::append(const StringT& s, Size size)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);

		AncestorType::append(Traits::CString<StringT>::Perform(s), size);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline void
	CString<ChunkSizeT,ExpandableT>::append(const StringT& str, Size size, Size offset)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		# ifndef NDEBUG
		Size len = Traits::Length<StringT,Size>::Value(str);
		assert(size + offset <= len && "Bound check error in CString::append(s, size, offset) !");
		# endif // NDEBUG
		AncestorType::append(Traits::CString<StringT>::Perform(str) + offset, size);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class U>
	inline void
	CString<ChunkSizeT,ExpandableT>::write(const U& u, Size size)
	{
		append(u, size);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class U>
	inline void
	CString<ChunkSizeT,ExpandableT>::write(const U& u)
	{
		append(u);
	}



	template<uint ChunkSizeT, bool ExpandableT>
	template<class U>
	inline void
	CString<ChunkSizeT,ExpandableT>::push_back(const U& u)
	{
		append(u);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class U>
	inline void
	CString<ChunkSizeT,ExpandableT>::push_front(const U& u)
	{
		insert(0, u);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline void
	CString<ChunkSizeT,ExpandableT>::assign(const StringT& str, Size size)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);

		if (not adapter)
			AncestorType::assign(Traits::CString<StringT>::Perform(str), size);
		else
			adapt(Traits::CString<StringT>::Perform(str), size);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline void
	CString<ChunkSizeT,ExpandableT>::assign(const StringT& str, Size size, Size offset)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);

		if (not adapter)
			AncestorType::assign(Traits::CString<StringT>::Perform(str) + offset, size);
		else
			adapt(Traits::CString<StringT>::Perform(str) + offset, size);
	}




	namespace // anonymous
	{
		/*!
		** \brief Find the end of a sequence, started and terminated by a given character (usually a quote)
		**
		** This method is not a simple find(), because it takes care of escaped
		** characters
		**
		** \param str The sequence
		** \param quote The character to find, usually a quote
		*/
		template<class StringT>
		static typename StringT::Size FindEndOfSequence(const char* str, char quote, typename StringT::Size maxLen)
		{
			if (str)
			{
				typename StringT::Size pos(0);
				while (pos < maxLen)
				{
					char c = str[pos];
					if ('\\' == c)
					{
						pos += 2;
						continue;
					}
					else
					{
						if (quote == c)
							return pos;
						++pos;
					}
				}
			}
			return StringT::npos;
		}

	} // anonymous namespace

	template<uint ChunkSizeT, bool ExpandableT>
	void
	CString<ChunkSizeT,ExpandableT>::assignFromEscapedCharacters(const char* const str,
		Size maxLen, Size offset)
	{
		clear();
		if (!maxLen || offset >= maxLen)
			return;

		// Preparing the copy
		AncestorType::size = maxLen - offset;
		AncestorType::reserve(AncestorType::size);

		// Browsing all char
		Size retPos(0);
		for (Size i = offset; i < maxLen; ++i, ++retPos)
		{
			if ('\\' == str[i] && i + 1 != maxLen)
			{
				switch (str[i + 1])
				{
					case 'r'  : AncestorType::data[retPos] = '\r'; break;
					case 'n'  : AncestorType::data[retPos] = '\n'; break;
					case '\\' : AncestorType::data[retPos] = '\\'; break;
					case ';'  : AncestorType::data[retPos] = ';'; break;
					case 'a'  : AncestorType::data[retPos] = '\a'; break;
					case 'f'  : AncestorType::data[retPos] = '\f'; break;
					case 't'  : AncestorType::data[retPos] = '\t'; break;
					case '\'' : AncestorType::data[retPos] = '\''; break;
					case '"'  : AncestorType::data[retPos] = '"'; break;
					default   : AncestorType::data[retPos] = str[i]; continue;
				}
				--(AncestorType::size);
				++i;
				continue;
			}
			AncestorType::data[retPos] = str[i];
		}
		if (zeroTerminated)
			AncestorType::data[AncestorType::size] = '\0';
	}



	template<uint ChunkSizeT, bool ExpandableT>
	inline CString<ChunkSizeT,ExpandableT>&  CString<ChunkSizeT,ExpandableT>::clear()
	{
		if (!adapter)
			AncestorType::clear();
		else
			AncestorType::size = 0;
		return *this;
	}



	template<uint ChunkSizeT, bool ExpandableT>
	inline void
	CString<ChunkSizeT,ExpandableT>::reserve(Size minCapacity)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		AncestorType::reserve(minCapacity);
	}



	template<uint ChunkSizeT, bool ExpandableT>
	inline void
	CString<ChunkSizeT,ExpandableT>::put(char c)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		AncestorType::put(c);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline void
	CString<ChunkSizeT,ExpandableT>::put(const unsigned char c)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		AncestorType::put(static_cast<char>(c));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class U>
	inline void
	CString<ChunkSizeT,ExpandableT>::put(const U& rhs)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		append(rhs);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	void CString<ChunkSizeT,ExpandableT>::fill(const StringT& pattern)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		typedef typename Static::Remove::Const<StringT>::Type UType;
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		if (AncestorType::size)
		{
			Yuni::Extension::CString::Fill<CString, UType>::
				Perform(AncestorType::data, AncestorType::size, pattern);
		}
	}

	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	void CString<ChunkSizeT,ExpandableT>::fill(Size offset, const StringT& pattern)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		typedef typename Static::Remove::Const<StringT>::Type UType;
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		if (offset < AncestorType::size)
		{
			Yuni::Extension::CString::Fill<CString, UType>::
				Perform(AncestorType::data + offset, AncestorType::size - offset, pattern);
		}
	}


	template<uint ChunkSizeT, bool ExpandableT>
	bool
	CString<ChunkSizeT,ExpandableT>::hasChar(char c) const
	{
		for (Size i = 0; i != AncestorType::size; ++i)
		{
			if (c == AncestorType::data[i])
				return true;
		}
		return false;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	uint
	CString<ChunkSizeT,ExpandableT>::countChar(char c) const
	{
		uint r = 0;
		for (Size i = 0; i != AncestorType::size; ++i)
		{
			if (c == AncestorType::data[i])
				++r;
		}
		return r;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	bool
	CString<ChunkSizeT,ExpandableT>::hasChar(unsigned char c) const
	{
		return hasChar(static_cast<char>(c));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	uint
	CString<ChunkSizeT,ExpandableT>::countChar(unsigned char c) const
	{
		return countChar(static_cast<char>(c));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::find(char c) const
	{
		for (Size i = 0; i != AncestorType::size; ++i)
		{
			if (c == AncestorType::data[i])
				return i;
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::find(char c, Size offset) const
	{
		for (Size i = offset; i < AncestorType::size; ++i)
		{
			if (c == AncestorType::data[i])
				return i;
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::find(const char* const cstr, Size offset, Size len) const
	{
		if (cstr && len && len <= AncestorType::size)
		{
			Size end = AncestorType::size - len + 1;
			for (Size i = offset; i < end; ++i)
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


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::find(const StringT& s, Size offset) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

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
				return find(Traits::CString<StringT>::Perform(s), offset, 1);
			// Researching for the substring with a known length
			return find(Traits::CString<StringT>::Perform(s), offset, Traits::Length<StringT,Size>::fixedLength);
		}
		// A mere CString, with a known length at runtime only
		return find(Traits::CString<StringT>::Perform(s), offset, Traits::Length<StringT,Size>::Value(s));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::ifind(char c) const
	{
		c = static_cast<char>(ToLower(c));
		for (Size i = 0; i != AncestorType::size; ++i)
		{
			if (c == static_cast<char>(ToLower(AncestorType::data[i])))
				return i;
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::ifind(char c, Size offset) const
	{
		c = static_cast<char>(ToLower(c));
		for (Size i = offset; i < AncestorType::size; ++i)
		{
			if (c == static_cast<char>(ToLower(AncestorType::data[i])))
				return i;
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::ifind(const char* const cstr,
		Size offset, Size len) const
	{
		if (cstr && len && len <= AncestorType::size)
		{
			Size end = AncestorType::size - len + 1;
			for (Size i = offset; i < end; ++i)
			{
				if (ToLower(AncestorType::data[i]) == ToLower(*cstr))
				{
					if (!CompareInsensitive(AncestorType::data + i, len, cstr, len))
						return i;
				}
			}
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::ifind(const StringT& s, Size offset) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

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
				return ifind(Traits::CString<StringT>::Perform(s), offset, 1);
			// Researching for the substring with a known length
			return ifind(Traits::CString<StringT>::Perform(s), offset, Traits::Length<StringT,Size>::fixedLength);
		}
		// A mere CString, with a known length at runtime only
		return ifind(Traits::CString<StringT>::Perform(s), offset, Traits::Length<StringT,Size>::Value(s));
	}



	template<uint ChunkSizeT, bool ExpandableT>
	typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::rfind(char c) const
	{
		Size i = AncestorType::size;
		while (i--)
		{
			if (c == AncestorType::data[i])
				return i;
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::rfind(char c, Size offset) const
	{
		Size i = (offset >= AncestorType::size) ? AncestorType::size : 1+offset;
		while (i--)
		{
			if (c == AncestorType::data[i])
				return i;
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::rfind(const char* const cstr, Size offset, Size len) const
	{
		if (len && len <= AncestorType::size && offset >= len)
		{
			Size i = (offset >= AncestorType::size) ? AncestorType::size : 1+offset;
			i -= len - 1;
			while (i--)
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


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::rfind(const StringT& s, Size offset) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

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
				return rfind(Traits::CString<StringT>::Perform(s), offset, 1);
			// Researching for the substring with a known length
			return rfind(Traits::CString<StringT>::Perform(s), offset, Traits::Length<StringT,Size>::fixedLength);
		}
		// A mere CString, with a known length at runtime only
		return rfind(Traits::CString<StringT>::Perform(s), offset, Traits::Length<StringT,Size>::Value(s));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::irfind(char c) const
	{
		c = static_cast<char>(ToLower(c));
		Size i = AncestorType::size;
		while (i--)
		{
			if (c == static_cast<char>(ToLower(AncestorType::data[i])))
				return i;
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::irfind(char c, Size offset) const
	{
		c = static_cast<char>(ToLower(c));
		Size i = (offset >= AncestorType::size) ? AncestorType::size : 1+offset;
		while (i--)
		{
			if (c == static_cast<char>(ToLower(AncestorType::data[i])))
				return i;
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::irfind(const char* const cstr,
		Size offset, Size len) const
	{
		if (len && len <= AncestorType::size && offset >= len)
		{
			Size i = (offset >= AncestorType::size) ? AncestorType::size : 1+offset;
			i -= len - 1;
			while (i--)
			{
				if (ToLower(AncestorType::data[i]) == ToLower(*cstr))
				{
					if (!CompareInsensitive(AncestorType::data + i, len, cstr, len))
						return i;
				}
			}
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::irfind(const StringT& s, Size offset) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

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
				return irfind(Traits::CString<StringT>::Perform(s), offset, 1);
			// Researching for the substring with a known length
			return irfind(Traits::CString<StringT>::Perform(s), offset, Traits::Length<StringT,Size>::fixedLength);
		}
		// A mere CString, with a known length at runtime only
		return irfind(Traits::CString<StringT>::Perform(s), offset, Traits::Length<StringT,Size>::Value(s));
	}



	template<uint ChunkSizeT, bool ExpandableT>
	bool
	CString<ChunkSizeT,ExpandableT>::contains(char c) const
	{
		for (Size i = 0; i != AncestorType::size; ++i)
		{
			if (c == AncestorType::data[i])
				return true;
		}
		return false;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	bool
	CString<ChunkSizeT,ExpandableT>::contains(const char* const cstr, Size len) const
	{
		if (cstr && len && len <= AncestorType::size)
		{
			Size end = AncestorType::size - len + 1;
			for (Size i = 0; i != end; ++i)
			{
				if (AncestorType::data[i] == *cstr)
				{
					if (!::memcmp(AncestorType::data + i, cstr, len))
						return true;
				}
			}
		}
		return false;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	bool
	CString<ChunkSizeT,ExpandableT>::contains(const StringT& s) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		// Find the substring
		if (Traits::Length<StringT,Size>::isFixed)
		{
			// We can make some optimisations when the length is known at compile compile time
			// This part of the code should not bring better performances but it should
			// prevent against bad uses of the API, like using a char* for looking for a single char.

			// The value to find is actually empty, npos will be the unique answer
			if (0 == Traits::Length<StringT,Size>::fixedLength)
				return false;
			// The string is actually a single POD item
			if (1 == Traits::Length<StringT,Size>::fixedLength)
				return contains(Traits::CString<StringT>::Perform(s), 1);
			// Researching for the substring with a known length
			return contains(Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::fixedLength);
		}
		// A mere CString, with a known length at runtime only
		return contains(Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::Value(s));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	bool
	CString<ChunkSizeT,ExpandableT>::icontains(char c) const
	{
		c = static_cast<char>(ToLower(c));
		for (Size i = 0; i != AncestorType::size; ++i)
		{
			if (c == static_cast<char>(ToLower(AncestorType::data[i])))
				return true;
		}
		return false;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	bool
	CString<ChunkSizeT,ExpandableT>::icontains(const char* const cstr, Size len) const
	{
		if (cstr && len && len <= AncestorType::size)
		{
			Size end = AncestorType::size - len + 1;
			for (Size i = 0; i != end; ++i)
			{
				if (ToLower(AncestorType::data[i]) == ToLower(*cstr))
				{
					if (!CompareInsensitive(AncestorType::data + i, len, cstr, len))
						return true;
				}
			}
		}
		return false;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	bool
	CString<ChunkSizeT,ExpandableT>::icontains(const StringT& s) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		// Find the substring
		if (Traits::Length<StringT,Size>::isFixed)
		{
			// We can make some optimisations when the length is known at compile compile time
			// This part of the code should not bring better performances but it should
			// prevent against bad uses of the API, like using a char* for looking for a single char.

			// The value to find is actually empty, npos will be the unique answer
			if (0 == Traits::Length<StringT,Size>::fixedLength)
				return false;
			// The string is actually a single POD item
			if (1 == Traits::Length<StringT,Size>::fixedLength)
				return icontains(Traits::CString<StringT>::Perform(s), 1);
			// Researching for the substring with a known length
			return icontains(Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::fixedLength);
		}
		// A mere CString, with a known length at runtime only
		return icontains(Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::Value(s));
	}





	template<uint ChunkSizeT, bool ExpandableT>
	uint
	CString<ChunkSizeT,ExpandableT>::indexOf(Size offset, char c) const
	{
		for (; offset < AncestorType::size; ++offset)
		{
			if (c == AncestorType::data[offset])
				return offset;
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::startsWith(const char* const cstr, Size len) const
	{
		return (cstr && len && len <= AncestorType::size)
			? (0 == ::memcmp(AncestorType::data, cstr, len))
			: false;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::startsWith(const StringT& s) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		return startsWith(Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::Value(s));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::startsWith(char c) const
	{
		return (0 != AncestorType::size) && (AncestorType::data[0] == c);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::istartsWith(const char* const cstr, Size len) const
	{
		if (cstr && len && len <= AncestorType::size)
		{
			for (uint i = 0; i != len; ++i)
			{
				if (ToLower(cstr[i]) != ToLower(AncestorType::data[i]))
					return false;
			}
			return true;
		}
		return false;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::istartsWith(const StringT& s) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		return startsWith(Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::Value(s));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::istartsWith(char c) const
	{
		return (0 != AncestorType::size) && (ToLower(AncestorType::data[0]) == ToLower(c));
	}



	template<uint ChunkSizeT, bool ExpandableT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::endsWith(const char* const cstr, Size len) const
	{
		return (cstr && len && len <= AncestorType::size)
			? (0 == ::memcmp(AncestorType::data + (AncestorType::size - len), cstr, len))
			: false;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::endsWith(const StringT& s) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		return endsWith(Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::Value(s));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::endsWith(char c) const
	{
		return (0 != AncestorType::size) && (AncestorType::data[AncestorType::size - 1] == c);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::iendsWith(const char* const cstr, Size len) const
	{
		if (cstr && len && len <= AncestorType::size)
		{
			uint offset = 0;
			for (uint i = AncestorType::size - len; i != AncestorType::size; ++i, ++offset)
			{
				if (ToLower(cstr[offset]) != ToLower(AncestorType::data[i]))
					return false;
			}
			return true;
		}
		return false;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::iendsWith(const StringT& s) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		return endsWith(Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::Value(s));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::iendsWith(char c) const
	{
		return (0 != AncestorType::size) && (ToLower(AncestorType::data[AncestorType::size - 1]) == ToLower(c));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline void
	CString<ChunkSizeT,ExpandableT>::removeLast()
	{
		if (AncestorType::size != 0)
		{
			--(AncestorType::size);
			if (zeroTerminated)
				Yuni::Private::CStringImpl::FinalZero<adapter>::Set(AncestorType::data, AncestorType::size);
		}
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline void
	CString<ChunkSizeT,ExpandableT>::removeTrailingSlash()
	{
		if (AncestorType::size != 0)
		{
			if (('/' == AncestorType::data[AncestorType::size - 1] || '\\' == AncestorType::data[AncestorType::size - 1]))
				resize(AncestorType::size - 1);
		}
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline void
	CString<ChunkSizeT,ExpandableT>::chop(uint n)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		if (AncestorType::size >= n)
		{
			AncestorType::size -= n;
			if (zeroTerminated)
				Yuni::Private::CStringImpl::FinalZero<adapter>::Set(AncestorType::data, AncestorType::size);
		}
		else
		{
			AncestorType::size = 0;
			if (zeroTerminated && AncestorType::capacity)
				Yuni::Private::CStringImpl::FinalZero<adapter>::Set(AncestorType::data, 0);
		}
	}




	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	bool
	CString<ChunkSizeT,ExpandableT>::glob(const StringT& pattern) const
	{
		// TODO This method should be completly removed
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		return Yuni::Private::CStringImpl::Glob(AncestorType::data, AncestorType::size,
			Traits::CString<StringT>::Perform(pattern), Traits::Length<StringT,Size>::Value(pattern));
	}



	template<uint ChunkSizeT, bool ExpandableT>
	uint
	CString<ChunkSizeT,ExpandableT>::indexOf(Size offset,
		const char* const cstr, Size len) const
	{
		if (cstr && len && len <= AncestorType::size)
		{
			Size end = AncestorType::size - len + 1;
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



	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	uint
	CString<ChunkSizeT,ExpandableT>::indexOf(Size offset, const StringT& s) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

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


	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::find_first_of(char c, Size offset) const
	{
		return indexOf(offset, c);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::ifind_first_of(char c, Size offset) const
	{
		c = static_cast<char>(ToLower(c));
		for (Size i = offset; i < AncestorType::size; ++i)
		{
			// alias to the current character
			if (c == static_cast<char>(ToLower(AncestorType::data[i])))
				return i;
		}
		return npos;
	}



	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::find_first_of(const StringT& seq, Size offset) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		// The given sequence
		const char* const s = Traits::CString<StringT>::Perform(seq);
		Size len = Traits::Length<StringT,Size>::Value(seq);
		Size j;

		for (Size i = offset; i < AncestorType::size; ++i)
		{
			// alias to the current character
			char c = AncestorType::data[i];
			for (j = 0; j != len; ++j)
			{
				if (s[j] == c)
					return i;
			}
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::find_first_not_of(char c, Size offset) const
	{
		for (Size i = offset; i < AncestorType::size; ++i)
		{
			// alias to the current character
			if (c == AncestorType::data[i])
				continue;
			else
				return i;
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::ifind_first_not_of(char c, Size offset) const
	{
		c = static_cast<char>(ToLower(c));
		for (Size i = offset; i < AncestorType::size; ++i)
		{
			// alias to the current character
			if (c == static_cast<char>(ToLower(AncestorType::data[i])))
				continue;
			else
				return i;
		}
		return npos;
	}



	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::find_first_not_of(const StringT& seq, Size offset) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		// The given sequence
		const char* const s = Traits::CString<StringT>::Perform(seq);
		Size len = Traits::Length<StringT,Size>::Value(seq);
		Size j;

		for (Size i = offset; i < AncestorType::size; ++i)
		{
			bool stop = true;
			// alias to the current character
			char c = AncestorType::data[i];
			for (j = 0; j != len; ++j)
			{
				if (s[j] == c)
				{
					stop = false;
					break;
				}
			}
			if (stop)
				return i;

		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::ifind_first_of(const StringT& seq, Size offset) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		// The given sequence
		const char* const s = Traits::CString<StringT>::Perform(seq);
		Size len = Traits::Length<StringT,Size>::Value(seq);
		Size j;

		for (Size i = offset; i < AncestorType::size; ++i)
		{
			// alias to the current character
			char c = static_cast<char>(ToLower(AncestorType::data[i]));
			for (j = 0; j != len; ++j)
			{
				if (static_cast<char>(ToLower(s[j])) == c)
					return i;
			}
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::ifind_first_not_of(const StringT& seq, Size offset) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		// The given sequence
		const char* const s = Traits::CString<StringT>::Perform(seq);
		Size len = Traits::Length<StringT,Size>::Value(seq);
		Size j;

		for (Size i = offset; i < AncestorType::size; ++i)
		{
			bool stop = true;
			// alias to the current character
			char c = static_cast<char>(ToLower(AncestorType::data[i]));
			for (j = 0; j != len; ++j)
			{
				if (static_cast<char>(ToLower(s[j])) == c)
				{
					stop = false;
					break;
				}
			}
			if (stop)
				return i;
		}
		return npos;
	}



	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::find_last_of(char c) const
	{
		Size i = AncestorType::size;
		while (i--)
		{
			if (c == AncestorType::data[i])
				return i;
		}
		return npos;
	}

	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::ifind_last_of(char c) const
	{
		c = static_cast<char>(ToLower(c));
		Size i = AncestorType::size;
		while (i--)
		{
			if (c == static_cast<char>(ToLower(AncestorType::data[i])))
				return i;
		}
		return npos;
	}

	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::find_last_of(char c, Size offset) const
	{
		c = static_cast<char>(ToLower(c));
		Size i = ((offset >= AncestorType::size) ? AncestorType::size : 1+offset);
		while (i--)
		{
			if (c == static_cast<char>(ToLower(AncestorType::data[i])))
				return i;
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::find_last_of(const StringT& seq, Size offset) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		// The given sequence
		const char* const s = Traits::CString<StringT>::Perform(seq);
		Size len = Traits::Length<StringT,Size>::Value(seq);
		Size j;

		Size i = ((offset >= AncestorType::size) ? AncestorType::size : 1+offset);
		while (i--)
		{
			// alias to the current character
			char c = AncestorType::data[i];
			for (j = 0; j != len; ++j)
			{
				if (s[j] == c)
					return i;
			}
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::ifind_last_of(const StringT& seq, Size offset) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		// The given sequence
		const char* const s = Traits::CString<StringT>::Perform(seq);
		Size len = Traits::Length<StringT,Size>::Value(seq);
		Size j;

		Size i = ((offset >= AncestorType::size) ? AncestorType::size : 1+offset);
		while (i--)
		{
			// alias to the current character
			char c = static_cast<char>(ToLower(AncestorType::data[i]));
			for (j = 0; j != len; ++j)
			{
				if (static_cast<char>(ToLower(s[j])) == c)
					return i;
			}
		}
		return npos;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline uint
	CString<ChunkSizeT,ExpandableT>::replace(char from, char to)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		uint count = 0;
		for (Size i = 0; i != AncestorType::size; ++i)
		{
			if (from == AncestorType::data[i])
			{
				AncestorType::data[i] = to;
				++count;
			}
		}
		return 0;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline uint
	CString<ChunkSizeT,ExpandableT>::ireplace(char from, char to)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		uint count = 0;
		from = static_cast<char>(ToLower(from));
		for (Size i = 0; i != AncestorType::size; ++i)
		{
			if (from == AncestorType::data[i])
			{
				AncestorType::data[i] = to;
				++count;
			}
		}
		return count;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline uint
	CString<ChunkSizeT,ExpandableT>::replace(Size offset, char from, char to)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		uint count = 0;
		for (Size i = offset; i != AncestorType::size; ++i)
		{
			if (from == AncestorType::data[i])
			{
				AncestorType::data[i] = to;
				++count;
			}
		}
		return count;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT1, class StringT2>
	inline uint
	CString<ChunkSizeT,ExpandableT>::replace(const StringT1& from, const StringT2& to)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		return replace<StringT1, StringT2>(0, from, to);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT1, class StringT2>
	inline uint
	CString<ChunkSizeT,ExpandableT>::ireplace(const StringT1& from, const StringT2& to)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		return ireplace<StringT1, StringT2>(0, from, to);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT1, class StringT2>
	uint
	CString<ChunkSizeT,ExpandableT>::replace(Size offset, const StringT1& from, const StringT2& to)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		YUNI_STATIC_ASSERT(Traits::CString<StringT1>::valid, CString_InvalidTypeForBuffer1);
		YUNI_STATIC_ASSERT(Traits::CString<StringT2>::valid, CString_InvalidTypeForBuffer2);
		YUNI_STATIC_ASSERT(Traits::Length<StringT1>::valid,  CString_InvalidTypeForBufferSize1);
		YUNI_STATIC_ASSERT(Traits::Length<StringT2>::valid,  CString_InvalidTypeForBufferSize2);

		uint count = 0;
		Size lenfrom = Traits::Length<StringT1,Size>::Value(from);
		if (lenfrom && offset < AncestorType::size)
		{
			Size lento = Traits::Length<StringT2,Size>::Value(to);
			Size pos;
			do
			{
				pos = find(from, offset);
				if (pos == npos)
					return count;
				erase(pos, lenfrom);
				insert(pos, to);
				offset = pos + lento;
				++count;
			}
			while (offset < AncestorType::size);
		}
		return count;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT1, class StringT2>
	uint
	CString<ChunkSizeT,ExpandableT>::ireplace(Size offset, const StringT1& from, const StringT2& to)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		YUNI_STATIC_ASSERT(Traits::CString<StringT1>::valid, CString_InvalidTypeForBuffer1);
		YUNI_STATIC_ASSERT(Traits::CString<StringT2>::valid, CString_InvalidTypeForBuffer2);
		YUNI_STATIC_ASSERT(Traits::Length<StringT1>::valid,  CString_InvalidTypeForBufferSize1);
		YUNI_STATIC_ASSERT(Traits::Length<StringT2>::valid,  CString_InvalidTypeForBufferSize2);

		Size lenfrom = Traits::Length<StringT1,Size>::Value(from);
		uint count = 0;
		if (lenfrom && offset < AncestorType::size)
		{
			Size lento = Traits::Length<StringT2,Size>::Value(to);
			Size pos;
			do
			{
				pos = ifind(from, offset);
				if (pos == npos)
					return count;
				erase(pos, lenfrom);
				insert(pos, to);
				offset = pos + lento;
				++count;
			}
			while (offset < AncestorType::size);
		}
		return count;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline uint
	CString<ChunkSizeT,ExpandableT>::ireplace(Size offset, char from, char to)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		uint count = 0;
		from = static_cast<char>(ToLower(from));
		for (Size i = offset; i < AncestorType::size; ++i)
		{
			if (from == AncestorType::data[i])
			{
				AncestorType::data[i] = to;
				++count;
			}
		}
		return count;
	}



	template<uint ChunkSizeT, bool ExpandableT>
	inline void
	CString<ChunkSizeT,ExpandableT>::consume(Size n)
	{
		if (n)
			Yuni::Private::CStringImpl::Consume<CStringType, adapter>::Perform(*this, n);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class U>
	inline U
	CString<ChunkSizeT,ExpandableT>::to() const
	{
		typedef typename Static::Remove::Const<U>::Type UType;
		return Yuni::Extension::CString::Into<UType>::Perform(*this);
	}

	template<uint ChunkSizeT, bool ExpandableT>
	template<class U>
	inline bool
	CString<ChunkSizeT,ExpandableT>::to(U& out) const
	{
		typedef typename Static::Remove::Const<U>::Type UType;
		return Yuni::Extension::CString::Into<UType>::Perform(*this, out);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class ModelT, bool ConstT>
	inline void
	CString<ChunkSizeT,ExpandableT>::erase(const IIterator<ModelT,ConstT>& it, Size len)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		erase(it.offset(), len);
	}



	template<uint ChunkSizeT, bool ExpandableT>
	void
	CString<ChunkSizeT,ExpandableT>::erase(Size offset, Size len)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
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
					AncestorType::data + sizeof(Char) * (offset + len), sizeof(Char) * (AncestorType::size - offset - len));
				// Reducing the cstr's size
				AncestorType::size -= len;
			}
			if (zeroTerminated)
				AncestorType::data[AncestorType::size] = Char();
		}
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline int
	CString<ChunkSizeT,ExpandableT>::at(Size offset) const
	{
		return (offset < AncestorType::size) ? AncestorType::data[offset] : 0;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class ModelT, bool ConstT, class StringT>
	inline void
	CString<ChunkSizeT,ExpandableT>::insert(const IIterator<ModelT,ConstT>& it, const StringT& string)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		insert(it.offset(), string);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::insert(Size offset, const StringT& s)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

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


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::insert(Size offset, const StringT& s, Size size)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);

		return insert(offset, Traits::CString<StringT>::Perform(s), size);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	bool
	CString<ChunkSizeT,ExpandableT>::insert(Size offset, const char* const cstr, Size size)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		if (size > 0)
		{
			if (offset >= AncestorType::size)
			{
				append(cstr, size);
				return true;
			}
			AncestorType::insert(offset, cstr, size);
			return true;
		}
		return false;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	bool
	CString<ChunkSizeT,ExpandableT>::insert(Size offset, char c)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		if (offset >= AncestorType::size)
		{
			append(&c, 1);
			return true;
		}
		AncestorType::insert(offset, &c, 1);
		return true;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::prepend(const StringT& s)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		return insert(0, s);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::prepend(const StringT& s, Size size)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);

		return insert(0, Traits::CString<StringT>::Perform(s), size);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::prepend(const char* const cstr, Size size)
	{
		return insert(0, cstr, size);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::prepend(char c)
	{
		return insert(0, c);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	void
	CString<ChunkSizeT,ExpandableT>::overwrite(Size offset, const char* const cstr, Size size)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		if (offset < AncestorType::size && size)
		{
			if (offset + size > AncestorType::size)
				YUNI_MEMCPY(AncestorType::data + offset, AncestorType::capacity, cstr, sizeof(Char) * (AncestorType::size - offset));
			else
				YUNI_MEMCPY(AncestorType::data + offset, AncestorType::capacity, cstr, sizeof(Char) * size);
		}
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline void
	CString<ChunkSizeT,ExpandableT>::overwrite(Size offset, const StringT& s)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

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


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline void
	CString<ChunkSizeT,ExpandableT>::overwrite(const StringT& s)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

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
				return overwrite(0, Traits::CString<StringT>::Perform(s), 1);
			// Researching for the substring with a known length
			return overwrite(0, Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::fixedLength);
		}

		return overwrite(0, Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::Value(s));
	}



	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline void
	CString<ChunkSizeT,ExpandableT>::overwriteRight(Size offset, const StringT& s)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

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
				return overwrite(AncestorType::size - offset - 1, Traits::CString<StringT>::Perform(s), 1);
			// Researching for the substring with a known length
			return overwrite(AncestorType::size - offset - Traits::Length<StringT,Size>::fixedLength,
				Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::fixedLength);
		}

		Size len = Traits::Length<StringT,Size>::Value(s);
		return overwrite(AncestorType::size - offset - len, Traits::CString<StringT>::Perform(s), len);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline void
	CString<ChunkSizeT,ExpandableT>::overwriteRight(const StringT& s)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

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
				return overwrite(AncestorType::size - 1, Traits::CString<StringT>::Perform(s), 1);
			// Researching for the substring with a known length
			return overwrite(AncestorType::size - Traits::Length<StringT,Size>::fixedLength,
				Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::fixedLength);
		}

		Size len = Traits::Length<StringT,Size>::Value(s);
		return overwrite(AncestorType::size - len, Traits::CString<StringT>::Perform(s), len);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline void
	CString<ChunkSizeT,ExpandableT>::overwriteCenter(const StringT& s)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

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
				return overwrite((AncestorType::size >> 1), Traits::CString<StringT>::Perform(s), 1);
			// Researching for the substring with a known length
			return overwrite((AncestorType::size >> 1) - (Traits::Length<StringT,Size>::fixedLength >> 1),
				Traits::CString<StringT>::Perform(s), Traits::Length<StringT,Size>::fixedLength);
		}

		Size len = Traits::Length<StringT,Size>::Value(s);
		return overwrite((AncestorType::size >> 1) - (len >> 1), Traits::CString<StringT>::Perform(s), len);
	}



	template<uint ChunkSizeT, bool ExpandableT>
	void
	CString<ChunkSizeT,ExpandableT>::truncate(Size newSize)
	{
		if (newSize < AncestorType::size)
			AncestorType::size = newSize;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::utf8size() const
	{
		// this routine is not exactly as fast as strlen, but it should make no
		// measurable difference
		uint i = 0;
		Size r = 0;
		for (; i != AncestorType::size; ++i)
		{
			if ((AncestorType::data[i] & 0xc0) != 0x80)
				++r;
		}
		return r;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::utf8valid() const
	{
		uint offset;
		return (UTF8::errNone == utf8valid(offset));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	UTF8::Error
	CString<ChunkSizeT,ExpandableT>::utf8valid(Size& offset) const
	{
		offset = 0;
		UTF8::Char c;
		UTF8::Error e;
		do
		{
			if (UTF8::errNone != (e = utf8next<false>(offset, c)))
				return (e == UTF8::errOutOfBound) ? UTF8::errNone : e;
		}
		while (true);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	bool
	CString<ChunkSizeT,ExpandableT>::utf8validFast() const
	{
		uint i = 0;
		uint l;
		while (i != AncestorType::size)
		{
			if (!(l = UTF8::Char::Size(AncestorType::data + i)))
				return false;
			i += l;
			if (i > AncestorType::size)
				return false;
		}
		return true;
	}

	template<uint ChunkSizeT, bool ExpandableT>
	template<bool InvalidateOffsetIfErrorT>
	UTF8::Error
	CString<ChunkSizeT,ExpandableT>::utf8next(Size& offset, UTF8::Char& out) const
	{
		if (offset >= AncestorType::size)
		{
			out.reset();
			if (InvalidateOffsetIfErrorT)
				offset = npos;
			return UTF8::errOutOfBound;
		}

		// Retrieving the lead character
		unsigned char lead = UTF8::Char::Mask8Bits(AncestorType::data[offset]);

		// {1}
		if (lead < 0x80)
		{
			++offset;
			out.pValue = lead;
			return UTF8::errNone;
		}
		// {2}
		if ((lead >> 5) == 0x6)
		{
			out.pValue = lead;
			if (++offset >= AncestorType::size)
			{
				if (InvalidateOffsetIfErrorT)
					offset = AncestorType::size;
				return UTF8::errNotEnoughData;
			}

			lead = UTF8::Char::Mask8Bits(AncestorType::data[offset]);
			if (UTF8::Char::IsTrail(lead))
			{
				out.pValue = ((out.pValue << 6) & 0x7ff) + ((lead) & 0x3f);
				++offset;
				return UTF8::errNone;
			}
			out.reset();
			if (InvalidateOffsetIfErrorT)
				offset = AncestorType::size;
			else
				--offset;
			return UTF8::errIncompleteSequence;
		}

		// {3}
		if ((lead >> 4) == 0xe)  // 1110 xxxx
		{
			out.pValue = lead;
			if (offset + 2 >= AncestorType::size)
			{
				if (InvalidateOffsetIfErrorT)
					offset = AncestorType::size;
				return UTF8::errNotEnoughData;
			}
			lead = UTF8::Char::Mask8Bits(AncestorType::data[++offset]);
			if (UTF8::Char::IsTrail(lead))
			{
				out.pValue = ((out.pValue << 12) & 0xffff) + ((lead << 6) & 0xfff);
				lead = UTF8::Char::Mask8Bits(AncestorType::data[++offset]);
				if (UTF8::Char::IsTrail(lead))
				{
					out.pValue += (lead) & 0x3f;
					++offset;
					return UTF8::errNone;
				}
				--offset;
			}
			out.reset();
			if (InvalidateOffsetIfErrorT)
				offset = AncestorType::size;
			else
				--offset;
			return UTF8::errIncompleteSequence;
		}

		// {4}
		if ((lead >> 3) == 0x1e) // 1111 0xxx
		{
			out.pValue = lead;
			if (offset + 3 >= AncestorType::size)
			{
				if (InvalidateOffsetIfErrorT)
					offset = AncestorType::size;
				return UTF8::errNotEnoughData;
			}

			lead = UTF8::Char::Mask8Bits(AncestorType::data[++offset]);
			if (UTF8::Char::IsTrail(lead))
			{
				out.pValue = ((out.pValue << 18) & 0x1fffff) + ((lead << 12) & 0x3ffff);
				lead = UTF8::Char::Mask8Bits(AncestorType::data[++offset]);
				if (UTF8::Char::IsTrail(lead))
				{
					out.pValue += (lead << 6) & 0xfff;
					lead = UTF8::Char::Mask8Bits(AncestorType::data[++offset]);
					if (UTF8::Char::IsTrail(lead))
					{
						out.pValue += (lead) & 0x3f;
						++offset;
						return UTF8::errNone;
					}
					--offset;
				}
				--offset;
			}

			out.reset();
			if (InvalidateOffsetIfErrorT)
				offset = AncestorType::size;
			else
				--offset;

			return UTF8::errIncompleteSequence;
		}
		out.reset();
		if (InvalidateOffsetIfErrorT)
			offset = AncestorType::size;
		return UTF8::errInvalidLead;
	}



	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::size() const
	{
		return AncestorType::size;
	}

	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::length() const
	{
		return AncestorType::size;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline size_t
	CString<ChunkSizeT,ExpandableT>::sizeInBytes() const
	{
		return (size_t) AncestorType::size * sizeof(Char);
	}



	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::capacity() const
	{
		return AncestorType::capacity;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline size_t
	CString<ChunkSizeT,ExpandableT>::max_size() const
	{
		return static_cast<Size>(-1);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline size_t
	CString<ChunkSizeT,ExpandableT>::capacityInBytes() const
	{
		return (size_t) AncestorType::capacity * sizeof(Char);
	}



	template<uint ChunkSizeT, bool ExpandableT>
	inline const char*
	CString<ChunkSizeT,ExpandableT>::data() const
	{
		return AncestorType::data;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline char*
	CString<ChunkSizeT,ExpandableT>::data()
	{
		return AncestorType::data;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline const char*
	CString<ChunkSizeT,ExpandableT>::c_str() const
	{
		return (NULL != AncestorType::data) ? AncestorType::data : "";
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::empty() const
	{
		return (0 == AncestorType::size);
	}

	template<uint ChunkSizeT, bool ExpandableT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::null() const
	{
		return (NULL == AncestorType::data);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline void
	CString<ChunkSizeT,ExpandableT>::shrink()
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		AncestorType::shrink();
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline void
	CString<ChunkSizeT,ExpandableT>::resize(Size len)
	{
		if (AncestorType::expandable)
		{
			// Dynamic cstr
			if (!adapter)
				AncestorType::reserve(len + 1 /*AncestorType::zeroTerminated*/);
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
		if (!adapter && zeroTerminated)
			Yuni::Private::CStringImpl::FinalZero<adapter>::Set(AncestorType::data, AncestorType::size);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	void
	CString<ChunkSizeT,ExpandableT>::resize(Size len, const StringT& pattern)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		if (len > AncestorType::size)
		{
			Size previousLength = AncestorType::size;
			resize(len);
			fill(previousLength, pattern);
		}
		else
			resize(len);
	}



	template<uint ChunkSizeT, bool ExpandableT>
	void
	CString<ChunkSizeT,ExpandableT>::trimRight(char c)
	{
		while (AncestorType::size > 0 && AncestorType::data[AncestorType::size - 1] == c)
			--AncestorType::size;
		if (zeroTerminated)
			Yuni::Private::CStringImpl::FinalZero<adapter>::Set(AncestorType::data, AncestorType::size);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	void
	CString<ChunkSizeT,ExpandableT>::trimLeft(char c)
	{
		if (AncestorType::size > 0)
		{
			Size offset = 0;
			while (offset < AncestorType::size && AncestorType::data[offset] == c)
				++offset;
			if (offset)
			{
				if (!adapter)
					erase(0, offset);
				else
				{
					AncestorType::data += offset;
					AncestorType::size -= offset;
				}
			}
		}
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	void
	CString<ChunkSizeT,ExpandableT>::trimRight(const StringT& whitespaces)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);

		const uint ptrlen = Traits::Length<StringT, uint>::Value(whitespaces);
		if (!ptrlen || empty())
			return;

		const char* const ptr = Traits::CString<StringT>::Perform(whitespaces);
		uint i;
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
		// The const_cast is only here to make it compile when the string
		// is an adapter
		if (!adapter && zeroTerminated)
			Yuni::Private::CStringImpl::FinalZero<adapter>::Set(AncestorType::data, AncestorType::size);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	void
	CString<ChunkSizeT,ExpandableT>::trimLeft(const StringT& whitespaces)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);

		const uint ptrlen = Traits::Length<StringT, uint>::Value(whitespaces);
		if (!ptrlen || empty())
			return;

		const char* const ptr = Traits::CString<StringT>::Perform(whitespaces);
		Size count = 0;
		uint i;
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
		// Remove the first 'count' characters
		consume(count);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline void
	CString<ChunkSizeT,ExpandableT>::decalOffset(Size count)
	{
		AncestorType::data += count;
		AncestorType::size -= count;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline void
	CString<ChunkSizeT,ExpandableT>::trim()
	{
		// It seems more interesting to trim from the end first, to reduce the size
		// of the cstr as soon as possible and to reduce the amount of data to move
		// if a region must be removed by trimLeft.
		trimRight(" \t\r\n");
		trimLeft(" \t\r\n");
	}



	template<uint ChunkSizeT, bool ExpandableT>
	inline void
	CString<ChunkSizeT,ExpandableT>::trim(char c)
	{
		// It seems more interesting to trim from the end first, to reduce the size
		// of the cstr as soon as possible and to reduce the amount of data to move
		// if a region must be removed by trimLeft.
		trimRight(c);
		trimLeft(c);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline void
	CString<ChunkSizeT,ExpandableT>::trim(const StringT& whitespaces)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForLength);

		// It seems more interesting to trim from the end first, to reduce the size
		// of the cstr as soon as possible and to reduce the amount of data to move
		// if a region must be removed by trimLeft.
		trimRight(whitespaces);
		trimLeft(whitespaces);
	}



	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::assignWithoutChecking(
		const char* const block, Size blockSize)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		return AncestorType::assignWithoutChecking(block, blockSize);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::appendWithoutChecking(
		const char* const block, Size blockSize)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		return AncestorType::appendWithoutChecking(block, blockSize);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::assignWithoutChecking(char c)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		return AncestorType::assignWithoutChecking(c);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::Size
	CString<ChunkSizeT,ExpandableT>::appendWithoutChecking(char c)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		return AncestorType::appendWithoutChecking(c);
	}





	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	CString<ChunkSizeT,ExpandableT>&
	CString<ChunkSizeT,ExpandableT>::format(const StringT& format, ...)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);

		// Empty the cstr
		clear();
		// Dealing with the variadic arguments
		va_list parg;
		va_start(parg, format);
		vappendFormat(Traits::CString<StringT>::Perform(format), parg);
		va_end(parg);
		return *this;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	CString<ChunkSizeT,ExpandableT>&
	CString<ChunkSizeT,ExpandableT>::appendFormat(const StringT& format, ...)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);

		// Dealing with the variadic arguments
		va_list parg;
		va_start(parg, format);
		vappendFormat(Traits::CString<StringT>::Perform(format), parg);
		va_end(parg);
		return *this;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	void
	CString<ChunkSizeT,ExpandableT>::vappendFormat(const char* format, va_list args)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
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
			{
				// -1 because reserve() always count a final zero
				AncestorType::reserve(AncestorType::size + chunkSize - 1);
			}
			do
			{
				// In C99, vnsprintf may modify its parameter arg
				va_list ag;
				YUNI_VA_COPY(ag, args);
				i = Private::CStringImpl::vnsprintf<Char>(AncestorType::data + AncestorType::size,
					(AncestorType::capacity - AncestorType::size), format, ag);
				va_end(ag);

				if (i < 0)
				{
					if (i == -1)
					{
						// The string was truncated
						// -1 because reserve() always count a final zero
						AncestorType::reserve(AncestorType::capacity + chunkSize - 1);
						continue;
					}
					// An error occured
					return;
				}
				AncestorType::size += (Size) i;
				if (zeroTerminated)
					AncestorType::data[AncestorType::size] = Char();
				return;
			}
			while (true);
		}
		else
		{
			// In this case, the cstr can not be expanded
			// We will only try once
			if (AncestorType::capacity != AncestorType::size)
			{
				i = Private::CStringImpl::vnsprintf<Char>(AncestorType::data + AncestorType::size,
					(AncestorType::capacity - AncestorType::size), format, args);
				if (i >= 0)
				{
					AncestorType::size += (Size) i;
					if (zeroTerminated)
						AncestorType::data[AncestorType::size] = Char();
				}
				else
				{
					if (i == -1)
					{
						// The string was truncated
						AncestorType::size = AncestorType::capacity;
						if (zeroTerminated)
							AncestorType::data[AncestorType::capacity] = Char();
					}
				}
			}
		}
	}


	template<uint ChunkSizeT, bool ExpandableT>
	CString<ChunkSizeT,ExpandableT>&
	CString<ChunkSizeT,ExpandableT>::toLower()
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		for (Size i = 0; i < AncestorType::size; ++i)
		{
			if (UTF8::Char::IsASCII((unsigned char)AncestorType::data[i]))
				AncestorType::data[i] = static_cast<Char>(ToLower(AncestorType::data[i]));
		}
		return *this;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	CString<ChunkSizeT,ExpandableT>&
	CString<ChunkSizeT,ExpandableT>::toUpper()
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		for (Size i = 0; i < AncestorType::size; ++i)
		{
			if (UTF8::Char::IsASCII((unsigned char)AncestorType::data[i]))
				AncestorType::data[i] = (Char) ToUpper(AncestorType::data[i]);
		}
		return *this;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<template<class,class> class ListT, class UType, class Alloc, class StringT>
	void
	CString<ChunkSizeT,ExpandableT>::split(ListT<UType,Alloc>& out, const StringT& sep,
		bool keepEmptyElements, bool trimElements, bool emptyBefore) const
	{
		// Empty the container
		if (emptyBefore)
			out.clear();
		// String empty
		if (AncestorType::size != 0)
		{
			// Indexes
			Size indx = 0;
			Size len  = 0;
			Size newIndx;

			// Temporary buffer
			WritableType segment;

			do
			{
				newIndx = this->find_first_of(sep, indx);
				if (npos == newIndx)
				{
					segment.assign(AncestorType::data + indx, AncestorType::size - indx);
					if (trimElements)
						segment.trim();
					if (not segment.empty() || keepEmptyElements)
						out.push_back(segment.template to<UType>());
					return;
				}

				if ((len = newIndx - indx) || keepEmptyElements)
				{
					segment.assign(AncestorType::data + indx, len);
					if (trimElements)
						segment.trim();
					if (not segment.empty() || keepEmptyElements)
						out.push_back(segment.template to<UType>());
				}
				indx = newIndx + 1;
			}
			while (true);
		}
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline char
	CString<ChunkSizeT,ExpandableT>::first() const
	{
		return (AncestorType::size) ? AncestorType::data[0] : '\0';
	}

	template<uint ChunkSizeT, bool ExpandableT>
	inline char
	CString<ChunkSizeT,ExpandableT>::last() const
	{
		return (AncestorType::size) ? AncestorType::data[AncestorType::size - 1] : '\0';
	}


	template<uint ChunkSizeT, bool ExpandableT>
	void
	CString<ChunkSizeT,ExpandableT>::convertSlashesIntoBackslashes()
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		for (uint i = 0; i != AncestorType::size; ++i)
		{
			if ('/' == AncestorType::data[i])
				AncestorType::data[i] = '\\';
		}
	}


	template<uint ChunkSizeT, bool ExpandableT>
	void
	CString<ChunkSizeT,ExpandableT>::convertBackslashesIntoSlashes()
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		for (uint i = 0; i != AncestorType::size; ++i)
		{
			if ('\\' == AncestorType::data[i])
				AncestorType::data[i] = '/';
		}
	}


	template<uint ChunkSizeT, bool ExpandableT>
	void
	CString<ChunkSizeT,ExpandableT>::duplicate(int n)
	{
		YUNI_STATIC_ASSERT(!adapter, CString_Adapter_ReadOnly);
		if (n > 0 && AncestorType::size > 0)
		{
			if (AncestorType::size == 1)
			{
				// Resize the string
				resize(AncestorType::size * (n + 1));
				// Caraceter copy
				for (uint i = 1; i != AncestorType::size; ++i)
					AncestorType::data[i] = AncestorType::data[0];
			}
			else
			{
				Size seglen = AncestorType::size;
				Size offset = AncestorType::size;
				// Resize the string
				resize(AncestorType::size * (n + 1));

				while (offset < AncestorType::size)
				{
					if (seglen + offset > AncestorType::size)
						YUNI_MEMCPY(AncestorType::data + offset, AncestorType::capacity, AncestorType::data, AncestorType::size - offset);
					else
						YUNI_MEMCPY(AncestorType::data + offset, AncestorType::capacity, AncestorType::data, seglen);
					offset += seglen;
				}
			}
		}
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline int
	CString<ChunkSizeT,ExpandableT>::Compare(const char* const s1, uint l1,
		const char* const s2, uint l2)
	{
		return Yuni::Private::CStringImpl::Compare(s1, l1, s2, l2);
	}

	template<uint ChunkSizeT, bool ExpandableT>
	inline int
	CString<ChunkSizeT,ExpandableT>::CompareInsensitive(const char* const s1, uint l1,
		const char* const s2, uint l2)
	{
		return Yuni::Private::CStringImpl::CompareInsensitive(s1, l1, s2, l2);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::equals(const StringT& rhs) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		return ((AncestorType::size == Traits::Length<StringT,Size>::Value(rhs))
			&& (!AncestorType::size
				|| Yuni::Private::CStringImpl::Equals(AncestorType::data, Traits::CString<StringT>::Perform(rhs), AncestorType::size)));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::equalsInsensitive(const StringT& rhs) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		return ((AncestorType::size == Traits::Length<StringT,Size>::Value(rhs))
			&& (!AncestorType::size
				|| Yuni::Private::CStringImpl::EqualsInsensitive(AncestorType::data, Traits::CString<StringT>::Perform(rhs), AncestorType::size)));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline int
	CString<ChunkSizeT,ExpandableT>::compare(const StringT& rhs) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		return Yuni::Private::CStringImpl::Compare(AncestorType::data, AncestorType::size,
			Traits::CString<StringT>::Perform(rhs), Traits::Length<StringT,Size>::Value(rhs));
	}

	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline int
	CString<ChunkSizeT,ExpandableT>::compareInsensitive(const StringT& rhs) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		return Yuni::Private::CStringImpl::CompareInsensitive(AncestorType::data, AncestorType::size,
			Traits::CString<StringT>::Perform(rhs), Traits::Length<StringT,Size>::Value(rhs));
	}



	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::ConstOperatorBracketReturnType // char&
	CString<ChunkSizeT,ExpandableT>::operator [] (Size offset) const
	{
		assert(offset < AncestorType::size && "string, operator[] : index out of bounds");
		return AncestorType::data[offset];
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline typename CString<ChunkSizeT,ExpandableT>::OperatorBracketReturnType // char&
	CString<ChunkSizeT,ExpandableT>::operator [] (Size offset)
	{
		assert(offset < AncestorType::size && "string, operator[] : index out of bounds");
		return AncestorType::data[offset];
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::operator != (const StringT& rhs) const
	{
		return !(*this == rhs);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::operator ! () const
	{
		return !AncestorType::size;
	}



	template<uint ChunkSizeT, bool ExpandableT>
	template<class U>
	inline CString<ChunkSizeT,ExpandableT>&
	CString<ChunkSizeT,ExpandableT>::operator += (const U& rhs)
	{
		append(rhs);
		return *this;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class U>
	inline CString<ChunkSizeT,ExpandableT>&
	CString<ChunkSizeT,ExpandableT>::operator << (const U& rhs)
	{
		append(rhs);
		return *this;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline CString<ChunkSizeT,ExpandableT>&
	CString<ChunkSizeT,ExpandableT>::operator = (const CString<ChunkSizeT,ExpandableT>& rhs)
	{
		assign(rhs);
		return *this;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class U>
	inline CString<ChunkSizeT,ExpandableT>&
	CString<ChunkSizeT,ExpandableT>::operator = (const U& rhs)
	{
		assign(rhs);
		return *this;
	}



	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::operator < (const StringT& rhs) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		return Yuni::Private::CStringImpl::Compare(AncestorType::data, AncestorType::size,
			Traits::CString<StringT>::Perform(rhs), Traits::Length<StringT,Size>::Value(rhs)) < 0;
	}

	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::operator > (const StringT& rhs) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		return Yuni::Private::CStringImpl::Compare(AncestorType::data, AncestorType::size,
			Traits::CString<StringT>::Perform(rhs), Traits::Length<StringT,Size>::Value(rhs)) > 0;
	}

	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::operator <= (const StringT& rhs) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		return Yuni::Private::CStringImpl::Compare(AncestorType::data, AncestorType::size,
			Traits::CString<StringT>::Perform(rhs), Traits::Length<StringT,Size>::Value(rhs)) <= 0;
	}

	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::operator >= (const StringT& rhs) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);

		return Yuni::Private::CStringImpl::Compare(AncestorType::data, AncestorType::size,
			Traits::CString<StringT>::Perform(rhs), Traits::Length<StringT,Size>::Value(rhs)) >= 0;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::operator == (const StringT& rhs) const
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, CString_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  CString_InvalidTypeForBufferSize);
		return equals(rhs);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline bool
	CString<ChunkSizeT,ExpandableT>::operator == (const CString& rhs) const
	{
		return equals(rhs);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	CString<ChunkSizeT,ExpandableT>&
	CString<ChunkSizeT,ExpandableT>::operator *= (int n)
	{
		duplicate(n);
		return *this;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	inline void
	CString<ChunkSizeT,ExpandableT>::adapt(const char* cstring, Size length)
	{
		Yuni::Private::CStringImpl::AdapterAssign<CStringType, adapter>::Perform(*this,
			cstring, length);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline void
	CString<ChunkSizeT,ExpandableT>::adapt(const StringT& string)
	{
		Yuni::Private::CStringImpl::AdapterAssign<CStringType, adapter>::Perform(*this,
			Traits::CString<StringT>::Perform(string),
			Traits::Length<StringT,Size>::Value(string));
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT>
	inline void
	CString<ChunkSizeT,ExpandableT>::adapt(const StringT& string, Size length, Size offset)
	{
		Yuni::Private::CStringImpl::AdapterAssign<CStringType, adapter>::Perform(*this,
			Traits::CString<StringT>::Perform(string) + offset,
			length);
	}

	template<uint ChunkSizeT, bool ExpandableT>
	inline void
	CString<ChunkSizeT,ExpandableT>::adaptWithoutChecking(const char* const cstring, Size length)
	{
		AncestorType::data = const_cast<char*>(cstring);
		AncestorType::size = length;
	}


	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT1, class StringT2>
	inline void
	CString<ChunkSizeT,ExpandableT>::extractKeyValue(StringT1& key, StringT2& value,
		bool ignoreCase, char separator) const
	{
		// ReInitializing
		key.clear();
		value.clear();

		if (empty()) // The string is empty, Nothing to do
			return;

		Size left = find_first_not_of(" \t\n\r");
		if (left == npos)
			return;

		// Section
		if ('{' == AncestorType::data[left])
		{
			key.append('{');
			return;
		}
		if ('}' == AncestorType::data[left])
		{
			key.append('}');
			return;
		}
		if ('[' == AncestorType::data[left])
		{
			key.append('[');
			++left;
			Size right = find(']', left);
			if (right != npos && right != left)
			{
				value.append(*this, right - left, left);
				value.trim();
			}
			return;
		}

		// all separators
		CString<8, false> seplist = "=/;";
		seplist[0] = separator;
		// If not a section, it should be a key/value
		// Looking for the symbol `=`
		Size equal = left;
		do
		{
			equal = find_first_of(seplist, equal);
			if (equal < AncestorType::size)
			{
				if ('/' == AncestorType::data[equal])
				{
					if (equal + 1 < AncestorType::size && AncestorType::data[equal + 1] != '/')
					{
						++equal;
						continue;
					}
				}
				if (equal == left)
					return;
				if (separator == AncestorType::data[equal])
					break;
			}
			return;
		}
		while (true);

		// Getting our key
		key.assign(*this, equal - left, left);
		key.trimRight(" \t\n\r");
		if (ignoreCase)
			key.toLower();

		// Looking for the first interesting char
		Size rv(equal);
		++rv; // After the symbol `=`
		while (rv < AncestorType::size && (AncestorType::data[rv] == ' ' || AncestorType::data[rv] == '\t' ||AncestorType::data[rv] == '\r' ||AncestorType::data[rv] == '\n'))
			++rv;
		if (rv < AncestorType::size) // Empty value
		{
			char c = AncestorType::data[rv];
			switch (c)
			{
				case ';':
					// Empty value
					break;
				case '"':
				case '\'':
					{
						// Value enclosed in a string
						++rv;
						typename AncestorType::Size next;
						next = FindEndOfSequence<CStringType>(AncestorType::data + rv, c, AncestorType::size - rv);
						if (next != npos)
							value.append(AncestorType::data + rv, next);
							//value.assignFromEscapedCharacters(AncestorType::data, next, rv);
						else
							value.append(AncestorType::data + rv, AncestorType::size - rv);
						break;
					}
				case '/':
					// Empty value if we have a comment otherwise '/' is a valid entry
					if (rv + 1 >= AncestorType::size || AncestorType::data[rv + 1] == '/')
						break;
				default:
					{
						// Standard value
						Size semicolon = find_first_of(';', rv);
						if (npos != semicolon)
							value.append(*this, semicolon - rv, rv);
						else
							value.append(*this, AncestorType::size - rv, rv);
						value.trimRight(" \t\n\r");
						break;
					}
			}
		}
	}



	template<uint ChunkSizeT, bool ExpandableT>
	template<class StringT, class PredicateT>
	void
	CString<ChunkSizeT,ExpandableT>::words(const StringT& separators, const PredicateT& predicate) const
	{
		if (0 == AncestorType::size)
			return;

		// Indexes
		Size offset = 0;
		Size len  = 0;
		Size newIndx;
		// Temporary buffer
		AnyString word;

		do
		{
			newIndx = find_first_of(separators, offset);

			if (newIndx < AncestorType::size)
			{
				len = newIndx - offset;
				if (len)
				{
					word.assign(AncestorType::data + offset, len);
					predicate(word);
				}
			}
			else
			{
				word.adapt(AncestorType::data + offset, AncestorType::size - offset);
				predicate(word);
				break;
			}

			offset = newIndx + 1;
		}
		while (true);
	}


	template<uint ChunkSizeT, bool ExpandableT>
	size_t
	CString<ChunkSizeT,ExpandableT>::hash() const
	{
		size_t hash = 0;
		for (uint i = 0; i != AncestorType::size; ++i)
			hash = AncestorType::data[i] + (hash << 6) + (hash << 16) - hash;

		return hash;
	}



} // namespace Yuni

#endif // __YUNI_CORE_STRING_STRING_HXX__
