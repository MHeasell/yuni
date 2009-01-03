/*!
 * This is a placeholder for the helloworld sample for the script
 * module. It is *not functional* yet, so it returns an error.
 */

#include <yuni/script.h>

int main()
{
	
	// Create a Lua script object, to execute a small script.
	Yuni::Script::AScript* sc = new Yuni::Script::Lua();

	// Destroy the script object to release the resources.
	delete sc;

	// Goodbye !
	return 0;
}
