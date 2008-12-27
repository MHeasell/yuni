#ifndef __YUNI_HASH_TABLE_H__
# define __YUNI_HASH_TABLE_H__

# include "../../yuni.h"
# include "std.hashmap.h"
# include "../string.h"
# include "key.h"
# include "../policies/threading.h"




namespace Yuni
{
namespace Hash
{

	enum Options
	{
		optNone = 0,
		optThreadSafe = 1,
		optIgnoreCase = 2
	};



	/*! \class Table
	**
	** \brief Unique Associative container
	**
	** \internal Do not forget to broadcast changes into Hash::Dictionary as well
	*/
	template<typename K, typename V, template<class> class TP = Policy::SingleThreaded>
	class Table : TP<V>
	{
	public:
		//! The threading policy used
		typedef TP<V> ThreadingPolicy;
		//! An iterator
		typedef typename YuniSTLExt::hash_map< K, V, YuniSTLExt::YUNI_OS_HASH_MAP_FUN<K> >::iterator  iterator;
		//! A const iterator
		typedef typename YuniSTLExt::hash_map< K, V, YuniSTLExt::YUNI_OS_HASH_MAP_FUN <K> >::const_iterator  const_iterator;

	public:
		//! \name Constructors & Destructor
		//@{
		//! Default constructor
		Table()
			:ThreadingPolicy(), pTable()
		{}
		//! Copy constructor
		Table(const Table& c)
			:ThreadingPolicy(), pTable(c.pTable)
		{}
		//! Destructor
		virtual ~Table() {this->clear();}
		//@}

		/*!
		** \brief Get if an entry exists
		**
		** \param key The key to find
		** \return True if the key exists, False otherwise
		*/
		bool exists(const K& key); 

		/*!
		** \brief Get/Set an entry
		**
		** If the entry does not exist, it will be created
		**
		** \param key The key to get/set
		** \return The value of the key
		*/
		V& operator[] (const K& key);

		/*!
		** \brief Find a key in the table
		**
		** \param key The key to find
		** \return The iterator pointing to the key, end() if not found
		*/
		iterator find(const K& key);

		/*!
		** \brief Get the value of a key
		**
		** \param key The key to find
		** \param defvalue The default value if the key can not be found
		** \return The value ofthe key, `defvalue` if the key could not be found
		*/
		V value(const K& key, const V& defvalue = V());


		/*!
		** \brief Returns a read/write iterator that points to the first element of the table
		*/
		iterator begin();
		/*!
		** \brief Returns a read-only (constant) iterator that points to the first element of the table
		*/
		//const_iterator begin() const {return pTable.begin();}

		/*!
		** \brief Returns a read/write iterator that points to the end of the table
		*/
		iterator end();
		/*!
		** \brief Returns a read-only (constant) iterator that points to the end of the table
		*/
		//const_iterator end() const {return pTable.end();}

		/*!
		** \brief Clear the table
		*/
		void clear();

		/*!
		** \brief Erase a single key
		**
		** \param key The key to find
		** \return True if the key has been erased, False if not found
		*/
		void erase(const K& key);

		//! Number of elements in the table
		int size();

		/*!
		** \brief Insert a key
		** \param key The key to insert in the hash map
		*/
		std::pair<iterator, bool> insert(const K& key);

	private:
		//! The real hash map
		YuniSTLExt::hash_map< K, V, YuniSTLExt::YUNI_OS_HASH_MAP_FUN<K> >  pTable;

	}; // class Hash::Table






} // namespace Hash
} // namespace Yuni


# include "table.hxx"

#endif // __YUNI_HASH_TABLE_H__
