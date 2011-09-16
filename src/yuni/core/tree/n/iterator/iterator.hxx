#ifndef __YUNI_CORE_TREE_N_ITERATOR_HXX__
# define __YUNI_CORE_TREE_N_ITERATOR_HXX__

namespace Yuni
{
namespace Core
{
namespace Tree
{

	template<class NodeT, bool ConstT>
	inline typename DepthPrefixIterator<NodeT,ConstT>::reference
	DepthPrefixIterator<NodeT,ConstT>::operator * ()
	{
		return *pNode;
	}


	template<class NodeT, bool ConstT>
	inline typename DepthPrefixIterator<NodeT,ConstT>::const_reference
	DepthPrefixIterator<NodeT,ConstT>::operator * () const
	{
		return *pNode;
	}


	template<class NodeT, bool ConstT>
	inline typename DepthPrefixIterator<NodeT,ConstT>::pointer
	DepthPrefixIterator<NodeT,ConstT>::operator -> ()
	{
		return NodeT::operator -> ();
	}


	template<class NodeT, bool ConstT>
	inline typename DepthPrefixIterator<NodeT,ConstT>::const_pointer
	DepthPrefixIterator<NodeT,ConstT>::operator -> () const
	{
		return NodeT::operator -> ();
	}


	template<class NodeT, bool ConstT>
	void DepthPrefixIterator<NodeT, ConstT>::forward()
	{
		// This is depth-first traversal, so do the children first
		if (!pNode->empty())
		{
			pNode = pNode[0];
			return;
		}
		// If we reached a leaf, do the siblings
		pointer next = pNode->nextSibling();
		if (next)
			pNode = next;
		// If there are no siblings
		else
		{
			// Keep the bottom-most node, it might be iterator::end
			pointer bottom = pNode;
			// Climb back the parents until we find siblings
			while (pNode->parent() && !pNode->parent()->nextSibling())
				pNode = pNode->parent();
			// If we reached the right-most sibling of the root,
			// it means the bottom node was actually the last one to traverse
			if (!pNode->parent() && !pNode->parent()->nextSibling())
			{
				pNode = bottom;
				return;
			}
			// Otherwise, the next sibling we found is the next node to traverse
			pNode = pNode->parent()->nextSibling();
		}
	}


	template<class NodeT, bool ConstT>
	void DepthPrefixIterator<NodeT, ConstT>::forward(difference_type n)
	{
		// TODO: There is possibility to optimize this a lot
		while (n--)
		{
			forward();
		}
	}


	template<class NodeT, bool ConstT>
	void DepthPrefixIterator<NodeT, ConstT>::backward()
	{
	}


	template<class NodeT, bool ConstT>
	void DepthPrefixIterator<NodeT, ConstT>::backward(difference_type n)
	{
		// TODO: There is possibility to optimize this a lot
		while (n--)
		{
			backward();
		}
	}



} // namespace Tree
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_TREE_N_ITERATOR_HXX__
