
#include <yuni/core/string.h>
// Keep <iostream> after any includes of the yuni library
#include <iostream>


#include "common.hxx"


int main(void)
{
	StringTest<wchar_t>::Run();
	return 0;
}
