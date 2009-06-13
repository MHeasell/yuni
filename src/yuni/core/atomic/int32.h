#ifndef __YUNI_CORE_ATOMIC_INT32_H__
# define __YUNI_CORE_ATOMIC_INT32_H__

# include "../../yuni.h"

# if defined(YUNI_OS_OSX)
#	include <libkern/OSAtomic.h>
# endif
# include "../system/windows.hdr.h"

# if defined(YUNI_OS_WINDOWS)
#	define YUNI_ATOMIC_INT32_TYPE  volatile long
# else
#	define YUNI_ATOMIC_INT32_TYPE  volatile sint32
# endif


namespace Yuni
{
namespace Atomic
{


	class Int32
	{
	public:
		Int32();
		explicit Int32(const int n);
		Int32(const Int32& rhs);

		void add(const int x);
		void sub(const int x);
		void increment();
		void decrement();

		void set(const int x);
		void set(const Int32& rhs);

		sint32 value() const;

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

	private:
		//! The value
		YUNI_ATOMIC_INT32_TYPE pValue;

	}; // class Int32




} // namespace Atomic
} // namespace Yuni

# include "int32.hxx"

#endif // __YUNI_CORE_ATOMIC_INT32_H__
