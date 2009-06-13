#ifndef __YUNI_CORE_ATOMIC_INT32_H__
# define __YUNI_CORE_ATOMIC_INT32_H__

# include "../../yuni.h"

# if defined(YUNI_OS_OSX)
#	include <libkern/OSAtomic.h>
# endif
# include "../system/windows.hdr.h"

# if defined(YUNI_OS_WINDOWS)
#	define YUNI_ATOMIC_INT32_TYPE  volatile LONG
# else
#	define YUNI_ATOMIC_INT32_TYPE  volatile int32_t
# endif


namespace Yuni
{
namespace Atomic
{


	class Int32
	{
	public:
        //! \name Constructors
        //@{
        //! Default Constructor
		Int32();
        /*!
        ** \brief Constructor with a default value
        ** \param n The default value
        */
		explicit Int32(const int n);
        //! Copy constructor
		Int32(const Int32& rhs);
        //@}

        //! \name Primitives
        //@{
        //! Add
		void add(const int x);
        //! Substract
		void sub(const int x);
        //! Increment the value
		void increment();
        //! Decrement the value
		void decrement();

        /*!
        ** \brief Set the value from a mere `int`
        */
		void set(const int x);

        /*!
        ** \brief Set the value from another Int32
        ** \param rhs Another Int32 value
        */
		void set(const Int32& rhs);

        /*!
        ** \brief Get the current value
        */
		sint32 value() const;
        //@}

        //! \name Operators
        //@{
		Int32& operator += (const int x);
		Int32& operator -= (const int x);

		Int32& operator ++ ();
		Int32& operator -- ();

		Int32 operator ++ (const int);
		Int32 operator -- (const int);

		Int32& operator = (const int x);
		Int32& operator = (const Int32& rhs);

		//! Cast operator
		operator sint32 () const {return pValue;}
        //@}

	private:
		//! The value
		YUNI_ATOMIC_INT32_TYPE pValue;

	}; // class Int32




} // namespace Atomic
} // namespace Yuni

# include "int32.hxx"

#endif // __YUNI_CORE_ATOMIC_INT32_H__
