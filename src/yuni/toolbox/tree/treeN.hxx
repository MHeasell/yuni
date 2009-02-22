#ifndef __YUNI_TOOLBOX_TREE_N_HXX__
# define __YUNI_TOOLBOX_TREE_N_HXX__



namespace Yuni
{
namespace Toolbox
{

	template<class T, template<class> class TP>
	inline TreeN<T,TP>::TreeN()
		:pParent(), pHaveParent(false), pChildrenCount(0)
	{}



	template<class T, template<class> class TP>
	inline TreeN<T,TP>::~TreeN()
	{
		// The node should be detached as soon as possible to avoid
		// any operation on it
		detachFromParent();
		// Remove all children
		clear();
	}


	template<class T, template<class> class TP>
	inline bool TreeN<T,TP>::empty()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return (0 == pChildrenCount);
	}
	

	template<class T, template<class> class TP>
	inline bool TreeN<T,TP>::leaf()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return (0 == pChildrenCount);
	}


	template<class T, template<class> class TP>
	inline typename TreeN<T,TP>::SizeType TreeN<T,TP>::count()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return pChildrenCount;
	}
		
	template<class T, template<class> class TP>
	inline typename TreeN<T,TP>::SizeType TreeN<T,TP>::size()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return pChildrenCount;
	}

	template<class T, template<class> class TP>
	inline void TreeN<T,TP>::detachFromParent()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (pHaveParent)
			detachFromParentWL();
	}

	template<class T, template<class> class TP>
	inline void TreeN<T,TP>::detachFromParentWL()
	{
		// Remove the reference from the parent
		pParent->internalRemoveChild(*this);
		// Removing our references to the parent
		pHaveParent = false;
		pParent = NULL;
		pPreviousSibling = NULL;
		pNextSibling = NULL;
	}


	template<class T, template<class> class TP>
	inline void TreeN<T,TP>::parent(TreeN<T,TP>::Ptr& newParent)
	{
		detachFromParent();
		newParent->push_back(this);
	}

	
	
	template<class T, template<class> class TP>
	inline bool TreeN<T,TP>::internalRemoveChild(Node& node)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return internalRemoveChildWL(node);
	}
	
	template<class T, template<class> class TP>
	bool TreeN<T,TP>::internalRemoveChildWL(Node& node)
	{
		if (!node.pPreviousSibling)
		{
			// It was the first child actually
			pFirstChild = node.pNextSibling;
		}
		else
		{
			// Updating the next sibling of the previous one
			node.pPreviousSibling->pNextSibling = node.pNextSibling;
		}
		if (!node.pNextSibling)
		{
			// It was the last child actually
			pLastChild = node.pPreviousSibling;
		}
		else
		{
			// Updating the previous sibling of the next one
			node.pNextSibling->pPreviousSibling = node.pPreviousSibling;
		}
		// We have lost a child anyway :'(
		--pChildrenCount;
		return true;
	}


	template<class T, template<class> class TP>
	inline bool TreeN<T,TP>::remove(TreeN<T,TP>::Ptr& node)
	{
		return (node->parent() == *this) ? internalRemoveChild(*node) : false;
	}




	

	template<class T, template<class> class TP>
	typename TreeN<T,TP>::Ptr
	TreeN<T,TP>::findFromIndexWL(const typename TreeN<T,TP>::SizeType index)
	{
		if (index < pChildrenCount)
		{
			// A little trick to spee-up the reseach when dealing with huge amount
			// of children
			if (index < pChildrenCount - index)
			{
				Ptr* it = &pFirstChild;
				SizeType i = 0;
				while (index != i)
				{
					it = &((*it)->pNextSibling);
					++i;
				}
				return *it;
			}
			else
			{
				Ptr* it = &pLastChild;
				SizeType i = pChildrenCount - 1;
				while (index != i)
				{
					it = &((*it)->pPreviousSibling);
					--i;
				}
				return *it;
			}
		}
		return Ptr();
	}


	

	template<class T, template<class> class TP>
	inline typename TreeN<T,TP>::Ptr
	TreeN<T,TP>::find(const typename TreeN<T,TP>::SizeType index)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return findFromIndexWL(index);
	}

	
	template<class T, template<class> class TP>
	inline typename TreeN<T,TP>::Ptr
	TreeN<T,TP>::find(const typename TreeN<T,TP>::SignedSizeType index)
	{
		if (index >= 0)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			return findFromIndexWL((SignedSizeType)index);
		}
		return NULL;
	}



	template<class T, template<class> class TP>
	inline bool
	TreeN<T,TP>::remove(const typename TreeN<T,TP>::SizeType index)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		Ptr* p = findFromIndexWL(index);
		return (p) ? internalRemoveChildWL(p) : false;
	}


	
	template<class T, template<class> class TP>
	inline bool
	TreeN<T,TP>::remove(const typename TreeN<T,TP>::SignedSizeType index)
	{
		if (index >= 0)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			Ptr* p = findFromIndexWL((typename Node::SizeType)index);
			return (p) ? internalRemoveChildWL(p) : false;
		}
		return false;
	}


	
	template<class T, template<class> class TP>
	void
	TreeN<T,TP>::internalDetachFromParentWithoutNotify()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (pHaveParent)
		{
			// Removing our references to the parent
			pHaveParent = false;
			pParent = NULL;
			pPreviousSibling = NULL;
			pNextSibling = NULL;
		}
	}


	template<class T, template<class> class TP>
	void TreeN<T,TP>::clear()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (pChildrenCount)
			clearWL();
	}


	template<class T, template<class> class TP>
	void TreeN<T,TP>::clearWL()
	{
		Node* it = Ptr::ExtractPointer(pFirstChild);
		while (NULL != it)
		{
			it->internalDetachFromParentWithoutNotify();
			it = Ptr::ExtractPointer(it->pNextSibling);
		}
		pLastChild = NULL;
		pFirstChild = NULL;
		pChildrenCount = 0;
	}


	template<class T, template<class> class TP>
	inline void
	TreeN<T,TP>::append(typename TreeN<T,TP>::Ptr& node)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		pushBackWL(node);
	}


	template<class T, template<class> class TP>
	inline void
	TreeN<T,TP>::append(T* node)
	{
		Ptr tmp(node);
		typename ThreadingPolicy::MutexLocker locker(*this);
		pushBackWL(tmp);
	}


	template<class T, template<class> class TP>
	inline void
	TreeN<T,TP>::push_back(T* node)
	{
		Ptr tmp(node);
		typename ThreadingPolicy::MutexLocker locker(*this);
		pushBackWL(tmp);
	}

	template<class T, template<class> class TP>
	inline void
	TreeN<T,TP>::push_front(T* node)
	{
		Ptr tmp(node);
		typename ThreadingPolicy::MutexLocker locker(*this);
		pushFrontWL(tmp);
	}


	template<class T, template<class> class TP>
	inline void TreeN<T,TP>::push_back(Ptr& node)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		pushBackWL(node);
	}

	template<class T, template<class> class TP>
	void TreeN<T,TP>::pushBackWL(Ptr& node)
	{
		if (!pChildrenCount)
		{
			pFirstChild = node;
			pLastChild = pFirstChild;
			pFirstChild->pPreviousSibling = NULL;
			pFirstChild->pNextSibling = NULL;
			pChildrenCount = 1;
		}
		else
		{
			pLastChild->pNextSibling = node;
			node->pPreviousSibling = pLastChild;
			node->pNextSibling = NULL;
			pLastChild = node;
			++pChildrenCount;
		}
	}




	template<class T, template<class> class TP>
	inline void TreeN<T,TP>::push_front(Ptr& node)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		pushFrontWL(node);
	}


	template<class T, template<class> class TP>
	void TreeN<T,TP>::pushFrontWL(Ptr& node)
	{
		if (!pChildrenCount)
		{
			pFirstChild = node;
			pLastChild = pFirstChild;
			pFirstChild->pPreviousSibling = NULL;
			pFirstChild->pNextSibling = NULL;
			pChildrenCount = 1;
		}
		else
		{
			node->pNextSibling = pFirstChild;
			node->pPreviousSibling = NULL;
			pFirstChild->pPreviousSibling = node;
			pFirstChild = node;
			++pChildrenCount;
		}
	}



	template<class T, template<class> class TP>
	inline void
	TreeN<T,TP>::printBeginWL(std::ostream& out, const unsigned int) const
	{
		out << "<node>";
	}

	template<class T, template<class> class TP>
	inline void
	TreeN<T,TP>::printEndWL(std::ostream& out, const unsigned int) const
	{
		out << "</node>";
	}


	template<class T, template<class> class TP>
	std::ostream&
	TreeN<T,TP>::print(std::ostream& out, const unsigned int level)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		for (unsigned int i = 0; i < level; ++i)
			out << "    ";
		printBeginWL(out, level);
		out << "\n";

		if (pChildrenCount)
		{
			Node* it = Ptr::ExtractPointer(pFirstChild);
			while (NULL != it)
			{
				it->print(out, level + 1);
				it = Ptr::ExtractPointer(it->pNextSibling);
			}
		}

		for (unsigned int i = 0; i < level; ++i)
			out << "    ";
		printEndWL(out, level);
		out << std::endl;
		return out;
	}


	template<class T, template<class> class TP>
	inline bool TreeN<T,TP>::equals(const Ptr& node) const
	{
		return (this == node);
	}


	template<class T, template<class> class TP>
	typename TreeN<T,TP>::SizeType
	TreeN<T,TP>::depth()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return (pHaveParent) ? (1 + pParent->depth()) : 0; 
	}




	template<class T, template<class> class TP>
	typename TreeN<T,TP>::SizeType
	TreeN<T,TP>::treeHeight()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pChildrenCount)
			return 0;
		SizeType d = 0;
		Node* it = Ptr::ExtractPointer(pFirstChild);
		while (NULL != it)
		{
			SizeType nd = it->treeHeight();
			if (nd > d)
				d = nd;
			it = Ptr::ExtractPointer(it->pNextSibling);
		}
		return d + 1;
	}



	template<class T, template<class> class TP>
	void TreeN<T,TP>::bringToFront()
	{
		// Locking
		typename ThreadingPolicy::MutexLocker locker(*this);

		// We check in a first time if we are not already at the end
		if (pHaveParent && pNextSibling)
		{
			// Locking the parent
			typename ThreadingPolicy::MutexLocker locker(pParent);
			
			// Ok we have to move
			detachFromParentWL();
			pParent->pushBackWL(this);
		}
	}


	template<class T, template<class> class TP>
	void TreeN<T,TP>::sendToBack()
	{
		// Locking
		typename ThreadingPolicy::MutexLocker locker(*this);

		// We check in a first time if we are not already at the end
		if (pHaveParent && pPreviousSibling)
		{
			// Locking the parent
			typename ThreadingPolicy::MutexLocker locker(pParent);
			
			// Ok we have to move
			detachFromParentWL();
			pParent->pushFrontWL(this);
		}
	}


	template<class T, template<class> class TP>
	inline void TreeN<T,TP>::invalidate()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		invalidateWL();
	}

	template<class T, template<class> class TP>
	inline bool TreeN<T,TP>::isInvalidated()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return isInvalidatedWL();
	}






} // namespace Toolbox
} // namespace Yuni


#endif // __YUNI_TOOLBOX_TREE_N_HXX__
