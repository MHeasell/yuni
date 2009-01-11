/*!
 * This is a placeholder for the helloworld sample for the script
 * module. It is *not functional* yet, so it returns an error.
 */

#include <yuni/script.h>
#include <iostream>

bool
bar(Yuni::Script::AScript* sc, const Yuni::Variant& arg1)
{ // Prints two integers
	(void)sc;
	std::cout << "Hi, i'm bar(). Here is 1 integer: " << arg1.asInt() << std::endl;
 	return true;
}

int main()
{
	
	// Create a Lua script object, to execute a small script.
	Yuni::Script::AScript* sc = new Yuni::Script::Lua();

	// Load a hello world script
	if (!sc->loadFromFile("helloworld.lua"))
	{ // An error has occured.
		// TODO: We must be able to determinate exactly what prevented the script loading.
		std::cout << "[EE] Error while loading script." << std::endl;
	}

	// Just run the script, executing any instruction in the main
	// scope.
	sc->run();

	if (!sc->loadFromString("foo();"))
	{ // An error has occured.
		// TODO: We must be able to determinate exactly what prevented the script loading.
		std::cout << "[EE] Error while loading string script." << std::endl;
	}

	// Run it again, just to see ?
	sc->run();

	// Declare a variant to store the call results
	Yuni::Variant ret;

	// Then call a function.
	if (!sc->call("callMeOnly", &ret))
	{
		std::cout << "[EE] Error while calling callMeOnly()" << std::endl;
	}
	
	// Then call a function with one argument, for example an Int.
	if (!sc->call("callMeWithArg", &ret, 42))
		std::cout << "[EE] Error while calling callMeWithArg(42)" << std::endl;

	// Then call a function with one argument, for example a String
	if (!sc->call("callMeWithArg", &ret, "Hello, World !"))
		std::cout << "[EE] Error while calling callMeWithArg(\"Hello, World !\")" << std::endl;


	// Test binding methods, with objects.
	//Sample aSample;
	//sc->bind("bar", &Sample::bar, &aSample);
	if (!sc->bind("bar", &(::bar)))
		std::cout << "[EE] Error while binding ::bar()" << std::endl;
	else
	{
		std::cout << "Fine, bar was bound. Call it !" << std::endl;
		if (!sc->call("callBar"))
		{
			std::cout << "[EE] Error while calling callBar()" << std::endl;
		}

	}





	// Destroy the script object to release the resources.
	delete sc;

	// Goodbye !
	return 0;
}
