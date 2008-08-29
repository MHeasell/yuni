#ifndef __YUNI_HASH_TABLE_H__
# define __YUNI_HASH_TABLE_H__

# include "../yuni.h"
# include "std.hashmap.h"
# include "../misc/string.h"
# include "key.h"
# include "../threads/mutex.h"




namespace Yuni
{
namespace Hash
{

	static const int optNone = 0;
	static const int optThreadSafe = 1;
	static const int optIgnoreCase = 2;




	/*! \class Table
	**
	** \brief Unique Associative container
	**
	** \internal Do not forget to broadcast changes into Hash::Dictionary as well
	*/
	template<typename K, typename V, bool ThreadSafe = false>
	class Table
	{
	public:
		//! An iterator
		typedef typename YuniSTLExt::hash_map< K, V, YuniSTLExt::hash<K> >::iterator  iterator;
		//! A const iterator
		typedef typename YuniSTLExt::hash_map< K, V, YuniSTLExt::hash<K> >::const_iterator  const_iterator;

	public:
		//! \name Constructors & Destructor
		//@{
		//! Default constructor
		Table() : pTable() {}
		//! Copy constructor
		Table(const Table& c) : pTable(c.pTable) {}
		//! Destructor
		virtual ~Table() {}
		//@}

		/*!
		** \brief Get if an entry exists
		**
		** \param key The key to find
		** \return True if the key exists, False otherwise
		*/
		bool exists(const K& key) const {return pTable.find(key) != pTable.end();}

		/*!
		** \brief Get/Set an entry
		**
		** If the entry does not exist, it will be created
		**
		** \param key The key to get/set
		** \return The value of the key
		*/
		V& operator[] (const K& key) {return pTable[key];}

		/*!
		** \brief Find a key in the table
		**
		** \param key The key to find
		** \return The iterator pointing to the key, end() if not found
		*/
		iterator find(const K& key) {return pTable.find(key);}
		const_iterator find(const K& key) const {return pTable.find(key);}

		/*!
		** \brief Get the value of a key
		**
		** \param key The key to find
		** \param defvalue The default value if the key can not be found
		** \return The value ofthe key, `defvalue` if the key could not be found
		*/
		V value(const K& key, const V& defvalue = V()) const;


		/*!
		** \brief Returns a read/write iterator that points to the first element of the table
		*/
		iterator begin() {return pTable.begin();}
		/*!
		** \brief Returns a read-only (constant) iterator that points to the first element of the table
		*/
		const_iterator begin() const {return pTable.begin();}

		/*!
		** \brief Returns a read/write iterator that points to the end of the table
		*/
		iterator end() {return pTable.end();}
		/*!
		** \brief Returns a read-only (constant) iterator that points to the end of the table
		*/
		const_iterator end() const {return pTable.end();}

		/*!
		** \brief Clear the table
		*/
		void clear() {pTable.clear();}

		/*!
		** \brief Erase a single key
		**
		** \param key The key to find
		** \return True if the key has been erased, False if not found
		*/
		void erase(const K& key);


	private:
		//! The real hash map
		YuniSTLExt::hash_map< K, V, YuniSTLExt::hash<K> >  pTable;

	}; // class Hash::Table




} // namespace Hash
} // namespace Yuni


# include <yuni/hash/table.hxx>

#endif // __YUNI_HASH_TABLE_H__
