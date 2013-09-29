
#include "node.h"



namespace Yuni
{
namespace Parser
{
namespace PEG
{

	template<class StreamT>
	static inline void PrintText(StreamT& out, const String& text)
	{
		String::const_utf8iterator end = text.utf8end();
		String::const_utf8iterator i   = text.utf8begin();

		for (; i != end; ++i)
		{
			if (i->size() == 1)
			{
				switch ((char) *i)
				{
					case '\n': out << "\\\\n"; break;
					case '\t': out << "\\\\t"; break;
					case '\r': out << "\\\\r"; break;
					case '\f': out << "\\\\f"; break;
					case '\v': out << "\\\\v"; break;
					case '"' : out << "\\\\\""; break;
					default: out << *i;
				}
			}
			else
				out << *i;
		}
	}



	static inline void PrintSubNodesIDs(Clob& out, const Node& node)
	{
		if (node.rule.type == Node::asRule and node.rule.text == "EOF")
			return;

		out << "\t\t\"" << node.id << "\" [label = \"";
		if (node.match.negate)
			out << "! ";

		switch (node.rule.type)
		{
			case Node::asAND:
			{
				out << "AND";
				break;
			}
			case Node::asOR:
			{
				out << "OR";
				break;
			}
			case Node::asString:
			{
				out << "\\\"";
				PrintText(out, node.rule.text);
				out << "\\\"";
				break;
			}
			case Node::asSet:
			{
				out << "one of \\\"";
				PrintText(out, node.rule.text);
				out << "\\\"";
				break;
			}
			case Node::asRule:
			{
				PrintText(out, node.rule.text);
				break;
			}
			default:
				PrintText(out, node.rule.text);
		}

		out << "\"";

		if (node.rule.type == Node::asAND or node.rule.type == Node::asOR)
			out << " shape = diamond";

		out << "];\n";
		for (uint i = 0; i != node.children.size(); ++i)
			PrintSubNodesIDs(out, node.children[i]);
	}


	static inline void PrintSubNodesLinks(Clob& out, const Node::Map& rules, const Node& node, const String& source, bool inverseColor)
	{
		if (node.rule.type == Node::asRule)
			return;

		if (node.rule.type == Node::asRule)
		{
			Node::Map::const_iterator i = rules.find(node.rule.text);
			if (i != rules.end())
				out << "\t\t\"" << source << "\" -> \"" << i->second.id << "\"";
			else
				out << "\t\t\"" << source << "\" -> \"" << node.id << "\"";
		}
		else
			out << "\t\t\"" << source << "\" -> \"" << node.id << "\"";

		out << ";\n";

		// relation
		if (not (node.match.min == 1 and node.match.max == 1))
		{
			out << "\t\t\"" << node.id << "\" -> \"" << node.id << "\" [";
			if (node.rule.type == Node::asRule)
				out << "lhead = \"cluster-" << node.rule.text << "\"; ";
			out << "label=<<font color=\"#FF5500\">";

			if (node.match.min == 0 and node.match.max == (uint) -1)
				out << '*' << node.id;
			else if (node.match.min == 0 and node.match.max == 1)
				out << '?';
			else if (node.match.min == 1 and node.match.max == (uint) -1)
				out << '+';
			else
			{
				out << '{' << node.match.min << ',';
				if (node.match.max == (uint) -1)
					out << 'n';
				else
					out << node.match.max;
				out << '}';
			}

			out << "</font>>];\n";
		}

		// display all subnodes
		if (not node.children.empty())
		{
			out << "\t\tsubgraph \"cluster-" << node.id << "\" {\n";
			if (inverseColor)
			{
				out << "\t\tstyle = filled;\n";
				out << "\t\tcolor = lightgrey;\n";
				out << "\t\tnode [style = filled, color = white];\n";
			}
			else
			{
				out << "\t\tstyle = filled;\n";
				out << "\t\tcolor = \"#dfdfdf\";\n";
				out << "\t\tnode [style = filled, color = lightgrey];\n";
			}

			switch (node.rule.type)
			{
				case Node::asOR:
				{
					PrintSubNodesLinks(out, rules, node.children[0], node.id, not inverseColor);
					for (uint i = 1; i != node.children.size(); ++i)
						PrintSubNodesLinks(out, rules, node.children[i], node.id, not inverseColor);
					break;
				}
				default:
				{
					PrintSubNodesLinks(out, rules, node.children[0], node.id, not inverseColor);
					for (uint i = 1; i != node.children.size(); ++i)
						PrintSubNodesLinks(out, rules, node.children[i], node.children[i - 1].id, not inverseColor);
				}
			}

			out << "\t\t}\n";
		}
	}





	void Node::clear()
	{
		match.negate = false;
		match.min = 1;
		match.max = 1;
		rule.type = asRule;
		rule.text.clear();
		children.clear();
	}


	void Node::resetIndex(uint& base)
	{
		id.clear() << "n" << base;
		++base;
		for (uint i = 0; i != children.size(); ++i)
			children[i].resetIndex(base);
	}


	void Node::resetRuleIndexesFromMap(const Node::Map& rules)
	{
		if (rule.type == Node::asRule)
		{
			if (rule.text == "EOF")
			{
				id = "EOF";
				enumID.clear();
			}
			else
			{
				Node::Map::const_iterator i = rules.find(rule.text);
				if (i != rules.end())
				{
					id = (i->second).id;
					enumID = (i->second).enumID;
				}
			}
		}

		for (uint i = 0; i != children.size(); ++i)
			children[i].resetRuleIndexesFromMap(rules);
	}


	void Node::resetEnumID(const AnyString& rulename)
	{
		enumID.clear();
		enumID << "rg";

		bool maj = false;
		AnyString::const_utf8iterator end = rulename.utf8end();
		AnyString::const_utf8iterator i   = rulename.utf8begin();
		for (; i != end; ++i)
		{
			char c = (char) *i;
			if (c == '-' or c == '_' or c == ' ')
			{
				maj = true;
			}
			else
			{
				if (not maj)
				{
					enumID += *i;
				}
				else
				{
					maj = false;
					if (i->size() > 1)
						enumID += *i;
					else
						enumID += (char) String::ToUpper(c);
				}
			}
		}

		if (enumID.size() > 2)
			enumID[2] = (char) String::ToUpper(enumID[2]);
	}


	bool Node::checkRules(AnyString& error, const Node::Map& rules) const
	{
		if (rule.type == asRule)
		{
			if (rule.text != '|' and rule.text != '.' and rule.text != "EOF")
			{
				if (rules.count(rule.text) == 0)
				{
					error = rule.text;
					return false;
				}
			}
		}

		for (uint i = 0; i != children.size(); ++i)
		{
			if (not children[i].checkRules(error, rules))
				return false;
		}
		return true;
	}



	void Node::exportDOTSubgraph(Clob& out, const Node::Map& rules, const String& rulename) const
	{
		// display all subnodes
		out << "\t\t\"" << id << "\" [label = \"" << rulename << "\"];\n";
		for (uint i = 0; i != children.size(); ++i)
			PrintSubNodesIDs(out, children[i]);

		// display all subnodes
		if (not children.empty())
		{
			PrintSubNodesLinks(out, rules, children[0], id, false);
			for (uint i = 1; i != children.size(); ++i)
				PrintSubNodesLinks(out, rules, children[i], children[i - 1].id, false);
		}
	}


	static inline Clob& PrintTabs(Clob& out, uint depth)
	{
		for (uint i = 0; i != depth; ++i)
			out += '\t';
		return out;
	}


	static inline Clob& PrintString(Clob& out, const String& text)
	{
		String::const_utf8iterator end = text.utf8end();
		String::const_utf8iterator i   = text.utf8begin();

		for (; i != end; ++i)
		{
			if (i->size() == 1)
			{
				switch ((char) *i)
				{
					case '\n': out << "\\n"; break;
					case '\t': out << "\\t"; break;
					case '\r': out << "\\r"; break;
					case '\f': out << "\\f"; break;
					case '\v': out << "\\v"; break;
					case '"' : out << "\\\""; break;
					default: out << *i;
				}
			}
			else
				out << *i;
		}

		return out;
	}


	static inline void PrintAsciiChar(Clob& out, char c)
	{
		switch (c)
		{
			case '\'':  out << "\\\'";break;
			case '\n':  out << "\\n";break;
			case '\t':  out << "\\t";break;
			case '\r':  out << "\\r";break;
			case '\f':  out << "\\f";break;
			case '\v':  out << "\\v";break;
			default: out << c;
		}
	}


	void Node::exportCPP(Clob& out, uint depth) const
	{
		uint d = depth;
		switch (rule.type)
		{
			case Node::asRule:
			{
				PrintTabs(out, d) << "goto i_" << rule.text << ";\n";
				break;
			}
			case Node::asString:
			{
				if (rule.text.size() == 1)
				{
					PrintTabs(out, d) << "if (not matchSingleAsciiChar('";
					PrintAsciiChar(out, rule.text[0]);
					out << "'))\n";
					PrintTabs(out, d) << "\tgoto i_ERROR;\n";
				}
				else
				{
					PrintTabs(out, d) << "if (not matchString(AnyString(\"";
					PrintString(out, rule.text) << "\", " << rule.text.size() << ")))" << '\n';
					PrintTabs(out, d) << "\tgoto i_ERROR;\n";
				}
				break;
			}
		}

		for (uint i = 0; i != children.size(); ++i)
		{
			PrintTabs(out, d) << "{\n";
			children[i].exportCPP(out, d + 1);
			PrintTabs(out, d) << "}\n";
		}
	}





} // namespace PEG
} // namespace Parser
} // namespace Yuni

