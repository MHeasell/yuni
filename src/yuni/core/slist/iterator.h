
// !!! Do not use includes here !!!


/*!
** \brief An iterator
*/
class Iterator
{
public:
	enum
	{
		canGoForward = true,
		canGoBackward = false
	};

	typedef int difference_type;
	typedef T value_type;

public:
	Iterator()
		:pCurrent(NULL)
	{}
	Iterator(const Iterator& rhs)
		:pCurrent(rhs.pCurrent)
	{}
	Iterator(Item* c)
		:pCurrent(c)
	{}

	bool valid() const
	{
		return pCurrent;
	}

	/*!
	** \brief Increment the iterator by the distance 1
	*/
	void forward()
	{
		pCurrent = ((pCurrent) ? pCurrent->next : NULL);
	}

	/*!
	** \brief Increment the iterator by the distance n
	*/
	void forward(difference_type n)
	{
		while (n-- > 0 && pCurrent)
			pCurrent = pCurrent->next;
	}

	/*!
	** \brief Get the distance between this iterator and another one
	*/
	int distance(const Iterator& rhs) const
	{
		Item* iter1 = pCurrent;
		Item* iter2 = rhs.pCurrent;
		int distance = 0;
		while (iter2 != pCurrent && iter1 != rhs.pCurrent)
		{
			++iter1;
			++iter2;
			++distance;
		}
		return distance;
	}


	Iterator& operator ++ ()
	{
		pCurrent = ((pCurrent) ? pCurrent->next : NULL);
		return *this;
	}

	Iterator operator ++ (int)
	{
		Iterator copy(*this);
		pCurrent = ((pCurrent) ? pCurrent->next : NULL);
		return copy;
	}

	ConstIterator& operator += (difference_type n)
	{
		while (n-- > 0 && pCurrent)
			pCurrent = pCurrent->next;
		return *this;
	}

	reference_type operator * ()
	{
		return pCurrent->data;
	}

	const_reference_type operator * () const
	{
		return pCurrent->data;
	}

	bool equals(const Iterator& rhs) const
	{
		return (pCurrent == rhs.pCurrent);
	}

	bool equals(const ConstIterator& rhs) const
	{
		return (pCurrent == rhs.pCurrent);
	}

	bool operator == (const Iterator& rhs) const
	{
		return (pCurrent == rhs.pCurrent);
	}

	bool operator == (const ConstIterator& rhs) const
	{
		return (pCurrent == rhs.pCurrent);
	}

	bool operator != (const Iterator& rhs) const
	{
		return (pCurrent != rhs.pCurrent);
	}

	bool operator != (const ConstIterator& rhs) const
	{
		return (pCurrent != rhs.pCurrent);
	}

	bool operator ! () const
	{
		return (NULL == pCurrent);
	}

private:
	Item* pCurrent;

	friend class ConstIterator;
	friend class LinkedList<T,Alloc>;
};


/*!
** \brief A const iterator
*/
class ConstIterator
{
public:
	enum
	{
		canGoForward = true,
		canGoBackward = false
	};

	typedef int difference_type;
	typedef T value_type;

public:
	ConstIterator()
		:pCurrent(NULL)
	{}
	ConstIterator(const ConstIterator& rhs)
		:pCurrent(rhs.pCurrent)
	{}
	ConstIterator(const Iterator& rhs)
		:pCurrent(rhs.pCurrent)
	{}
	ConstIterator(const Item* c)
		:pCurrent(c)
	{}

	bool valid() const
	{
		return pCurrent;
	}

	/*!
	** \brief Increment the iterator by the distance 1
	*/
	void forward()
	{
		pCurrent = ((pCurrent) ? pCurrent->next : NULL);
	}

	/*!
	** \brief Increment the iterator by the distance n
	*/
	void forward(difference_type n)
	{
		while (n-- > 0 && pCurrent)
			pCurrent = pCurrent->next;
	}

	ConstIterator& operator ++ ()
	{
		pCurrent = ((pCurrent) ? pCurrent->next : NULL);
		return *this;
	}

	ConstIterator operator ++ (int)
	{
		ConstIterator copy(*this);
		pCurrent = ((pCurrent) ? pCurrent->next : NULL);
		return copy;
	}

	ConstIterator& operator += (difference_type n)
	{
		while (n-- > 0 && pCurrent)
			pCurrent = pCurrent->next;
		return *this;
	}

	const_reference_type operator * () const
	{
		return pCurrent->data;
	}

	bool equals(const Iterator& rhs) const
	{
		return (pCurrent == rhs.pCurrent);
	}

	bool equals(const ConstIterator& rhs) const
	{
		return (pCurrent == rhs.pCurrent);
	}

	bool operator == (const Iterator& rhs) const
	{
		return (pCurrent == rhs.pCurrent);
	}

	bool operator == (const ConstIterator& rhs) const
	{
		return (pCurrent == rhs.pCurrent);
	}

	bool operator != (const Iterator& rhs) const
	{
		return (pCurrent != rhs.pCurrent);
	}

	bool operator != (const ConstIterator& rhs) const
	{
		return (pCurrent != rhs.pCurrent);
	}

	bool operator ! () const
	{
		return (NULL == pCurrent);
	}

private:
	const Item* pCurrent;
	friend class Iterator;
};


