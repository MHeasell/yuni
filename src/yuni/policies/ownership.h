#ifndef __YUNI_POLICIES_OWNERSHIP_H__
# define __YUNI_POLICIES_OWNERSHIP_H__
/*!
** \file
** \brief Ownership policies
**
** All available ownership policies :
**
** Policy::Ownership::ReferenceCounted<T>
** Policy::Ownership::ReferenceCountedMT<T>
** Policy::Ownership::COMReferenceCounted<T>
** Policy::Ownership::DestructiveCopy<T>
** Policy::Ownership::NoCopy<T>
*/


# include "policies.h"
# include "../policies/threads.h"
# include "../misc/static.h"


namespace Yuni
{
namespace Policy
{
namespace Ownership
{
	
	/*!
	** \defgroup OwnershipPolicies Ownership policies
	** \ingroup Policies
	*/

	/*!
	** \brief Implementation of the reference counting ownership policy
	** \ingroup OwnershipPolicies
	*/
	template<class T>
	class ReferenceCounted
	{
	public:
		//! \name Constructors
		//@{
		//! Default constructor
		ReferenceCounted()
			:pCount(new unsigned int(1))
		{}
		//! Copy constructor
		ReferenceCounted(const ReferenceCounted& c)
			:pCount(c.pCount)
		{}
		//! Copy constructor for any king of template parameter
		template<typename U> ReferenceCounted(const ReferenceCounted<U>& c)
			:pCount(reinterpret_cast<const ReferenceCounted&>(c).pCount)
		{}
		//@}

		/*!
		** \brief Clone this object
		** \param rhs The original object
		*/
		T clone(const T& rhs)
		{
			++(*pCount);
			return rhs;
		}

		/*!
		** \brief Release the reference
		*/
		bool release(const T& rhs)
		{
			if (!(--(*pCount)))
			{
				delete pCount;
				pCount = NULL;
				return true;
			}
			return false;
		}

	private:
		//! The reference count
		unsigned int* pCount;

	}; // class ReferenceCounted





	/*!
	** \brief Implementation of the COM intrusive reference counting ownership policy
	** \ingroup OwnershipPolicies
	*/
	template<class T>
	class COMReferenceCounted
	{
	public:
		//! \name Constructors
		//@{
		//! Default constructor
		COMReferenceCounted()
		{}
		//! Copy constructor for any king of template parameter
		template<typename U> COMReferenceCounted(const COMReferenceCounted<U>&)
		{}
		//@}

		/*!
		** \brief Clone this object
		** \param rhs The original object
		*/
		static T clone(const T& rhs)
		{
			if (0 != rhs)
				rhs->AddRef();
			return rhs;
		}

		/*!
		** \brief Release the reference
		*/
		static bool release(const T& rhs)
		{
			if (0 != rhs)
				rhs->Release();
			return false;
		}

	}; // class COMReferenceCounted




	/*!
	** \brief Implementation of the thread-safe reference counting ownership policy
	** \ingroup OwnershipPolicies
	*/
	template<class T>
	class ReferenceCountedMT
	{
	public:
		typedef Policy::ClassLevelLockable< ReferenceCountedMT<T> >::MutexLocker  MutexLocker; 
	public:
		//! \name Constructors
		//@{
		//! Default constructor
		ReferenceCountedMT()
			:pCount(new unsigned int(1))
		{}
		//! Copy constructor
		ReferenceCountedMT(const ReferenceCountedMT& c)
		{
			MutexLocker locker(*this);
			pCount = c.pCount;
		}
		//! Copy constructor for any king of template parameter
		template<typename U> ReferenceCountedMT(const ReferenceCountedMT<U>& c)
		{
			MutexLocker locker1(*this);
			Policy::ClassLevelLockable< ReferenceCountedMT<U> >::MutexLocker locker2(*this);
			pCount = reinterpret_cast<const ReferenceCounted&>(c).pCount;
		}
		//@}

		/*!
		** \brief Clone this object
		** \param rhs The original object
		*/
		T clone(const T& rhs)
		{
			MutexLocker locker(*this);
			++(*pCount);
			return rhs;
		}

		/*!
		** \brief Release the reference
		*/
		bool release(const T& rhs)
		{
			MutexLocker locker(*this);
			if (!(--(*pCount)))
			{
				delete pCount;
				pCount = NULL;
				return true;
			}
			return false;
		}

	private:
		//! The reference count
		unsigned int* pCount;

	}; // class ReferenceCountedMT





	/*!
	** \brief Implementation of the destructive copy ownership policy
	** \ingroup OwnershipPolicies
	*/
	template<class T>
	class DestructiveCopy
	{
	public:
		//! \name Constructors
		//@{
		//! Default constructor
		DestructiveCopy()
		{}
		//! Copy constructor
		template<class U> DestructiveCopy(const DestructiveCopy<U>&)
		{}
		//@}

		/*!
		** \brief Clone this object
		** \param rhs The original object
		*/
		template<class U> static T clone(U& rhs)
		{
			T result(rhs);
			rhs = U();
			return result;
		}

	}; // class DestructiveCopy





	/*!
	** \brief Implementation of the no-copy ownership policy
	** \ingroup OwnershipPolicies
	*/
	template<class T>
	class NoCopy
	{
	public:
		//! \name Constructors
		//@{
		//! Default constructor
		NoCopy() {}
		//! Copy constructor
		template <class U> NoCopy(const NoCopy<U>&) {}
		//@}

		/*!
		** \brief Clone this object
		**
		** This method can not be called at compile time
		*/
		static T clone(const T&)
		{
			YUNI_STATIC_ASSERT(sizeof(T) == 0, OwnershipPolicyNoCopy);
		}

		static bool release(const T&) {return true;}

	}; // class NoCopy




} // namespace Ownership
} // namespace Policy
} // namespace Yuni

#endif // __YUNI_POLICIES_OWNERSHIP_H__
