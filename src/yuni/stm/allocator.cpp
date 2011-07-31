
#include "allocator.h"

namespace Yuni
{
namespace STM
{


	Allocator::Allocator()
	{
		
	}
	

	Allocator::~Allocator()
	{
	}


	Pointer Allocator::allocate(uint64 size)
	{
		return invalid;
	}


	void  Allocator::release(Pointer ptr)
	{
	}


	Transaction::Handle   Allocator::begin()
	{
		return invalid;
	}


	bool Allocator::commit(Transaction::Handle handle)
	{
		return false;
	}


	void Allocator::rollback(Transaction::Handle handle)
	{
	}




} // namespace STM
} // namespace Yuni
