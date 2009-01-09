/*!
 * This is a placeholder for the helloworld sample for the script
 * module. It is *not functional* yet, so it returns an error.
 */

#include <yuni/script.h>
#include <iostream>

int main()
{
	
	// Create a Lua script object, to execute a small script.
	Yuni::Script::AScript* sc = new Yuni::Script::Lua();

	// Load a hello world script
	if (!sc->loadFromFile("helloworld.lua"))
	{ // An error has occured.
		// TODO: We must be able to determinate exactly what prevented the script loading.
		std::cout << "Error while loading script." << std::endl;
	}

	// Just run the script, executing any instruction in the main
	// scope.
	sc->run();

	if (!sc->loadFromString("foo();"))
	{ // An error has occured.
		// TODO: We must be able to determinate exactly what prevented the script loading.
		std::cout << "Error while loading string script." << std::endl;
	}

	// Run it again, just to see ?
	sc->run();

	// Declare a vector to store the call results
	Yuni::Script::RetValues ret;
	// Then call a function.
	sc->call("callMeOnly", ret);
	
	// Then call a function with one argument, for example an Int.
	sc->call("callMeWithArg", ret, 42);

	// Then call a function with one argument, for example a String
	sc->call("callMeWithArg", ret, "Hello, World !");





	// Destroy the script object to release the resources.
	delete sc;

	// Goodbye !
	return 0;
}
