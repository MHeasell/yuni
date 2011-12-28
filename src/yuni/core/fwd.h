#ifndef __YUNI_CORE_FWD_H__
# define __YUNI_CORE_FWD_H__

# include <iosfwd> // STL
# ifndef YUNI_OS_MSVC
#	include <bits/stringfwd.h>
# endif


namespace Yuni
{


	//! Type for a default behavior / policy
	struct YUNI_DECL Default {};

	//! Absence Option
	struct YUNI_DECL None {};


	// Forward declaration for the base class String
	template<unsigned int ChunkSizeT = 128, bool ExpandableT = true, bool ZeroTerminatedT = true>
	class YUNI_DECL CString;


} // namespace Yuni


#endif // __YUNI_CORE_FWD_H__
