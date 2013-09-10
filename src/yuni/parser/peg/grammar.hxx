#ifndef __YUNI_PARSER_GENERATOR_GRAMMAR_HXX__
# define __YUNI_PARSER_GENERATOR_GRAMMAR_HXX__


namespace Yuni
{
namespace Parser
{
namespace PEG
{


	inline bool Grammar::loadFromString(const AnyString& content)
	{
		return loadFromData(content, "<memory>");
	}


	namespace // anonymous
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

	} // anonymous namespace


	template<class StreamT>
	void Node::print(StreamT& out, uint depth) const
	{
		for (uint i = 0; i != depth; ++i)
			out << "    ";
		out << ((match.negate) ? "- " : "+ ");

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




} // namespace PEG
} // namespace Parser
} // namespace Yuni

#endif // __YUNI_PARSER_GENERATOR_GRAMMAR_H__
