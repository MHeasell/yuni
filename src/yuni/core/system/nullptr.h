#ifndef __YUNI_CORE_SYSTEM_NULLPTR_H__
# define __YUNI_CORE_SYSTEM_NULLPTR_H__

# ifdef __cplusplus /* Only with a C++ Compiler */


namespace Yuni
{

	# ifdef YUNI_HAS_NULLPTR

	typedef std::nullptr_t NullPtr;

	# else

	/*!
	** \brief C++ Idioms/nullptr
	**
	** \see proposal (N2431)
	*/
	const class NullPtr
	{
	public:
		/*! Convertible to any type of null non-member */
		template<class T> operator T*() const
		{
			return 0;
		}

		/*!
		** \brief Any type of null member pointer
		**
		** \note In gcc 4.1.1 compiler that does not recognize the comparison of
		** nullptr with point to member function.
		*/
		template<class C, class T> operator T C::*() const
		{
			return 0;
		}

		/*!
		** \brief Equality comparison with any type of pointer
		*/
		template<class T>
		bool operator == (const T* ptr) const
		{
			return !ptr;
		}

		/*!
		** \brief Difference comparison with any type of pointer
		*/
		template<class T>
		bool operator != (const T* ptr) const
		{
			return !(!ptr);
		}

	private:
		void operator&() const;  /* Can't take address of nullptr */

	} nullptr = {};


	# endif // nullptr support



} /* namespace Yuni */

# endif /* C++ Compiler */


#endif /* __YUNI_CORE_SYSTEM_NULLPTR_H__ */
