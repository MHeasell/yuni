#ifndef __YUNI_CORE_FWD_H__
# define __YUNI_CORE_FWD_H__

# include <iosfwd> // STL
# include <bits/stringfwd.h>


namespace Yuni
{


	//! Type for a default behavior / policy
	struct Default {};

	//! Absence Option
	struct None {};


	template<class C = char, int ChunkSizeT = 128> class StringBase;



namespace Core
{

	// Forward declaration for the base class IString<>
	template<unsigned int ChunkSizeT = 128, bool ExpandableT = true, bool ZeroTerminatedT = true, class C = char>
	class IString;

} // namespace Core
} // namespace Yuni


#endif // __YUNI_CORE_FWD_H__
