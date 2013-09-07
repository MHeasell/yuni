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


	template<class StreamT> void RuleTypeToString(StreamT& out, RuleType type)
	{
		switch (type)
		{
			case rtRule:         out << "rule";break;
			case rtGroup:        out << "group";break;
			case rtModifier:     out << "modifier";break;
			case rtString:       out << "string";break;
			case rtListOfChars:  out << "set";break;
		}
	}




} // namespace PEG
} // namespace Parser
} // namespace Yuni

#endif // __YUNI_PARSER_GENERATOR_GRAMMAR_H__
