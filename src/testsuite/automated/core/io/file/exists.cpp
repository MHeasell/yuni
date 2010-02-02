
#include <vector>
#include <yuni/core/io/file.h>
#include <iostream>

struct FileWithResult
{
	const char* name;
	bool result;
};

int main(void)
{
	std::vector<FileWithResult> values;
	values.Add(FileWithResult("test.txt", true));
	values.Add(FileWithResult("completelyImprobableName.none", false));

	int nbErrors = 0;
	for (int i = 0; i < values.size(); ++i)
	{
		bool found = Yuni::Core::IO::File::Exists(values[i].name);
		bool expected = valuesTested[i].result;
		if (found != expected)
		{
			std::cout << "Error: Core::IO::File::Exists should find \""
					  << values[i].name << "\" as "
					  << expected ? " existing!" : " not existing!";
			nbErrors++;
		}
	}
	return nbErrors;
}
