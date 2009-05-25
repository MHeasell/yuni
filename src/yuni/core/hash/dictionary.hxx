#ifndef __YUNI_HASH_DICTIONARY_HXX__
# define __YUNI_HASH_DICTIONARY_HXX__



# define YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC(O,K,XT,CONV) \
	template<> \
	XT Dictionary<String,O>:: CONV (const String& key, const XT defvalue) \
	{ \
		iterator it = TableType::find(K); \
		return (end() == it || it->second.empty()) ? defvalue : it->second. CONV (); \
	}

# define YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC_CONST(O,K,XT,CONV) //\

	//template<> \
	//XT Dictionary<String,O>:: CONV (const String& key, const XT defvalue) const \
	//{ \
	//	const_iterator it = TableType::find(K); \
	//	return (end() == it || it->second.empty()) ? defvalue : it->second. CONV (); \
	//}

# define YUNI_HASH_DICTIONARY_STRIMPL_STRING(O,K) \
	template<> \
	String Dictionary<String,O>:: CONV (const String& key, const String& defvalue) \
	{ \
		iterator it = TableType::find(K); \
		return (end() == it || it->second.empty()) ? defvalue : it->second; \
	}

# define YUNI_HASH_DICTIONARY_STRIMPL_STRING_CONST(O,K,XT) //\

	//template<> \
	//String Dictionary<String,O>:: CONV (const String& key, const String& defvalue) const \
	//{ \
	//	const_iterator it = TableType::find(K); \
	//	return (end() == it || it->second.empty()) ? defvalue : it->second; \
	//}





namespace Yuni
{
namespace Hash
{




	template<typename V>
	class Dictionary<V, optThreadSafe> : public Table<String, V, Policy::ObjectLevelLockable>
	{
	public:
		typedef Table<String, V, Policy::ObjectLevelLockable> TableType;
		typedef typename TableType ::iterator  iterator;

	public:
		//! \name Constructors & Destructor
		//@{
		//! Default constructor
		Dictionary() : TableType() {}
		//! Copy constructor
		Dictionary(const Dictionary& c) : TableType(c) {}
		//! Destructor
		virtual ~Dictionary() {TableType::clear();}
		//@}

		bool exists(const String& key) {return TableType::exists(key);}

		V& operator[] (const String& key) {return (*(static_cast < Table<String, V, optThreadSafe > * > (this)))[key];}

		iterator find(const String& key) {return TableType::find(key);}

		V value(const String& key, const V& defvalue = V()) {return TableType::value(key, defvalue);}

		iterator begin() {return TableType::begin();}

		iterator end() {return TableType::end();}

		void clear() {TableType::clear();}

		void erase(const String& key) {TableType::erase(key);}

		int size() {return TableType::size();}

	}; // class Hash::Dictionary




	template<typename V>
	class Dictionary<V, optIgnoreCase | optThreadSafe> : public Table<String, V, Policy::ObjectLevelLockable>
	{
	public:
		typedef Table<String, V, Policy::ObjectLevelLockable> TableType;
		typedef typename TableType ::iterator  iterator;

	public:
		//! \name Constructors & Destructor
		//@{
		//! Default constructor
		Dictionary() : TableType() {}
		//! Copy constructor
		Dictionary(const Dictionary& c) : TableType(c) {}
		//! Destructor
		virtual ~Dictionary() {TableType::clear();}
		//@}

		bool exists(String key) {return TableType::exists(key.toLower());}

		V& operator[] (String key) {return (*(static_cast < TableType* > (this)))[key.toLower()];}

		iterator find(String key) {return TableType::find(key.toLower());}

		V value(String key, const V& defvalue = V()) {return TableType::value(key.toLower(), defvalue);}

		iterator begin() {return TableType::begin();}

		iterator end() {return TableType::end();}

		void clear() {TableType::clear();}

		void erase(String key) {TableType::erase(key.toLower());}

		int size() {return TableType::size();}

	}; // class Hash::Dictionary




	template<typename V>
	class Dictionary<V, optIgnoreCase> : public Table<String, V, Policy::SingleThreaded>
	{
	public:
		typedef Table<String, V, Policy::SingleThreaded> TableType;
		typedef typename TableType ::iterator  iterator;
		typedef typename TableType ::const_iterator  const_iterator;

	public:
		//! \name Constructors & Destructor
		//@{
		//! Default constructor
		Dictionary() : TableType() {}
		//! Copy constructor
		Dictionary(const Dictionary& c) : TableType(c) {}
		//! Destructor
		virtual ~Dictionary() {TableType::clear();}
		//@}

		bool exists(String key) const {return TableType::exists(key.toLower());}

		V& operator[] (String key) {return (*(static_cast <TableType*> (this)))[key.toLower()];}

		iterator find(String key) {return TableType::find(key.toLower());}
		const_iterator find(String key) const {return TableType::find(key.toLower());}

		V value(String key, const V& defvalue = V()) {return TableType::value(key.toLower(), defvalue);}

		iterator begin() {return TableType::begin();}
		const_iterator begin() const {return TableType::begin();}

		iterator end() {return TableType::end();}
		const_iterator end() const {return TableType::end();}

		void clear() {TableType::clear();}

		void erase(String key) {TableType::erase(key.toLower());}

		int size() {return TableType::size();}

	}; // class Hash::Dictionary






	YUNI_HASH_DICTIONARY_STRIMPL_STRING_CONST(optNone, key)
	YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC_CONST(optNone, key, sint8,  toInt8())
	YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC_CONST(optNone, key, sint16, toInt16)
	YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC_CONST(optNone, key, sint32, toInt32)
	YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC_CONST(optNone, key, sint64, toInt64)
	//
	YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC_CONST(optNone, key, uint8,  toUInt8)
	YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC_CONST(optNone, key, uint16, toUInt16)
	YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC_CONST(optNone, key, uint32, toUInt32)
	YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC_CONST(optNone, key, uint64, toUInt64)
	//
	YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC_CONST(optNone, key, float,  toFloat)
	YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC_CONST(optNone, key, double, toDouble)
	YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC_CONST(optNone, key, bool,   toBool)

} // namespace Hash
} // namespace Yuni


# undef YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC
# undef YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC_CONST
# undef YUNI_HASH_DICTIONARY_STRIMPL_STRING
# undef YUNI_HASH_DICTIONARY_STRIMPL_STRING_CONST

#endif // __YUNI_HASH_DICTIONARY_HXX__
