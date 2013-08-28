#ifndef __YUNI_PARSER_GENERATOR_VARIABLE_HXX__
# define __YUNI_PARSER_GENERATOR_VARIABLE_HXX__



namespace Yuni
{
namespace Parser
{
namespace Generator
{


	template<class T> class V;

	typedef V<uint>  Vuint;
	typedef V<int>   Vint;
	typedef V<bool>  Vbool;



	template<class T>
	class V final
	{
	public:
		V(const T& value, bool dynamic = true) :
			dynamic(dynamic),
			value(),
			index((uint) -1)
		{}

	public:
		//! Get if the value is dynamic (runtime dependant behavior)
		bool dynamic;
		//! Internal value
		T value;
		//! Variable index (if any)
		uint index;

	}; // class V






} // namespace Generator
} // namespace Parser
} // namespace Yuni

#endif // __YUNI_PARSER_GENERATOR_VARIABLE_HXX__
