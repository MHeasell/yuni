
#include <yuni/yuni.h>
#include <yuni/toolbox/smartptr/sharedptr.h>
#include <iostream>

struct Foo
{
	Foo()  {std::cout << "Constructor" << std::endl;}
	~Foo() {std::cout << "Destructor" << std::endl;}
};

int main(void)
{
	// We create an instance of Foo
	Yuni::SharedPtr<Foo> p (new Foo());
	Yuni::SharedPtr<Foo> t; // NULL by default

	// Assignation. `t` and `p` will share the same pointer
	t = p;
	return 0;
}
