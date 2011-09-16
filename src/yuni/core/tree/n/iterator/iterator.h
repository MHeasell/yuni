#ifndef __YUNI_CORE_TREE_N_ITERATOR_H__
# define __YUNI_CORE_TREE_N_ITERATOR_H__

namespace Yuni
{
namespace Core
{
namespace Tree
{


	template<class NodeT, bool ConstT>
	class DepthPrefixIterator: public IIterator<DepthPrefixIterator<NodeT, ConstT>, ConstT>
	{
	public:
		typedef DepthPrefixIterator<NodeT, ConstT>  IteratorType;

		typedef IIterator<DepthPrefixIterator<NodeT, ConstT>, ConstT>  BaseIterator;

		typedef typename NodeT::Ptr Ptr;

		//! \name  STL Compatibility
		//@{
		typedef NodeT  value_type;
		typedef NodeT*  pointer;
		typedef const NodeT*  const_pointer;
		typedef NodeT&  reference;
		typedef const NodeT&  const_reference;
		typedef std::bidirectional_iterator_tag  iterator_category;
		typedef ptrdiff_t  difference_type;
		//@}

	public:
		enum
		{
			canGoForward = true,
			canGoBackward = true,
		};

	public:
		//! \name Constructors
		//@{
		DepthPrefixIterator():
			BaseIterator(), pNode(), pGoingUp(false)
		{}
		DepthPrefixIterator(const DepthPrefixIterator& it):
			BaseIterator(it),
			pNode(it.pNode),
			pGoingUp(false)
		{}
		DepthPrefixIterator(const NodeT& p):
			BaseIterator(p), pNode(p), pGoingUp(false)
		{}
		DepthPrefixIterator(const Ptr& p):
			BaseIterator(p), pNode(p.pointer()), pGoingUp(false)
		{}
		//@}

		//! \name Static overloads from IIterator
		//@{
		void forward();

		void forward(difference_type n);

		void backward();

		void backward(difference_type n);

		void advance(difference_type n);

		template<class N, bool C>
		difference_type distance(const DepthPrefixIterator<N,C>& rhs) const;
		//@}


		//! \name Operator overloads
		//@{

		//! The operator `*`
		DepthPrefixIterator<NodeT,ConstT>::reference operator * ();

		//! The operator `*`
		DepthPrefixIterator<NodeT,ConstT>::const_reference operator * () const;

		//! The operator `->`
		DepthPrefixIterator<NodeT,ConstT>::pointer operator -> ();

		//! The operator `->`
		DepthPrefixIterator<NodeT,ConstT>::const_pointer operator -> () const;

		//! The operator `==`
		bool operator == (const IteratorType& rhs) const {return pNode == rhs.pNode;}
		//! The operator `!=`
		bool operator != (const IteratorType& rhs) const {return pNode != rhs.pNode;}
		//! The operator `<`
		bool operator < (const IteratorType& rhs) const {return pNode < rhs.pNode;}
		//! The operator `>`
		bool operator > (const IteratorType& rhs) const {return pNode > rhs.pNode;}
		//! The operator `<=`
		bool operator <= (const IteratorType& rhs) const {return pNode <= rhs.pNode;}
		//! The operator `>=`
		bool operator >= (const IteratorType& rhs) const {return pNode >= rhs.pNode;}

		//@}

	private:
		NodeT* pNode;

		bool pGoingUp;
	};


} // namespace Tree
} // namespace Core
} // namespace Yuni

# include "iterator.hxx"

#endif // __YUNI_CORE_TREE_N_ITERATOR_H__
