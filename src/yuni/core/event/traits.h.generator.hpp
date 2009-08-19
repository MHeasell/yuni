#ifndef __YUNI_CORE_EVENT_TRAITS_H__
# define __YUNI_CORE_EVENT_TRAITS_H__

<%
require File.dirname(__FILE__) + '/../../../tools/generators/commons.rb'
generator = Generator.new()
%>
<%=generator.thisHeaderHasBeenGenerated("traits.h.generator.hpp")%>


namespace Yuni
{
namespace Private
{
namespace EventImpl
{

	template<int N, class BindT> class WithNArguments;


	template<typename T>
	class EmptyPredicate
	{
	public:
		typedef void ResultType;
	public:
		inline void operator () (T) {}
		static void result() {}
	};



<% (0..generator.argumentCount).each do |i| %>
	template<class BindT>
	class WithNArguments<<%=i%>, BindT> : public Policy::ObjectLevelLockable<WithNArguments<<%=i%>,BindT> >
	{
	public:
		//! The Threading Policy
		typedef Policy::ObjectLevelLockable<WithNArguments<<%=i%>,BindT> > ThreadingPolicy;
		//! Bind
		typedef BindT BindType;
		//! The Return type
		typedef typename BindType::ReturnType R;<% (0..i-1).each do |j| %>
		//! Type of the argument <%=j%>
		typedef typename BindType::template Argument<<%=j%>>::Type A<%=j%>;<% end %>

	public:
		//! \name Constructors
		//@{
		//! Default constructor
		WithNArguments() {}
		//! Copy constructor
		WithNArguments(const WithNArguments& rhs)
			:pBindList(rhs.pBindList)
		{}
		//@}

		//! \name Invoke
		//@{
		/*!
		** \brief Invoke the delegate
		*/
		void invoke(<%=generator.variableList(i)%>) const
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			if (!pBindList.empty())
			{
				const typename BindList::const_iterator end = pBindList.end();
				for (typename BindList::const_iterator i = pBindList.begin(); i != end; ++i)
					(*i).invoke(<%=generator.list(i,'a')%>);
			}
		}

		template<template<class> class PredicateT>
		typename PredicateT<R>::ResultType invoke(<%=generator.variableList(i)%>) const
		{
			PredicateT<R> predicate;
			typename ThreadingPolicy::MutexLocker locker(*this);
			if (!pBindList.empty())
			{
				const typename BindList::const_iterator end = pBindList.end();
				for (typename BindList::const_iterator i = pBindList.begin(); i != end; ++i)
					predicate((*i).invoke(<%=generator.list(i,'a')%>));
			}
			return predicate.result();
		}

		template<template<class> class PredicateT>
		typename PredicateT<R>::ResultType invoke(PredicateT<R>& predicate<%=generator.variableList(i,"A","a", ", ")%>) const
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			if (!pBindList.empty())
			{
				const typename BindList::const_iterator end = pBindList.end();
				for (typename BindList::const_iterator i = pBindList.begin(); i != end; ++i)
					predicate((*i).invoke(<%=generator.list(i,'a')%>));
			}
			return predicate.result();
		}


		/*!
		** \brief Invoke the delegate
		*/
		void operator () (<%=generator.variableList(i)%>) const
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			if (!pBindList.empty())
			{
				const typename BindList::const_iterator end = pBindList.end();
				for (typename BindList::const_iterator i = pBindList.begin(); i != end; ++i)
					(*i).invoke(<%=generator.list(i,'a')%>);
			}
		}
		//@}

	protected:
		typedef std::vector<BindType> BindList;
		BindList pBindList;

	}; // class WithNArguments


<% end %>


} // namespace EventImpl
} // namespace Private
} // namespace Yuni

#endif // __YUNI_CORE_EVENT_TRAITS_H__
