#ifndef __YUNI_PARSER_GENERATOR_GRAMMAR_H__
# define __YUNI_PARSER_GENERATOR_GRAMMAR_H__

# include "../../yuni.h"
# include "../../core/string.h"
# include "../../core/noncopyable.h"
# include "../../core/event/event.h"
# include <map>


namespace Yuni
{
namespace Parser
{
namespace PEG
{

	class Node final
	{
	public:
		enum Type
		{
			asRule,
			asString,
			asSet,
			asAND,
			asOR,
		};

	public:
		//! List of nodes
		typedef std::vector<Node> Vector;
		//! Map of nodes
		typedef std::map<String, Node> Map;

	public:
		Node();

		template<class StreamT> void print(StreamT& out, uint depth = 0) const;

	public:
		struct
		{
			//! negate the return value
			bool negate;
			//! Minimum number of occurences
			uint min;
			//! Maximum number of occurences
			uint max;

			void reset(uint a, uint b) {min = a; max = b;}
		}
		match;

		struct
		{
			//! Type of node
			Type type;
			//! Text or set of chars to match
			String text;
		}
		rule;

		//! Sub nodes
		Vector children;
		//! Other possible match
		Vector alternatives;
		//! Has alternatives ? The keyword '|' has been found
		bool hasAlternatives;

	}; // class Node




	class Grammar final : private NonCopyable<Grammar>
	{
	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		Grammar();
		//! Destructor
		~Grammar();
		//@}

		bool loadFromFile(const AnyString& filename);
		bool loadFromString(const AnyString& content);


	public:
		//! Event: warning
		Event<void (const AnyString&)> onWarning;
		//! Event: error
		Event<void (const AnyString&)> onError;

	private:
		bool loadFromData(const AnyString& content, const AnyString& source);

	}; // class Grammar




} // namespace PEG
} // namespace Parser
} // namespace Yuni

# include "grammar.hxx"

#endif // __YUNI_PARSER_GENERATOR_GRAMMAR_H__
