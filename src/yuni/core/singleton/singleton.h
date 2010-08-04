#ifndef __YUNI_CORE_SINGLETON_SINGLETON_H__
# define __YUNI_CORE_SINGLETON_SINGLETON_H__

# include "../../yuni.h"
# include "../../thread/policy.h"
# include "policies/creation.h"
# include "policies/lifetime.h"


namespace Yuni
{


	/*!
	** \brief Holder for a singleton class
	**
	** Manages creation, deletion and access in a MT environment
	*/
	template <class T,
		template <class> class CreationT = Policy::Creation::EmptyConstructor,
		template <class> class LifetimeT = Policy::Lifetime::Normal,
		template <class> class ThreadingT = Policy::SingleThreaded>
	class Singleton : public ThreadingT<Singleton<T, CreationT, LifetimeT, ThreadingT> >
	{
	public:
		//! Stored singleton type
		typedef T StoredType;
		//! Creation policy
		typedef CreationT<T> CreationPolicy;
		//! Lifetime policy
		typedef LifetimeT<T> LifetimePolicy;
		//! Threading policy
		typedef ThreadingT<Singleton<T, CreationT, LifetimeT, ThreadingT> > ThreadingPolicy;
		//! Type as stored in the singleton (volatile if necessary)
		typedef typename ThreadingPolicy::template Volatile<T>::Type InstanceType;

	public:
		/*!
		** \brief Get the instance of this singleton
		*/
		static InstanceType& Instance();

	protected:
		/*!
		** \brief Private constructor !
		*/
		Singleton();

		/*!
		** \brief Private copy constructor !
		*/
		Singleton(const Singleton&);

		/*!
		** \brief Private assignment operator !
		*/
		Singleton operator = (const Singleton&);

		/*!
		** Destroy the stored instance
		*/
		static void DestroyInstance();

	private:
		/*!
		** \brief Unique instance of the class
		*/
		static InstanceType* pInstance;

		/*!
		** \brief Has the instance already been destroyed once ?
		*/
		static bool pDestroyed;

		template<class U> friend class CreationT;

	}; // class Singleton






} // namespace Yuni

# include "singleton.hxx"

#endif // __YUNI_CORE_SINGLETON_SINGLETON_H__
