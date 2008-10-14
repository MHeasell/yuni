#ifndef __YUNI_MISC_EVENTS_H__
# define __YUNI_MISC_EVENTS_H__

# include "../yuni.h"
# include <algorithm>
# include <list>
# include <set>
# include "sharedptr.h"
# include "../policies/threading.h"



namespace Yuni
{
namespace Event
{

	enum EmitMode
	{
		emImmediate = 0,
		emDeferred
	};


	/*!
	** \brief Base class for Notifiers
	*/
	class Notifier : public Policy::ObjectLevelLockable<Notifier>
	{
	public:
		//! \name Constructor & Destructor
		//@{

		//! Default constructor
		Notifier()
			:Policy::ObjectLevelLockable<Notifier>(), pBroadcastDisconnection(true)
		{}
		
		//! Destructor
		virtual ~Notifier() {}

		//@}
		
		virtual void disconnect(const void* cl, const bool broadcast = true) = 0;

		/*!
		** \brief Get if the information can be broacasted
		*/
		bool isDisconnectionBroadcastAllowed() const {return pBroadcastDisconnection;}

	protected:
		bool pBroadcastDisconnection;

	}; // class Notifier



	/*!
	** \brief Provide the ability to receive events
	*/
	class Receiver : public Policy::ObjectLevelLockable<Receiver>
	{
	public:
		//! \name Constructor & Destructor
		//@{
		//! Constructor
		Receiver() :Policy::ObjectLevelLockable<Receiver>() {}
		//! Destructor
		virtual ~Receiver() {disconnectAllNotifiers();}
		//@}

		/*!
		** \brief Connect a notifier to this class
		*/
		void connectEventNotifier(Notifier* n);

		/*!
		** \brief Disconnect a notifier to this class
		*/
		void disconnectEventNotifier(Notifier* n);

		/*!
		** \brief Disconnect all notifiers
		*/
		void disconnectAllNotifiers();

	protected:
		/*!
		** \brief Disconnect all notifiers (thread-unsafe)
		*/
		void disconnectAllNotifiersWL();

	private:
		//! All notifiers
		std::set<Notifier*> pNotifiers;

	}; // class Receiver




} // namespace Event
} // namespace Yuni




# include "event.private.h"




namespace Yuni
{
namespace Event
{

	/*!
	** \brief Event (with no parameter)
	*/
	class E0 : public Notifier
	{
	private:
		typedef std::list< SharedPtr< Private::Events::It0 > >  ReceiverList;

	public:
		//! \name Constructor & Destructor
		//@{
		//! Constructor
		E0() :Notifier() {}
		//! Destructor
		virtual ~E0() {disconnectAll();}
		//@}

		/*!
		** \brief Connect a new receiver
		**
		** \param[in] cl
		** \param[in] fn
		*/
		template<class C> void connect(C* cl, void (C::*fn)(void))
		{
			// assert((dynamic_cast<Receiver*>(cl) == true));
			pMutex.lock();
			if (cl)
			{
				pReceiverList.push_back(new Private::Events::ItTmpl0<C>(this, cl, fn));
				(static_cast<Receiver*>(cl))->connectEventNotifier(this);
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect a receiver
		**
		** \param cl The object to disconnect
		** \param broadcast Broadcast the disconnection when destroyed
		*/
		virtual void disconnect(const void* cl, const bool broadcast = true)
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				pBroadcastDisconnection = broadcast;
				pReceiverList.erase(std::remove_if(pReceiverList.begin(), pReceiverList.end(),
					Private::Events::RemoveIfIt0(cl) ), 
					pReceiverList.end());
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect all receivers
		*/
		void disconnectAll()
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				ReceiverList copy(pReceiverList);
				pReceiverList.clear();
				pBroadcastDisconnection = true;
				pMutex.unlock();
				// Remove an item in the list will call the method `disconnect()`
				copy.clear();
				return;
			}
			pMutex.unlock();
		}


		/*!
		** \brief Emit an event for all receivers
		*/
		void operator () (const EmitMode em = emImmediate)
		{
			pMutex.lock();
			for (ReceiverList::iterator i = pReceiverList.begin(); i != pReceiverList.end(); ++i)
				(*i)->emit(em);
			pMutex.unlock();
		}

	private:
		//! All connected receivers
		ReceiverList pReceiverList;

	}; // class E0



	/*!
	** \brief Event (with 1 parameters)
	*/
	template<typename T1>
	class E1 : public Notifier
	{
	private:
		typedef typename std::list< SharedPtr< Private::Events::It1<T1> > >  ReceiverList;

	public:
		//! \name Constructor & Destructor
		//@{
		//! Constructor
		E1() :Notifier() {}
		//! Destructor
		virtual ~E1() {disconnectAll();}
		//@}

		/*!
		** \brief Connect a new receiver
		**
		** \param[in] cl
		** \param[in] fn
		*/
		template<class C> void connect(C* cl, void (C::*fn)(T1))
		{
			// assert((dynamic_cast<Receiver*>(cl) == true));
			pMutex.lock();
			if (cl)
			{
				pReceiverList.push_back(new Private::Events::ItTmpl1<C, T1>(this, cl, fn));
				(static_cast<Receiver*>(cl))->connectEventNotifier(this);
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect a receiver
		**
		** \param cl The object to disconnect
		** \param broadcast Broadcast the disconnection when destroyed
		*/
		virtual void disconnect(const void* cl, const bool broadcast = true)
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				pBroadcastDisconnection = broadcast;
				pReceiverList.erase(std::remove_if(pReceiverList.begin(), pReceiverList.end(),
					Private::Events::RemoveIfIt1<T1>(cl) ), 
					pReceiverList.end());
			}
			pMutex.unlock();
		}


		/*!
		** \brief Disconnect all receivers
		*/
		void disconnectAll()
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				ReceiverList copy(pReceiverList);
				pReceiverList.clear();
				pBroadcastDisconnection = true;
				pMutex.unlock();
				// Remove an item in the list will call the method `disconnect()`
				copy.clear();
				return;
			}
			pMutex.unlock();
		}


		/*!
		** \brief Emit an event for all receivers
		*/
		void operator () (T1 a1, const EmitMode em = emImmediate)
		{
			pMutex.lock();
			for (typename ReceiverList::iterator i = pReceiverList.begin(); i != pReceiverList.end(); ++i)
				(*i)->emit(a1, em);
			pMutex.unlock();
		}

	private:
		//! All connected receivers
		ReceiverList pReceiverList;

	}; // class E1




	/*!
	** \brief Event (with 2 parameters)
	*/
	template<typename T1, typename T2>
	class E2 : public Notifier
	{
	private:
		typedef typename std::list< SharedPtr< Private::Events::It2<T1, T2> > >  ReceiverList;

	public:
		//! \name Constructor & Destructor
		//@{
		//! Constructor
		E2() :Notifier() {}
		//! Destructor
		virtual ~E2() {disconnectAll();}
		//@}

		/*!
		** \brief Connect a new receiver
		**
		** \param[in] cl
		** \param[in] fn
		*/
		template<class C> void connect(C* cl, void (C::*fn)(T1, T2))
		{
			// assert((dynamic_cast<Receiver*>(cl) == true));
			pMutex.lock();
			if (cl)
			{
				pReceiverList.push_back(new Private::Events::ItTmpl2<C, T1, T2>(this, cl, fn));
				(static_cast<Receiver*>(cl))->connectEventNotifier(this);
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect a receiver
		**
		** \param cl The object to disconnect
		** \param broadcast Broadcast the disconnection when destroyed
		*/
		virtual void disconnect(const void* cl, const bool broadcast = true)
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				pBroadcastDisconnection = broadcast;
				pReceiverList.erase(std::remove_if(pReceiverList.begin(), pReceiverList.end(),
					Private::Events::RemoveIfIt2<T1, T2>(cl) ), 
					pReceiverList.end());
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect all receivers
		*/
		void disconnectAll()
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				ReceiverList copy(pReceiverList);
				pReceiverList.clear();
				pBroadcastDisconnection = true;
				pMutex.unlock();
				// Remove an item in the list will call the method `disconnect()`
				copy.clear();
				return;
			}
			pMutex.unlock();
		}


		/*!
		** \brief Emit an event for all receivers
		*/
		void operator () (T1 a1, T2 a2, const EmitMode em = emImmediate)
		{
			pMutex.lock();
			for (typename ReceiverList::iterator i = pReceiverList.begin(); i != pReceiverList.end(); ++i)
				(*i)->emit(a1, a2, em);
			pMutex.unlock();
		}

	private:
		//! All connected receivers
		ReceiverList pReceiverList;

	}; // class E2



	/*!
	** \brief Event (with 3 parameters)
	*/
	template<typename T1, typename T2, typename T3>
	class E3 : public Notifier
	{
	private:
		typedef typename std::list< SharedPtr< Private::Events::It3<T1, T2, T3> > >  ReceiverList;

	public:
		//! \name Constructor & Destructor
		//@{
		//! Constructor
		E3() :Notifier() {}
		//! Destructor
		virtual ~E3() {disconnectAll();}
		//@}

		/*!
		** \brief Connect a new receiver
		**
		** \param[in] cl
		** \param[in] fn
		*/
		template<class C> void connect(C* cl, void (C::*fn)(T1, T2, T3))
		{
			// assert((dynamic_cast<Receiver*>(cl) == true));
			pMutex.lock();
			if (cl)
			{
				pReceiverList.push_back(new Private::Events::ItTmpl3<C, T1, T2, T3>(this, cl, fn));
				(static_cast<Receiver*>(cl))->connectEventNotifier(this);
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect a receiver
		**
		** \param cl The object to disconnect
		** \param broadcast Broadcast the disconnection when destroyed
		*/
		virtual void disconnect(const void* cl, const bool broadcast = true)
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				pBroadcastDisconnection = broadcast;
				pReceiverList.erase(std::remove_if(pReceiverList.begin(), pReceiverList.end(),
					Private::Events::RemoveIfIt3<T1, T2, T3>(cl) ), 
					pReceiverList.end());
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect all receivers
		*/
		void disconnectAll()
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				ReceiverList copy(pReceiverList);
				pReceiverList.clear();
				pBroadcastDisconnection = true;
				pMutex.unlock();
				// Remove an item in the list will call the method `disconnect()`
				copy.clear();
				return;
			}
			pMutex.unlock();
		}


		/*!
		** \brief Emit an event for all receivers
		*/
		void operator () (T1 a1, T2 a2, T3 a3, const EmitMode em = emImmediate)
		{
			pMutex.lock();
			for (typename ReceiverList::iterator i = pReceiverList.begin(); i != pReceiverList.end(); ++i)
				(*i)->emit(a1, a2, a3, em);
			pMutex.unlock();
		}

	private:
		//! All connected receivers
		ReceiverList pReceiverList;

	}; // class E3



	/*!
	** \brief Event (with 4 parameters)
	*/
	template<typename T1, typename T2, typename T3, typename T4>
	class E4 : public Notifier
	{
	private:
		typedef typename std::list< SharedPtr< Private::Events::It4<T1, T2, T3, T4> > >  ReceiverList;

	public:
		//! \name Constructor & Destructor
		//@{
		//! Constructor
		E4() :Notifier() {}
		//! Destructor
		virtual ~E4() {disconnectAll();}
		//@}

		/*!
		** \brief Connect a new receiver
		**
		** \param[in] cl
		** \param[in] fn
		*/
		template<class C> void connect(C* cl, void (C::*fn)(T1, T2, T3, T4))
		{
			// assert((dynamic_cast<Receiver*>(cl) == true));
			pMutex.lock();
			if (cl)
			{
				pReceiverList.push_back(new Private::Events::ItTmpl4<C, T1, T2, T3, T4>(this, cl, fn));
				(static_cast<Receiver*>(cl))->connectEventNotifier(this);
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect a receiver
		**
		** \param cl The object to disconnect
		** \param broadcast Broadcast the disconnection when destroyed
		*/
		virtual void disconnect(const void* cl, const bool broadcast = true)
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				pBroadcastDisconnection = broadcast;
				pReceiverList.erase(std::remove_if(pReceiverList.begin(), pReceiverList.end(),
					Private::Events::RemoveIfIt4<T1, T2, T3, T4>(cl) ), 
					pReceiverList.end());
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect all receivers
		*/
		void disconnectAll()
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				ReceiverList copy(pReceiverList);
				pReceiverList.clear();
				pBroadcastDisconnection = true;
				pMutex.unlock();
				// Remove an item in the list will call the method `disconnect()`
				copy.clear();
				return;
			}
			pMutex.unlock();
		}


		/*!
		** \brief Emit an event for all receivers
		*/
		void operator () (T1 a1, T2 a2, T3 a3, T4 a4, const EmitMode em = emImmediate)
		{
			pMutex.lock();
			for (typename ReceiverList::iterator i = pReceiverList.begin(); i != pReceiverList.end(); ++i)
				(*i)->emit(a1, a2, a3, a4, em);
			pMutex.unlock();
		}

	private:
		//! All connected receivers
		ReceiverList pReceiverList;

	}; // class E4



	/*!
	** \brief Event (with 5 parameters)
	*/
	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	class E5 : public Notifier
	{
	private:
		typedef typename std::list< SharedPtr< Private::Events::It5<T1, T2, T3, T4, T5> > >  ReceiverList;

	public:
		//! \name Constructor & Destructor
		//@{
		//! Constructor
		E5() :Notifier() {}
		//! Destructor
		virtual ~E5() {disconnectAll();}
		//@}

		/*!
		** \brief Connect a new receiver
		**
		** \param[in] cl
		** \param[in] fn
		*/
		template<class C> void connect(C* cl, void (C::*fn)(T1, T2, T3, T4, T5))
		{
			// assert((dynamic_cast<Receiver*>(cl) == true));
			pMutex.lock();
			if (cl)
			{
				pReceiverList.push_back(new Private::Events::ItTmpl5<C, T1, T2, T3, T4, T5>(this, cl, fn));
				(static_cast<Receiver*>(cl))->connectEventNotifier(this);
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect a receiver
		**
		** \param cl The object to disconnect
		** \param broadcast Broadcast the disconnection when destroyed
		*/
		virtual void disconnect(const void* cl, const bool broadcast = true)
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				pBroadcastDisconnection = broadcast;
				pReceiverList.erase(std::remove_if(pReceiverList.begin(), pReceiverList.end(),
					Private::Events::RemoveIfIt5<T1, T2, T3, T4, T5>(cl) ), 
					pReceiverList.end());
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect all receivers
		*/
		void disconnectAll()
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				ReceiverList copy(pReceiverList);
				pReceiverList.clear();
				pBroadcastDisconnection = true;
				pMutex.unlock();
				// Remove an item in the list will call the method `disconnect()`
				copy.clear();
				return;
			}
			pMutex.unlock();
		}


		/*!
		** \brief Emit an event for all receivers
		*/
		void operator () (T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, const EmitMode em = emImmediate)
		{
			pMutex.lock();
			for (typename ReceiverList::iterator i = pReceiverList.begin(); i != pReceiverList.end(); ++i)
				(*i)->emit(a1, a2, a3, a4, a5, em);
			pMutex.unlock();
		}

	private:
		//! All connected receivers
		ReceiverList pReceiverList;

	}; // class E5



	/*!
	** \brief Event (with 6 parameters)
	*/
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	class E6 : public Notifier
	{
	private:
		typedef typename std::list< SharedPtr< Private::Events::It6<T1, T2, T3, T4, T5, T6> > >  ReceiverList;

	public:
		//! \name Constructor & Destructor
		//@{
		//! Constructor
		E6() :Notifier() {}
		//! Destructor
		virtual ~E6() {disconnectAll();}
		//@}

		/*!
		** \brief Connect a new receiver
		**
		** \param[in] cl
		** \param[in] fn
		*/
		template<class C> void connect(C* cl, void (C::*fn)(T1, T2, T3, T4, T5, T6))
		{
			// assert((dynamic_cast<Receiver*>(cl) == true));
			pMutex.lock();
			if (cl)
			{
				pReceiverList.push_back(new Private::Events::ItTmpl6<C, T1, T2, T3, T4, T5, T6>(this, cl, fn));
				(static_cast<Receiver*>(cl))->connectEventNotifier(this);
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect a receiver
		**
		** \param cl The object to disconnect
		** \param broadcast Broadcast the disconnection when destroyed
		*/
		virtual void disconnect(const void* cl, const bool broadcast = true)
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				pBroadcastDisconnection = broadcast;
				pReceiverList.erase(std::remove_if(pReceiverList.begin(), pReceiverList.end(),
					Private::Events::RemoveIfIt6<T1, T2, T3, T4, T5, T6>(cl) ), 
					pReceiverList.end());
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect all receivers
		*/
		void disconnectAll()
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				ReceiverList copy(pReceiverList);
				pReceiverList.clear();
				pBroadcastDisconnection = true;
				pMutex.unlock();
				// Remove an item in the list will call the method `disconnect()`
				copy.clear();
				return;
			}
			pMutex.unlock();
		}


		/*!
		** \brief Emit an event for all receivers
		*/
		void operator () (T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, const EmitMode em = emImmediate)
		{
			pMutex.lock();
			for (typename ReceiverList::iterator i = pReceiverList.begin(); i != pReceiverList.end(); ++i)
				(*i)->emit(a1, a2, a3, a4, a5, a6, em);
			pMutex.unlock();
		}

	private:
		//! All connected receivers
		ReceiverList pReceiverList;

	}; // class E6



	/*!
	** \brief Event (with 7 parameters)
	*/
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	class E7 : public Notifier
	{
	private:
		typedef typename std::list< SharedPtr< Private::Events::It7<T1, T2, T3, T4, T5, T6, T7> > >  ReceiverList;

	public:
		//! \name Constructor & Destructor
		//@{
		//! Constructor
		E7() :Notifier() {}
		//! Destructor
		virtual ~E7() {disconnectAll();}
		//@}

		/*!
		** \brief Connect a new receiver
		**
		** \param[in] cl
		** \param[in] fn
		*/
		template<class C> void connect(C* cl, void (C::*fn)(T1, T2, T3, T4, T5, T6, T7))
		{
			// assert((dynamic_cast<Receiver*>(cl) == true));
			pMutex.lock();
			if (cl)
			{
				pReceiverList.push_back(new Private::Events::ItTmpl7<C, T1, T2, T3, T4, T5, T6, T7>(this, cl, fn));
				(static_cast<Receiver*>(cl))->connectEventNotifier(this);
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect a receiver
		**
		** \param cl The object to disconnect
		** \param broadcast Broadcast the disconnection when destroyed
		*/
		virtual void disconnect(const void* cl, const bool broadcast = true)
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				pBroadcastDisconnection = broadcast;
				pReceiverList.erase(std::remove_if(pReceiverList.begin(), pReceiverList.end(),
					Private::Events::RemoveIfIt7<T1, T2, T3, T4, T5, T6, T7>(cl) ), 
					pReceiverList.end());
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect all receivers
		*/
		void disconnectAll()
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				ReceiverList copy(pReceiverList);
				pReceiverList.clear();
				pBroadcastDisconnection = true;
				pMutex.unlock();
				// Remove an item in the list will call the method `disconnect()`
				copy.clear();
				return;
			}
			pMutex.unlock();
		}


		/*!
		** \brief Emit an event for all receivers
		*/
		void operator () (T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, const EmitMode em = emImmediate)
		{
			pMutex.lock();
			for (typename ReceiverList::iterator i = pReceiverList.begin(); i != pReceiverList.end(); ++i)
				(*i)->emit(a1, a2, a3, a4, a5, a6, a7, em);
			pMutex.unlock();
		}

	private:
		//! All connected receivers
		ReceiverList pReceiverList;

	}; // class E7



	/*!
	** \brief Event (with 8 parameters)
	*/
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	class E8 : public Notifier
	{
	private:
		typedef typename std::list< SharedPtr< Private::Events::It8<T1, T2, T3, T4, T5, T6, T7, T8> > >  ReceiverList;

	public:
		//! \name Constructor & Destructor
		//@{
		//! Constructor
		E8() :Notifier() {}
		//! Destructor
		virtual ~E8() {disconnectAll();}
		//@}

		/*!
		** \brief Connect a new receiver
		**
		** \param[in] cl
		** \param[in] fn
		*/
		template<class C> void connect(C* cl, void (C::*fn)(T1, T2, T3, T4, T5, T6, T7, T8))
		{
			// assert((dynamic_cast<Receiver*>(cl) == true));
			pMutex.lock();
			if (cl)
			{
				pReceiverList.push_back(new Private::Events::ItTmpl8<C, T1, T2, T3, T4, T5, T6, T7, T8>(this, cl, fn));
				(static_cast<Receiver*>(cl))->connectEventNotifier(this);
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect a receiver
		**
		** \param cl The object to disconnect
		** \param broadcast Broadcast the disconnection when destroyed
		*/
		virtual void disconnect(const void* cl, const bool broadcast = true)
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				pBroadcastDisconnection = broadcast;
				pReceiverList.erase(std::remove_if(pReceiverList.begin(), pReceiverList.end(),
					Private::Events::RemoveIfIt8<T1, T2, T3, T4, T5, T6, T7, T8>(cl) ), 
					pReceiverList.end());
			}
			pMutex.unlock();
		}

		/*!
		** \brief Disconnect all receivers
		*/
		void disconnectAll()
		{
			pMutex.lock();
			if (!pReceiverList.empty())
			{
				ReceiverList copy(pReceiverList);
				pReceiverList.clear();
				pBroadcastDisconnection = true;
				pMutex.unlock();
				// Remove an item in the list will call the method `disconnect()`
				copy.clear();
				return;
			}
			pMutex.unlock();
		}


		/*!
		** \brief Emit an event for all receivers
		*/
		void operator () (T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8, const EmitMode em = emImmediate)
		{
			pMutex.lock();
			for (typename ReceiverList::iterator i = pReceiverList.begin(); i != pReceiverList.end(); ++i)
				(*i)->emit(a1, a2, a3, a4, a5, a6, a7, a8, em);
			pMutex.unlock();
		}

	private:
		//! All connected receivers
		ReceiverList pReceiverList;

	}; // class E8





} // namespace Event
} // namespace Yuni

#endif // __YUNI_MISC_EVENTS_H__
