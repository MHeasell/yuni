#ifndef __YUNI_CORE_BIND_BIND_H__
# define __YUNI_CORE_BIND_BIND_H__

# include "../../yuni.h"
# include "../../threads/policy.h"
# include "../static/types.h"
# include "../static/assert.h"
# include "../static/remove.h"
# include "../smartptr.h"
# include "traits.h"

<%
require '../../../tools/generators/commons.rb'
generator = Generator.new()
%>
<%=generator.thisHeaderHasBeenGenerated("bind.h.generator.hpp")%>


namespace Yuni
{


	/*!
	** \brief A delegate implementation
	**
	** How to bind a mere function :
	** \code
	** #include <iostream>
	** #include <yuni/bind.h>
	**
	** static int Foo(int value)
	** {
	** 	std::cout << "Foo: " << value << std::endl;
	** 	return 0;
	** }
	**
	** int main()
	** {
	** 	Yuni::Bind<int (int)> callback;
	** 	callback.bind(&Foo);
	** 	callback(42);
	** 	callback(61);
	** 	callback(-1)
	** 	return 0;
	** }
	** \endcode
	**
	** How to bind a member of an object :
	** \code
	** #include <iostream>
	** #include <yuni/bind.h>
	**
	** class Foo
	** {
	** public:
	**	int bar(int value)
	**	{
	** 		std::cout << "Foo::bar  : " << value << std::endl;
	** 		return 0;
	**	}
	**	int bar2(int value)
	**	{
	** 		std::cout << "Foo::bar2 : " << value << std::endl;
	** 		return 0;
	**	}
	** };
	**
	** int main()
	** {
	**	Foo foo;
	** 	Yuni::Bind<int (int)> callback;
	** 	callback.bind(foo, &Foo::bar);
	** 	callback(42);
	** 	callback(61);
	** 	callback(-1)
	** 	callback.bind(foo, &Foo::bar2);
	** 	callback(42);
	** 	callback(61);
	** 	callback(-1)
	** 	return 0;
	** }
	** \endcode
	**
	** This class is thread-safe, this is guarantee by the use of smartptr.
	**
	** \note This class does not take care of deleted objects. It is the responsibility
	** to the user to unbind the delegate before the linked object is delete and/or
	** to not invoke the delegate when the object does not exist.
	**
	** \note It is safe to provide a null pointer when binding the delegate
	** \note It is always safe to invoke the delegate when unbound.
	**
	** \tparam P The prototype of the targetted function/member
	*/
	template<typename P = void ()>
	class Bind
	{
		// We must use one the specialization (see below)
		YUNI_STATIC_ASSERT(false, Bind_BadFunctionOrMemberSignature);
	};



<% (0..generator.argumentCount).each do |i| %>

	/*!
	** \brief Bind to a function/member with <%=generator.xArgumentsToStr(i)%> (Specialization)
	**
	** This class is thread-safe, this is guarantee by the use of smartptr.
	**
	** \tparam R The return Type
<%= generator.templateParameterListDoxygen(i)%>
	*/
	template<class R<%=generator.templateParameterList(i) %>>
	class Bind<R (<%=generator.list(i)%>)>
	{
	public:
		//! The Bind Type
		typedef Bind<R(<%=generator.list(i)%>)> Type;
		//! The Bind Type
		typedef Bind<R(<%=generator.list(i)%>)> BindType;
		//! The most suitable smartptr for the class
		typedef SmartPtr<BindType> Ptr;

		//! Pointer-to-function
		typedef R (*FunctionType)(<%=generator.list(i)%>);
		/*!
		** \brief Pointer-to-member of any Class
		** \tparam C Any class
		*/
		template<class C>
		struct PointerToMember
		{
			//! Type for a pointer-to-member
			typedef R (C::*Type)(<%=generator.list(i)%>);
		};
		enum
		{
			//! The number of arguments
			argumentCount = <%=i%>,
		};
		enum
		{
			//! A non-zero value if the prototype has a return value (!= void)
			hasReturnValue = Static::Type::StrictlyEqual<R,void>::No,
		};

		//! The type of the return value
		typedef R ReturnType;
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
			typedef typename Private::BindImpl::Argument<R(<%=generator.list(i)%>),I>::Type Type;
		};

		/*!
		** \brief Types when an additional user data is present
		*/
		template<class U>
		struct WithUserData
		{
			//! The most suitable type as a parameter
			typedef typename Private::BindImpl::Parameter<U>::Type ParameterType;

			enum
			{
				//! The number of arguments
				argumentCount = <%=i%> + 1, // original count + userdata
			};
			//! A pointer-to-function
			typedef R (*FunctionType)(<%=generator.list(i,'A', "", ", ")%>U);

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
				//! Type of the argument at position I
				typedef typename Private::BindImpl::Argument<R(<%=generator.list(i,'A', "", ", ")%>U),I>::Type Type;
			};
		}; // class WithUserData


	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		Bind();
		/*!
		** \brief Copy constructor
		*/
		Bind(const Bind& rhs);
		/*!
		** \brief Destructor
		*/
		~Bind();
		//@}

		//! \name Bind
		//@{
		/*!
		** \brief Bind to a function
		**
		** \param pointer A pointer-to-function
		*/
		void bind(R (*pointer)(<%=generator.list(i)%>));


		/*!
		** \brief Bind to a function with a custom and persistent user data
		**
		** \tparam U The type of the user data
		** \param pointer A pointer-to-function
		** \param userdata The userdata that will be copied and stored
		*/
		template<class U>
		void bind(R (*pointer)(<%=generator.list(i,'A', "", ", ")%>U), typename WithUserData<U>::ParameterType userdata);

		/*!
		** \brief Bind to an object member
		**
		** \tparam C Any class
		** \param c A pointer to an object (can be null)
		** \param member A pointer-to-member
		*/
		template<class C> void bind(C* c, R (C::*member)(<%=generator.list(i)%>));
		template<class C> void bind(C& c, R (C::*member)(<%=generator.list(i)%>));

		/*!
		** \brief Bind to an object member
		**
		** \tparam C Any smartptr
		** \param c A pointer to an object (can be null)
		** \param member A pointer-to-member
		*/
		template<class C,
			template <class> class OwspP, template <class> class ChckP, class ConvP,
			template <class> class StorP, template <class> class ConsP>
		void bind(const SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP> c, R (C::*member)(<%=generator.list(i)%>));
		template<class C,
			template <class> class OwspP, template <class> class ChckP, class ConvP,
			template <class> class StorP, template <class> class ConsP>
		void bind(const SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP> c, R (C::*member)(<%=generator.list(i)%>) const);

		/*!
		** \brief Bind to a const object member
		**
		** \tparam C Any class
		** \param c A pointer to an object (can be null)
		** \param member A pointer-to-member
		*/
		template<class C> void bind(const C* c, R (C::*member)(<%=generator.list(i)%>) const);
		template<class C> void bind(const C& c, R (C::*member)(<%=generator.list(i)%>) const);


		/*!
		** \brief Bind to an object member with a custom and persistent user data
		**
		** \tparam U The type of the user data
		** \tparam C Any class
		** \param c A pointer to an object (can be null)
		** \param member A pointer-to-member
		*/
		template<class U, class C>
		void bind(C* c, R (C::*member)(<%=generator.list(i,'A', "", ", ")%>U), typename WithUserData<U>::ParameterType userdata);
		template<class U, class C>
		void bind(C& c, R (C::*member)(<%=generator.list(i,'A', "", ", ")%>U), typename WithUserData<U>::ParameterType userdata);
		template<class U, class C>
		void bind(const C* c, R (C::*member)(<%=generator.list(i,'A', "", ", ")%>U) const, typename WithUserData<U>::ParameterType userdata);
		template<class U, class C>
		void bind(const C& c, R (C::*member)(<%=generator.list(i,'A', "", ", ")%>U) const, typename WithUserData<U>::ParameterType userdata);

		/*!
		** \brief Bind to an object member with a custom and persistent user data
		**
		** \tparam C Any smartptr
		** \param c A pointer to an object (can be null)
		** \param member A pointer-to-member
		*/
		template<class U, class C,
			template <class> class OwspP, template <class> class ChckP, class ConvP,
			template <class> class StorP, template <class> class ConsP>
		void bind(const SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP> c, R (C::*member)(<%=generator.list(i)%>),
			typename WithUserData<U>::ParameterType userdata);
		template<class U, class C,
			template <class> class OwspP, template <class> class ChckP, class ConvP,
			template <class> class StorP, template <class> class ConsP>
		void bind(const SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP> c, R (C::*member)(<%=generator.list(i)%>) const,
			typename WithUserData<U>::ParameterType userdata);


		/*!
		** \brief Bind from another Bind object
		*/
		void bind(const Bind& rhs);
		//@} // Bind

		//! \name Unbind
		//@{
		/*!
		** \brief Unbind
		**
		** It is safe to call this method several times
		*/
		void unbind();

		//! \see unbind
		void clear();
		//@}

		//! \name Invoke
		//@{
		/*!
		** \brief Invoke the delegate
		*/
		R execute(<%=generator.variableList(i)%>) const;

		/*!
		** \brief Invoke the delegate
		*/
		R operator () (<%=generator.variableList(i)%>) const;
		//@}

		//! \name Operators
		//@{
		//! Assignment with another Bind object
		Bind& operator = (const Bind& rhs);
		//! Assignment with a pointer-to-function
		Bind& operator = (R (*pointer)(<%=generator.list(i)%>));
		//! Assignment with a nullptr (equivalent to unbind)
		Bind& operator = (const NullPtr*);
		//! Assignment with a nullptr (equivalent to unbind)
		Bind& operator = (const NullPtr&);
		//@}

	private:
		//! Empty callback when not binded (returns a default value)
		R emptyCallback(<%=generator.list(i)%>);
		//! Empty callback when not binded (returns void)
		void emptyCallbackReturnsVoid(<%=generator.list(i)%>);

	private:
		//! The holder type
		typedef Private::BindImpl::IPointer<R(<%=generator.list(i)%>)> IHolder;

		/*!
		** \brief Pointer to function/member
		** \internal The smartptr is used to guarantee the thread-safety, and to avoid
		** expensive copies
		*/
		SmartPtr<IHolder> pHolder;

		// A friend !
		template<class R1, class B1> friend class Private::BindImpl::Unbind;

	}; // class Bind<R(<%=generator.list(i,'A')%>)>




<% end %>






} // namespace Yuni

# include "bind.hxx"

#endif // __YUNI_CORE_BIND_BIND_H__
