#ifndef __YUNI_CORE_ALLOCATOR_SMALLOBJECT_H__
# define __YUNI_CORE_ALLOCATOR_SMALLOBJECT_H__

# include "../../threads/policy.h"
# include "smallobjallocator.h"

namespace Yuni
{

	/*!
	** \brief A small object can be allocated and deallocated more efficiently.
	**
	** To mark a class as small, simply have it inherit SmallObject following
	** a CRTP, e.g.:
	**
	** struct MySmallObject: public SmallObject<MySmallObject>
	** {
	**     int a;
	** };
	**
	** \ingroup Alloc
	*/
	template<typename T, template <class> class TP = Policy::ClassLevelLockable>
	class SmallObject : public TP<T>
	{
	public:
		//! The Threading Policy
		typedef TP<T> ThreadingPolicy;

	public:
		// Virtual destructor is essential for delete to perform on the correct type
		virtual ~SmallObject() {}

		/*!
		** \brief Override operator new
		*/
		static void* operator new (std::size_t size);

		/*!
		** \brief Override operator delete
		*/
		static void operator delete (void* ptr, std::size_t size);

		/*!
		** \brief Override operator new for arrays
		*/
		static void* operator new[] (std::size_t size);

		/*!
		** \brief Override operator delete for arrays
		*/
		static void operator delete[] (void* ptr, std::size_t size);

	protected:
		// Disallow small object creation
		inline SmallObject() {}

	}; // class SmallObject





} // namespace Yuni

# include "smallobject.hxx"

#endif // __YUNI_CORE_ALLOCATOR_SMALLOBJECT_H__
