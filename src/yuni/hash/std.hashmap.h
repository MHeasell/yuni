#ifndef __YUNI_HASH_STD_HASH_MAP_H__
#define __YUNI_HASH_STD_HASH_MAP_H__



# if defined(YUNI_OS_WINDOWS) && defined(YUNI_OS_MSVC)

// Microsoft Visual Studio Implementation
//

#	ifdef _DEFINE_DEPRECATED_HASH_CLASSES
#		undef _DEFINE_DEPRECATED_HASH_CLASSES
#	endif
#   define _DEFINE_DEPRECATED_HASH_CLASSES 0
#   include <hash_map>
#	include <functional>
namespace YuniSTLExt = ::stdext;

# else // !YUNI_OS_WINDOWS || !YUNI_OS_MSVC

// Gnu implementation

#   include <ext/hash_fun.h>
#   include <ext/hash_map>
namespace YuniSTLExt = ::__gnu_cxx;

#   define YUNI_OS_GNU_HASH_MAP

# endif // YUNI_OS_WINDOWS && YUNI_OS_MSVC



#endif // __YUNI_HASH_STD_HASH_MAP_H__
