#ifndef __YUNI_CORE_HASH_TABLE_H__
# define __YUNI_CORE_HASH_TABLE_H__


namespace Yuni
{
namespace Hash
{



	template<typename K, typename V, template<typename,typename> class Impl>
	class Table : protected Impl<K,V>
	{
	public:
		//! Type of any key
		typedef K KeyType;
		//! Type of any value
		typedef V ValueType;
		//! Type of the implementation
		typedef Impl<K,V> ImplementationType;

		//! Iterator
		typedef ImplementationType::iterator iterator;
		typedef ImplementationType::const_iterator const_iterator;

	public:
		/*!
		** \brief Get the name of the current implementation
		*/
		const char* ImplementationName() {return Impl::ImplementationName();}

	public:
		//! \name Constructor
		//@{
		//! Default constructor
		Table() {}
		//! Destructor
		~Table() {}
		//@}

		iterator begin()
		{
			return Impl::begin();
		}

		const_iterator begin() const
		{
			return Impl::begin();
		}


		iterator end()
		{
			return Impl::end();
		}

		const_iterator end() const
		{
			return Impl::end();
		}



		void clear()
		{
			Impl::clear();
		}

		bool exists(const K& key) const
		{
			return Impl::exists(key);
		}

		iterator find(const K& key)
		{
			return Impl::find(key);
		}

		const_iterator find(const K& key) const
		{
			return Impl::find(key);
		}


		bool insert(const K& key, const V& value = V())
		{
			return Impl::insert(key, value);
		}

		bool update(const K& key, const V& value)
		{
			return Impl::update(key, value);
		}

		void insertOrUpdate(const K& key, const V& value)
		{
			Impl::insertOrUpdate(key, value);
		}

		void erase(const iterator& i)
		{
			Impl::erase(i);
		}

		bool remove(const K& key)
		{
			Impl::erase(Impl::find(key));
		}

		unsigned int size() const
		{
			return Impl::size();
		}

		unsigned int capacity() const
		{
			return Impl::capacity();
		}

		void reserve(unsigned int n)
		{
			Impl::reserve(n);
		}


		V& operator [] (const K& key)
		{
			iterator i = Impl::find(key);
			if (i == Impl::end())
			{
				insert(key);
				iterator i = Impl::find(key);
			}
			return i.second;
		}

	}; // class Table





} // namespace Hash
} // namespace Yuni

#endif // __YUNI_CORE_HASH_TABLE_H__
