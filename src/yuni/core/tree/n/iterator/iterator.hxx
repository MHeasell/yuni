#ifndef __YUNI_CORE_TREE_N_ITERATOR_HXX__
# define __YUNI_CORE_TREE_N_ITERATOR_HXX__

namespace Yuni
{
namespace Private
{
namespace Core
{
namespace Tree
{


	template<class NodeT>
	inline ChildIterator<NodeT>::ChildIterator():
		pNode(nullptr)
	{}


	template<class NodeT>
	inline ChildIterator<NodeT>::ChildIterator(const Type& it):
		pNode(it.pNode)
	{}


	template<class NodeT>
	template<class N>
	inline ChildIterator<NodeT>::ChildIterator(const ChildIterator<N>& p):
		pNode(p.pNode)
	{}


	template<class NodeT>
	inline ChildIterator<NodeT>::ChildIterator(const NodePtr& p):
		pNode(p)
	{}


	template<class NodeT>
	inline typename ChildIterator<NodeT>::reference
	ChildIterator<NodeT>::operator * ()
	{
		return *pNode;
	}


	template<class NodeT>
	inline typename ChildIterator<NodeT>::const_reference
	ChildIterator<NodeT>::operator * () const
	{
		return *pNode;
	}


	template<class NodeT>
	inline typename ChildIterator<NodeT>::pointer
	ChildIterator<NodeT>::operator -> ()
	{
		return pNode.pointer();
	}


	template<class NodeT>
	inline typename ChildIterator<NodeT>::const_pointer
	ChildIterator<NodeT>::operator -> () const
	{
		return pNode.pointer();
	}


	template<class NodeT>
	template<class N>
	inline bool ChildIterator<NodeT>::equals(const ChildIterator<N>& rhs) const
	{
		return pNode == rhs.pNode;
	}


	template<class NodeT>
	template<class N>
	inline void ChildIterator<NodeT>::reset(const ChildIterator<N>& rhs)
	{
		pNode = rhs.pNode;
	}


	template<class NodeT>
	void ChildIterator<NodeT>::forward()
	{
		pNode = pNode->nextSibling();
	}


	template<class NodeT>
	void ChildIterator<NodeT>::forward(difference_type n)
	{
		while (n--)
		{
			forward();
		}
	}


	template<class NodeT>
	void ChildIterator<NodeT>::backward()
	{
		pNode = pNode->previousSibling();
	}


	template<class NodeT>
	void ChildIterator<NodeT>::backward(difference_type n)
	{
		while (n--)
		{
			backward();
		}
	}






	template<class NodeT>
	inline DepthPrefixIterator<NodeT>::DepthPrefixIterator():
		pNode(nullptr)
	{}


	template<class NodeT>
	inline DepthPrefixIterator<NodeT>::DepthPrefixIterator(const Type& it):
		pNode(it.pNode)
	{}


	template<class NodeT>
	template<class N>
	inline DepthPrefixIterator<NodeT>::DepthPrefixIterator(const DepthPrefixIterator<N>& p):
		pNode(p.pNode)
	{}


	template<class NodeT>
	inline DepthPrefixIterator<NodeT>::DepthPrefixIterator(const NodePtr& p):
		pNode(p)
	{}


	template<class NodeT>
	inline typename DepthPrefixIterator<NodeT>::reference
	DepthPrefixIterator<NodeT>::operator * ()
	{
		return *pNode;
	}


	template<class NodeT>
	inline typename DepthPrefixIterator<NodeT>::const_reference
	DepthPrefixIterator<NodeT>::operator * () const
	{
		return *pNode;
	}


	template<class NodeT>
	inline typename DepthPrefixIterator<NodeT>::pointer
	DepthPrefixIterator<NodeT>::operator -> ()
	{
		return pNode.pointer();
	}


	template<class NodeT>
	inline typename DepthPrefixIterator<NodeT>::const_pointer
	DepthPrefixIterator<NodeT>::operator -> () const
	{
		return pNode.pointer();
	}


	template<class NodeT>
	template<class N>
	inline bool DepthPrefixIterator<NodeT>::equals(const DepthPrefixIterator<N>& rhs) const
	{
		return pNode == rhs.pNode;
	}


	template<class NodeT>
	template<class N>
	inline void DepthPrefixIterator<NodeT>::reset(const DepthPrefixIterator<N>& rhs)
	{
		pNode = rhs.pNode;
	}


	template<class NodeT>
	void DepthPrefixIterator<NodeT>::forward()
	{
		// This is depth-first traversal, so do the children first
		if (!pNode->empty())
		{
			pNode = (*pNode)[0];
			return;
		}
		// If we reached a leaf, do the siblings
		NodePtr next = pNode->nextSibling();
		if (next)
			pNode = next;
		// If there are no siblings
		else
		{
			// Climb back the parents until we find siblings
			while (pNode->parent() && !pNode->parent()->nextSibling())
				pNode = pNode->parent();
			// If we reached the right-most sibling of the root,
			// it means we have finished.
			if (!pNode->parent() && !pNode->parent()->nextSibling())
			{
				pNode = nullptr;
				return;
			}
			// Otherwise, the next sibling we found is the next node to traverse
			pNode = pNode->parent()->nextSibling();
		}
	}


	template<class NodeT>
	void DepthPrefixIterator<NodeT>::forward(difference_type n)
	{
		// TODO: There is possibility to optimize this a lot
		while (n--)
		{
			forward();
		}
	}


	template<class NodeT>
	void DepthPrefixIterator<NodeT>::backward()
	{
	}


	template<class NodeT>
	void DepthPrefixIterator<NodeT>::backward(difference_type n)
	{
		// TODO: There is possibility to optimize this a lot
		while (n--)
		{
			backward();
		}
	}



} // namespace Tree
} // namespace Core
} // namespace Private
} // namespace Yuni

#endif // __YUNI_CORE_TREE_N_ITERATOR_HXX__
