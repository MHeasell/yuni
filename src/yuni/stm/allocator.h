#ifndef __YUNI_STM_ALLOCATOR_H__
# define __YUNI_STM_ALLOCATOR_H__


namespace Yuni
{
namespace STM
{


	class Allocator
	{
	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		Allocator();
		//! Destructor
		~Allocator();
		//@}

		Pointer allocate(uint64 size);

		void release(Pointer ptr);


		Transaction::Handle  begin();

		bool commit(Transaction::Handle handle);

		void rollback(Transaction::Handle handle);

	private:
		void releaseNotNull(Pointer ptr);

	}; // class Allocator





} // namespace STM
} // namespace Yuni

#endif // __YUNI_STM_ALLOCATOR_H__
