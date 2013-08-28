#ifndef __YUNI_PARSER_GENERATOR_RULE_RULE_HXX__
# define __YUNI_PARSER_GENERATOR_RULE_RULE_HXX__


namespace Yuni
{
namespace Parser
{
namespace Generator
{

	template<class T> inline Rule::Rep<T>  rep(const T& expr, const V<uint>& n, const V<uint>& m)
	{
		return Rule::Rep<T>(expr, n, m);
	}


	template<class T> inline Rule::Rep<T> plus(const T& expr)
	{
		return Rule::Rep<T>(expr, 1);
	}


	template<class T> inline Rule::Rep<T> star(const T& expr)
	{
		return Rule::Rep<T>(expr, 0);
	}


	template<class T> inline Rule::Rep<T>  opt(const T& expr)
	{
		return Rule::Rep<T>(expr, 0, 1);
	}


	template<class T> inline Rule::Rep<T>  rep(const T& expr, const V<uint>& m)
	{
		return Rule::Rep<T>(expr, n);
	}


	template<class T, class S>
	inline Rule::List<T,S> list(const T& elem, const S& sep, const V<uint>& n, const V<uint>& m)
	{
		return Rule::List<T,S>(elem, sep, n, m);
	}





} // namespace Generator
} // namespace Parser
} // namespace Yuni

#endif // __YUNI_PARSER_GENERATOR_RULE_RULE_HXX__
