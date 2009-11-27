#ifndef __YUNI_CORE_STATIC_INHERIT_H__
# define __YUNI_CORE_STATIC_INHERIT_H__

# include "../../yuni.h"


namespace Yuni
{
namespace Static
{

	/*!
	** \brief Statically check if an arbitrary class C is a descendant of another one
	**
	** \code
	** #include <yuni/static/inherit.h>
	** #include <iostream>
	**
	** class Base {};
	**
	** class A : public Base {};
	**
	** class B {};
	**
	** int main()
	** {
	** 	std::cout << "A inherits from Base :" << Yuni::Static::InheritsFrom<A,Base>::Yes << "\n";
	** 	std::cout << "B inherits from Base :" << Yuni::Static::InheritsFrom<B,Base>::Yes << "\n";
	** 	return 0;
	** }
	** \endcode
	**
	** \tparam C Any class (may be virtual)
	** \tparam BaseT The base class to compare with (may be virtual)
	*/
	template<class C, class BaseT>
	class InheritsFrom
	{
	private:
		typedef sint32 True;
		typedef sint8  False;

		// C obvisouly inherits from BaseT
		static True CheckIfCInheritsFromBaseT(const BaseT*);
		// C does not inherits from BaseT
		static False CheckIfCInheritsFromBaseT(...);
		// A dummy routine, for returning a type C
		static C* DummyClassCMaker();

	public:
		enum
		{
			//! A non-zero value if C inherits from BaseT
			Yes = sizeof(CheckIfCInheritsFromBaseT(DummyClassCMaker())) == sizeof(True),
			//! A non-zero value if C does not inherit from BaseT
			No = sizeof(CheckIfCInheritsFromBaseT(DummyClassCMaker())) == sizeof(False),
		};
	};




} // namespace Static
} // namespace Yuni

#endif // __YUNI_CORE_STATIC_INHERIT_H__
