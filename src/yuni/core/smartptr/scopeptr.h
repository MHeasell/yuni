#ifndef __YUNI_MISC_SCOPE_PTR_H__
# define __YUNI_MISC_SCOPE_PTR_H__

# include "../../yuni.h"



namespace Yuni
{


	/*!
	** \brief Scope Pointer
	**
	** Shared pointers are objects which store pointers to dynamically allocated (heap) object
	** They behave much like built-in C++ pointers except that they automatically delete the
	** object pointed when it goes out of the scope.
	**
	** This class is not copyable
	**
	** \deprecated Use smart pointers instead
	*/
	template<typename T>
	class ScopePtr
	{
	public:
		YUNI_DEPRECATED ScopePtr(T* p = 0) :pPtr(p) {}
		~ScopePtr() { if (pPtr) delete pPtr; }

		ScopePtr& operator = (T* rhs) { if (pPtr) delete pPtr; pPtr = rhs; }

		//! The operator *
		T& operator * () const throw() {return *pPtr;}
		//! The operator ->
		T* operator-> () const throw() {return pPtr;}

		/*!
		** \brief Get the real pointer
		*/
		T* get() const throw()  {return pPtr;}

		/*!
		** \brief Get if the pointer is null
		*/
		bool null() const {return (pPtr == NULL);}

		/*!
		** \brief Get if the pointer is valid
		*/
		bool valid() const {return (pPtr != NULL);}

	private:
		T* pPtr;

	}; // ScopePtr



} // namespace Yuni

#endif // __YUNI_MISC_SCOPE_PTR_H__
