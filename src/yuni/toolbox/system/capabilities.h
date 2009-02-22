#ifndef __YUNI_SYSTEM_OS_DETECTION_H__
# define __YUNI_SYSTEM_OS_DETECTION_H__

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

/* Microsoft Windows */
#	define YUNI_OS_WINDOWS
/* Windows 64 */
#	ifdef _WIN64
#	   define YUNI_OS_WIN64
#	   define YUNI_OS_64
#	else
#	   define YUNI_OS_WIN32
#	endif
/* Windows CE */
#	ifdef _WIN32_WCE
#	   define YUNI_OS_WINCE
#	endif
/* Visual Studio */
#	ifdef _MSC_VER
#	   define YUNI_OS_MSVC
#	endif
/* Borland Compiler */
#	ifdef __BORLANDC__
#	   define YUNI_OS_BORLAND
#	endif
/* Cygwin */
#	ifdef __CYGWIN__
#	   define YUNI_OS_CYGWIN
#	endif
/* MinGW */
#	ifdef __MINGW32__
#	   define YUNI_OS_MINGW
#	endif


# else /* if Windows */

/* BeOS */
# ifdef __BEOS__
#	define YUNI_OS_BEOS
# else
/* Unix compliant */
#	define YUNI_OS_UNIX
/* AIX */
#	ifdef _AIX
#		define YUNI_OS_AIX
#	endif
/* DragonFly */
#	ifdef __DragonFly__
#		define YUNI_OS_DRAGONFLY
#	endif
/* Linux */
#	if defined(__linux) || defined(linux)
#		define YUNI_OS_LINUX
#	else
/* FreeBSD */
#		ifdef __FreeBSD__
#			define YUNI_OS_FREEBSD __FreeBSD__
#		endif
/* HP-UX */
#		ifdef _hpux
#			define YUNI_OS_HPUX
#		endif
/* Mac OS */
#		if defined(__APPLE__) || defined(__MACH__)
#			define YUNI_OS_MAC
#			define YUNI_OS_DARWIN
#		endif
/* NetBSD */
#		ifdef __NetBSD__
#			define YUNI_OS_NETBSD
#		endif
/* OpenBSD */
#		ifdef __OpenBSD__
#			define YUNI_OS_OPENBSD
#		endif
#		if defined(sun) || defined(__sun)
/* Solaris */
#			if defined(__SVR4) || defined(__svr4__)
#				 define YUNI_OS_SOLARIS
#			else
/* SunOS */
#				 define YUNI_OS_SUNOS
#			endif
#			if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#				 define YUNI_OS_SUNSTUDIO
#			endif
#		endif /* Sun/Solaris */
#	endif /* Linux */
/* Lynx */
#	ifdef __Lynx__
#		define YUNI_OS_LYNX
#	endif
# endif /* BEOS */
# endif /* Microsoft Windows */
 



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
#	define ALWAYS_INLINE 
# endif


/* Deprecated */
# if (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#	define YUNI_DEPRECATED  __attribute__((__deprecated__))
# else
#	define YUNI_DEPRECATED
# endif /* __GNUC__ */


#endif /* __YUNI_SYSTEM_OS_DETECTION_H__ */
