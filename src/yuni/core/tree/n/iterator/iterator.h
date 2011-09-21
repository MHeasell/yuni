#ifndef __YUNI_CORE_TREE_N_ITERATOR_H__
# define __YUNI_CORE_TREE_N_ITERATOR_H__

# include "../../../iterator/iterator.h"

namespace Yuni
{
namespace Private
{
namespace Core
{
namespace Tree
{

	template<class NodeT>
	class ChildIterator
	{
	public:
		typedef ChildIterator<NodeT>  Type;

		typedef typename NodeT::Ptr NodePtr;

		typedef NodeT  value_type;
		typedef int  difference_type;
		typedef value_type&  reference;
		typedef const value_type&  const_reference;
		typedef value_type*  pointer;
		typedef const value_type*  const_pointer;

	public:
		enum
		{
			canGoForward = true,
			canGoBackward = true,
		};

	public:
		//! \name Constructors
		//@{
		ChildIterator();

		ChildIterator(const Type& it);

		template<class N>
		ChildIterator(const ChildIterator<N>& p);

		ChildIterator(const NodePtr& p);
		//@}

		//! \name Static overloads from IIterator
		//@{
		void forward();

		void forward(difference_type n);

		void backward();

		void backward(difference_type n);

		void advance(difference_type n);

		template<class N>
		bool equals(const ChildIterator<N>& rhs) const;

		template<class N>
		void reset(const ChildIterator<N>& rhs);

		template<class N>
		difference_type distance(const ChildIterator<N>& rhs) const;
		//@}


		//! \name Operator overloads
		//@{

		//! The operator `*`
		reference operator * ();

		//! The operator `*`
		const_reference operator * () const;

		//! The operator `->`
		pointer operator -> ();

		//! The operator `->`
		const_pointer operator -> () const;

		//@}

	private:
		//! The actual data
		NodePtr pNode;
	};



	template<class NodeT>
	class DepthPrefixIterator
	{
	public:
		typedef DepthPrefixIterator<NodeT>  Type;

		typedef typename NodeT::Ptr NodePtr;

		typedef NodeT  value_type;
		typedef int  difference_type;
		typedef value_type&  reference;
		typedef const value_type&  const_reference;
		typedef value_type*  pointer;
		typedef const value_type*  const_pointer;

	public:
		enum
		{
			canGoForward = true,
			canGoBackward = true,
		};

	public:
		//! \name Constructors
		//@{
		DepthPrefixIterator();

		DepthPrefixIterator(const Type& it);

		template<class N>
		DepthPrefixIterator(const DepthPrefixIterator<N>& p);

		DepthPrefixIterator(const NodePtr& p);
		//@}

		//! \name Static overloads from IIterator
		//@{
		void forward();

		void forward(difference_type n);

		void backward();

		void backward(difference_type n);

		void advance(difference_type n);

		template<class N>
		bool equals(const DepthPrefixIterator<N>& rhs) const;

		template<class N>
		void reset(const DepthPrefixIterator<N>& rhs);

		template<class N>
		difference_type distance(const DepthPrefixIterator<N>& rhs) const;
		//@}


		//! \name Operator overloads
		//@{

		//! The operator `*`
		reference operator * ();

		//! The operator `*`
		const_reference operator * () const;

		//! The operator `->`
		pointer operator -> ();

		//! The operator `->`
		const_pointer operator -> () const;

		//@}

	private:
		//! The actual data
		NodePtr pNode;
	};


} // namespace Tree
} // namespace Core
} // namespace Private
} // namespace Yuni

# include "iterator.hxx"

#endif // __YUNI_CORE_TREE_N_ITERATOR_H__