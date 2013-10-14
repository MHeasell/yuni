
template<class StreamT>
static inline void PrepareCPPInclude(StreamT& out)
{
	out << '\n';
	out << "	# define TRACE(X)  std::cout << \"  :: \" << ctx.urls[ctx.stack[ctx.offset].urlindex] \\\n";
	out << "		<< \", depth:\" << ctx.offset << \": \" << X << std::endl\n";
	out << '\n';
	out << "	# define TRACE_LOCAL(X)  std::cout << \"  :: \" << urls[stack[offset].urlindex] \\\n";
	out << "		<< \", depth:\" << offset << \": \" << X << std::endl\n";
	out << '\n';
	out << '\n';
	out << "	struct Chunk\n";
	out << "	{\n";
	out << "		//! Iterator on the source\n";
	out << "		uint offset;\n";
	out << "		//! Index of the current source url (see `urls`)\n";
	out << "		uint urlindex;\n";
	out << "	};\n";
	out << '\n';
	out << '\n';
	out << '\n';
	out << "	class Datasource final\n";
	out << "	{\n";
	out << "	public:\n";
	out << '\n';
	out << "	public:\n";
	out << "		//! \\name Constructors\n";
	out << "		//@{\n";
	out << "		//! Default constructor\n";
	out << "		Datasource();\n";
	out << "		~Datasource();\n";
	out << "		//@}\n";
	out << '\n';
	out << "		//! \\name Matching\n";
	out << "		//@{\n";
	out << "		bool matchSingleAsciiChar(char);\n";
	out << "		bool matchString(const AnyString& text, uint ut8Count);\n";
	out << "		bool matchOneOf(const AnyString& text, uint utf8count);\n";
	out << "		//@}\n";
	out << '\n';
	out << "		//! \\name Chunk\n";
	out << "		//@{\n";
	out << "		void pushInclude(uint urlindex);\n";
	out << "		uint push();\n";
	out << "		void restart(uint from);\n";
	out << "		void pop();\n";
	out << "		//@}\n";
	out << '\n';
	out << "		//! \\name Filename manipulation\n";
	out << "		//@{\n";
	out << "		//! Open a new url\n";
	out << "		bool open(const AnyString& newurl);\n";
	out << "		//! Open from anonymous origin\n";
	out << "		void openContent(const AnyString& content);\n";
	out << "		//! Close the current url\n";
	out << "		void close();\n";
	out << "		//@}\n";
	out << '\n';
	out << "	public:\n";
	out << "		//! Stack\n";
	out << "		Chunk* stack;\n";
	out << "		uint offset;\n";
	out << "		uint capacity;\n";
	out << '\n';
	out << "		//! Root folder\n";
	out << "		String root;\n";
	out << "		//! File Content of all encountered urls, ordered by their order of arrival\n";
	out << "		Clob::Vector contents;\n";
	out << "		//! Reverse mapping for retriving the index of a known file\n";
	out << "		::Yuni::Dictionary<AnyString, uint>::Unordered  reverseUrlIndexes;\n";
	out << "		//! All urls\n";
	out << "		::Yuni::String::Vector urls;\n";
	out << '\n';
	out << "	}; // class Datasource\n";
	out << '\n';
	out << '\n';
	out << '\n';
	out << "	inline Datasource::Datasource() :\n";
	out << "		offset(0),\n";
	out << "		capacity(512)\n";
	out << "	{\n";
	out << "		stack = (Chunk*)::malloc(sizeof(Chunk) * capacity);\n";
	out << "		stack[0].offset   = (uint) -1; // EOF\n";
	out << "		stack[0].urlindex = 0; // the first one will be good enough\n";
	out << "	}\n";
	out << '\n';
	out << '\n';
	out << "	inline Datasource::~Datasource()\n";
	out << "	{\n";
	out << "		::free(stack);\n";
	out << "	}\n";
	out << '\n';
	out << '\n';
	out << "	inline void Datasource::pushInclude(uint urlindex)\n";
	out << "	{\n";
	out << "		if (not (++offset < capacity))\n";
	out << "		{\n";
	out << "			// Grow !\n";
	out << "			capacity += 512;\n";
	out << "			stack = (Chunk*)::realloc(stack, capacity * sizeof(Chunk));\n";
	out << "		}\n";
	out << "		stack[offset].urlindex = urlindex;\n";
	out << "		stack[offset].offset = 0;\n";
	out << "	}\n";
	out << '\n';
	out << '\n';
	out << "	inline uint Datasource::push()\n";
	out << "	{\n";
	out << "		if (not (++offset < capacity))\n";
	out << "		{\n";
	out << "			// Grow !\n";
	out << "			capacity += 512;\n";
	out << "			stack = (Chunk*)::realloc(stack, capacity * sizeof(Chunk));\n";
	out << "		}\n";
	out << "		stack[offset] = stack[offset - 1];\n";
	out << "		TRACE_LOCAL(\"    push at offset \" << stack[offset].offset);\n";
	out << "		return offset - 1;\n";
	out << "	}\n";
	out << '\n';
	out << '\n';
	out << "	inline void Datasource::restart(uint from)\n";
	out << "	{\n";
	out << "		assert(from + 1 < capacity);\n";
	out << "		offset = from + 1;\n";
	out << "		stack[offset] = stack[offset - 1];\n";
	out << "		TRACE_LOCAL(\"    restart at offset \" << stack[offset].offset);\n";
	out << "	}\n";
	out << '\n';
	out << '\n';
	out << "	inline void Datasource::pop()\n";
	out << "	{\n";
	out << "		assert(offset > 0 and \"internal error on offset\");\n";
	out << "		--offset;\n";
	out << "		TRACE_LOCAL(\"    pop to offset \" << stack[offset].offset);\n";
	out << "	}\n";
	out << '\n';
	out << '\n';
	out << "	inline bool Datasource::open(const AnyString& newurl)\n";
	out << "	{\n";
	out << "		// getting the root directory once and for all if not already done\n";
	out << "		// the operation is not done in the constructor to let the caller\n";
	out << "		// initialize this variable if needed\n";
	out << "		if (root.empty())\n";
	out << "			::Yuni::IO::Directory::Current::Get(root, false);\n";
	out << '\n';
	out << "		// canonicalizing the filename\n";
	out << "		String filename;\n";
	out << "		::Yuni::IO::Canonicalize(filename, newurl, root);\n";
	out << '\n';
	out << "		// filename index\n";
	out << "		uint index;\n";
	out << "		Yuni::Dictionary<AnyString, uint>::Unordered::const_iterator knownIndex = reverseUrlIndexes.find(filename);\n";
	out << "		if (YUNI_LIKELY(knownIndex == reverseUrlIndexes.end()))\n";
	out << "		{\n";
	out << "			// indexes\n";
	out << "			index = (uint) contents.size();\n";
	out << "			reverseUrlIndexes[filename] = index;\n";
	out << "			// load the entire content in memory\n";
	out << "			contents.push_back(nullptr);\n";
	out << "			urls.push_back(filename);\n";
	out << "			::Yuni::IO::File::LoadFromFile(contents.back(), filename);\n";
	out << "		}\n";
	out << "		else\n";
	out << "			index = knownIndex->second;\n";
	out << '\n';
	out << "		// new item in the stack\n";
	out << "		pushInclude(index);\n";
	out << "		return true;\n";
	out << "	}\n";
	out << '\n';
	out << '\n';
	out << "	inline void Datasource::openContent(const AnyString& content)\n";
	out << "	{\n";
	out << "		String filename = \"<memory>\";\n";
	out << "		// filename index\n";
	out << "		uint index;\n";
	out << "		::Yuni::Dictionary<AnyString, uint>::Unordered::const_iterator knownIndex = reverseUrlIndexes.find(filename);\n";
	out << "		if (YUNI_LIKELY(knownIndex == reverseUrlIndexes.end()))\n";
	out << "		{\n";
	out << "			// indexes\n";
	out << "			index = (uint) contents.size();\n";
	out << "			reverseUrlIndexes[filename] = index;\n";
	out << "			// load the entire content in memory\n";
	out << "			contents.push_back(nullptr);\n";
	out << "			urls.push_back(filename);\n";
	out << "			contents.back() = content;\n";
	out << "		}\n";
	out << "		else\n";
	out << "			index = knownIndex->second;\n";
	out << '\n';
	out << "		pushInclude(index);\n";
	out << "	}\n";
	out << '\n';
	out << '\n';
	out << "	inline bool Datasource::matchSingleAsciiChar(char c)\n";
	out << "	{\n";
	out << "		Chunk& cursor = stack[offset];\n";
	out << "		Clob&  data   = contents[cursor.urlindex];\n";
	out << "		if (cursor.offset < data.size() and c == data[cursor.offset])\n";
	out << "		{\n";
	out << "			++cursor.offset;\n";
	out << "			return true;\n";
	out << "		}\n";
	out << "		return false;\n";
	out << "	}\n";
	out << '\n';
	out << '\n';
	out << "	inline bool Datasource::matchString(const AnyString& text, uint ut8Count)\n";
	out << "	{\n";
	out << "		Chunk& cursor = stack[offset];\n";
	out << "		Clob&  data   = contents[cursor.urlindex];\n";
	out << '\n';
	out << "		if (AnyString(data, cursor.offset).startsWith(text))\n";
	out << "		{\n";
	out << "			cursor.offset += text.size();\n";
	out << "			return true;\n";
	out << "		}\n";
	out << "		return false;\n";
	out << "	}\n";
	out << '\n';
	out << '\n';
	out << "	inline bool Datasource::matchOneOf(const AnyString& text, uint utf8count)\n";
	out << "	{\n";
	out << "		Chunk& cursor = stack[offset];\n";
	out << "		Clob&  data   = contents[cursor.urlindex];\n";
	out << '\n';
	out << "		if (cursor.offset < data.size())\n";
	out << "		{\n";
	out << "			if (text.contains(data[cursor.offset]))\n";
	out << "			{\n";
	out << "				++cursor.offset;\n";
	out << "				return true;\n";
	out << "			}\n";
	out << "		}\n";
	out << "		return false;\n";
	out << "	}\n";
	out << '\n';
	out << '\n';
	out << "	static bool StandardURILoaderHandler(Clob& out, const AnyString& uri)\n";
	out << "	{\n";
	out << "		if (not uri.empty())\n";
	out << "		{\n";
	out << "			out.clear();\n";
	out << "			if (::Yuni::IO::errNone == ::Yuni::IO::File::LoadFromFile(out, uri))\n";
	out << "				return true;\n";
	out << "		}\n";
	out << "		return false;\n";
	out << "	}\n";
	out << '\n';
	out << '\n';
	out << '\n';
	out << '\n';
	out << '\n';
	out << "";
}