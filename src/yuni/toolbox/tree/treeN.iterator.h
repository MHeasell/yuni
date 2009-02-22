#ifndef __YUNI_TOOLBOX_TREE_N_ITERATOR_H__
# define __YUNI_TOOLBOX_TREE_N_ITERATOR_H__

// !!! Do not use includes here  !!!



class iterator
{
public:
	YUNI_TOOLBOX_TREE_N_ITERATOR_PRE(iterator);

public:
	//! \name Constructors
	//@{
	iterator() :pNode() {}
	iterator(iterator& it)  :pNode(it.pNode) {}
	iterator(const iterator& it)  :pNode(it.pNode)  {}
	iterator(NodeT& p) :pNode(p) {}
	iterator(const NodeT& p) :pNode(p) {}
	//@}


	IteratorType& operator ++ ()
	{
		pNode = pNode->pNextSibling;
		return *this;
	}

	IteratorType& operator -- ()
	{
		pNode = pNode->pPreviousSibling;
		return *this;
	}

	YUNI_TOOLBOX_TREE_N_ITERATOR_COMMON_PUBLIC_METHODS

protected:
	YUNI_TOOLBOX_TREE_N_ITERATOR_PROTECTED;

}; // name iterator




#endif // __YUNI_TOOLBOX_TREE_N_ITERATOR_H__
