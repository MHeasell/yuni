#ifndef __YUNI_MISC_SHARED_POINTER_H__
# define __YUNI_MISC_SHARED_POINTER_H__

# include "../yuni.h"


namespace Yuni
{

	/*!
	** \brief Shared Pointer
	**
	** Shared pointers are objects which store pointers to dynamically allocated (heap) object
	** They behave much like built-in C++ pointers except that they automatically delete the
	** object pointed to at the appropriate time.
	*/
	template <class T>
	class SharedPtr
	{
	public:
		typedef T element_type;
		typedef unsigned int ReferenceSize;

	public:
		//! \name Constructors & Destructor
		//@{
		//! Constructor with an optional value
		SharedPtr(T* p = 0) :counter(0) {if (p) counter = new Counter(p);}
		//! Copy constructor
		SharedPtr(const SharedPtr& c) throw() {acquire(c.counter);}
		//! Destructor
		~SharedPtr() {release();}
		//@}

		//! \name Operators
		//@{
		//! The operator =
		SharedPtr<T>& operator = (const SharedPtr<T>& rhs);
		SharedPtr<T>& operator = (T* rhs) { *this = SharedPtr<T>(rhs); return *this;}
		//! The operator *
		T& operator * () const throw() {return *counter->ptr;}
		//! The operator ->
		T* operator-> () const throw() {return counter->ptr;}

		//! Equality operators
		bool operator == (const T* rhs) const { return get() == rhs; }
		bool operator == (const SharedPtr<T>& rhs) const { return get() == rhs.get(); }
		bool operator != (const T* rhs) const { return get() != rhs; }
		bool operator != (const SharedPtr<T>& rhs) const { return get() != rhs.get(); }

		//! Inequality operators
		int operator < (const SharedPtr<T>& rhs) const { return get() < rhs.get(); }
		int operator <= (const SharedPtr<T>& rhs) const { return get() <= rhs.get(); }
		int operator > (const SharedPtr<T>& rhs) const { return get() > rhs.get(); }
		int operator >= (const SharedPtr<T>& rhs) const { return get() >= rhs.get(); }

		//@}

		/*!
		** \brief Get the real pointer
		*/
		T* get() const throw()  {return counter ? counter->ptr : 0;}

		/*!
		** \brief Get if the pointer is null
		*/
		bool null() const {return !counter || !counter->ptr;}

		/*!
		** \brief Get if the pointer is valid
		*/
		bool valid() const {return counter && counter->ptr;}

		/*!
		** \brief Get if this reference is an unique reference
		*/
		bool unique()  const throw() {return (counter ? counter->count == 1 : true);}

		/*!
		** \brief Get how many references are linked to our pointer
		*/
		ReferenceSize refsCount() const {return (counter ? counter->count : 0);}

	private:
		struct Counter
		{
			Counter(T* p = 0, ReferenceSize c = 1) :ptr(p), count(c) {}
			T* ptr;
			ReferenceSize count;
		}* counter;

		void acquire(Counter* c) throw()
		{
			// increment the count
			counter = c;
			if (c)
				++c->count;
		}

		/*!
		** \brief Release this reference
		*/
		void release();

	}; // class SharedPtr



} // namespace Yuni


# include "sharedptr.hxx"

#endif // __YUNI_MISC_SHARED_POINTER_H__
