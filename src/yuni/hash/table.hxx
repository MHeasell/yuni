#ifndef __YUNI_HASH_TABLE_HXX__
# define __YUNI_HASH_TABLE_HXX__


namespace Yuni
{
namespace Hash
{


	/*!
	** Partial specialization when the hash table must be thread-safe
	** Be cautious : Choose carefully the routines you call to avoid
	** as musch as possible the overhead produced by the locking mechanism
	*/
	template<typename K, typename V>
	class Table<K, V, true>
	{
	public:
		typedef typename YuniSTLExt::hash_map< K, V, YuniSTLExt::hash<K> >::iterator  iterator;

	public:
		Table() : pTable() {}
		Table(const Table& c) : pTable(c.pTable) {}
		virtual ~Table() {}

		bool exists(const K& key) {MutexLocker locker(pMutex);return pTable.find(key) != pTable.end();}

		V& operator[] (const K& key) {MutexLocker locker(pMutex);return pTable[key];}

		iterator find(const K& key) {MutexLocker locker(pMutex);return pTable.find(key);}

		V value(const K& key, const V& defvalue = V());

		iterator begin() {MutexLocker locker(pMutex);return pTable.begin();}

		iterator end() {MutexLocker locker(pMutex); return pTable.end();}

		void clear() {pTable.clear();}

		void erase(const K& key);

	private:
		//! The mutex
		Mutex pMutex;
		//! The real hash map
		YuniSTLExt::hash_map< K, V, YuniSTLExt::hash<K> >  pTable;
	};




	template<typename K, typename V, bool ThreadSafe>
	void Table<K,V,ThreadSafe>::erase(const K& key)
	{
		iterator it = pTable.find(key);
		if (pTable.end() != it)
			pTable.erase(it);
	}


	template<typename K, typename V, bool ThreadSafe>
	V Table<K,V,ThreadSafe>::value(const K& key, const V& defvalue) const
	{
		const_iterator it = pTable.find(key);
		return (it == pTable.end()) ? defvalue : it->second;
	}
	
	
	template<typename K, typename V>
	V Table<K,V,true>::value(const K& key, const V& defvalue)
	{
		MutexLocker locker(pMutex);
		iterator it = pTable.find(key);
		return (it == pTable.end()) ? defvalue : it->second;
	}

	template<typename K, typename V>
	void Table<K,V,true>::erase(const K& key)
	{
		pMutex.lock();
		iterator it = pTable.find(key);
		if (pTable.end() != it)
			pTable.erase(it);
		pMutex.unlock();
	}






} // namespace Hash
} // namespace Yuni

#endif // __YUNI_HASH_TABLE_HXX__
