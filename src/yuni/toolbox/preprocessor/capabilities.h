#ifndef __YUNI_PREPROCESSOR_OS_DETECTION_H__
# define __YUNI_PREPROCESSOR_OS_DETECTION_H__

/* !!! "C compatibility" header !!! */


/*!
** \brief Operating System / Capabilities Auto-Detection
**
**
** Usefull defines :
**
** - Microsoft Windows
** YUNI_OS_WINDOWS: The Microsoft Windows Operating system (32/64Bits)
** YUNI_OS_WIN32: Microsoft Windows 32Bits
** YUNI_OS_WIN64: Microsoft Windows 64Bits
** YUNI_OS_WINCE: Microsoft Windows CE
** YUNI_OS_MSVC: The compiler is Microsoft Visual Studio
**
** - Unixes
** YUNI_OS_UNIX
**
** - GNU/Linux
** YUNI_IS_LINUX
**
** - MacOS
** YUNI_OS_MAC or YUNI_OS_DARWIN
**
** - FreeBSD
** YUNI_OS_FREEBSD (The value is the version)
**
** - AIX
** YUNI_OS_AIX
**
** - HPUX
** YUNI_OS_HPUX
**
** - BEOS
** YUNI_OS_BEOS
**
** - DragonFLY
** YUNI_OS_DRAGONFLY
**
** - LynxOS
** YUNI_OS_LYNX
**
** - NetBSD
** YUNI_OS_NETBSD
**
** - OpenBSD
** YUNI_OS_OPENBSD
**
** - Solaris/SunOS
** YUNI_OS_SOLARIS
** YUNI_OS_SUNOS
**
**
**
** Misc:
**
** - Borland C++ : YUNI_OS_BORLAND
** - MinGW: YUNI_OS_MINGW
** - Cygwin : YUNI_OS_CYGWIN
** - Gcc/G++ : YUNI_OS_GCC, YUNI_OS_GCC_VERSION : if YUNI_OS_GCC_VERSION > 30200  (> 3.2.0)
** - Intel Compiler: YUNI_OS_INTELCOMPILER
** - Sun Studio: YUNI_OS_SUNSTUDIO
**
** 32/64 Bits
** YUNI_OS_32 or YUNI_OS_64
**
** All those informations can be found at http://predef.sourceforge.net/
*/


# if defined(__TOS_WIN__) || defined(__WIN32__) || defined(_WIN64) || defined(_WIN32)
#	include "capabilities/windows.h"
# else
#	include "capabilities/unixes.h"
# endif




/* GNU project C and C++ compiler */
# ifdef __GNUC__
#	define YUNI_OS_GCC
#	define YUNI_OS_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
# else
#	define YUNI_OS_GCC_VERSION 0
# endif

/* Intel Compiler */
# ifdef __INTEL_COMPILER
#	define YUNI_OS_INTELCOMPILER
# endif



/* 32/64 Bits modes */
# if !defined(YUNI_OS_32) && !defined(YUNI_OS_64)
#	if defined(__IA64__) || defined(_IA64) || defined(__amd64__) || defined(__x86_64__)
#		 define YUNI_OS_64
#	else
#		 define YUNI_OS_32
#	endif
# endif



/* export */
# if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BCPLUSPLUS__)  || defined(__MWERKS__)
#	if defined(YUNI_LIBRARY_STATIC)
#		define YUNI_EXPORT
#	elif defined(YUNI_LIBRARY)
#		define YUNI_EXPORT   __declspec(dllexport)
#	else
#		define YUNI_EXPORT   __declspec(dllimport)
#	endif
# else
#	define YUNI_EXPORT
# endif




/* inline */
# ifdef YUNI_OS_GCC
#	define ALWAYS_INLINE  __attribute__((always_inline))
# else
#	ifdef YUNI_OS_MSVC
#		define ALWAYS_INLINE  __forceinline
#	else
#		define ALWAYS_INLINE
# 	endif
# endif


/* Deprecated */
# if (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#	define YUNI_DEPRECATED  __attribute__((__deprecated__))
# else
#	define YUNI_DEPRECATED
# endif /* __GNUC__ */




#endif /* __YUNI_PREPROCESSOR_OS_DETECTION_H__ */
