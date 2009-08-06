#ifndef __YUNI_CORE_BIND_BIND_HXX__
# define __YUNI_CORE_BIND_BIND_HXX__

<%
require '../../../tools/generators/commons.rb'
generator = Generator.new()
%>
<%=generator.thisHeaderHasBeenGenerated("bind.hxx.generator.hpp")%>


namespace Yuni
{


<% (0..generator.argumentCount).each do |i| %>

	// Constructor
	template<class R<%=generator.templateParameterList(i) %>>
	inline Bind<R (<%=generator.list(i)%>)>::Bind()
	{
		Private::BindImpl::Unbind<R, BindType>::Execute(this);
	}

	// Constructor
	template<class R<%=generator.templateParameterList(i) %>>
	inline Bind<R (<%=generator.list(i)%>)>::Bind(const Bind<R (<%=generator.list(i)%>)>& rhs)
		:pHolder(rhs)
	{}



	// Destructor
	template<class R<%=generator.templateParameterList(i) %>>
	inline Bind<R (<%=generator.list(i)%>)>::~Bind()
	{}


	// Bind: Pointer-to-function
	template<class R<%=generator.templateParameterList(i) %>>
	inline void Bind<R (<%=generator.list(i)%>)>::bind(R (*pointer)(<%=generator.list(i)%>))
	{
		pHolder = new Private::BindImpl::BoundWithFunction<R (<%=generator.list(i)%>)>(pointer);
	}


	// Bind: Pointer-to-function + user data
	template<class R<%=generator.templateParameterList(i) %>>
	template<class U>
	inline void Bind<R (<%=generator.list(i)%>)>::bind(R (*pointer)(<%=generator.list(i, "A", "", ", ")%>U),
		typename Bind<R (<%=generator.list(i)%>)>::template WithUserData<U>::ParameterType userdata)
	{
		pHolder = new Private::BindImpl::BoundWithFunctionAndUserData
			<typename WithUserData<U>::ParameterType, R (<%=generator.list(i, "A", "", ", ")%>U)>(pointer, userdata);
	}



	// Bind: pointer-to-member
	template<class R<%=generator.templateParameterList(i) %>>
	template<class C>
	void Bind<R (<%=generator.list(i)%>)>::bind(C* c, R (C::*member)(<%=generator.list(i)%>))
	{
		if (c)
		{
			// The object is not null, go ahead
			// Assigning a new bind
			pHolder = new Private::BindImpl::BoundWithMember<C, R(<%=generator.list(i)%>)>(c, member);
		}
		else
			// The object is null, we should unbind
			unbind();
	}


	// Bind: pointer-to-member const
	template<class R<%=generator.templateParameterList(i) %>>
	template<class C>
	void Bind<R (<%=generator.list(i)%>)>::bind(const C* c, R (C::*member)(<%=generator.list(i)%>) const)
	{
		if (c)
		{
			// The object is not null, go ahead
			// Assigning a new bind
			typedef R (C::*MemberType)(<%=generator.list(i)%>);
			pHolder = new Private::BindImpl::BoundWithMember<C, R(<%=generator.list(i)%>)>
				(const_cast<C*>(c), reinterpret_cast<MemberType>(member));
		}
		else
			// The object is null, we should unbind
			unbind();
	}


	// Bind: pointer-to-member const
	template<class R<%=generator.templateParameterList(i) %>>
	template<class C,
		template <class> class OwspP, template <class> class ChckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline void
	Bind<R (<%=generator.list(i)%>)>::bind(const SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP> c, R (C::*member)(<%=generator.list(i)%>))
	{
		bind(SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP>::WeakPointer(c), member);
	}


	// Bind: pointer-to-member const
	template<class R<%=generator.templateParameterList(i) %>>
	template<class C,
		template <class> class OwspP, template <class> class ChckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline void
	Bind<R (<%=generator.list(i)%>)>::bind(const SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP> c, R (C::*member)(<%=generator.list(i)%>) const)
	{
		bind(SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP>::WeakPointer(c), member);
	}


	// Bind: pointer-to-member const
	template<class R<%=generator.templateParameterList(i) %>>
	template<class U, class C,
		template <class> class OwspP, template <class> class ChckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline void
	Bind<R (<%=generator.list(i)%>)>::bind(const SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP> c, R (C::*member)(<%=generator.list(i)%>),
		typename Bind<R (<%=generator.list(i)%>)>::template WithUserData<U>::ParameterType userdata)
	{
		bind(SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP>::WeakPointer(c), member, userdata);
	}


	// Bind: pointer-to-member const
	template<class R<%=generator.templateParameterList(i) %>>
	template<class U, class C,
		template <class> class OwspP, template <class> class ChckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline void
	Bind<R (<%=generator.list(i)%>)>::bind(const SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP> c, R (C::*member)(<%=generator.list(i)%>) const,
		typename Bind<R (<%=generator.list(i)%>)>::template WithUserData<U>::ParameterType userdata)
	{
		bind(SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP>::WeakPointer(c), member, userdata);
	}





	// Bind: pointer-to-member
	template<class R<%=generator.templateParameterList(i) %>>
	template<class C>
	void Bind<R (<%=generator.list(i)%>)>::bind(C& c, R (C::*member)(<%=generator.list(i)%>))
	{
		if (&c)
		{
			// The object is not null, go ahead
			// Assigning a new bind
			pHolder = new Private::BindImpl::BoundWithMember<C, R(<%=generator.list(i)%>)>(&c, member);
		}
		else
			// The object is null, we should unbind
			unbind();
	}


	// Bind: pointer-to-member const
	template<class R<%=generator.templateParameterList(i) %>>
	template<class C>
	void Bind<R (<%=generator.list(i)%>)>::bind(const C& c, R (C::*member)(<%=generator.list(i)%>) const)
	{
		if (&c)
		{
			// The object is not null, go ahead
			// Assigning a new bind
			typedef R (C::*MemberType)(<%=generator.list(i)%>);
			pHolder = new Private::BindImpl::BoundWithMember<C, R(<%=generator.list(i)%>)>
				(const_cast<C*>(&c), reinterpret_cast<MemberType>(member));
		}
		else
			// The object is null, we should unbind
			unbind();
	}





	template<class R<%=generator.templateParameterList(i) %>>
	template<class U, class C>
	void Bind<R (<%=generator.list(i)%>)>::bind(C* c, R (C::*member)(<%=generator.list(i,"A","",", ")%>U),
		typename Bind<R (<%=generator.list(i)%>)>::template WithUserData<U>::ParameterType userdata)
	{
		if (c)
		{
			// The object is not null, go ahead
			// Assigning a new bind
			pHolder = new Private::BindImpl::BoundWithMemberAndUserData<
				typename WithUserData<U>::ParameterType,C, R(<%=generator.list(i,"A","",", ")%>U)>
				(c, member, userdata);
		}
		else
			// The object is null, we should unbind
			unbind();
	}


	template<class R<%=generator.templateParameterList(i) %>>
	template<class U, class C>
	void Bind<R (<%=generator.list(i)%>)>::bind(C& c, R (C::*member)(<%=generator.list(i,"A","",", ")%>U),
		typename Bind<R (<%=generator.list(i)%>)>::template WithUserData<U>::ParameterType userdata)
	{
		if (&c)
		{
			// The object is not null, go ahead
			// Assigning a new bind
			pHolder = new Private::BindImpl::BoundWithMemberAndUserData<
				typename WithUserData<U>::ParameterType,C, R(<%=generator.list(i,"A","",", ")%>U)>
				(&c, member, userdata);
		}
		else
			// The object is null, we should unbind
			unbind();
	}



	template<class R<%=generator.templateParameterList(i) %>>
	template<class U, class C>
	void Bind<R (<%=generator.list(i)%>)>::bind(const C* c, R (C::*member)(<%=generator.list(i,"A","",", ")%>U) const,
		typename Bind<R (<%=generator.list(i)%>)>::template WithUserData<U>::ParameterType userdata)
	{
		if (c)
		{
			// The object is not null, go ahead
			// Assigning a new bind
			typedef R (C::*MemberType)(<%=generator.list(i,"A","",", ")%>U);
			pHolder = new Private::BindImpl::BoundWithMemberAndUserData<
				typename WithUserData<U>::ParameterType,C, R(<%=generator.list(i,"A","",", ")%>U)>
				(const_cast<C*>(c), reinterpret_cast<MemberType>(member), userdata);
		}
		else
			// The object is null, we should unbind
			unbind();
	}


	template<class R<%=generator.templateParameterList(i) %>>
	template<class U, class C>
	void Bind<R (<%=generator.list(i)%>)>::bind(const C& c, R (C::*member)(<%=generator.list(i,"A","",", ")%>U) const,
		typename Bind<R (<%=generator.list(i)%>)>::template WithUserData<U>::ParameterType userdata)
	{
		if (&c)
		{
			// The object is not null, go ahead
			// Assigning a new bind
			typedef R (C::*MemberType)(<%=generator.list(i,"A","",", ")%>U);
			pHolder = new Private::BindImpl::BoundWithMemberAndUserData<
				typename WithUserData<U>::ParameterType,C, R(<%=generator.list(i,"A","",", ")%>U)>
				(const_cast<C*>(&c), reinterpret_cast<MemberType>(member), userdata);
		}
		else
			// The object is null, we should unbind
			unbind();
	}


	template<class R<%=generator.templateParameterList(i) %>>
	inline void Bind<R (<%=generator.list(i)%>)>::bind(const Bind<R (<%=generator.list(i)%>)>& rhs)
	{
		// Inc the reference count
		pHolder = rhs.pHolder;
	}


	// Bind: unbind
	template<class R<%=generator.templateParameterList(i) %>>
	inline void Bind<R (<%=generator.list(i)%>)>::unbind()
	{
		Private::BindImpl::Unbind<R, BindType>::Execute(this);
	}


	// Bind: unbind
	template<class R<%=generator.templateParameterList(i) %>>
	inline void Bind<R (<%=generator.list(i)%>)>::clear()
	{
		Private::BindImpl::Unbind<R, BindType>::Execute(this);
	}





	template<class R<%=generator.templateParameterList(i) %>>
	inline R Bind<R (<%=generator.list(i)%>)>::execute(<%=generator.variableList(i)%>) const
	{
		return pHolder->execute(<%=generator.list(i,'a')%>);
	}


	template<class R<%=generator.templateParameterList(i) %>>
	inline R Bind<R (<%=generator.list(i)%>)>::operator () (<%=generator.variableList(i)%>) const
	{
		return pHolder->execute(<%=generator.list(i,'a')%>);
	}


	template<class R<%=generator.templateParameterList(i) %>>
	inline R Bind<R (<%=generator.list(i)%>)>::emptyCallback(<%=generator.list(i,"A")%>)
	{
		return R();
	}

	template<class R<%=generator.templateParameterList(i) %>>
	inline void Bind<R (<%=generator.list(i)%>)>::emptyCallbackReturnsVoid(<%=generator.list(i,"A")%>)
	{
		/* Do nothing */
	}






	template<class R<%=generator.templateParameterList(i) %>>
	inline Bind<R (<%=generator.list(i)%>)>& Bind<R (<%=generator.list(i)%>)>::operator = (R (*pointer)(<%=generator.list(i)%>))
	{
		bind(pointer);
		return *this;
	}


	template<class R<%=generator.templateParameterList(i) %>>
	inline Bind<R (<%=generator.list(i)%>)>& Bind<R (<%=generator.list(i)%>)>::operator = (const Bind<R (<%=generator.list(i)%>)>& rhs)
	{
		// Inc the reference count
		pHolder = rhs.pHolder;
		return *this;
	}


	template<class R<%=generator.templateParameterList(i) %>>
	inline Bind<R (<%=generator.list(i)%>)>& Bind<R (<%=generator.list(i)%>)>::operator = (const NullPtr*)
	{
		// equivalent to unbind
		Private::BindImpl::Unbind<R, BindType>::Execute(this);
		return *this;
	}


	template<class R<%=generator.templateParameterList(i) %>>
	inline Bind<R (<%=generator.list(i)%>)>& Bind<R (<%=generator.list(i)%>)>::operator = (const NullPtr&)
	{
		// equivalent to unbind
		Private::BindImpl::Unbind<R, BindType>::Execute(this);
		return *this;
	}




<% end %>

} // namespace Yuni

#endif // __YUNI_CORE_BIND_BIND_H__
