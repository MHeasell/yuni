
#include "node.h"



namespace Yuni
{
namespace Parser
{
namespace PEG
{

	void Node::clear()
	{
		match.negate = false;
		match.min = 1;
		match.max = 1;
		rule.type = asRule;
		rule.text.clear();
		children.clear();
	}


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
	}



	void Node::print(std::ostream& out, uint depth) const
	{
		for (uint i = 0; i != depth; ++i)
			out << "    . ";

		if (match.negate)
			out << "not / ";

		switch (rule.type)
		{
			case asString:
			{
				out << "match string \"";
				PrintText(out, rule.text);
				out << '"';
				break;
			}
			case asSet:
			{
				out << "match one of \"";
				PrintText(out, rule.text);
				out << '"';
				break;
			}
			case asRule:
			{
				if (rule.text == '.')
					out << "match any";
				else
					out << "match rule " << rule.text;
				break;
			}
			case asAND:
			{
				out << "and";
				break;
			}
			case asOR:
			{
				out << "or";
				break;
			}
		}

		if (not (match.min == 1 and match.max == 1))
		{
			out << " {" << match.min << ',';
			if (match.max == (uint) -1)
				out << 'n';
			else
				out << match.max;
			out << '}';
		}

		out << '\n';

		++depth;
		for (uint i = 0; i != children.size(); ++i)
			children[i].print(out, depth);
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


	void Node::exportDepsToDOT(Clob& out, const AnyString& sourcerulename) const
	{
		if (rule.type == asRule)
		{
			if (rule.text != '|' and rule.text != '.' and rule.text != "EOF")
			{
				out << "\t\"" << sourcerulename << "\" -> \"" << rule.text << "\"";

				if (not (match.min == 1 and match.max == 1))
				{
					out << " [label=\"";
					if (match.min == 0 and match.max == (uint) -1)
						out << '*';
					else if (match.min == 0 and match.max == 1)
						out << '?';
					else if (match.min == 1 and match.max == (uint) -1)
						out << '+';
					else
					{
						out << '{' << match.min << ',';
						if (match.max == (uint) -1)
							out << 'n';
						else
							out << match.max;
						out << '}';
					}

					out << "\"]";
				}

				out << ";\n";

			}
		}

		for (uint i = 0; i != children.size(); ++i)
			children[i].exportDepsToDOT(out, sourcerulename);
	}




} // namespace PEG
} // namespace Parser
} // namespace Yuni

