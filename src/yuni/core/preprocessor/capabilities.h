#ifndef __YUNI_PREPROCESSOR_OS_DETECTION_H__
# define __YUNI_PREPROCESSOR_OS_DETECTION_H__

/* !!! "C compatibility" header !!! */


/*!
** \brief Operating System / Capabilities Auto-Detection
**
** General defines :
** YUNI_OS_NAME: Name of the operating system (without its version which can only be
**   determined at runtime)
** YUNI_COMPILER_NAME: Name of the compiler currently used
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
** - Unknown
** YUNI_OS_UNKNOWN
** YUNI_OS_COMPILER
**
** Window systems
** - X Window System
** YUNI_WINDOWSYSTEM_X11
** - MFC (Microsoft Foundation Class) or any Microsoft Windows Window System
** YUNI_WINDOWSYSTEM_MSW
** - Mac OS X Cocoa
** YUNI_WINDOWSYSTEM_COCOA
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
** C++0X
** YUNI_CPP_0X
**
** All those informations can be found at http://predef.sourceforge.net/
*/


# if defined(__TOS_WIN__) || defined(__WIN32__) || defined(_WIN64) || defined(_WIN32)
#	include "capabilities/windows.h"
# else
#	include "capabilities/unixes.h"
# endif



/* Window System */
# ifdef YUNI_OS_WINDOWS
#	define YUNI_WINDOWSYSTEM_MSW
# else
#	ifdef YUNI_OS_MAC
#		define YUNI_WINDOWSYSTEM_COCOA
#	else
#		define YUNI_WINDOWSYSTEM_X11
#	endif
# endif


/* GNU C and C++ compiler */
# ifdef __GNUC__
#	define YUNI_OS_GCC
#	define YUNI_OS_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#	ifndef YUNI_COMPILER_NAME
#		define YUNI_COMPILER_NAME "GCC (the GNU Compiler Collection)"
#	endif
# else
#	define YUNI_OS_GCC_VERSION 0
# endif


/* Intel Compiler */
# ifdef __INTEL_COMPILER
#	define YUNI_OS_INTELCOMPILER
#	define YUNI_COMPILER_NAME "ICC (Intel C++ Compiler)"
# endif



/* 32/64 Bits modes */
# if !defined(YUNI_OS_32) && !defined(YUNI_OS_64)
#	if defined(__IA64__) || defined(_IA64) || defined(__amd64__) || defined(__x86_64__) || defined(_M_IA64) || defined(_WIN64)
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
# endif
# ifndef YUNI_EXPORT
#	define YUNI_EXPORT
# endif




/* inline */
# ifdef YUNI_OS_GCC
#	define YUNI_ALWAYS_INLINE  __attribute__((always_inline))
# else
#	ifdef YUNI_OS_MSVC
#		define YUNI_ALWAYS_INLINE  __forceinline
# 	endif
# endif
# ifndef YUNI_ALWAYS_INLINE
#	define YUNI_ALWAYS_INLINE
# endif


/* Deprecated */
# if defined(YUNI_OS_GCC)
#	if (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#		define YUNI_DEPRECATED  __attribute__((__deprecated__))
#	endif
# endif
# ifndef YUNI_DEPRECATED
#	define YUNI_DEPRECATED
# endif

/* Noreturn */
# if defined(YUNI_OS_GCC)
#	if (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#		define YUNI_NORETURN  __attribute__((noreturn))
#	endif
# endif
# ifndef YUNI_NORETURN
#	define YUNI_NORETURN
# endif




/* C++0x */
# if defined(__GXX_EXPERIMENTAL_CPP0X__) || defined(_RWSTD_EXT_CXX_0X)
#	define YUNI_CPP_0X
# endif



/* OS Detection */
# ifndef YUNI_OS_NAME
#	define YUNI_OS_NAME "Unknown"
#	define YUNI_OS_UNKNOWN
#	warning "OS Detection: Unable to guess the operating system"
# endif

/* Compiler Detection */
# ifndef YUNI_OS_NAME
#	define YUNI_COMPILER_NAME "Unknown"
#	define YUNI_COMPILER_UNKNOWN
#	warning "Compiler Detection: Unable to guess the compiler"
# endif



/*!
** \brief Thread-local variable
*/
/* Usage Example :
** \code
** YUNI_THREAD_LOCAL int myThreadLocalVariable = 0;
** \endcode
**
** \see Rules and Limitations for TLS on Windows http://msdn.microsoft.com/en-us/library/2s9wt68x.aspx
*/
# if defined(YUNI_OS_MSVC) || defined(__INTEL_COMPILER)
#	define YUNI_THREAD_LOCAL __declspec(thread)
#	define YUNI_HAS_THREAD_LOCAL_STORAGE 1
# else
#	define YUNI_THREAD_LOCAL __thread
#	define YUNI_HAS_THREAD_LOCAL_STORAGE 1
# endif


#endif /* __YUNI_PREPROCESSOR_OS_DETECTION_H__ */
