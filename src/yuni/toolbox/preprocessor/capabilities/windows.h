#ifndef __YUNI_TOOLBOX_PREPROCESSOR_CAPABILITIES_WINDOWS_H__
# define __YUNI_TOOLBOX_PREPROCESSOR_CAPABILITIES_WINDOWS_H__


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


#endif // __YUNI_TOOLBOX_PREPROCESSOR_CAPABILITIES_WINDOWS_H__
