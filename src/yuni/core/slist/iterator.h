
// !!! Do not use includes here !!!


/*!
** \brief An iterator
*/
class Iterator
{
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

	ConstIterator& operator += (int n)
	{
		while (n > 0)
		{
			pCurrent = ((pCurrent) ? pCurrent->next : NULL);
			--n;
		}
		return *this;
	}

	T& operator * ()
	{
		return pCurrent->data;
	}

	const T& operator * () const
	{
		return pCurrent->data;
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
};


/*!
** \brief A const iterator
*/
class ConstIterator
{
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

	ConstIterator& operator += (int n)
	{
		while (n > 0)
		{
			pCurrent = ((pCurrent) ? pCurrent->next : NULL);
			--n;
		}
		return *this;
	}

	const T& operator * () const
	{
		return pCurrent->data;
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


