#include <iostream>
#include <string>
#include <complex>
#include <yuni/toolbox/string.h>
#include <yuni/toolbox/variant.h>

using namespace Yuni;
using namespace std;

void outputVariant(const Variant& a, ostream& o)
{
#define IMPLEMENT_OUT(type) \
	if (a.is<type>()) \
	{ \
		o << a.to<type>() << endl; \
		return; \
	}

	IMPLEMENT_OUT(int)
	IMPLEMENT_OUT(char)
	IMPLEMENT_OUT(double)
	IMPLEMENT_OUT(float)
	IMPLEMENT_OUT(String)
	IMPLEMENT_OUT(complex<int>)

	o << "Unexpected type: " << a.type().name() << endl;
    throw 0;
}

void simpleTest()
{
  cout << "simple test of Yuni::Variant" << endl;
  
  cout << "expecting 42    : "; outputVariant(42, cout);
  cout << "expecting q     : "; outputVariant('q', cout);
  cout << "expecting 3.14  : "; outputVariant(3.14, cout);
  cout << "expecting (1,2) : "; outputVariant(complex<int>(1,2), cout);
  cout << "expecting piko  : "; outputVariant("piko", cout);

  cout << "expecting 42    : "; int n = 42; outputVariant(n, cout);
  cout << "expecting q     : "; char c = 'q'; outputVariant(c, cout);
  cout << "expecting 3.14  : "; double d = 3.14; outputVariant(d, cout);
  cout << "expecting (1,2) : "; complex<int> x(1,2); outputVariant(x, cout);
  cout << "expecting piko  : "; char * s = "piko"; outputVariant(s, cout);
  
  Yuni::Variant a;
  cout << "expecting 42    : "; outputVariant(a = n, cout);
  cout << "expecting q     : "; outputVariant(a = c, cout);
  cout << "expecting 3.14  : "; outputVariant(a = d, cout);  
  cout << "expecting (1,2) : "; outputVariant(a = x, cout);
  cout << "expecting 13    : "; outputVariant(a = 13, cout);
  cout << "expecting nyu   : "; outputVariant(s = "nyu", cout);

  cout << "Empty tests" << endl;
  cout << "expecting false : " << boolalpha << a.empty() << endl;
  a = 0;
  cout << "expecting false : " << boolalpha << a.empty() << endl;
  a.reset();
  cout << "expecting true  : " << boolalpha << a.empty() << endl;  
  
  try {
    cout << a.to<int>() << endl;
    cout << "failure: expected error" << endl;
  }
  catch(...) {
    cout << "success: casting error" << endl;
  }
}

int main()
{
	simpleTest();	

	return 0;
}
