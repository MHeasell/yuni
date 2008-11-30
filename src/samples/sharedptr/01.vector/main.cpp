
#include <yuni/yuni.h>
#include <yuni/toolbox/smartptr/sharedptr.h>
#include <vector>
#include <iostream>


//
// A stupid and useless class, just for the demo
//
class Foo
{
public:
	explicit Foo(int i) :p(i) {std::cout << "Constructor:" << i << std::endl;}
	~Foo() {std::cout << "Destructor:"<< p << std::endl;}

private:
	int p;
};



int main(void)
{
	// We may need a list of pointer, for example :
	// std::vector<Foo*>
	//
	// However, we have to manually delete those pointer when the list
	// is cleared, or a single item is removed
	//
	// Instead, we would use a shared pointer to automatically do this
	// annoying thing
	std::vector< Yuni::SharedPtr<Foo> > lst;
	lst.push_back(new Foo(1));
	lst.push_back(new Foo(2));
	lst.push_back(new Foo(3));
	lst.push_back(new Foo(4));
	lst.push_back(new Foo(5));
	return 0;
}
