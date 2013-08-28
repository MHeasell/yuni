#ifndef __YUNI_PARSER_GENERATOR_RULE_LIST_HXX__
# define __YUNI_PARSER_GENERATOR_RULE_LIST_HXX__

# include <cassert>



namespace Yuni
{
namespace Parser
{
namespace Generator
{
namespace Rule
{

	class Any final  { };


	template<class T>
	class Rep final
	{
	public:
		Rep(const T& expr, uint n, uint m = Yuni::Parser::Generator::inf) :
			expression(expr)
		{
			assert(n <= m and "invalid repeat interval");
		}

	public:
		//! The sub expression
		T expression;
		//! The minimum number of occurences
		uint n;
		//! The maximum number of occurences
		uint m;

	}; // class Rep



	template<class T, class S>
	class List final
	{
	public:
		List(const T& elem, const S& sep, const V<uint>& n, const V<uint>& m) :
			element(elem),
			separator(sep),
			n(n),
			m(m)
		{}

	public:
		//! Expression for each element
		T element;
		//! Expression for a single separator
		S separator;
		//! The minimum number of elements
		V<uint> n;
		//! The maximum number of elements
		V<uint> m;

	}; // class List



	class StringMatch final
	{
	public:
		StringMatch(const AnyString& text) :
			text(text)
		{}

	public:
		//! Text to match
		AnyString text;

	}; // class StringMatch





} // namespace Rule
} // namespace Generator
} // namespace Parser
} // namespace Yuni

#endif // __YUNI_PARSER_GENERATOR_RULE_LIST_HXX__
