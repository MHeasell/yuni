#ifndef __YUNI_CORE_BIND_BIND_HXX__
# define __YUNI_CORE_BIND_BIND_HXX__

<%
require File.dirname(__FILE__) + '/../../../tools/generators/commons.rb'
generator = Generator.new()
%>
<%=generator.thisHeaderHasBeenGenerated("bind.hxx.generator.hpp")%>


namespace Yuni
{


<%
(0..(generator.argumentCount)).each do |i|
[ ["class R" + generator.templateParameterList(i), "R ("+generator.list(i) + ")", "void"],
  ["class R" + generator.templateParameterList(i), "R (*)(" + generator.list(i) + ")", "void"],
  ["class ClassT, class R" + generator.templateParameterList(i), "R (ClassT::*)(" + generator.list(i) + ")", "ClassT"] ].each do |tmpl|

%>

	// Constructor
	template<<%=tmpl[0]%>>
	inline Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::Bind()
	{
		Private::BindImpl::Unbind<R, BindType>::Execute(this);
	}

	// Constructor
	template<<%=tmpl[0]%>>
	inline Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::Bind(const Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>& rhs)
		:pHolder(rhs.pHolder)
	{}



	// Destructor
	template<<%=tmpl[0]%>>
	inline Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::~Bind()
	{}


	// Bind: Pointer-to-function
	template<<%=tmpl[0]%>>
	inline void Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::bind(R (*pointer)(<%=generator.list(i)%>))
	{
		pHolder = new Private::BindImpl::BoundWithFunction<R (<%=generator.list(i)%>)>(pointer);
	}


	// Bind: Pointer-to-function + user data
	template<<%=tmpl[0]%>>
	template<class U>
	inline void Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::bind(R (*pointer)(<%=generator.list(i, "A", "", ", ")%>U),
		typename Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::template WithUserData<U>::ParameterType userdata)
	{
		pHolder = new Private::BindImpl::BoundWithFunctionAndUserData
			<typename WithUserData<U>::ParameterType, R (<%=generator.list(i, "A", "", ", ")%>U)>(pointer, userdata);
	}



	// Bind: pointer-to-member
	template<<%=tmpl[0]%>>
	template<class C>
	void Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::bind(C* c, R (C::*member)(<%=generator.list(i)%>))
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
	template<<%=tmpl[0]%>>
	template<class C>
	void Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::bind(const C* c, R (C::*member)(<%=generator.list(i)%>) const)
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
	template<<%=tmpl[0]%>>
	template<class C,
		template <class> class OwspP, template <class> class ChckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline void
	Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::bind(const SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP> c, R (C::*member)(<%=generator.list(i)%>))
	{
		bind(SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP>::WeakPointer(c), member);
	}


	// Bind: pointer-to-member const
	template<<%=tmpl[0]%>>
	template<class C,
		template <class> class OwspP, template <class> class ChckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline void
	Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::bind(const SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP> c, R (C::*member)(<%=generator.list(i)%>) const)
	{
		bind(SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP>::WeakPointer(c), member);
	}


	// Bind: pointer-to-member const
	template<<%=tmpl[0]%>>
	template<class U, class C,
		template <class> class OwspP, template <class> class ChckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline void
	Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::bind(const SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP> c, R (C::*member)(<%=generator.list(i)%>),
		typename Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::template WithUserData<U>::ParameterType userdata)
	{
		bind(SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP>::WeakPointer(c), member, userdata);
	}


	// Bind: pointer-to-member const
	template<<%=tmpl[0]%>>
	template<class U, class C,
		template <class> class OwspP, template <class> class ChckP, class ConvP,
		template <class> class StorP, template <class> class ConsP>
	inline void
	Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::bind(const SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP> c, R (C::*member)(<%=generator.list(i)%>) const,
		typename Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::template WithUserData<U>::ParameterType userdata)
	{
		bind(SmartPtr<C, OwspP,ChckP,ConvP,StorP,ConsP>::WeakPointer(c), member, userdata);
	}


	template<<%=tmpl[0]%>>
	template<class U, class C>
	void Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::bind(C* c, R (C::*member)(<%=generator.list(i,"A","",", ")%>U),
		typename Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::template WithUserData<U>::ParameterType userdata)
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


	template<<%=tmpl[0]%>>
	template<class U, class C>
	void Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::bind(const C* c, R (C::*member)(<%=generator.list(i,"A","",", ")%>U) const,
		typename Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::template WithUserData<U>::ParameterType userdata)
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


	template<<%=tmpl[0]%>>
	inline void Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::bind(const Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>& rhs)
	{
		// Inc the reference count
		pHolder = rhs.pHolder;
	}


	// Bind: unbind
	template<<%=tmpl[0]%>>
	inline void Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::unbind()
	{
		Private::BindImpl::Unbind<R, BindType>::Execute(this);
	}


	// Bind: unbind
	template<<%=tmpl[0]%>>
	inline void Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::clear()
	{
		Private::BindImpl::Unbind<R, BindType>::Execute(this);
	}


	template<<%=tmpl[0]%>>
	template<class UserTypeT, template<class UserTypeGT, class ArgumentIndexTypeT> class ArgGetterT>
	inline R
	Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::callWithArgumentGetter(UserTypeT userdata) const
	{
		return invoke(<%=
			ret = ''
			(0..i-1).each do |j|
				if j > 0
					ret += ', '
				end
				if ((j + 1).modulo(2) == 0)
					ret += "\n\t\t\t\t"
				end

				ret += "ArgGetterT<UserTypeT, A" + j.to_s + ">::Get(userdata, " + j.to_s + ")"
			end
			ret %>);
	}






	template<<%=tmpl[0]%>>
	inline R Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::invoke(<%=generator.variableList(i)%>) const
	{
		return pHolder->invoke(<%=generator.list(i,'a')%>);
	}


	template<<%=tmpl[0]%>>
	inline R Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::operator () (<%=generator.variableList(i)%>) const
	{
		return pHolder->invoke(<%=generator.list(i,'a')%>);
	}


	template<<%=tmpl[0]%>>
	inline R Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::emptyCallback(<%=generator.list(i,"A")%>)
	{
		return R();
	}

	template<<%=tmpl[0]%>>
	inline void Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::emptyCallbackReturnsVoid(<%=generator.list(i,"A")%>)
	{
		/* Do nothing */
	}






	template<<%=tmpl[0]%>>
	inline Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>& Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::operator = (R (*pointer)(<%=generator.list(i)%>))
	{
		bind(pointer);
		return *this;
	}


	template<<%=tmpl[0]%>>
	inline Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>& Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::operator = (const Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>& rhs)
	{
		// Inc the reference count
		pHolder = rhs.pHolder;
		return *this;
	}


	template<<%=tmpl[0]%>>
	inline Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>& Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::operator = (const NullPtr*)
	{
		// equivalent to unbind
		Private::BindImpl::Unbind<R, BindType>::Execute(this);
		return *this;
	}


	template<<%=tmpl[0]%>>
	inline Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>& Bind<<%=tmpl[1]%>, <%=tmpl[2]%>>::operator = (const NullPtr&)
	{
		// equivalent to unbind
		Private::BindImpl::Unbind<R, BindType>::Execute(this);
		return *this;
	}




<% end end %>

} // namespace Yuni

#endif // __YUNI_CORE_BIND_BIND_H__
