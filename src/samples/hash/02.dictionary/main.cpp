
#include <yuni/yuni.h>
#include <yuni/string.h>		   // Yuni::String
#include <yuni/hash/dictionary.h>  // Yuni::Hash::Dictionary
#include <iostream>				// std::cout


int main(void)
{
	// A dictionary is an associative container where the key is merely a string
	// The value of the key if given by the template parameter (`int` here)
	Yuni::Hash::Dictionary<int>  months;

	// How many days in each month ?
	// Populating the dictionary...
	months["january"] = 31;
	months["february"] = 28;
	months["march"] = 31;
	months["april"] = 30;
	months["may"] = 31;
	months["june"] = 30;
	months["july"] = 31;
	months["august"] = 31;
	months["september"] = 30;
	months["october"] = 31;
	months["november"] = 30;
	months["december"] = 31;

	// Displaying the values stored in the dictionary
	std::cout << "september -> " << months["september"] << std::endl;  // 30
	std::cout << "april	 -> " << months["april"] << std::endl;	  // 30
	std::cout << "june	  -> " << months["june"] << std::endl;	   // 30
	std::cout << "november  -> " << months["november"] << std::endl;   // 30
	std::cout << "december  -> " << months["december"] << std::endl;   // 31
	return 0;
}
