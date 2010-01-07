#ifndef __YUNI_CORE_BIT_BIT_ARRAY_H__
# define __YUNI_CORE_BIT_BIT_ARRAY_H__

# include "../../yuni.h"
# include "../memorybuffer.h"
# include "bit.h"
# include <iostream>


namespace Yuni
{
namespace Core
{
namespace Bit
{


	/*!
	** \brief Array of bits
	**
	** This class provides routines for handling an array of bits and is especially
	** efficient for a medium or large amount of bits.
	** 
	** Performance Tip: For small arrays of bits (for example < 50), a typical
	**   char[] may be faster, but it will use more memory.
	**
	**
	** \code
	** Core::Bit::Array bits(50);
	** std::cout << bits << "\n";
	**
	** bits.set(12);
	** bits.set(27);
	** bits.set(48);
	** std::cout << bits << "\n";
	**
	** bits.unset(27);
	** std::cout << bits << "\n";
	**
	** bits.unset();
	** std::cout << bits << "\n";
	** \endcode
	*/
	class Array
	{
	public:
		//! Size
		typedef unsigned int Size;

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		Array();

		/*!
		** \brief Constructor, with an initial number of bits
		*/
		explicit Array(unsigned int n);

		/*!
		** \brief Constructor, with an initial number of bits and a value for each of them
		*/
		Array(unsigned int n, bool value);

		/*!
		** \brief Copy constructor
		*/
		Array(const Array& copy);

		//! Destructor
		~Array() {}
		//@}


		//! \name Bit manipulation
		//@{
		/*!
		** \brief Unset all bits at once
		*/
		void reset();

		/*!
		** \brief Set/Unset all bits at once
		*/
		void reset(bool value);

		/*!
		** \brief Set the Ith bit
		*/
		void set(unsigned int i);

		/*!
		** \brief Set/Unset the Ith bit
		*/
		void set(unsigned int i, bool value);

		/*!
		** \brief Unset the Ith bit
		*/
		void unset(unsigned int i);

		/*!
		** \brief Unset all bits at once
		**
		** Equivalent to reset().
		*/
		void unset();

		/*!
		** \brief Get if the Ith bit is set
		*/
		bool get(unsigned int i);
		//@}


		//! \name Import/Export
		//@{
		/*!
		** \brief Load an array of bit from a buffer
		**
		** \param buffer Any buffer
		*/
		template<class AnyStringT> void loadFromBuffer(const AnyStringT& u);

		/*!
		** \brief Load an array of bit from a buffer
		**
		** \param buffer A raw buffer
		** \param size Size ofthe buffer
		*/
		template<class AnyStringT> void loadFromBuffer(const AnyStringT& u, unsigned int size);

		/*!
		** \brief Save the array of bits into another buffer (which may use any type)
		**
		** \param u A buffer
		*/
		template<class AnyBufferT> void saveToBuffer(AnyBufferT& u);
		//@}


		//! \name Memory management
		//@{
		/*!
		** \brief The number of bits within the buffer
		*/
		unsigned int size() const;

		/*!
		** \brief The number of bits within the buffer
		*/
		unsigned int count() const;

		/*!
		** \brief The size in bytes needed to store all bits within the buffer
		**
		** This value greater of equal to the value returned by size().
		*/
		unsigned int sizeInBytes() const;

		/*!
		** \brief Reserve an amount of bits
		*/
		void reserve(unsigned int n);

		/*!
		** \brief Truncate to an amount of bits
		*/
		void truncate(unsigned int n);

		/*!
		** \brief Resize the internal buffer to a given amount of bit
		*/
		void resize(unsigned int n);
		//@}


		//! \name Stream
		//@{
		template<class U> void print(U& out) const;
		//@}

		//! \name Operators
		//@{
		//! The operator `=` (clear)
		Array& operator = (const NullPtr&);
		//! The operator `=` (clear)
		Array& operator = (const NullPtr*);
		//! The operator `=`
		Array& operator = (const Array& rhs);
		//! The operator `=`
		template<class AnyStringT> Array& operator = (const AnyStringT& rhs);
		//@}


	private:
		//! Buffer Type
		typedef IString<20, true, false> BufferType;
		//! Number of bits into the buffer, requested by the caller
		unsigned int pCount;
		//! Internal buffer
		BufferType pBuffer;

	}; // class Array






} // namespace Bit
} // namespace Core
} // namespace Yuni


# include "array.hxx"



//! \name Operator overload for stream printing
//@{
inline std::ostream& operator << (std::ostream& out, const Yuni::Core::Bit::Array& rhs)
{
	rhs.print(out);
	return out;
}
//@}


#endif // __YUNI_CORE_BIT_BIT_ARRAY_H__
