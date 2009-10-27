#ifndef __YUNI_CORE_FWD_H__
# define __YUNI_CORE_FWD_H__

# include <iosfwd> // STL
# include <bits/stringfwd.h>


namespace Yuni
{


	/*! Type for a default behavior / policy */
	struct Default {};

	/*! Absence Option */
	struct None {};


	template<class C = char, int ChunkSizeT = 80> class StringBase;


namespace Core
{

	// Forward declaration for MemoryBuffer
	template<class C, unsigned int ChunkSizeT = 80, bool ZeroTerminatedT = false, bool ExpandableT = true>
	class MemoryBuffer;

} // namespace Core

} // namespace Yuni


#endif // __YUNI_CORE_FWD_H__
