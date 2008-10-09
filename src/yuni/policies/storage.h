#ifndef __YUNI_POLICIES_STORAGE_H__
# define __YUNI_POLICIES_STORAGE_H__

# include <functional>


namespace Yuni
{
namespace Policy
{
namespace Storage
{
	

	/*!
	** \brief Implementation of the default storage policy
	**
	** \tparam T The data type
	*/
	template<class T>
	class Pointer
	{
	public:
		//! The type stored
		typedef T* StoredType;
		//! The type used by the operator ->
		typedef T* PointerType;
		//! The type used by the operator *
		typedef T& ReferenceType;

		//! The default value for this type
		static StoredType DefaultValue() {return NULL;}

	public:
		//! \name Constructors
		//@{
		Pointer() :pData(DefaultValue()) {}
		template<class U> Pointer(const Default<U>&) :pData(DefaultValue()) {}
		template<class U> Pointer(const StoredType& p) :pData(p) {}
		//@}

		//! Swap the data
		void swap(Pointer& rhs) {std::swap(pData, rhs.pData);}

		//! \name Get the data
		//@{
		friend PointerType get(const Pointer& rhs) {return rhs.pData;}
		friend const StoredType& reference(const Pointer& rhs) const {return rhs.pData;}
		friend StoredType& reference(Pointer& rhs) {return rhs.pData;}
		//@}

		//! \name Operators
		//@{
		//! The operator ->
		PointerType   operator -> () const {return pData;}
		//! The operator *
		ReferenceType operator * () const {return *pData;}
		//@}

	protected:
		//! Destroy the inner data
		void destroy() { delete pData; }

	private:
		//! The data
		StoredType pData;

	}; // class Pointer





	/*!
	** \brief Implementation of the Array storage policy
	**
	** \tparam T The data type
	*/
	template<class T>
	class Array
	{
	public:
		//! The type stored
		typedef T* StoredType;
		//! The type used by the operator ->
		typedef T* PointerType;
		//! The type used by the operator *
		typedef T& ReferenceType;

		//! The default value for this type
		static StoredType DefaultValue() {return NULL;}

	public:
		//! \name Constructors
		//@{
		Default() :pData(DefaultValue()) {}
		template<class U> Default(const Default<U>&) :pData(DefaultValue()) {}
		template<class U> Default(const StoredType& p) :pData(p) {}
		//@}

		//! Swap the data
		void swap(Pointer& rhs) {std::swap(pData, rhs.pData);}

		//! \name Get the data
		//@{
		friend PointerType get(const Array& rhs) {return rhs.pData;}
		friend const StoredType& reference(const Array& rhs) const {return rhs.pData;}
		friend StoredType& reference(Array& rhs) {return rhs.pData;}
		//@}

		//! \name Operators
		//@{
		//! The operator ->
		PointerType   operator -> () const {return pData;}
		//! The operator *
		ReferenceType operator * () const {return *pData;}
		//@}

	protected:
		//! Destroy the inner data
		void destroy() { delete[] pData; }

	private:
		//! The data
		StoredType pData;

	}; // class Array




} // namespace Storage
} // namespace Policy
} // namespace Yuni

#endif // __YUNI_POLICIES_STORAGE_H__
