#ifndef __YUNI_PARSER_GENERATOR_NODE_HXX__
# define __YUNI_PARSER_GENERATOR_NODE_HXX__



namespace Yuni
{
namespace Parser
{
namespace PEG
{

	inline Node::Node()
	{
		match.negate = false;
		match.min = 1;
		match.max = 1;
		rule.type = asRule;
	}





} // namespace PEG
} // namespace Parser
} // namespace Yuni

#endif // __YUNI_PARSER_GENERATOR_NODE_HXX__
