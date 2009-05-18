#ifndef __YUNI_TOOLBOX_EVENT_PROXY_H__
# define __YUNI_TOOLBOX_EVENT_PROXY_H__

# include "event.h"


namespace Yuni
{
namespace Event
{
namespace Proxy
{


	/*!
	** \brief Proxy event (with no parameter)
	*/
	template<typename R>
	class P0
	{
	public:
		typedef Event::E0<R> EventType;
	public:
		P0() : pProxy(NULL) {}
		virtual ~P0() {disconnectAll();}

		void assign(EventType* p) {pProxy = p;}

		template<class C> void connect(C* cl, void (C::*fn)(void))
		{if (pProxy) pProxy->connect(cl, fn);}

		void disconnect(const void* cl, const bool broadcast = true)
		{if (pProxy) pProxy->disconnect(cl, broadcast);}

		void disconnectAll()
		{if (pProxy) pProxy->disconnectAll();}

		void operator () ()
		{if (pProxy) (*pProxy)();}

	private:
		EventType* pProxy;
	};


	/*!
	** \brief Proxy event (with 1 parameter)
	*/
	template<typename R, typename T1>
	class P1
	{
	public:
		typedef typename Event::E1<R, T1> EventType;
	public:
		P1() : pProxy(NULL) {}
		virtual ~P1() {disconnectAll();}

		void assign(EventType* p) {pProxy = p;}

		template<class C> void connect(C* cl, void (C::*fn)(T1))
		{if (pProxy) pProxy->connect(cl, fn);}

		void disconnect(const void* cl, const bool broadcast = true)
		{if (pProxy) pProxy->disconnect(cl, broadcast);}

		void disconnectAll()
		{if (pProxy) pProxy->disconnectAll();}

		void operator () (T1 a1)
		{if (pProxy) (*pProxy)(a1);}

	private:
		EventType* pProxy;
	};


	/*!
	** \brief Proxy event (with 2 parameter)
	*/
	template<typename R, typename T1, typename T2>
	class P2
	{
	public:
		typedef typename Event::E2<R, T1, T2> EventType;
	public:
		P2() : pProxy(NULL) {}
		virtual ~P2() {disconnectAll();}

		void assign(EventType* p) {pProxy = p;}

		template<class C> void connect(C* cl, void (C::*fn)(T1, T2))
		{if (pProxy) pProxy->connect(cl, fn);}

		void disconnect(const void* cl, const bool broadcast = true)
		{if (pProxy) pProxy->disconnect(cl, broadcast);}

		void disconnectAll()
		{if (pProxy) pProxy->disconnectAll();}

		void operator () (T1 a1, T2 a2)
		{if (pProxy) (*pProxy)(a1, a2);}

	private:
		EventType* pProxy;
	};


	/*!
	** \brief Proxy event (with 3 parameter)
	*/
	template<typename R, typename T1, typename T2, typename T3>
	class P3
	{
	public:
		typedef typename Event::E3<R, T1, T2, T3> EventType;
	public:
		P3() : pProxy(NULL) {}
		virtual ~P3() {disconnectAll();}

		void assign(EventType* p) {pProxy = p;}

		template<class C> void connect(C* cl, void (C::*fn)(T1, T2, T3))
		{if (pProxy) pProxy->connect(cl, fn);}

		void disconnect(const void* cl, const bool broadcast = true)
		{if (pProxy) pProxy->disconnect(cl, broadcast);}

		void disconnectAll()
		{if (pProxy) pProxy->disconnectAll();}

		void operator () (T1 a1, T2 a2, T3 a3)
		{if (pProxy) (*pProxy)(a1, a2, a3);}

	private:
		EventType* pProxy;
	};



	/*!
	** \brief Proxy event (with 4 parameter)
	*/
	template<typename R, typename T1, typename T2, typename T3, typename T4>
	class P4
	{
	public:
		typedef typename Event::E4<R, T1, T2, T3, T4> EventType;
	public:
		P4() : pProxy(NULL) {}
		virtual ~P4() {disconnectAll();}

		void assign(EventType* p) {pProxy = p;}

		template<class C> void connect(C* cl, void (C::*fn)(T1, T2, T3, T4))
		{if (pProxy) pProxy->connect(cl, fn);}

		void disconnect(const void* cl, const bool broadcast = true)
		{if (pProxy) pProxy->disconnect(cl, broadcast);}

		void disconnectAll()
		{if (pProxy) pProxy->disconnectAll();}

		void operator () (T1 a1, T2 a2, T3 a3, T4 a4)
		{if (pProxy) (*pProxy)(a1, a2, a3, a4);}

	private:
		EventType* pProxy;
	};


	/*!
	** \brief Proxy event (with 5 parameter)
	*/
	template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
	class P5
	{
	public:
		typedef typename Event::E5<R, T1, T2, T3, T4, T5> EventType;
	public:
		P5() : pProxy(NULL) {}
		virtual ~P5() {disconnectAll();}

		void assign(EventType* p) {pProxy = p;}

		template<class C> void connect(C* cl, void (C::*fn)(T1, T2, T3, T4, T5))
		{if (pProxy) pProxy->connect(cl, fn);}

		void disconnect(const void* cl, const bool broadcast = true)
		{if (pProxy) pProxy->disconnect(cl, broadcast);}

		void disconnectAll()
		{if (pProxy) pProxy->disconnectAll();}

		void operator () (T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
		{if (pProxy) (*pProxy)(a1, a2, a3, a4, a5);}

	private:
		EventType* pProxy;
	};


	/*!
	** \brief Proxy event (with 6 parameter)
	*/
	template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	class P6
	{
	public:
		typedef typename Event::E6<R, T1, T2, T3, T4, T5, T6> EventType;
	public:
		P6() : pProxy(NULL) {}
		virtual ~P6() {disconnectAll();}

		void assign(EventType* p) {pProxy = p;}

		template<class C> void connect(C* cl, void (C::*fn)(T1, T2, T3, T4, T5, T6))
		{if (pProxy) pProxy->connect(cl, fn);}

		void disconnect(const void* cl, const bool broadcast = true)
		{if (pProxy) pProxy->disconnect(cl, broadcast);}

		void disconnectAll()
		{if (pProxy) pProxy->disconnectAll();}

		void operator () (T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
		{if (pProxy) (*pProxy)(a1, a2, a3, a4, a5, a6);}

	private:
		EventType* pProxy;
	};



	/*!
	** \brief Proxy event (with 7 parameter)
	*/
	template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	class P7
	{
	public:
		typedef typename Event::E7<R, T1, T2, T3, T4, T5, T6, T7> EventType;
	public:
		P7() : pProxy(NULL) {}
		virtual ~P7() {disconnectAll();}

		void assign(EventType* p) {pProxy = p;}

		template<class C> void connect(C* cl, void (C::*fn)(T1, T2, T3, T4, T5, T6, T7))
		{if (pProxy) pProxy->connect(cl, fn);}

		void disconnect(const void* cl, const bool broadcast = true)
		{if (pProxy) pProxy->disconnect(cl, broadcast);}

		void disconnectAll()
		{if (pProxy) pProxy->disconnectAll();}

		void operator () (T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7)
		{if (pProxy) (*pProxy)(a1, a2, a3, a4, a5, a6, a7);}

	private:
		EventType* pProxy;
	};


	/*!
	** \brief Proxy event (with 8 parameter)
	*/
	template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	class P8
	{
	public:
		typedef typename Event::E8<R, T1, T2, T3, T4, T5, T6, T7, T8> EventType;
	public:
		P8() : pProxy(NULL) {}
		virtual ~P8() {disconnectAll();}

		void assign(EventType* p) {pProxy = p;}

		template<class C> void connect(C* cl, void (C::*fn)(T1, T2, T3, T4, T5, T6, T7, T8))
		{if (pProxy) pProxy->connect(cl, fn);}

		void disconnect(const void* cl, const bool broadcast = true)
		{if (pProxy) pProxy->disconnect(cl, broadcast);}

		void disconnectAll()
		{if (pProxy) pProxy->disconnectAll();}

		void operator () (T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8)
		{if (pProxy) (*pProxy)(a1, a2, a3, a4, a5, a6, a7, a8);}

	private:
		EventType* pProxy;
	};



} // namespace Proxy
} // namespace Event
} // namespace Yuni


#endif // __YUNI_TOOLBOX_EVENT_PROXY_H__
