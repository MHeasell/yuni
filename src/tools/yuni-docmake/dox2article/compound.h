#ifndef __YUNI_TOOL_DOCMAKE_DOXYGEN_2_ARTICLE_COMPOUND_H__
# define __YUNI_TOOL_DOCMAKE_DOXYGEN_2_ARTICLE_COMPOUND_H__

# include <yuni/yuni.h>
# include <yuni/core/string.h>
# include <map>
# include <deque>


namespace Yuni
{
namespace Edalene
{
namespace Dox2Article
{


	class Compound
	{
	public:
		//! Reference ID
		typedef CString<256,false> RefID;
		//! The most suitable smart ptr
		typedef SmartPtr<Compound>  Ptr;
		//! Map
		typedef std::map<RefID, Ptr>  Map;
		//! Deque
		typedef std::deque<Ptr>  Deque;

		//! Any kind of compound
		enum Kind
		{
			kdUnknown = 0,
			kdNamespace,
			kdClass,
			kdFunction,
			kdVariable,
			kdTypedef,
			kdEnum,
			kdFile,
			kdFolder,
			kdGroup,
			kdMax
		};

		//! All symbols, ordered by their type
		typedef Map*  MapPerKind;

	public:
		template<class StringT> static Kind  StringToKind(const StringT& str);
		template<class StreamT> static void AppendKindToString(StreamT& out, Kind kind);

	public:
		Compound();
		~Compound();

		void prepare();


	public:
		//! Kind of compound
		Kind kind;
		//! Reference ID
		RefID refid;
		//!
		String name;

		String htdocs;

		Map members;

		Compound* parent;

	}; // class Compound










	//! All symbols ordered by their reference id
	extern Compound::Map  allSymbolsByRefID;

	//! All symbols, ordered by their type and their reference id
	extern Compound::MapPerKind  allSymbols;

	//! All symbols, ordered by their type and their name
	extern Compound::MapPerKind  allSymbolsByName;




} // namespace Dox2Article
} // namespace Edalene
} // namespace Yuni

# include "compound.hxx"

#endif // __YUNI_TOOL_DOCMAKE_DOXYGEN_2_ARTICLE_COMPOUND_H__
