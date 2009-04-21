#ifndef __YUNI_TOOLBOX_FUNCTION_FUNCTION_HXX__
# define __YUNI_TOOLBOX_FUNCTION_FUNCTION_HXX__


/*!
** \internal This header has been generated
**  Please report any changes to the appropriate script
*/



namespace Yuni
{
namespace Function
{





	/* Implementation class F0 */

	template<typename R>
	inline F0<R>::F0()
		:pPtr(NULL)
	{}

	template<typename R>
	inline F0<R>::F0(const typename F0<R>::Type p)
		:pPtr(p)
	{}

	template<typename R>
	inline F0<R>::F0(const F0<R>& copy)
		:pPtr(copy.pPtr)
	{}

	template<typename R>
	inline F0<R>::F0(const DynamicLibrary::Symbol& symbol)
		:pPtr((Type)(symbol.ptr()))
	{}

	template<typename R>
	inline R
	F0<R>::call() const
	{
		return pPtr ? pPtr() : R();
	}

	template<typename R>
	inline R
	F0<R>::operator () () const
	{
		return pPtr ? pPtr() : R();
	}

	template<typename R>
	inline bool
	F0<R>::null() const
	{
		return NULL == pPtr;
	}

	template<typename R>
	inline bool
	F0<R>::valid() const
	{
		return NULL != pPtr;
	}

	template<typename R>
	inline typename F0<R>::Type
	F0<R>::ptr() const
	{
		return pPtr;
	}

	template<typename R>
	inline F0<R>&
	F0<R>::operator = (const F0<R>& copy)
	{
		pPtr = copy.pPtr;
		return *this;
	}

	template<typename R>
	inline F0<R>&
	F0<R>::operator = (const Type rhs)
	{
		pPtr = rhs;
		return *this;
	}

	template<typename R>
	inline F0<R>&
	F0<R>::operator = (const DynamicLibrary::Symbol& symbol)
	{
		pPtr = (Type)(symbol.ptr());
		return *this;
	}




	/* Implementation class F0 Template specialization */

	template<>
	class F0 <void>
	{
	public:
		//! Prototype of the function
		typedef void (*Type) (void);
		//! Prototype of the function
		typedef void (*value_type) (void);

		enum
		{
			//! Arguments count
			argumentsCount = 0
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 0
		};

	public:
		F0()
			:pPtr(NULL)
		{}

		F0(const F0& copy)
			:pPtr(copy.pPtr)
		{}

		F0(const Type rhs)
			:pPtr(rhs)
		{}

		F0(const DynamicLibrary::Symbol& symbol)
			:pPtr((Type)(symbol.ptr()))
		{}

		void call() const
		{
			if (pPtr)
				pPtr();
		}


		bool null() const {return NULL == pPtr;}

		bool valid() const {return NULL != pPtr;}

		Type ptr() const {return pPtr;}

		F0& operator = (const F0& copy)
		{
			pPtr = copy.pPtr;
			return *this;
		}

		F0& operator = (const Type rhs)
		{
			pPtr = rhs;
			return *this;
		}

		F0& operator = (const DynamicLibrary::Symbol& symbol)
		{
			pPtr = (Type)(symbol.ptr());
			return *this;
		}

		void operator () () const
		{
			if (pPtr)
				pPtr();
		}

	public:
		//! Pointer
		Type pPtr;

	}; // class F0 - Template specialization






	/* Implementation class F1 */

	template<typename R, typename A0>
	inline F1<R, A0>::F1()
		:pPtr(NULL)
	{}

	template<typename R, typename A0>
	inline F1<R, A0>::F1(const typename F1<R, A0>::Type p)
		:pPtr(p)
	{}

	template<typename R, typename A0>
	inline F1<R, A0>::F1(const F1<R, A0>& copy)
		:pPtr(copy.pPtr)
	{}

	template<typename R, typename A0>
	inline F1<R, A0>::F1(const DynamicLibrary::Symbol& symbol)
		:pPtr((Type)(symbol.ptr()))
	{}

	template<typename R, typename A0>
	inline R
	F1<R, A0>::call(A0 a0) const
	{
		return pPtr ? pPtr(a0) : R();
	}

	template<typename R, typename A0>
	inline R
	F1<R, A0>::operator () (A0 a0) const
	{
		return pPtr ? pPtr(a0) : R();
	}

	template<typename R, typename A0>
	inline bool
	F1<R, A0>::null() const
	{
		return NULL == pPtr;
	}

	template<typename R, typename A0>
	inline bool
	F1<R, A0>::valid() const
	{
		return NULL != pPtr;
	}

	template<typename R, typename A0>
	inline typename F1<R, A0>::Type
	F1<R, A0>::ptr() const
	{
		return pPtr;
	}

	template<typename R, typename A0>
	inline F1<R, A0>&
	F1<R, A0>::operator = (const F1<R, A0>& copy)
	{
		pPtr = copy.pPtr;
		return *this;
	}

	template<typename R, typename A0>
	inline F1<R, A0>&
	F1<R, A0>::operator = (const Type rhs)
	{
		pPtr = rhs;
		return *this;
	}

	template<typename R, typename A0>
	inline F1<R, A0>&
	F1<R, A0>::operator = (const DynamicLibrary::Symbol& symbol)
	{
		pPtr = (Type)(symbol.ptr());
		return *this;
	}




	/* Implementation class F1 Template specialization */

	template<typename A0>
	class F1 <void, A0>
	{
	public:
		//! Prototype of the function
		typedef void (*Type) (A0);
		//! Prototype of the function
		typedef void (*value_type) (A0);

		enum
		{
			//! Arguments count
			argumentsCount = 1
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 0
		};

	public:
		F1()
			:pPtr(NULL)
		{}

		F1(const F1& copy)
			:pPtr(copy.pPtr)
		{}

		F1(const Type rhs)
			:pPtr(rhs)
		{}

		F1(const DynamicLibrary::Symbol& symbol)
			:pPtr((Type)(symbol.ptr()))
		{}

		void call(A0 a0) const
		{
			if (pPtr)
				pPtr(a0);
		}


		bool null() const {return NULL == pPtr;}

		bool valid() const {return NULL != pPtr;}

		Type ptr() const {return pPtr;}

		F1& operator = (const F1& copy)
		{
			pPtr = copy.pPtr;
			return *this;
		}

		F1& operator = (const Type rhs)
		{
			pPtr = rhs;
			return *this;
		}

		F1& operator = (const DynamicLibrary::Symbol& symbol)
		{
			pPtr = (Type)(symbol.ptr());
			return *this;
		}

		void operator () (A0 a0) const
		{
			if (pPtr)
				pPtr(a0);
		}

	public:
		//! Pointer
		Type pPtr;

	}; // class F1 - Template specialization






	/* Implementation class F2 */

	template<typename R, typename A0, typename A1>
	inline F2<R, A0, A1>::F2()
		:pPtr(NULL)
	{}

	template<typename R, typename A0, typename A1>
	inline F2<R, A0, A1>::F2(const typename F2<R, A0, A1>::Type p)
		:pPtr(p)
	{}

	template<typename R, typename A0, typename A1>
	inline F2<R, A0, A1>::F2(const F2<R, A0, A1>& copy)
		:pPtr(copy.pPtr)
	{}

	template<typename R, typename A0, typename A1>
	inline F2<R, A0, A1>::F2(const DynamicLibrary::Symbol& symbol)
		:pPtr((Type)(symbol.ptr()))
	{}

	template<typename R, typename A0, typename A1>
	inline R
	F2<R, A0, A1>::call(A0 a0, A1 a1) const
	{
		return pPtr ? pPtr(a0, a1) : R();
	}

	template<typename R, typename A0, typename A1>
	inline R
	F2<R, A0, A1>::operator () (A0 a0, A1 a1) const
	{
		return pPtr ? pPtr(a0, a1) : R();
	}

	template<typename R, typename A0, typename A1>
	inline bool
	F2<R, A0, A1>::null() const
	{
		return NULL == pPtr;
	}

	template<typename R, typename A0, typename A1>
	inline bool
	F2<R, A0, A1>::valid() const
	{
		return NULL != pPtr;
	}

	template<typename R, typename A0, typename A1>
	inline typename F2<R, A0, A1>::Type
	F2<R, A0, A1>::ptr() const
	{
		return pPtr;
	}

	template<typename R, typename A0, typename A1>
	inline F2<R, A0, A1>&
	F2<R, A0, A1>::operator = (const F2<R, A0, A1>& copy)
	{
		pPtr = copy.pPtr;
		return *this;
	}

	template<typename R, typename A0, typename A1>
	inline F2<R, A0, A1>&
	F2<R, A0, A1>::operator = (const Type rhs)
	{
		pPtr = rhs;
		return *this;
	}

	template<typename R, typename A0, typename A1>
	inline F2<R, A0, A1>&
	F2<R, A0, A1>::operator = (const DynamicLibrary::Symbol& symbol)
	{
		pPtr = (Type)(symbol.ptr());
		return *this;
	}




	/* Implementation class F2 Template specialization */

	template<typename A0, typename A1>
	class F2 <void, A0, A1>
	{
	public:
		//! Prototype of the function
		typedef void (*Type) (A0, A1);
		//! Prototype of the function
		typedef void (*value_type) (A0, A1);

		enum
		{
			//! Arguments count
			argumentsCount = 2
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 0
		};

	public:
		F2()
			:pPtr(NULL)
		{}

		F2(const F2& copy)
			:pPtr(copy.pPtr)
		{}

		F2(const Type rhs)
			:pPtr(rhs)
		{}

		F2(const DynamicLibrary::Symbol& symbol)
			:pPtr((Type)(symbol.ptr()))
		{}

		void call(A0 a0, A1 a1) const
		{
			if (pPtr)
				pPtr(a0, a1);
		}


		bool null() const {return NULL == pPtr;}

		bool valid() const {return NULL != pPtr;}

		Type ptr() const {return pPtr;}

		F2& operator = (const F2& copy)
		{
			pPtr = copy.pPtr;
			return *this;
		}

		F2& operator = (const Type rhs)
		{
			pPtr = rhs;
			return *this;
		}

		F2& operator = (const DynamicLibrary::Symbol& symbol)
		{
			pPtr = (Type)(symbol.ptr());
			return *this;
		}

		void operator () (A0 a0, A1 a1) const
		{
			if (pPtr)
				pPtr(a0, a1);
		}

	public:
		//! Pointer
		Type pPtr;

	}; // class F2 - Template specialization






	/* Implementation class F3 */

	template<typename R, typename A0, typename A1, typename A2>
	inline F3<R, A0, A1, A2>::F3()
		:pPtr(NULL)
	{}

	template<typename R, typename A0, typename A1, typename A2>
	inline F3<R, A0, A1, A2>::F3(const typename F3<R, A0, A1, A2>::Type p)
		:pPtr(p)
	{}

	template<typename R, typename A0, typename A1, typename A2>
	inline F3<R, A0, A1, A2>::F3(const F3<R, A0, A1, A2>& copy)
		:pPtr(copy.pPtr)
	{}

	template<typename R, typename A0, typename A1, typename A2>
	inline F3<R, A0, A1, A2>::F3(const DynamicLibrary::Symbol& symbol)
		:pPtr((Type)(symbol.ptr()))
	{}

	template<typename R, typename A0, typename A1, typename A2>
	inline R
	F3<R, A0, A1, A2>::call(A0 a0, A1 a1, A2 a2) const
	{
		return pPtr ? pPtr(a0, a1, a2) : R();
	}

	template<typename R, typename A0, typename A1, typename A2>
	inline R
	F3<R, A0, A1, A2>::operator () (A0 a0, A1 a1, A2 a2) const
	{
		return pPtr ? pPtr(a0, a1, a2) : R();
	}

	template<typename R, typename A0, typename A1, typename A2>
	inline bool
	F3<R, A0, A1, A2>::null() const
	{
		return NULL == pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2>
	inline bool
	F3<R, A0, A1, A2>::valid() const
	{
		return NULL != pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2>
	inline typename F3<R, A0, A1, A2>::Type
	F3<R, A0, A1, A2>::ptr() const
	{
		return pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2>
	inline F3<R, A0, A1, A2>&
	F3<R, A0, A1, A2>::operator = (const F3<R, A0, A1, A2>& copy)
	{
		pPtr = copy.pPtr;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2>
	inline F3<R, A0, A1, A2>&
	F3<R, A0, A1, A2>::operator = (const Type rhs)
	{
		pPtr = rhs;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2>
	inline F3<R, A0, A1, A2>&
	F3<R, A0, A1, A2>::operator = (const DynamicLibrary::Symbol& symbol)
	{
		pPtr = (Type)(symbol.ptr());
		return *this;
	}




	/* Implementation class F3 Template specialization */

	template<typename A0, typename A1, typename A2>
	class F3 <void, A0, A1, A2>
	{
	public:
		//! Prototype of the function
		typedef void (*Type) (A0, A1, A2);
		//! Prototype of the function
		typedef void (*value_type) (A0, A1, A2);

		enum
		{
			//! Arguments count
			argumentsCount = 3
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 0
		};

	public:
		F3()
			:pPtr(NULL)
		{}

		F3(const F3& copy)
			:pPtr(copy.pPtr)
		{}

		F3(const Type rhs)
			:pPtr(rhs)
		{}

		F3(const DynamicLibrary::Symbol& symbol)
			:pPtr((Type)(symbol.ptr()))
		{}

		void call(A0 a0, A1 a1, A2 a2) const
		{
			if (pPtr)
				pPtr(a0, a1, a2);
		}


		bool null() const {return NULL == pPtr;}

		bool valid() const {return NULL != pPtr;}

		Type ptr() const {return pPtr;}

		F3& operator = (const F3& copy)
		{
			pPtr = copy.pPtr;
			return *this;
		}

		F3& operator = (const Type rhs)
		{
			pPtr = rhs;
			return *this;
		}

		F3& operator = (const DynamicLibrary::Symbol& symbol)
		{
			pPtr = (Type)(symbol.ptr());
			return *this;
		}

		void operator () (A0 a0, A1 a1, A2 a2) const
		{
			if (pPtr)
				pPtr(a0, a1, a2);
		}

	public:
		//! Pointer
		Type pPtr;

	}; // class F3 - Template specialization






	/* Implementation class F4 */

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	inline F4<R, A0, A1, A2, A3>::F4()
		:pPtr(NULL)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	inline F4<R, A0, A1, A2, A3>::F4(const typename F4<R, A0, A1, A2, A3>::Type p)
		:pPtr(p)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	inline F4<R, A0, A1, A2, A3>::F4(const F4<R, A0, A1, A2, A3>& copy)
		:pPtr(copy.pPtr)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	inline F4<R, A0, A1, A2, A3>::F4(const DynamicLibrary::Symbol& symbol)
		:pPtr((Type)(symbol.ptr()))
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	inline R
	F4<R, A0, A1, A2, A3>::call(A0 a0, A1 a1, A2 a2, A3 a3) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	inline R
	F4<R, A0, A1, A2, A3>::operator () (A0 a0, A1 a1, A2 a2, A3 a3) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	inline bool
	F4<R, A0, A1, A2, A3>::null() const
	{
		return NULL == pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	inline bool
	F4<R, A0, A1, A2, A3>::valid() const
	{
		return NULL != pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	inline typename F4<R, A0, A1, A2, A3>::Type
	F4<R, A0, A1, A2, A3>::ptr() const
	{
		return pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	inline F4<R, A0, A1, A2, A3>&
	F4<R, A0, A1, A2, A3>::operator = (const F4<R, A0, A1, A2, A3>& copy)
	{
		pPtr = copy.pPtr;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	inline F4<R, A0, A1, A2, A3>&
	F4<R, A0, A1, A2, A3>::operator = (const Type rhs)
	{
		pPtr = rhs;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3>
	inline F4<R, A0, A1, A2, A3>&
	F4<R, A0, A1, A2, A3>::operator = (const DynamicLibrary::Symbol& symbol)
	{
		pPtr = (Type)(symbol.ptr());
		return *this;
	}




	/* Implementation class F4 Template specialization */

	template<typename A0, typename A1, typename A2, typename A3>
	class F4 <void, A0, A1, A2, A3>
	{
	public:
		//! Prototype of the function
		typedef void (*Type) (A0, A1, A2, A3);
		//! Prototype of the function
		typedef void (*value_type) (A0, A1, A2, A3);

		enum
		{
			//! Arguments count
			argumentsCount = 4
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 0
		};

	public:
		F4()
			:pPtr(NULL)
		{}

		F4(const F4& copy)
			:pPtr(copy.pPtr)
		{}

		F4(const Type rhs)
			:pPtr(rhs)
		{}

		F4(const DynamicLibrary::Symbol& symbol)
			:pPtr((Type)(symbol.ptr()))
		{}

		void call(A0 a0, A1 a1, A2 a2, A3 a3) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3);
		}


		bool null() const {return NULL == pPtr;}

		bool valid() const {return NULL != pPtr;}

		Type ptr() const {return pPtr;}

		F4& operator = (const F4& copy)
		{
			pPtr = copy.pPtr;
			return *this;
		}

		F4& operator = (const Type rhs)
		{
			pPtr = rhs;
			return *this;
		}

		F4& operator = (const DynamicLibrary::Symbol& symbol)
		{
			pPtr = (Type)(symbol.ptr());
			return *this;
		}

		void operator () (A0 a0, A1 a1, A2 a2, A3 a3) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3);
		}

	public:
		//! Pointer
		Type pPtr;

	}; // class F4 - Template specialization






	/* Implementation class F5 */

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	inline F5<R, A0, A1, A2, A3, A4>::F5()
		:pPtr(NULL)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	inline F5<R, A0, A1, A2, A3, A4>::F5(const typename F5<R, A0, A1, A2, A3, A4>::Type p)
		:pPtr(p)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	inline F5<R, A0, A1, A2, A3, A4>::F5(const F5<R, A0, A1, A2, A3, A4>& copy)
		:pPtr(copy.pPtr)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	inline F5<R, A0, A1, A2, A3, A4>::F5(const DynamicLibrary::Symbol& symbol)
		:pPtr((Type)(symbol.ptr()))
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	inline R
	F5<R, A0, A1, A2, A3, A4>::call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	inline R
	F5<R, A0, A1, A2, A3, A4>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	inline bool
	F5<R, A0, A1, A2, A3, A4>::null() const
	{
		return NULL == pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	inline bool
	F5<R, A0, A1, A2, A3, A4>::valid() const
	{
		return NULL != pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	inline typename F5<R, A0, A1, A2, A3, A4>::Type
	F5<R, A0, A1, A2, A3, A4>::ptr() const
	{
		return pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	inline F5<R, A0, A1, A2, A3, A4>&
	F5<R, A0, A1, A2, A3, A4>::operator = (const F5<R, A0, A1, A2, A3, A4>& copy)
	{
		pPtr = copy.pPtr;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	inline F5<R, A0, A1, A2, A3, A4>&
	F5<R, A0, A1, A2, A3, A4>::operator = (const Type rhs)
	{
		pPtr = rhs;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	inline F5<R, A0, A1, A2, A3, A4>&
	F5<R, A0, A1, A2, A3, A4>::operator = (const DynamicLibrary::Symbol& symbol)
	{
		pPtr = (Type)(symbol.ptr());
		return *this;
	}




	/* Implementation class F5 Template specialization */

	template<typename A0, typename A1, typename A2, typename A3, typename A4>
	class F5 <void, A0, A1, A2, A3, A4>
	{
	public:
		//! Prototype of the function
		typedef void (*Type) (A0, A1, A2, A3, A4);
		//! Prototype of the function
		typedef void (*value_type) (A0, A1, A2, A3, A4);

		enum
		{
			//! Arguments count
			argumentsCount = 5
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 0
		};

	public:
		F5()
			:pPtr(NULL)
		{}

		F5(const F5& copy)
			:pPtr(copy.pPtr)
		{}

		F5(const Type rhs)
			:pPtr(rhs)
		{}

		F5(const DynamicLibrary::Symbol& symbol)
			:pPtr((Type)(symbol.ptr()))
		{}

		void call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4);
		}


		bool null() const {return NULL == pPtr;}

		bool valid() const {return NULL != pPtr;}

		Type ptr() const {return pPtr;}

		F5& operator = (const F5& copy)
		{
			pPtr = copy.pPtr;
			return *this;
		}

		F5& operator = (const Type rhs)
		{
			pPtr = rhs;
			return *this;
		}

		F5& operator = (const DynamicLibrary::Symbol& symbol)
		{
			pPtr = (Type)(symbol.ptr());
			return *this;
		}

		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4);
		}

	public:
		//! Pointer
		Type pPtr;

	}; // class F5 - Template specialization






	/* Implementation class F6 */

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	inline F6<R, A0, A1, A2, A3, A4, A5>::F6()
		:pPtr(NULL)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	inline F6<R, A0, A1, A2, A3, A4, A5>::F6(const typename F6<R, A0, A1, A2, A3, A4, A5>::Type p)
		:pPtr(p)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	inline F6<R, A0, A1, A2, A3, A4, A5>::F6(const F6<R, A0, A1, A2, A3, A4, A5>& copy)
		:pPtr(copy.pPtr)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	inline F6<R, A0, A1, A2, A3, A4, A5>::F6(const DynamicLibrary::Symbol& symbol)
		:pPtr((Type)(symbol.ptr()))
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	inline R
	F6<R, A0, A1, A2, A3, A4, A5>::call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4, a5) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	inline R
	F6<R, A0, A1, A2, A3, A4, A5>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4, a5) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	inline bool
	F6<R, A0, A1, A2, A3, A4, A5>::null() const
	{
		return NULL == pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	inline bool
	F6<R, A0, A1, A2, A3, A4, A5>::valid() const
	{
		return NULL != pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	inline typename F6<R, A0, A1, A2, A3, A4, A5>::Type
	F6<R, A0, A1, A2, A3, A4, A5>::ptr() const
	{
		return pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	inline F6<R, A0, A1, A2, A3, A4, A5>&
	F6<R, A0, A1, A2, A3, A4, A5>::operator = (const F6<R, A0, A1, A2, A3, A4, A5>& copy)
	{
		pPtr = copy.pPtr;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	inline F6<R, A0, A1, A2, A3, A4, A5>&
	F6<R, A0, A1, A2, A3, A4, A5>::operator = (const Type rhs)
	{
		pPtr = rhs;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	inline F6<R, A0, A1, A2, A3, A4, A5>&
	F6<R, A0, A1, A2, A3, A4, A5>::operator = (const DynamicLibrary::Symbol& symbol)
	{
		pPtr = (Type)(symbol.ptr());
		return *this;
	}




	/* Implementation class F6 Template specialization */

	template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	class F6 <void, A0, A1, A2, A3, A4, A5>
	{
	public:
		//! Prototype of the function
		typedef void (*Type) (A0, A1, A2, A3, A4, A5);
		//! Prototype of the function
		typedef void (*value_type) (A0, A1, A2, A3, A4, A5);

		enum
		{
			//! Arguments count
			argumentsCount = 6
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 0
		};

	public:
		F6()
			:pPtr(NULL)
		{}

		F6(const F6& copy)
			:pPtr(copy.pPtr)
		{}

		F6(const Type rhs)
			:pPtr(rhs)
		{}

		F6(const DynamicLibrary::Symbol& symbol)
			:pPtr((Type)(symbol.ptr()))
		{}

		void call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4, a5);
		}


		bool null() const {return NULL == pPtr;}

		bool valid() const {return NULL != pPtr;}

		Type ptr() const {return pPtr;}

		F6& operator = (const F6& copy)
		{
			pPtr = copy.pPtr;
			return *this;
		}

		F6& operator = (const Type rhs)
		{
			pPtr = rhs;
			return *this;
		}

		F6& operator = (const DynamicLibrary::Symbol& symbol)
		{
			pPtr = (Type)(symbol.ptr());
			return *this;
		}

		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4, a5);
		}

	public:
		//! Pointer
		Type pPtr;

	}; // class F6 - Template specialization






	/* Implementation class F7 */

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	inline F7<R, A0, A1, A2, A3, A4, A5, A6>::F7()
		:pPtr(NULL)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	inline F7<R, A0, A1, A2, A3, A4, A5, A6>::F7(const typename F7<R, A0, A1, A2, A3, A4, A5, A6>::Type p)
		:pPtr(p)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	inline F7<R, A0, A1, A2, A3, A4, A5, A6>::F7(const F7<R, A0, A1, A2, A3, A4, A5, A6>& copy)
		:pPtr(copy.pPtr)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	inline F7<R, A0, A1, A2, A3, A4, A5, A6>::F7(const DynamicLibrary::Symbol& symbol)
		:pPtr((Type)(symbol.ptr()))
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	inline R
	F7<R, A0, A1, A2, A3, A4, A5, A6>::call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4, a5, a6) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	inline R
	F7<R, A0, A1, A2, A3, A4, A5, A6>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4, a5, a6) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	inline bool
	F7<R, A0, A1, A2, A3, A4, A5, A6>::null() const
	{
		return NULL == pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	inline bool
	F7<R, A0, A1, A2, A3, A4, A5, A6>::valid() const
	{
		return NULL != pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	inline typename F7<R, A0, A1, A2, A3, A4, A5, A6>::Type
	F7<R, A0, A1, A2, A3, A4, A5, A6>::ptr() const
	{
		return pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	inline F7<R, A0, A1, A2, A3, A4, A5, A6>&
	F7<R, A0, A1, A2, A3, A4, A5, A6>::operator = (const F7<R, A0, A1, A2, A3, A4, A5, A6>& copy)
	{
		pPtr = copy.pPtr;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	inline F7<R, A0, A1, A2, A3, A4, A5, A6>&
	F7<R, A0, A1, A2, A3, A4, A5, A6>::operator = (const Type rhs)
	{
		pPtr = rhs;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	inline F7<R, A0, A1, A2, A3, A4, A5, A6>&
	F7<R, A0, A1, A2, A3, A4, A5, A6>::operator = (const DynamicLibrary::Symbol& symbol)
	{
		pPtr = (Type)(symbol.ptr());
		return *this;
	}




	/* Implementation class F7 Template specialization */

	template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	class F7 <void, A0, A1, A2, A3, A4, A5, A6>
	{
	public:
		//! Prototype of the function
		typedef void (*Type) (A0, A1, A2, A3, A4, A5, A6);
		//! Prototype of the function
		typedef void (*value_type) (A0, A1, A2, A3, A4, A5, A6);

		enum
		{
			//! Arguments count
			argumentsCount = 7
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 0
		};

	public:
		F7()
			:pPtr(NULL)
		{}

		F7(const F7& copy)
			:pPtr(copy.pPtr)
		{}

		F7(const Type rhs)
			:pPtr(rhs)
		{}

		F7(const DynamicLibrary::Symbol& symbol)
			:pPtr((Type)(symbol.ptr()))
		{}

		void call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4, a5, a6);
		}


		bool null() const {return NULL == pPtr;}

		bool valid() const {return NULL != pPtr;}

		Type ptr() const {return pPtr;}

		F7& operator = (const F7& copy)
		{
			pPtr = copy.pPtr;
			return *this;
		}

		F7& operator = (const Type rhs)
		{
			pPtr = rhs;
			return *this;
		}

		F7& operator = (const DynamicLibrary::Symbol& symbol)
		{
			pPtr = (Type)(symbol.ptr());
			return *this;
		}

		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4, a5, a6);
		}

	public:
		//! Pointer
		Type pPtr;

	}; // class F7 - Template specialization






	/* Implementation class F8 */

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	inline F8<R, A0, A1, A2, A3, A4, A5, A6, A7>::F8()
		:pPtr(NULL)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	inline F8<R, A0, A1, A2, A3, A4, A5, A6, A7>::F8(const typename F8<R, A0, A1, A2, A3, A4, A5, A6, A7>::Type p)
		:pPtr(p)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	inline F8<R, A0, A1, A2, A3, A4, A5, A6, A7>::F8(const F8<R, A0, A1, A2, A3, A4, A5, A6, A7>& copy)
		:pPtr(copy.pPtr)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	inline F8<R, A0, A1, A2, A3, A4, A5, A6, A7>::F8(const DynamicLibrary::Symbol& symbol)
		:pPtr((Type)(symbol.ptr()))
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	inline R
	F8<R, A0, A1, A2, A3, A4, A5, A6, A7>::call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4, a5, a6, a7) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	inline R
	F8<R, A0, A1, A2, A3, A4, A5, A6, A7>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4, a5, a6, a7) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	inline bool
	F8<R, A0, A1, A2, A3, A4, A5, A6, A7>::null() const
	{
		return NULL == pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	inline bool
	F8<R, A0, A1, A2, A3, A4, A5, A6, A7>::valid() const
	{
		return NULL != pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	inline typename F8<R, A0, A1, A2, A3, A4, A5, A6, A7>::Type
	F8<R, A0, A1, A2, A3, A4, A5, A6, A7>::ptr() const
	{
		return pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	inline F8<R, A0, A1, A2, A3, A4, A5, A6, A7>&
	F8<R, A0, A1, A2, A3, A4, A5, A6, A7>::operator = (const F8<R, A0, A1, A2, A3, A4, A5, A6, A7>& copy)
	{
		pPtr = copy.pPtr;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	inline F8<R, A0, A1, A2, A3, A4, A5, A6, A7>&
	F8<R, A0, A1, A2, A3, A4, A5, A6, A7>::operator = (const Type rhs)
	{
		pPtr = rhs;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	inline F8<R, A0, A1, A2, A3, A4, A5, A6, A7>&
	F8<R, A0, A1, A2, A3, A4, A5, A6, A7>::operator = (const DynamicLibrary::Symbol& symbol)
	{
		pPtr = (Type)(symbol.ptr());
		return *this;
	}




	/* Implementation class F8 Template specialization */

	template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	class F8 <void, A0, A1, A2, A3, A4, A5, A6, A7>
	{
	public:
		//! Prototype of the function
		typedef void (*Type) (A0, A1, A2, A3, A4, A5, A6, A7);
		//! Prototype of the function
		typedef void (*value_type) (A0, A1, A2, A3, A4, A5, A6, A7);

		enum
		{
			//! Arguments count
			argumentsCount = 8
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 0
		};

	public:
		F8()
			:pPtr(NULL)
		{}

		F8(const F8& copy)
			:pPtr(copy.pPtr)
		{}

		F8(const Type rhs)
			:pPtr(rhs)
		{}

		F8(const DynamicLibrary::Symbol& symbol)
			:pPtr((Type)(symbol.ptr()))
		{}

		void call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4, a5, a6, a7);
		}


		bool null() const {return NULL == pPtr;}

		bool valid() const {return NULL != pPtr;}

		Type ptr() const {return pPtr;}

		F8& operator = (const F8& copy)
		{
			pPtr = copy.pPtr;
			return *this;
		}

		F8& operator = (const Type rhs)
		{
			pPtr = rhs;
			return *this;
		}

		F8& operator = (const DynamicLibrary::Symbol& symbol)
		{
			pPtr = (Type)(symbol.ptr());
			return *this;
		}

		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4, a5, a6, a7);
		}

	public:
		//! Pointer
		Type pPtr;

	}; // class F8 - Template specialization






	/* Implementation class F9 */

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	inline F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>::F9()
		:pPtr(NULL)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	inline F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>::F9(const typename F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>::Type p)
		:pPtr(p)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	inline F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>::F9(const F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>& copy)
		:pPtr(copy.pPtr)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	inline F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>::F9(const DynamicLibrary::Symbol& symbol)
		:pPtr((Type)(symbol.ptr()))
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	inline R
	F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>::call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	inline R
	F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	inline bool
	F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>::null() const
	{
		return NULL == pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	inline bool
	F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>::valid() const
	{
		return NULL != pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	inline typename F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>::Type
	F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>::ptr() const
	{
		return pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	inline F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>&
	F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>::operator = (const F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>& copy)
	{
		pPtr = copy.pPtr;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	inline F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>&
	F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>::operator = (const Type rhs)
	{
		pPtr = rhs;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	inline F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>&
	F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8>::operator = (const DynamicLibrary::Symbol& symbol)
	{
		pPtr = (Type)(symbol.ptr());
		return *this;
	}




	/* Implementation class F9 Template specialization */

	template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	class F9 <void, A0, A1, A2, A3, A4, A5, A6, A7, A8>
	{
	public:
		//! Prototype of the function
		typedef void (*Type) (A0, A1, A2, A3, A4, A5, A6, A7, A8);
		//! Prototype of the function
		typedef void (*value_type) (A0, A1, A2, A3, A4, A5, A6, A7, A8);

		enum
		{
			//! Arguments count
			argumentsCount = 9
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 0
		};

	public:
		F9()
			:pPtr(NULL)
		{}

		F9(const F9& copy)
			:pPtr(copy.pPtr)
		{}

		F9(const Type rhs)
			:pPtr(rhs)
		{}

		F9(const DynamicLibrary::Symbol& symbol)
			:pPtr((Type)(symbol.ptr()))
		{}

		void call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8);
		}


		bool null() const {return NULL == pPtr;}

		bool valid() const {return NULL != pPtr;}

		Type ptr() const {return pPtr;}

		F9& operator = (const F9& copy)
		{
			pPtr = copy.pPtr;
			return *this;
		}

		F9& operator = (const Type rhs)
		{
			pPtr = rhs;
			return *this;
		}

		F9& operator = (const DynamicLibrary::Symbol& symbol)
		{
			pPtr = (Type)(symbol.ptr());
			return *this;
		}

		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8);
		}

	public:
		//! Pointer
		Type pPtr;

	}; // class F9 - Template specialization






	/* Implementation class F10 */

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	inline F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>::F10()
		:pPtr(NULL)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	inline F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>::F10(const typename F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>::Type p)
		:pPtr(p)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	inline F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>::F10(const F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>& copy)
		:pPtr(copy.pPtr)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	inline F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>::F10(const DynamicLibrary::Symbol& symbol)
		:pPtr((Type)(symbol.ptr()))
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	inline R
	F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>::call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	inline R
	F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	inline bool
	F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>::null() const
	{
		return NULL == pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	inline bool
	F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>::valid() const
	{
		return NULL != pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	inline typename F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>::Type
	F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>::ptr() const
	{
		return pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	inline F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>&
	F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>::operator = (const F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>& copy)
	{
		pPtr = copy.pPtr;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	inline F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>&
	F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>::operator = (const Type rhs)
	{
		pPtr = rhs;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	inline F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>&
	F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>::operator = (const DynamicLibrary::Symbol& symbol)
	{
		pPtr = (Type)(symbol.ptr());
		return *this;
	}




	/* Implementation class F10 Template specialization */

	template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	class F10 <void, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9>
	{
	public:
		//! Prototype of the function
		typedef void (*Type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9);
		//! Prototype of the function
		typedef void (*value_type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9);

		enum
		{
			//! Arguments count
			argumentsCount = 10
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 0
		};

	public:
		F10()
			:pPtr(NULL)
		{}

		F10(const F10& copy)
			:pPtr(copy.pPtr)
		{}

		F10(const Type rhs)
			:pPtr(rhs)
		{}

		F10(const DynamicLibrary::Symbol& symbol)
			:pPtr((Type)(symbol.ptr()))
		{}

		void call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
		}


		bool null() const {return NULL == pPtr;}

		bool valid() const {return NULL != pPtr;}

		Type ptr() const {return pPtr;}

		F10& operator = (const F10& copy)
		{
			pPtr = copy.pPtr;
			return *this;
		}

		F10& operator = (const Type rhs)
		{
			pPtr = rhs;
			return *this;
		}

		F10& operator = (const DynamicLibrary::Symbol& symbol)
		{
			pPtr = (Type)(symbol.ptr());
			return *this;
		}

		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
		}

	public:
		//! Pointer
		Type pPtr;

	}; // class F10 - Template specialization






	/* Implementation class F11 */

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	inline F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::F11()
		:pPtr(NULL)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	inline F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::F11(const typename F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::Type p)
		:pPtr(p)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	inline F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::F11(const F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>& copy)
		:pPtr(copy.pPtr)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	inline F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::F11(const DynamicLibrary::Symbol& symbol)
		:pPtr((Type)(symbol.ptr()))
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	inline R
	F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	inline R
	F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	inline bool
	F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::null() const
	{
		return NULL == pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	inline bool
	F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::valid() const
	{
		return NULL != pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	inline typename F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::Type
	F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::ptr() const
	{
		return pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	inline F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>&
	F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::operator = (const F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>& copy)
	{
		pPtr = copy.pPtr;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	inline F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>&
	F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::operator = (const Type rhs)
	{
		pPtr = rhs;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	inline F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>&
	F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::operator = (const DynamicLibrary::Symbol& symbol)
	{
		pPtr = (Type)(symbol.ptr());
		return *this;
	}




	/* Implementation class F11 Template specialization */

	template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	class F11 <void, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>
	{
	public:
		//! Prototype of the function
		typedef void (*Type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
		//! Prototype of the function
		typedef void (*value_type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);

		enum
		{
			//! Arguments count
			argumentsCount = 11
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 0
		};

	public:
		F11()
			:pPtr(NULL)
		{}

		F11(const F11& copy)
			:pPtr(copy.pPtr)
		{}

		F11(const Type rhs)
			:pPtr(rhs)
		{}

		F11(const DynamicLibrary::Symbol& symbol)
			:pPtr((Type)(symbol.ptr()))
		{}

		void call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
		}


		bool null() const {return NULL == pPtr;}

		bool valid() const {return NULL != pPtr;}

		Type ptr() const {return pPtr;}

		F11& operator = (const F11& copy)
		{
			pPtr = copy.pPtr;
			return *this;
		}

		F11& operator = (const Type rhs)
		{
			pPtr = rhs;
			return *this;
		}

		F11& operator = (const DynamicLibrary::Symbol& symbol)
		{
			pPtr = (Type)(symbol.ptr());
			return *this;
		}

		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
		}

	public:
		//! Pointer
		Type pPtr;

	}; // class F11 - Template specialization






	/* Implementation class F12 */

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	inline F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::F12()
		:pPtr(NULL)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	inline F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::F12(const typename F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::Type p)
		:pPtr(p)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	inline F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::F12(const F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>& copy)
		:pPtr(copy.pPtr)
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	inline F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::F12(const DynamicLibrary::Symbol& symbol)
		:pPtr((Type)(symbol.ptr()))
	{}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	inline R
	F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	inline R
	F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const
	{
		return pPtr ? pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) : R();
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	inline bool
	F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::null() const
	{
		return NULL == pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	inline bool
	F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::valid() const
	{
		return NULL != pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	inline typename F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::Type
	F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::ptr() const
	{
		return pPtr;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	inline F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>&
	F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::operator = (const F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>& copy)
	{
		pPtr = copy.pPtr;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	inline F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>&
	F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::operator = (const Type rhs)
	{
		pPtr = rhs;
		return *this;
	}

	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	inline F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>&
	F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::operator = (const DynamicLibrary::Symbol& symbol)
	{
		pPtr = (Type)(symbol.ptr());
		return *this;
	}




	/* Implementation class F12 Template specialization */

	template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	class F12 <void, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>
	{
	public:
		//! Prototype of the function
		typedef void (*Type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11);
		//! Prototype of the function
		typedef void (*value_type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11);

		enum
		{
			//! Arguments count
			argumentsCount = 12
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 0
		};

	public:
		F12()
			:pPtr(NULL)
		{}

		F12(const F12& copy)
			:pPtr(copy.pPtr)
		{}

		F12(const Type rhs)
			:pPtr(rhs)
		{}

		F12(const DynamicLibrary::Symbol& symbol)
			:pPtr((Type)(symbol.ptr()))
		{}

		void call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
		}


		bool null() const {return NULL == pPtr;}

		bool valid() const {return NULL != pPtr;}

		Type ptr() const {return pPtr;}

		F12& operator = (const F12& copy)
		{
			pPtr = copy.pPtr;
			return *this;
		}

		F12& operator = (const Type rhs)
		{
			pPtr = rhs;
			return *this;
		}

		F12& operator = (const DynamicLibrary::Symbol& symbol)
		{
			pPtr = (Type)(symbol.ptr());
			return *this;
		}

		void operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const
		{
			if (pPtr)
				pPtr(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
		}

	public:
		//! Pointer
		Type pPtr;

	}; // class F12 - Template specialization





} // namespace Function
} // namespace Yuni

#endif // __YUNI_TOOLBOX_FUNCTION_FUNCTION_HXX__
