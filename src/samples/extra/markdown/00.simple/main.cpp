
#include <yuni/yuni.h>
#include <yuni/extra/markdown/reader.h>


int main()
{
	using namespace Yuni;

	Markdown::Reader  reader;
	reader.beginDocument("<memory>");

	reader += "# Introduction\n";
	reader += "Here is a proposal...\n";
	reader += "\n";
	reader += "\n";
	reader += "> Quoting level...\n";
	reader += "> > *  Another quote\n";
	reader += "> >    Another quote\n";
	reader += "> >    Another quote\n";
	reader += "> > * > Another quote\n";
	reader += "> > * > ## Subtitle > \n";
	reader += "\n";
	reader += "\n";

	reader.endDocument();

	return 0;
}


