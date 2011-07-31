#ifndef __YUNI_STM_FWD_H__
# define __YUNI_STM_FWD_H__

# include "../yuni.h"


namespace Yuni
{
namespace STM
{

	//! Pointer
	typedef uint64  Pointer;

	enum
	{
		//! Invalid pointer
		invalid = (Pointer) -1,
	};


} // namespace STM
} // namespace Yuni



namespace Yuni
{
namespace STM
{
namespace Transaction
{

	//! Transaction Handle
	typedef unsigned int  Handle;


	/*!
	** \brief Transaction (abtract)
	*/
	template<class ReadOnlyT = true> class ITransaction;


	//! Read-Only transaction
	typedef  ITransaction</*readonly =*/ true>   RO;

	//! Read / Write transaction
	typedef  ITransaction</*readonly =*/ false>  RW;



} // namespace Transaction
} // namespace STM
} // namespace Yuni

#endif // __YUNI_STM_FWD_H__
