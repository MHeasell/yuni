#ifndef __YUNI_PARSER_GENERATOR_NODE_H__
# define __YUNI_PARSER_GENERATOR_NODE_H__

# include "../../yuni.h"
# include "../../core/string.h"
# include <map>
# include <iosfwd>


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

		void clear();
		void print(std::ostream& out, uint depth = 0) const;
		bool checkRules(AnyString& error, const Node::Map& rules) const;
		void exportDepsToDOT(Clob& out, const AnyString& sourcerulename) const;

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

	}; // class Node





} // namespace PEG
} // namespace Parser
} // namespace Yuni

# include "node.hxx"

#endif // __YUNI_PARSER_GENERATOR_NODE_H__
