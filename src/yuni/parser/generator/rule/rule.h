#ifndef __YUNI_PARSER_GENERATOR_RULE_RULE_H__
# define __YUNI_PARSER_GENERATOR_RULE_RULE_H__

# include "../variable.h"
# include "list.h"


namespace Yuni
{
namespace Parser
{
namespace Generator
{

	//! Infinity representation
	static const V<uint> inf = V<uint>((uint) -1, false);

	//! Any UTF8 character
	static const Rule::Any any;


	//! Instanciate a new dynamic variable
	//template<class T> Value<T, false>  var(const AnyString& name);

	//! Instanciate a new dynamic variable with a specific default value
	//template<class T> Value<T, false>  var(const AnyString& name, const T& defvalue);

	//! Instanciate a new parameter (static value)
	//template<class T> Value<T, true>   param(const AnyString& name, const T& defvalue);


	//! Match one of the given character
	Rule::One one(const AnyString& listofchars);

	//! Math a given string
	Rule::StringMatch string(const AnyString& text);


	//! E+ : One or more
	template<class T> Rule::Rep<T> plus(const T& expr);

	//! E* : Zero or more
	template<class T> Rule::Rep<T> star(const T& expr);

	//! E? : Zero or one (optional)
	template<class T> Rule::Rep<T>  opt(const T& expr);

	//! E{n} : N occurences
	template<class T, bool D> Rule::Rep<T>  rep(const T& expr, const V<uint>& m);

	//! E{n, m} : N up to M occurences
	template<class T, bool D> Rule::Rep<T>  rep(const T& expr, const V<uint>& n, const V<uint>& m);





	/*!
	** \brief List of element T, separated by S
	**
	** \param n The minimum number of elements
	** \param m The maximum number of elements
	*/
	template<class T, class S> Rule::List<T,S> list(const T& elem, const S& sep, const V<uint>& n = 0, const V<uint>& m = inf);




} // namespace Generator
} // namespace Parser
} // namespace Yuni

# include "rule.hxx"

#endif // __YUNI_PARSER_GENERATOR_RULE_RULE_H__
