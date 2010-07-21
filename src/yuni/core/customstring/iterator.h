#ifndef __YUNI_CORE_CUSTOMSTRING_ITERATOR_H__
# define __YUNI_CORE_CUSTOMSTRING_ITERATOR_H__


// !!! Do not use includes here


struct Model
{

	// Forward declarations
	class NullIterator;
	class UTF8Iterator;
	class ByteIterator;


	class NullIterator
	{
	public:
		//! Type of the original string
		typedef CustomStringType StringType;

		//! The type of the orignal object
		typedef UTF8::Char value_type;
		//! An unsigned integral type
		typedef typename CustomStringType::size_type  size_type;
		//! A signed integral type
		typedef typename CustomStringType::difference_type  difference_type;

		enum
		{
			iteratorModelForCustomString = 1,
			//! A non-zero value if the iterator can go forward
			canGoForward  = true,
			//! A non-zero value if the iterator can go backward
			canGoBackward = false,
		};


	public:
		/*!
		** \brief Get the current offset in the string
		*/
		Size offset() const {return pString.size();}

		/*!
		** \brief Get a reference to the original string
		*/
		const StringType& string() const {return pString;}

		/*!
		** \brief Get the current offset in the string
		**
		** This method should not be directly used and is only useful
		** for other external iterators
		*/
		Size rawOffset() const {return pString.size();}

	protected:
		NullIterator(const StringType& s)
			:pString(const_cast<StringType&>(s))
		{}

		NullIterator(const NullIterator& copy)
			:pString(copy.pString)
		{}

		template<class ModelT>
		NullIterator(const ModelT& copy)
			:pString(const_cast<StringType&>(copy.string()))
		{}

		static void forward(difference_type)
		{
			// Do nothing
		}

		template<class ModelT>
		static void reset(const ModelT&)
		{
			// Do nothing
		}

		template<class ModelT>
		bool equals(const ModelT& model)
		{
			return (pString.size() == model.rawOffset());
		}

		template<class ModelT>
		difference_type distance(const ModelT& model)
		{
			return pString.size() - model.offset();
		}

		// UTF8::Char& operator * ()

		// UTF8::Char* operator -> ()

	private:
		//! Reference to the original string
		mutable StringType& pString;

	}; // class NullIterator



	class UTF8Iterator
	{
	public:
		//! Type of the original string
		typedef CustomStringType StringType;

		//! The type of the orignal object
		typedef UTF8::Char value_type;
		//! An unsigned integral type
		typedef typename CustomStringType::size_type  size_type;
		//! A signed integral type
		typedef typename CustomStringType::difference_type  difference_type;

		enum
		{
			iteratorModelForCustomString = 1,
			//! A non-zero value if the iterator can go forward
			canGoForward  = true,
			//! A non-zero value if the iterator can go backward
			canGoBackward = false,
		};

	public:
		/*!
		** \brief Get the current offset in the string
		*/
		Size offset() const {return (pOffset >= pString.size()) ? (pString.size() - pChar.size()) : (pOffset - pChar.size());}

		/*!
		** \brief Get a reference to the original string
		*/
		StringType& string() {return pString;}
		const StringType& string() const {return pString;}

		/*!
		** \brief Get the current offset in the string
		**
		** This method should not be directly used and is only useful
		** for other external iterators
		*/
		Size rawOffset() const {return pOffset;}

	protected:
		UTF8Iterator(const StringType& s, size_type offset)
			:pOffset(offset), pString(const_cast<StringType&>(s))
		{
			// We must forward once to got the first char
			forward();
		}
		UTF8Iterator(const NullIterator& s)
			:pOffset(s.rawOffset()), pString(const_cast<StringType&>(s.string()))
		{}

		explicit UTF8Iterator(const StringType& s)
			:pOffset(0), pString(s)
		{}
		UTF8Iterator(const UTF8Iterator& copy)
			:pChar(copy.pChar), pOffset(copy.rawOffset()),
			pString(const_cast<StringType&>(copy.pString))
		{}

		void forward()
		{
			pString.utf8next<true>(pOffset, pChar);
		}

		void forward(difference_type n)
		{
			while (n > 0)
			{
				forward();
				--n;
			}
		}

		template<class ModelT>
		void reset(const ModelT& model)
		{
			pOffset = model.rawOffset();
		}

		template<class ModelT>
		difference_type distance(const ModelT& model) const
		{
			return offset() - model.offset();
		}

		template<class ModelT>
		bool equals(const ModelT& model) const
		{
			return (pOffset == model.rawOffset());
		}

		UTF8::Char& operator * ()
		{
			return pChar;
		}

		UTF8::Char* operator -> ()
		{
			return &pChar;
		}

	private:
		UTF8::Char pChar;
		//! Offset in the string
		Size pOffset;
		//! Reference to the original
		mutable StringType& pString;

	}; // class UTF8Iterator



	class ByteIterator
	{
	public:
		//! Type of the original string
		typedef CustomStringType StringType;

		//! The type of the orignal object
		typedef char value_type;
		//! An unsigned integral type
		typedef typename CustomStringType::size_type  size_type;
		//! A signed integral type
		typedef typename CustomStringType::difference_type  difference_type;

		enum
		{
			iteratorModelForCustomString = 1,
			//! A non-zero value if the iterator can go forward
			canGoForward  = true,
			//! A non-zero value if the iterator can go backward
			canGoBackward = false,
		};

	public:
		/*!
		** \brief Get the current offset in the string
		*/
		Size offset() const {return pOffset;}

		/*!
		** \brief Get a reference to the original string
		*/
		StringType& string() {return pString;}
		const StringType& string() const {return pString;}

		/*!
		** \brief Get the current offset in the string
		**
		** This method should not be directly used and is only useful
		** for other external iterators
		*/
		Size rawOffset() const {return pOffset;}


	protected:
		ByteIterator(const StringType& s, size_type offset)
			:pOffset(offset), pString(const_cast<StringType&>(s))
		{}
		ByteIterator(const NullIterator& s)
			:pOffset(s.rawOffset()),
			pString(const_cast<StringType&>(s.string()))
		{}

		explicit ByteIterator(const StringType& s)
			:pOffset(0), pString(s)
		{}
		ByteIterator(const ByteIterator& copy)
			:pOffset(copy.rawOffset()),
			pString(const_cast<StringType&>(copy.pString))
		{}
		ByteIterator(const UTF8Iterator& copy)
			:pOffset(copy.offset()),
			pString(const_cast<StringType&>(copy.string()))
		{}

		void forward()
		{
			++pOffset;
		}

		void forward(difference_type n)
		{
			pOffset += n;
		}

		template<class ModelT>
		void reset(const ModelT& model)
		{
			pOffset = model.rawOffset();
		}

		template<class ModelT>
		difference_type distance(const ModelT& model) const
		{
			return offset() - model.offset();
		}

		template<class ModelT>
		bool equals(const ModelT& model) const
		{
			return (pOffset == model.rawOffset());
		}

		char& operator * ()
		{
			return pString[pOffset];
		}

		char* operator -> ()
		{
			return &(pString[pOffset]);
		}

	private:
		//! Offset in the string
		size_type pOffset;
		//! Reference to the original
		mutable StringType& pString;

	}; // class ByteIterator





}; // class Model

#endif // __YUNI_CORE_CUSTOMSTRING_ITERATOR_H__