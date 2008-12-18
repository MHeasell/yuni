
#include <iostream>	                      // std::cout
#include <yuni/yuni.h>
#include <yuni/toolbox/hash/dictionary.h> // Yuni::Hash::Dictionary



Yuni::Hash::Dictionary<Yuni::String, Yuni::Hash::optIgnoreCase | Yuni::Hash::optThreadSafe>  logins;


void displayLogins()
{
	// Displaying the values stored in the dictionary, with a default if not exists
	std::cout << "--- Report --- " << std::endl;
	std::cout << "Name for `guest`	: " << logins.value("Guest") << std::endl;
	std::cout << "Name for `milipili` : " << logins.value("Milipili") << std::endl;
	std::cout << "Name for `spammer`  : " << logins.value("Spammer") << std::endl;
	std::cout << std::endl;
}


int main(void)
{
	// Populating...
	logins["milipili"] = "DamiEn"; // We've got a mistake
	logins["MIlipIli"] = "Damien"; // Fix it
	logins["spammer"]  = "I see dead people...";

	displayLogins();

	logins.erase("spaMMer");

	displayLogins();

	return 0;
}
