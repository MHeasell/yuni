/*!
 * This is a placeholder for the helloworld sample for the script
 * module. It is *not functional* yet, so it returns an error.
 */

#include <iostream>
#include <yuni/script.h>


namespace
{
	Yuni::String bar(int arg1, double arg2, Yuni::String arg3, void* arg4, int, int)
	{
		std::cout << "[ C++] Hi, i'm bar(). Here are 4 integers: "
			<< arg1 << ", "
			<< arg2 << ", "
			<< arg3 << ", "
			<< arg4 << "."
			<< std::endl;
	 	return "Piko";
	}
}


class Piko
{
public:
	void foo(const Yuni::String& nyu)
	{
		std::cout << "[ C++] " << __PRETTY_FUNCTION__ << ": " << nyu << "\n";
	}
};


int main()
{

	// Create a Lua script object, to execute a small script.
	Yuni::Script::AScript* sc = new Yuni::Script::Lua();

	// Load a hello world script
	if (!sc->loadFromFile("helloworld.lua"))
	{
		// An error has occured.
		// TODO: We must be able to determine exactly what prevented the script loading.
		std::cout << "[ C++] Error while loading script." << std::endl;
	}

	if (!sc->appendFromString("foo();"))
	{
		// An error has occured.
		// TODO: We must be able to determine exactly what prevented the script loading.
		std::cout << "[ C++] Error while loading string script." << std::endl;
	}

	sc->call(NULL, "foo");

	if (!sc->appendFromString("print(\"[ Lua] Pyo !\");"))
	{
		// An error has occured.
		// TODO: We must be able to determine exactly what prevented the script loading.
		std::cout << "[ C++] Error while loading string script." << std::endl;
	}

	// Run it again, just to see ?
	sc->prepare();

	// And again.
	sc->prepare();

	// Declare a variant to store the call results
	Yuni::Any ret;

	// Then call a function.
	if (!sc->call(&ret, "callMeOnly"))
	{
		std::cout << "[ C++] Error while calling callMeOnly()" << std::endl;
	}

	// Then call a function with one argument, for example an Int.
	if (!sc->call(&ret, "callMeWithArg", 42, 15.2))
		std::cout << "[ C++] Error while calling callMeWithArg(42, 15.2)" << std::endl;

	// Then call a function with one argument, for example a String
	if (!sc->call(&ret, "callMeWithArg", "Hello, World !", 45.22432))
		std::cout << "[ C++] Error while calling callMeWithArg(\"Hello, World !\", 45.22432)" << std::endl;

	std::cout << "[ C++] Got result of type " << ret.type().name() << std::endl;


	Piko piko;
	sc->bind("classMemberFoo", &piko, &Piko::foo);


	if (!sc->bind("bar", &bar))
		std::cout << "[ C++] Error while binding ::bar()" << std::endl;
	else
	{
		std::cout << "[ C++] Fine, bar was bound. Call it !" << std::endl;
		if (!sc->call(NULL, "callBar"))
		{
			std::cout << "[ C++] Error while calling callBar()" << std::endl;
		}

	}

		// Destroy the script object to release the resources.
	delete sc;

	// Goodbye !
	return 0;
}
