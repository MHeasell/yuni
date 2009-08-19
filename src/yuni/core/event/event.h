#ifndef __YUNI_CORE_EVENT_EVENT_H__
# define __YUNI_CORE_EVENT_EVENT_H__

# include "interfaces.h"
# include "../bind.h"
# include "../smartptr.h"
# include "traits.h"


namespace Yuni
{



	/*!
	** \brief Event
	*/
	template<typename P = void ()>
	class Event :
		public IEvent,                                  // base class IEvent
		public Private::EventImpl::WithNArguments<Bind<P>::argumentCount, Bind<P> >
	{
	public:
		//! Event
		typedef Event<P> EventType;
		//! The Bind Type
		typedef Bind<P> BindType;
		//! Type of the Ancestor
		typedef typename Private::EventImpl::template WithNArguments<BindType::argumentCount, BindType> AncestorType;

		//! The Threading Policy
		typedef typename AncestorType::ThreadingPolicy ThreadingPolicy;
		//! The most suitable smartptr for the class
		typedef SmartPtr<Event> Ptr;

		//! Pointer-to-function
		typedef typename BindType::FunctionType FunctionType;
		/*!
		** \brief Pointer-to-member of any Class
		** \tparam C Any class
		*/
		template<class C>
		struct PointerToMember
		{
			//! Mere type for C
			typedef typename BindType::template PointerToMember<C>::Class Class;
			//! Type for a pointer-to-member
			typedef typename BindType::template PointerToMember<C>::Type Type;
			//! Type for a const pointer-to-member
			typedef typename BindType::template PointerToMember<C>::ConstType ConstType;
		};
		enum
		{
			//! The number of arguments
			argumentCount = BindType::argumentCount,
		};
		enum
		{
			//! A non-zero value if the prototype has a return value (!= void)
			hasReturnValue = BindType::hasReturnValue,
		};

		//! The type of the return value
		typedef typename BindType::ReturnType ReturnType;

		/*!
		** \brief Type of each argument by their index
		**
		** The typedef Type is always valid, even if the argument does not exist.
		** If this case, the type will be the empty class Yuni::None. You may
		** use `argumentCount` to know exactly the number of arguments.
		** \tparam I Index of the argument (zero-based)
		*/
		template<int I>
		struct Argument
		{
			//! Type of the argument at position I (zero-based)
			typedef typename BindType::template Argument<I>::Type Type;
		};


	public:
		//! name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		Event();
		/*!
		** \brief Copy constructor
		*/
		Event(const Event& rhs);
		//! Destructor
		virtual ~Event();
		//@}


		//! \name Connection
		//@{
		/*!
		** \brief Connect to a function
		**
		** \param pointer Pointer-to-function
		*/
		void connect(typename BindType::FunctionType pointer);

		/*!
		** \brief Connect to a function with a custom user data
		**
		** \param pointer Pointer-to-function
		** \param userdata The userdata to copy and store
		*/
		template<class U>
		void connect(typename BindType::template WithUserData<U>::FunctionType pointer,
			typename BindType::template WithUserData<U>::ParameterType userdata);

		/*!
		** \brief Connect to a object member
		**
		** \param o An object, with IEventObserverBase as ancestor
		** \param method Pointer-to-member
		*/
		template<class C> void connect(C* o, typename PointerToMember<C>::Type method);
		template<class C> void connect(const C* o, typename PointerToMember<C>::ConstType method);

		/*!
		** \brief Connect directly with a Bind
		**
		** This method might be useful to create a new connection without any check
		*/
		void connect(const BindType& custom);
		//@}


		//! \name Disconnection
		//@{
		/*!
		** \brief Disconnect all
		*/
		void clear();

		/*!
		** \brief
		*/
		template<class U> void remove(const U* object);
		//@}


		//! \name Misc
		//@{
		//! Get the number of current connections
		unsigned int size() const;
		//! \see size()
		unsigned int count() const;

		//! Get if the event does not have any single connection
		bool empty() const;
		//@}

		//[!] \name Invoke (documentation imported from the class WithNArguments)
		//@{
		// ReturnType invoke(<parameters>) const;
		// ReturnType operator () (<parameters>) const;
		//@}

		//! \name Operators
		//@{
		//! Assignment with a nullptr (equivalent to clear())
		Event& operator = (const NullPtr*);
		//! Assignment with a nullptr (equivalent to clear())
		Event& operator = (const NullPtr&);
		//! Copy operator
		Event& operator = (const Event& rhs);
		//@}

	protected:
		/*virtual*/ bool unregisterObserver(const IEventObserverBase* pointer);

	}; // class Event




} // namespace Yuni

# include "event.hxx"

#endif // __YUNI_CORE_EVENT_EVENT_H__
