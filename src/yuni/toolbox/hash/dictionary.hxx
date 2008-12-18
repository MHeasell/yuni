#ifndef __YUNI_HASH_DICTIONARY_HXX__
# define __YUNI_HASH_DICTIONARY_HXX__



# define YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC(O,K,XT,CONV) \
	template<> \
	XT Dictionary<String,O>:: CONV (const String& key, const XT defvalue) \
	{ \
		iterator it = Table<String, String, O>::find(K); \
		return (end() == it || it->second.empty()) ? defvalue : it->second. CONV (); \
	}

# define YUNI_HASH_DICTIONARY_STRIMPL_NUMERIC_CONST(O,K,XT,CONV) \
	template<> \
	XT Dictionary<String,O>:: CONV (const String& key, const XT defvalue) const \
	{ \
		const_iterator it = Table<String, String, O>::find(K); \
		return (end() == it || it->second.empty()) ? defvalue : it->second. CONV (); \
	}

# define YUNI_HASH_DICTIONARY_STRIMPL_STRING(O,K) \
	template<> \
	String Dictionary<String,O>:: CONV (const String& key, const String& defvalue) \
	{ \
		iterator it = Table<String, String, O>::find(K); \
		return (end() == it || it->second.empty()) ? defvalue : it->second; \
	}

# define YUNI_HASH_DICTIONARY_STRIMPL_STRING_CONST(O,K,XT) \
	template<> \
	String Dictionary<String,O>:: CONV (const String& key, const String& defvalue) const \
	{ \
		const_iterator it = Table<String, String, O>::find(K); \
		return (end() == it || it->second.empty()) ? defvalue : it->second; \
	}




 
namespace Yuni
{
namespace Hash
{




	template<typename V>
	class Dictionary<V, optThreadSafe> : public Table<String, V, true>
	{
	public:
		typedef typename Table<String, V, true> ::iterator  iterator;

	public:
		//! \name Constructors & Destructor
		//@{
		//! Default constructor
		Dictionary() : Table<String, V, true>() {}
		//! Copy constructor
		Dictionary(const Dictionary& c) : Table<String, V, true>(c) {}
		//! Destructor
		virtual ~Dictionary() {Table<String, V, true>::clear();}
		//@}

		bool exists(const String& key) {return Table<String, V, true>::exists(key);}

		V& operator[] (const String& key) {return (*(static_cast < Table<String, V, optThreadSafe > * > (this)))[key];}

		iterator find(const String& key) {return Table<String, V, true>::find(key);}

		V value(const String& key, const V& defvalue = V()) {return Table<String, V, true>::value(key, defvalue);}

		iterator begin() {return Table<String, V, true>::begin();}

		iterator end() {return Table<String, V, true>::end();}

		void clear() {Table<String, V, true>::clear();}

		void erase(const String& key) {Table<String, V, true>::erase(key);}

	}; // class Hash::Dictionary




	template<typename V>
	class Dictionary<V, optIgnoreCase | optThreadSafe> : public Table<String, V, true>
	{
	public:
		typedef typename Table<String, V, true> ::iterator  iterator;

	public:
		//! \name Constructors & Destructor
		//@{
		//! Default constructor
		Dictionary() : Table<String, V, true>() {}
		//! Copy constructor
		Dictionary(const Dictionary& c) : Table<String, V, true>(c) {}
		//! Destructor
		virtual ~Dictionary() {Table<String, V, true>::clear();}
		//@}

		bool exists(String key) {return Table<String, V, true>::exists(key.toLower());}

		V& operator[] (String key) {return (*(static_cast < Table<String, V, optThreadSafe > * > (this)))[key.toLower()];}

		iterator find(String key) {return Table<String, V, true>::find(key.toLower());}

		V value(String key, const V& defvalue = V()) {return Table<String, V, true>::value(key.toLower(), defvalue);}

		iterator begin() {return Table<String, V, true>::begin();}

		iterator end() {return Table<String, V, true>::end();}

		void clear() {Table<String, V, true>::clear();}

		void erase(String key) {Table<String, V, true>::erase(key.toLower());}

	}; // class Hash::Dictionary




	template<typename V>
	class Dictionary<V, optIgnoreCase> : public Table<String, V, false>
	{
	public:
		typedef typename Table<String, V, false> ::iterator  iterator;
		typedef typename Table<String, V, false> ::const_iterator  const_iterator;

	public:
		//! \name Constructors & Destructor
		//@{
		//! Default constructor
		Dictionary() : Table<String, V, false>() {}
		//! Copy constructor
		Dictionary(const Dictionary& c) : Table<String, V, false>(c) {}
		//! Destructor
		virtual ~Dictionary() {Table<String, V, false>::clear();}
		//@}

		bool exists(String key) const {return Table<String, V, false>::exists(key.toLower());}

		V& operator[] (String key) {return (*(static_cast < Table<String, V, false > * > (this)))[key.toLower()];}

		iterator find(String key) {return Table<String, V, false>::find(key.toLower());}
		const_iterator find(String key) const {return Table<String, V, false>::find(key.toLower());}

		V value(String key, const V& defvalue = V()) const {return Table<String, V, false>::value(key.toLower(), defvalue);}

		iterator begin() {return Table<String, V, false>::begin();}
		const_iterator begin() const {return Table<String, V, false>::begin();}

		iterator end() {return Table<String, V, false>::end();}
		const_iterator end() const {return Table<String, V, false>::end();}

		void clear() {Table<String, V, false>::clear();}

		void erase(String key) {Table<String, V, false>::erase(key.toLower());}

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
