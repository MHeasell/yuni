
#include <iostream>	                      // std::cout
#include <yuni/yuni.h>
#include <yuni/core/hash/dictionary.h> // Yuni::Hash::Dictionary


// Use a case-insensitive dictionary, keys ignore case, but not values.
Yuni::Hash::Dictionary<Yuni::String, Yuni::Hash::optIgnoreCase>  logins;


void displayLogins()
{
	// Displaying the values stored in the dictionary, with a default if not exists
	std::cout << "--- Report --- " << std::endl;
	std::cout << "Name for `guest`    : " << logins.value("Guest") << std::endl;
	std::cout << "Name for `milipili` : " << logins.value("Milipili") << std::endl;
	std::cout << "Name for `spammer`  : " << logins.value("Spammer") << std::endl;
	std::cout << std::endl;
}


int main(void)
{
	// Populating...
	logins["milipili"] = "DamiEn"; // We introduce a typographic error
	logins["spammer"]  = "I see dead people..."; // This is a spam entry

	displayLogins();

	logins["MIlipIli"] = "Damien"; // Fix the error
	logins.erase("spaMMer"); // Erase the "spammer" key

	displayLogins();

	return 0;
}
