#ifndef __YUNI_SYSTEM_STANDARD_INTERFACE_INT_DATA_H__
# define __YUNI_SYSTEM_STANDARD_INTERFACE_INT_DATA_H__

/*!
** \file stdint.h
** \brief Standard types used by the Yuni Library
*/


# ifndef YUNI_OS_MSVC
#	include <stdint.h>
# endif

# ifdef YUNI_OS_MSVC
#	define YUNI_MSVC_SECURE_VSPRINTF
# endif



namespace Yuni
{

# if defined(YUNI_OS_WINDOWS) && defined(YUNI_OS_MSVC)
	typedef int ssize_t;
# endif

# if defined(YUNI_OS_WINDOWS) && defined(YUNI_OS_MSVC)
#	define YUNI_TYPES_INT8_CHAR_ARE_IDENTICAL
#   if defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 64 // For Visual 6.x and later
	// 64-bit ints, guaranteed to be 8 bytes in size
	typedef unsigned __int64  uint64;
	typedef signed __int64    sint64;
#   else
#	   error __int64 type not supported
#   endif
	// 32-bit ints, guaranteed to be 4 bytes in size
	typedef unsigned __int32  uint32;
	typedef signed __int32	  sint32;
	// 16-bit ints, guaranteed to be 2 bytes in size
	typedef unsigned __int16  uint16;
	typedef signed __int16	  sint16;
	// 8-bit ints, guaranteed to be 1 byte in size
	typedef unsigned __int8   uint8;
	typedef signed __int8	  sint8;
# else
	// 64-bit ints, guaranteed to be 8 bytes in size
	typedef uint64_t  uint64;
	typedef int64_t   sint64;
	// 32-bit ints, guaranteed to be 4 bytes in size
	typedef uint32_t  uint32;
	typedef int32_t   sint32;
	// 16-bit ints, guaranteed to be 2 bytes in size
	typedef uint16_t  uint16;
	typedef int16_t   sint16;
	// 8-bit ints, guaranteed to be 1 byte in size
	typedef unsigned char  uint8;
	typedef char           sint8;
# endif




	/*!
	** \brief Constant int64 value to indicate that the size must be autodetected by the location
	** of the terminating null character
	*/
	static const uint64 AutoDetectNullChar = (uint64)(-1);


	//! A null class
	class NullPtr;



} // namespace Yuni



# ifndef YUNI_CPP_0X
//! nullptr
#	define nullptr  ((const Yuni::NullPtr*)0)
# endif


#endif // __YUNI_SYSTEM_STANDARD_INTERFACE_INT_DATA_H__
