#ifndef __YUNI_CORE_PREPROCESSOR_CAPABILITIES_UNIXES_H__
# define __YUNI_CORE_PREPROCESSOR_CAPABILITIES_UNIXES_H__


# if defined(__HAIKU) || defined(__HAIKU__) || defined(_HAIKU)
/* Haiku */
#	define YUNI_OS_HAIKU
# else
/* BeOS */
#	if defined(__BeOS) || defined(__BEOS__) || defined(_BEOS)
#		define YUNI_OS_BEOS
#	endif
# endif


/* Unix compliant */
# define YUNI_OS_UNIX



/* Linux */
# if defined(__linux) || defined(linux) || defined(__linux__)
#	define YUNI_OS_LINUX
# else

/* AIX */
# 	if defined(_AIX)
#		define YUNI_OS_AIX
# 	endif

/* DragonFly */
# 	if defined(__DragonFly__)
# 		define YUNI_OS_DRAGONFLY
# 	endif

/* FreeBSD */
#	if defined(__FreeBSD__)
#		define YUNI_OS_FREEBSD __FreeBSD__
#	endif

/* HP-UX */
#	if defined(_hpux) || defined(__hpux) || defined(__hpux__)
#		define YUNI_OS_HPUX
#	endif

/* Mac OS */
#	if defined(__APPLE__) || defined(__MACH__)
#		define YUNI_OS_MAC
#		define YUNI_OS_DARWIN
#	endif

/* NetBSD */
#	if defined(__NetBSD__)
#		define YUNI_OS_NETBSD
#	endif

/* OpenBSD */
#	if defined(__OpenBSD__)
#		define YUNI_OS_OPENBSD
#	endif
#	if defined(sun) || defined(__sun)

/* Solaris */
#		if defined(__SVR4) || defined(__svr4__)
#			 define YUNI_OS_SOLARIS
#		else
/* SunOS */
#			 define YUNI_OS_SUNOS
#		endif
#		if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#			 define YUNI_OS_SUNSTUDIO
#		endif
#	endif /* Sun */
/* Lynx */
# 	ifdef __Lynx__
#		define YUNI_OS_LYNX
# 	endif

# endif /* Linux */



#endif // __YUNI_CORE_PREPROCESSOR_CAPABILITIES_UNIXES_H__
