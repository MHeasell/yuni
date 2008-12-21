#ifndef __YUNI_SYSTEM_OS_DETECTION_H__
# define __YUNI_SYSTEM_OS_DETECTION_H__

/*!
** \brief Operating System / Architecture Detection
*/



/*
** Usefull defines
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
** - Gcc/G++ : YUNI_OS_GCC, YUNI_OS_GCC_VERSION : #if YUNI_OS_GCC_VERSION > 30200  (> 3.2.0)
** - Intel Compiler: YUNI_OS_INTELCOMPILER
** - Sun Studio: YUNI_OS_SUNSTUDIO
**
** 32/64 Bits
** YUNI_OS_32 or YUNI_OS_64
**
** All those informations can be found at http://predef.sourceforge.net/
*/


# if defined(__TOS_WIN__) || defined(__WIN32__) || defined(_WIN64) || defined(_WIN32)
// Windows
#	define YUNI_OS_WINDOWS
#	ifdef _WIN64
#	   define YUNI_OS_WIN64
#	   define YUNI_OS_64
#	else
#	   define YUNI_OS_WIN32
#	endif
#	ifdef _WIN32_WCE
#	   define YUNI_OS_WINCE
#	endif
#	ifdef _MSC_VER // Visual Studio
#	   define YUNI_OS_MSVC
#	endif
#	ifdef __BORLANDC__
#	   define YUNI_OS_BORLAND
#	endif
#	ifdef __CYGWIN__
#	   define YUNI_OS_CYGWIN
#	endif
#	ifdef __MINGW32__
#	   define YUNI_OS_MINGW
#	endif
# else
// Unixes
# ifdef __BEOS__
#	define YUNI_OS_BEOS
# else
#	define YUNI_OS_UNIX
#	ifdef _AIX
#		define YUNI_OS_AIX
#	endif
#	ifdef __DragonFly__
#		define YUNI_OS_DRAGONFLY
#	endif
#	if defined(__linux) || defined(linux)
#		define YUNI_OS_LINUX
#	else
#		ifdef __FreeBSD__
#			define YUNI_OS_FREEBSD __FreeBSD__
#		endif
#		ifdef _hpux
#			define YUNI_OS_HPUX
#		endif
#		if defined(__APPLE__) || defined(__MACH__)
#			define YUNI_OS_MAC
#			define YUNI_OS_DARWIN
#		endif
#		ifdef __NetBSD__
#			define YUNI_OS_NETBSD
#		endif
#		ifdef __OpenBSD__
#			define YUNI_OS_OPENBSD
#		endif
#		if defined(sun) || defined(__sun)
#			if defined(__SVR4) || defined(__svr4__)
#				 define YUNI_OS_SOLARIS
#			else
#				 define YUNI_OS_SUNOS
#			endif
#			if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#				 define YUNI_OS_SUNSTUDIO
#			endif
#		endif // Sun/Solaris
#	endif // Linux
#	ifdef __Lynx__
#		define YUNI_OS_LYNX
#	endif
# endif // BEOS
# endif // Microsoft Windows
 
# ifdef __GNUC__
#	define YUNI_OS_GCC
#	define YUNI_OS_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
# else
#	define YUNI_OS_GCC_VERSION 0 
# endif

# ifdef __INTEL_COMPILER
#	define YUNI_OS_INTELCOMPILER
# endif

# if !defined(YUNI_OS_32) && !defined(YUNI_OS_64)
#	if defined(__IA64__) || defined(_IA64) || defined(__amd64__) || defined(__x86_64__)
#		 define YUNI_OS_64
#	else
#		 define YUNI_OS_32
#	endif
# endif



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


#endif // __YUNI_SYSTEM_OS_DETECTION_H__
