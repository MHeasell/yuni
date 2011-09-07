#ifndef __YUNI_CORE_FWD_H__
# define __YUNI_CORE_FWD_H__

# include <iosfwd> // STL
# ifndef YUNI_OS_MSVC
#	include <bits/stringfwd.h>
# endif


namespace Yuni
{


	//! Type for a default behavior / policy
	struct Default {};

	//! Absence Option
	struct None {};


	// Forward declaration for the base class String
	template<unsigned int ChunkSizeT = 128, bool ExpandableT = true, bool ZeroTerminatedT = true>
	class CString;


} // namespace Yuni


#endif // __YUNI_CORE_FWD_H__
