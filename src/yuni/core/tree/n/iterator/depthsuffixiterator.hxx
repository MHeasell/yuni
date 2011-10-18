#ifndef __YUNI_CORE_TREE_N_DEPTH_SUFFIX_ITERATOR_HXX__
# define __YUNI_CORE_TREE_N_DEPTH_SUFFIX_ITERATOR_HXX__

namespace Yuni
{
namespace Private
{
namespace Core
{
namespace Tree
{


	template<class NodeT>
	inline DepthSuffixIterator<NodeT>::DepthSuffixIterator():
		pNode(nullptr)
	{}


	template<class NodeT>
	inline DepthSuffixIterator<NodeT>::DepthSuffixIterator(const Type& it):
		pNode(it.pNode)
	{}


	template<class NodeT>
	template<class N>
	inline DepthSuffixIterator<NodeT>::DepthSuffixIterator(const DepthSuffixIterator<N>& p):
		pNode(p.pNode)
	{}


	template<class NodeT>
	inline DepthSuffixIterator<NodeT>::DepthSuffixIterator(const NodePtr& p):
		pNode(p)
	{}


	template<class NodeT>
	inline typename DepthSuffixIterator<NodeT>::reference
	DepthSuffixIterator<NodeT>::operator * ()
	{
		return *pNode;
	}


	template<class NodeT>
	inline typename DepthSuffixIterator<NodeT>::const_reference
	DepthSuffixIterator<NodeT>::operator * () const
	{
		return *pNode;
	}


	template<class NodeT>
	inline typename DepthSuffixIterator<NodeT>::pointer
	DepthSuffixIterator<NodeT>::operator -> ()
	{
		return pNode.pointer();
	}


	template<class NodeT>
	inline typename DepthSuffixIterator<NodeT>::const_pointer
	DepthSuffixIterator<NodeT>::operator -> () const
	{
		return pNode.pointer();
	}


	template<class NodeT>
	template<class N>
	inline bool DepthSuffixIterator<NodeT>::equals(const DepthSuffixIterator<N>& rhs) const
	{
		return pNode == rhs.pNode;
	}


	template<class NodeT>
	template<class N>
	inline void DepthSuffixIterator<NodeT>::reset(const DepthSuffixIterator<N>& rhs)
	{
		pNode = rhs.pNode;
	}


	template<class NodeT>
	void DepthSuffixIterator<NodeT>::forward()
	{
		// TODO
	}


	template<class NodeT>
	void DepthSuffixIterator<NodeT>::forward(difference_type n)
	{
		// FIXME : There is possibility to optimize this a lot
		while (n--)
		{
			forward();
		}
	}


	template<class NodeT>
	void DepthSuffixIterator<NodeT>::backward()
	{
		// TODO
	}


	template<class NodeT>
	void DepthSuffixIterator<NodeT>::backward(difference_type n)
	{
		// FIXME : There is possibility to optimize this a lot
		while (n--)
		{
			backward();
		}
	}



} // namespace Tree
} // namespace Core
} // namespace Private
} // namespace Yuni

#endif // __YUNI_CORE_TREE_N_DEPTH_SUFFIX_ITERATOR_HXX__
