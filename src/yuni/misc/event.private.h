#ifndef __YUNI_MISC_EVENTS_PRIVATE_H__
# define __YUNI_MISC_EVENTS_PRIVATE_H__

# include "sharedptr.h"


namespace Yuni
{
namespace Private
{
namespace Events
{


	class It0
	{
	public:
		It0() {}
		virtual ~It0() {}
		virtual bool checkObj(const void *) const = 0;
		virtual void emit(const Yuni::Event::EmitMode em) = 0;
	};


	template<typename T1>
	class It1
	{
	public:
		It1() {}
		virtual ~It1() {}
		virtual bool checkObj(const void *) const = 0;
		virtual void emit(T1, const Yuni::Event::EmitMode em) = 0;
	};


	template<typename T1, typename T2>
	class It2
	{
	public:
		It2() {}
		virtual ~It2() {}
		virtual bool checkObj(const void *) const = 0;
		virtual void emit(T1, T2, const Yuni::Event::EmitMode em) = 0;
	};


	template<typename T1, typename T2, typename T3>
	class It3
	{
	public:
		It3() {}
		virtual ~It3() {}
		virtual bool checkObj(const void *) const = 0;
		virtual void emit(T1, T2, T3, const Yuni::Event::EmitMode em) = 0;
	};


	template<typename T1, typename T2, typename T3, typename T4>
	class It4
	{
	public:
		It4() {}
		virtual ~It4() {}
		virtual bool checkObj(const void *) const = 0;
		virtual void emit(T1, T2, T3, T4, const Yuni::Event::EmitMode em) = 0;
	};

	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	class It5
	{
	public:
		It5() {}
		virtual ~It5() {}
		virtual bool checkObj(const void *) const = 0;
		virtual void emit(T1, T2, T3, T4, T5, const Yuni::Event::EmitMode em) = 0;
	};

	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	class It6
	{
	public:
		It6() {}
		virtual ~It6() {}
		virtual bool checkObj(const void *) const = 0;
		virtual void emit(T1, T2, T3, T4, T5, T6, const Yuni::Event::EmitMode em) = 0;
	};

	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	class It7
	{
	public:
		It7() {}
		virtual ~It7() {}
		virtual bool checkObj(const void *) const = 0;
		virtual void emit(T1, T2, T3, T4, T5, T6, T7, const Yuni::Event::EmitMode em) = 0;
	};

	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	class It8
	{
	public:
		It8() {}
		virtual ~It8() {}
		virtual bool checkObj(const void *) const = 0;
		virtual void emit(T1, T2, T3, T4, T5, T6, T7, T8, const Yuni::Event::EmitMode em) = 0;
	};











	template<class C>
	class ItTmpl0 : public It0
	{
	public:
		ItTmpl0(Yuni::Event::Notifier* n, C* cl, void (C::* fn)(void))
			:It0(), pNotifier(n), pObj(cl), pFn(fn)
		{}

		virtual ~ItTmpl0()
		{
			if (pNotifier->isDisconnectionBroadcastAllowed())
				(dynamic_cast<Yuni::Event::Receiver*>(pObj))->disconnectEventNotifier(pNotifier);
		}

		virtual void emit(const Yuni::Event::EmitMode em)
		{
			if (Yuni::Event::emImmediate == em)
				(pObj->*pFn)();
			else
				(pObj->*pFn)(); // TODO Use the jobs instead
		}

		virtual bool checkObj(const void* o) const {return o == (void*)pObj;}

	private:
		Yuni::Event::Notifier* pNotifier;
		C* pObj;
		void (C::* pFn)(void);

	}; // ItTmpl0


	template<class C, typename T1>
	class ItTmpl1 : public It1<T1>
	{
	public:
		ItTmpl1(Yuni::Event::Notifier* n, C* cl, void (C::* fn)(T1))
			:It1<T1>(), pNotifier(n), pObj(cl), pFn(fn)
		{}

		virtual ~ItTmpl1()
		{
			if (pNotifier->isDisconnectionBroadcastAllowed())
				(dynamic_cast<Yuni::Event::Receiver*>(pObj))->disconnectEventNotifier(pNotifier);
		}

		virtual void emit(T1 a1, const Yuni::Event::EmitMode em)
		{
			if (Yuni::Event::emImmediate == em)
				(pObj->*pFn)(a1);
			else
				(pObj->*pFn)(a1); // TODO Use the jobs instead
		}

		virtual bool checkObj(const void* o) const {return o == (void*)pObj;}

	private:
		Yuni::Event::Notifier* pNotifier;
		C* pObj;
		void (C::* pFn)(T1);

	}; // ItTmpl1


	template<class C, typename T1, typename T2>
	class ItTmpl2 : public It2<T1, T2>
	{
	public:
		ItTmpl2(Yuni::Event::Notifier* n, C* cl, void (C::* fn)(T1, T2))
			:It2<T1, T2>(), pNotifier(n), pObj(cl), pFn(fn)
		{}

		virtual ~ItTmpl2()
		{
			if (pNotifier->isDisconnectionBroadcastAllowed())
				(dynamic_cast<Yuni::Event::Receiver*>(pObj))->disconnectEventNotifier(pNotifier);
		}

		virtual void emit(T1 a1, T2 a2, const Yuni::Event::EmitMode em)
		{
			if (Yuni::Event::emImmediate == em)
				(pObj->*pFn)(a1, a2);
			else
				(pObj->*pFn)(a1, a2); // TODO Use the jobs instead
		}

		virtual bool checkObj(const void* o) const {return o == (void*)pObj;}

	private:
		Yuni::Event::Notifier* pNotifier;
		C* pObj;
		void (C::* pFn)(T1, T2);

	}; // ItTmpl2


	template<class C, typename T1, typename T2, typename T3>
	class ItTmpl3 : public It3<T1, T2, T3>
	{
	public:
		ItTmpl3(Yuni::Event::Notifier* n, C* cl, void (C::* fn)(T1, T2, T3))
			:It3<T1, T2, T3>(), pNotifier(n), pObj(cl), pFn(fn)
		{}

		virtual ~ItTmpl3()
		{
			if (pNotifier->isDisconnectionBroadcastAllowed())
				(dynamic_cast<Yuni::Event::Receiver*>(pObj))->disconnectEventNotifier(pNotifier);
		}

		virtual void emit(T1 a1, T2 a2, T3 a3, const Yuni::Event::EmitMode em)
		{
			if (Yuni::Event::emImmediate == em)
				(pObj->*pFn)(a1, a2, a3);
			else
				(pObj->*pFn)(a1, a2, a3); // TODO Use the jobs instead
		}

		virtual bool checkObj(const void* o) const {return o == (void*)pObj;}

	private:
		Yuni::Event::Notifier* pNotifier;
		C* pObj;
		void (C::* pFn)(T1, T2, T3);

	}; // ItTmpl3


	template<class C, typename T1, typename T2, typename T3, typename T4>
	class ItTmpl4 : public It4<T1, T2, T3, T4>
	{
	public:
		ItTmpl4(Yuni::Event::Notifier* n, C* cl, void (C::* fn)(T1, T2, T3, T4))
			:It4<T1, T2, T3, T4>(), pNotifier(n), pObj(cl), pFn(fn)
		{}

		virtual ~ItTmpl4()
		{
			if (pNotifier->isDisconnectionBroadcastAllowed())
				(dynamic_cast<Yuni::Event::Receiver*>(pObj))->disconnectEventNotifier(pNotifier);
		}

		virtual void emit(T1 a1, T2 a2, T3 a3, T4 a4, const Yuni::Event::EmitMode em)
		{
			if (Yuni::Event::emImmediate == em)
				(pObj->*pFn)(a1, a2, a3, a4);
			else
				(pObj->*pFn)(a1, a2, a3, a4); // TODO Use the jobs instead
		}

		virtual bool checkObj(const void* o) const {return o == (void*)pObj;}

	private:
		Yuni::Event::Notifier* pNotifier;
		C* pObj;
		void (C::* pFn)(T1, T2, T3, T4);

	}; // ItTmpl4


	template<class C, typename T1, typename T2, typename T3, typename T4, typename T5>
	class ItTmpl5 : public It5<T1, T2, T3, T4, T5>
	{
	public:
		ItTmpl5(Yuni::Event::Notifier* n, C* cl, void (C::* fn)(T1, T2, T3, T4, T5))
			:It5<T1, T2, T3, T4, T5>(), pNotifier(n), pObj(cl), pFn(fn)
		{}

		virtual ~ItTmpl5()
		{
			if (pNotifier->isDisconnectionBroadcastAllowed())
				(dynamic_cast<Yuni::Event::Receiver*>(pObj))->disconnectEventNotifier(pNotifier);
		}

		virtual void emit(T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, const Yuni::Event::EmitMode em)
		{
			if (Yuni::Event::emImmediate == em)
				(pObj->*pFn)(a1, a2, a3, a4, a5);
			else
				(pObj->*pFn)(a1, a2, a3, a4, a5); // TODO Use the jobs instead
		}

		virtual bool checkObj(const void* o) const {return o == (void*)pObj;}

	private:
		Yuni::Event::Notifier* pNotifier;
		C* pObj;
		void (C::* pFn)(T1, T2, T3, T4, T5);

	}; // ItTmpl5


	template<class C, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	class ItTmpl6 : public It6<T1, T2, T3, T4, T5, T6>
	{
	public:
		ItTmpl6(Yuni::Event::Notifier* n, C* cl, void (C::* fn)(T1, T2, T3, T4, T5, T6))
			:It6<T1, T2, T3, T4, T5, T6>(), pNotifier(n), pObj(cl), pFn(fn)
		{}

		virtual ~ItTmpl6()
		{
			if (pNotifier->isDisconnectionBroadcastAllowed())
				(dynamic_cast<Yuni::Event::Receiver*>(pObj))->disconnectEventNotifier(pNotifier);
		}

		virtual void emit(T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, const Yuni::Event::EmitMode em)
		{
			if (Yuni::Event::emImmediate == em)
				(pObj->*pFn)(a1, a2, a3, a4, a5, a6);
			else
				(pObj->*pFn)(a1, a2, a3, a4, a5, a6); // TODO Use the jobs instead
		}

		virtual bool checkObj(const void* o) const {return o == (void*)pObj;}

	private:
		Yuni::Event::Notifier* pNotifier;
		C* pObj;
		void (C::* pFn)(T1, T2, T3, T4, T5, T6);

	}; // ItTmpl6


	template<class C, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	class ItTmpl7 : public It7<T1, T2, T3, T4, T5, T6, T7>
	{
	public:
		ItTmpl7(Yuni::Event::Notifier* n, C* cl, void (C::* fn)(T1, T2, T3, T4, T5, T6, T7))
			:It7<T1, T2, T3, T4, T5, T6, T7>(), pNotifier(n), pObj(cl), pFn(fn)
		{}

		virtual ~ItTmpl7()
		{
			if (pNotifier->isDisconnectionBroadcastAllowed())
				(dynamic_cast<Yuni::Event::Receiver*>(pObj))->disconnectEventNotifier(pNotifier);
		}

		virtual void emit(T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, const Yuni::Event::EmitMode em)
		{
			if (Yuni::Event::emImmediate == em)
				(pObj->*pFn)(a1, a2, a3, a4, a5, a6, a7);
			else
				(pObj->*pFn)(a1, a2, a3, a4, a5, a6, a7); // TODO Use the jobs instead
		}

		virtual bool checkObj(const void* o) const {return o == (void*)pObj;}

	private:
		Yuni::Event::Notifier* pNotifier;
		C* pObj;
		void (C::* pFn)(T1, T2, T3, T4, T5, T6, T7);

	}; // ItTmpl7


	template<class C, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	class ItTmpl8 : public It8<T1, T2, T3, T4, T5, T6, T7, T8>
	{
	public:
		ItTmpl8(Yuni::Event::Notifier* n, C* cl, void (C::* fn)(T1, T2, T3, T4, T5, T6, T7, T8))
			:It8<T1, T2, T3, T4, T5, T6, T7, T8>(), pNotifier(n), pObj(cl), pFn(fn)
		{}

		virtual ~ItTmpl8()
		{
			if (pNotifier->isDisconnectionBroadcastAllowed())
				(dynamic_cast<Yuni::Event::Receiver*>(pObj))->disconnectEventNotifier(pNotifier);
		}

		virtual void emit(T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, const Yuni::Event::EmitMode em)
		{
			if (Yuni::Event::emImmediate == em)
				(pObj->*pFn)(a1, a2, a3, a4, a5, a6, a7, a8);
			else
				(pObj->*pFn)(a1, a2, a3, a4, a5, a6, a7, a8); // TODO Use the jobs instead
		}

		virtual bool checkObj(const void* o) const {return o == (void*)pObj;}

	private:
		Yuni::Event::Notifier* pNotifier;
		C* pObj;
		void (C::* pFn)(T1, T2, T3, T4, T5, T6, T7, T8);

	}; // ItTmpl8












	class RemoveIfIt0
	{
	public:
		RemoveIfIt0(const void* p) : o(p) {}
		bool operator () (const SharedPtr< It0 >& i) const {return i->checkObj(o);}

	private:
		const void* o;
	};


	template<typename T1>
	class RemoveIfIt1
	{
	public:
		RemoveIfIt1(const void* p) : o(p) {}
		bool operator () (const SharedPtr< It1<T1> >& i) const {return i->checkObj(o);}

	private:
		const void* o;
	};


	template<typename T1, typename T2>
	class RemoveIfIt2
	{
	public:
		RemoveIfIt2(const void* p) : o(p) {}
		bool operator () (const SharedPtr< It2<T1,T2> >& i) const {return i->checkObj(o);}

	private:
		const void* o;
	};

	template<typename T1, typename T2, typename T3>
	class RemoveIfIt3
	{
	public:
		RemoveIfIt3(const void* p) : o(p) {}
		bool operator () (const SharedPtr< It3<T1,T2,T3> >& i) const {return i->checkObj(o);}

	private:
		const void* o;
	};

	template<typename T1, typename T2, typename T3, typename T4>
	class RemoveIfIt4
	{
	public:
		RemoveIfIt4(const void* p) : o(p) {}
		bool operator () (const SharedPtr< It4<T1,T2,T3,T4> >& i) const {return i->checkObj(o);}

	private:
		const void* o;
	};

	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	class RemoveIfIt5
	{
	public:
		RemoveIfIt5(const void* p) : o(p) {}
		bool operator () (const SharedPtr< It5<T1,T2,T3,T4,T5> >& i) const {return i->checkObj(o);}

	private:
		const void* o;
	};

	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	class RemoveIfIt6
	{
	public:
		RemoveIfIt6(const void* p) : o(p) {}
		bool operator () (const SharedPtr< It6<T1,T2,T3,T4,T5,T6> >& i) const {return i->checkObj(o);}

	private:
		const void* o;
	};

	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	class RemoveIfIt7
	{
	public:
		RemoveIfIt7(const void* p) : o(p) {}
		bool operator () (const SharedPtr< It7<T1,T2,T3,T4,T5,T6,T7> >& i) const {return i->checkObj(o);}

	private:
		const void* o;
	};

	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	class RemoveIfIt8
	{
	public:
		RemoveIfIt8(const void* p) : o(p) {}
		bool operator () (const SharedPtr< It8<T1,T2,T3,T4,T5,T6,T7,T8> >& i) const {return i->checkObj(o);}

	private:
		const void* o;
	};






} // namespace Events
} // namespace Private
} // namespace yuni

#endif // __YUNI_MISC_EVENTS_PRIVATE_H__
