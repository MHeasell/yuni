#ifndef __YUNI_CORE_TREE_N_HXX__
# define __YUNI_CORE_TREE_N_HXX__

# include <iostream>

namespace Yuni
{
namespace Core
{

	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline TreeN<T,TP,ChckP,TrckP,ConvP>::TreeN()
		:pParent(), pHaveParent(false), pChildrenCount(0), pRefCount(0)
	{}



	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline TreeN<T,TP,ChckP,TrckP,ConvP>::~TreeN()
	{
		// The node should be detached as soon as possible to avoid
		// any operation on it
		detachFromParent();
		// Remove all children
		clear();
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline bool TreeN<T,TP,ChckP,TrckP,ConvP>::empty()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return (0 == pChildrenCount);
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline bool TreeN<T,TP,ChckP,TrckP,ConvP>::leaf()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return (0 == pChildrenCount);
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline typename TreeN<T,TP,ChckP,TrckP,ConvP>::SizeType TreeN<T,TP,ChckP,TrckP,ConvP>::count()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return pChildrenCount;
	}

	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline typename TreeN<T,TP,ChckP,TrckP,ConvP>::SizeType TreeN<T,TP,ChckP,TrckP,ConvP>::size()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return pChildrenCount;
	}

	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline void TreeN<T,TP,ChckP,TrckP,ConvP>::detachFromParent()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (pHaveParent)
			detachFromParentWL();
	}

	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline void TreeN<T,TP,ChckP,TrckP,ConvP>::detachFromParentWL()
	{
		// Remove the reference from the parent
		pParent->internalRemoveChild(*this);
		// Removing our references to the parent
		pHaveParent = false;
		pParent = NULL;
		pPreviousSibling = NULL;
		pNextSibling = NULL;
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline void TreeN<T,TP,ChckP,TrckP,ConvP>::parent(Ptr& newParent)
	{
		detachFromParent();
		newParent->push_back(this);
	}



	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline bool TreeN<T,TP,ChckP,TrckP,ConvP>::internalRemoveChild(Node& node)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return internalRemoveChildWL(node);
	}

	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	bool TreeN<T,TP,ChckP,TrckP,ConvP>::internalRemoveChildWL(Node& node)
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


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline bool TreeN<T,TP,ChckP,TrckP,ConvP>::remove(Ptr& node)
	{
		return (node->parent() == *this) ? internalRemoveChild(*node) : false;
	}






	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	typename TreeN<T,TP,ChckP,TrckP,ConvP>::Ptr
	TreeN<T,TP,ChckP,TrckP,ConvP>::findFromIndexWL(const typename TreeN<T,TP,ChckP,TrckP,ConvP>::SizeType index)
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




	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline typename TreeN<T,TP,ChckP,TrckP,ConvP>::Ptr
	TreeN<T,TP,ChckP,TrckP,ConvP>::find(const typename TreeN<T,TP,ChckP,TrckP,ConvP>::SizeType index)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return findFromIndexWL(index);
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline typename TreeN<T,TP,ChckP,TrckP,ConvP>::Ptr
	TreeN<T,TP,ChckP,TrckP,ConvP>::find(const typename TreeN<T,TP,ChckP,TrckP,ConvP>::SignedSizeType index)
	{
		if (index >= 0)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			return findFromIndexWL((SignedSizeType)index);
		}
		return NULL;
	}



	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline bool
	TreeN<T,TP,ChckP,TrckP,ConvP>::remove(const typename TreeN<T,TP,ChckP,TrckP,ConvP>::SizeType index)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		Ptr* p = findFromIndexWL(index);
		return (p) ? internalRemoveChildWL(p) : false;
	}



	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline bool
	TreeN<T,TP,ChckP,TrckP,ConvP>::remove(const typename TreeN<T,TP,ChckP,TrckP,ConvP>::SignedSizeType index)
	{
		if (index >= 0)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			Ptr* p = findFromIndexWL((typename Node::SizeType)index);
			return (p) ? internalRemoveChildWL(p) : false;
		}
		return false;
	}



	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	void
	TreeN<T,TP,ChckP,TrckP,ConvP>::internalDetachFromParentWithoutNotify()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		// Removing all our children before
		clearWL();
		// Removing our references to the parent
		pHaveParent = false;
		pParent = NULL;
		pPreviousSibling = NULL;
		pNextSibling = NULL;
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	void TreeN<T,TP,ChckP,TrckP,ConvP>::clear()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (pChildrenCount)
			clearWL();
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	void TreeN<T,TP,ChckP,TrckP,ConvP>::clearWL()
	{
		{
			std::stack<Ptr> queue;

			// Getting a copy of the list of all children
			const iterator end;
			for (iterator i = begin(); i != end; ++i)
				queue.push(*i);

			// Now we have a copy of the list, we can safely removing our links
			// with out children

			while (!queue.empty())
			{
				queue.top()->internalDetachFromParentWithoutNotify();
				queue.pop();
			}
		}

		pLastChild = NULL;
		pFirstChild = NULL;
		pChildrenCount = 0;
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline void
	TreeN<T,TP,ChckP,TrckP,ConvP>::append(typename TreeN<T,TP,ChckP,TrckP,ConvP>::Ptr& node)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		pushBackWL(node);
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline void
	TreeN<T,TP,ChckP,TrckP,ConvP>::append(T* node)
	{
		Ptr tmp(node);
		typename ThreadingPolicy::MutexLocker locker(*this);
		pushBackWL(tmp);
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline void
	TreeN<T,TP,ChckP,TrckP,ConvP>::push_back(T* node)
	{
		Ptr tmp(node);
		typename ThreadingPolicy::MutexLocker locker(*this);
		pushBackWL(tmp);
	}

	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline void
	TreeN<T,TP,ChckP,TrckP,ConvP>::push_front(T* node)
	{
		Ptr tmp(node);
		typename ThreadingPolicy::MutexLocker locker(*this);
		pushFrontWL(tmp);
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline void
	TreeN<T,TP,ChckP,TrckP,ConvP>::push_back(Ptr& node)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		pushBackWL(node);
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	void
	TreeN<T,TP,ChckP,TrckP,ConvP>::pushBackWL(Ptr& node)
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




	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline void
	TreeN<T,TP,ChckP,TrckP,ConvP>::push_front(Ptr& node)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		pushFrontWL(node);
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	void
	TreeN<T,TP,ChckP,TrckP,ConvP>::pushFrontWL(Ptr& node)
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



	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline void
	TreeN<T,TP,ChckP,TrckP,ConvP>::printBeginWL(std::ostream& out, const unsigned int) const
	{
		out << "<node>";
	}

	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline void
	TreeN<T,TP,ChckP,TrckP,ConvP>::printEndWL(std::ostream& out, const unsigned int) const
	{
		out << "</node>";
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	std::ostream&
	TreeN<T,TP,ChckP,TrckP,ConvP>::print(std::ostream& out, const bool recursive, const unsigned int level)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		for (unsigned int i = 0; i < level; ++i)
			out << "    ";
		printBeginWL(out, level);
		out << "\n";

		if (recursive && pChildrenCount)
		{
			const iterator end;
			for (iterator i = begin(); i != end; ++i)
				i->print(out, true, level + 1);
		}

		for (unsigned int i = 0; i < level; ++i)
			out << "    ";
		printEndWL(out, level);
		out << std::endl;
		return out;
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline bool TreeN<T,TP,ChckP,TrckP,ConvP>::equals(const Ptr& node) const
	{
		return (this == node);
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	typename TreeN<T,TP,ChckP,TrckP,ConvP>::SizeType
	TreeN<T,TP,ChckP,TrckP,ConvP>::depth()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return (pHaveParent) ? (1 + pParent->depth()) : 0;
	}




	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	typename TreeN<T,TP,ChckP,TrckP,ConvP>::SizeType
	TreeN<T,TP,ChckP,TrckP,ConvP>::treeHeight()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pChildrenCount)
			return 0;
		SizeType d = 0;

		const iterator end;
		for (iterator i = begin(); i != end; ++i)
		{
			SizeType nd = i->treeHeight();
			if (nd > d)
				d = nd;
		}

		return d + 1;
	}



	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	void TreeN<T,TP,ChckP,TrckP,ConvP>::bringToFront()
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


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	void
	TreeN<T,TP,ChckP,TrckP,ConvP>::sendToBack()
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


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline void
	TreeN<T,TP,ChckP,TrckP,ConvP>::invalidate()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		invalidateWL();
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline bool
	TreeN<T,TP,ChckP,TrckP,ConvP>::isInvalidated()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		return isInvalidatedWL();
	}



	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	inline void
	TreeN<T,TP,ChckP,TrckP,ConvP>::addRef()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		++pRefCount;
	}


	template<class T, template<class> class TP, template <class> class ChckP,
		template <class> class TrckP, class ConvP>
	void
	TreeN<T,TP,ChckP,TrckP,ConvP>::release()
	{
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			if (--pRefCount > 0)
				return;
			// Early clean-up
			if (pHaveParent)
				detachFromParentWL();
			if (pChildrenCount)
				clearWL();
		}
		delete this;
	}




} // namespace Core
} // namespace Yuni


#endif // __YUNI_CORE_TREE_N_HXX__
