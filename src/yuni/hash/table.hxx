#ifndef __YUNI_HASH_TABLE_HXX__
# define __YUNI_HASH_TABLE_HXX__


namespace Yuni
{
namespace Hash
{


    template<class K, typename V>
    Table<K,V>::Table()
        :pTable()
    {}

    template<class K, typename V>
    Table<K,V>::~Table()
    {
        clear();
    }


    template<class K, typename V>
    Table<K,V>::Table(const Table& c)
        :pTable(c.pTable)
    {}


    template<class K, typename V>
    V& Table<K,V>::value(const K& key, const V& defvalue) const
    {
        const_iterator it = find(key);
        return (it == end()) ? defvalue : it->second;
    }

    template<class K, typename V>
    void Table<K,V>::clear()
    {
        pTable.clear();
    }

    template<class K, typename V>
    void Table<K,V>::erase(const K& key)
    {
        iterator it = pTable.find(key);
        if (end() != it)
        {
            pTable.erase(it);
        }
    }



} // namespace Hash
} // namespace Yuni

#endif // __YUNI_HASH_TABLE_HXX__
