
#include <yuni/yuni.h>
#include <yuni/core/io/file.h>
#include "tinyxml/tinyxml.h"

using namespace Yuni;

#define SEP Core::IO::Separator




namespace // anonymous
{

	static bool ReadIndex(const String& folder)
	{
		String filename;
		filename << folder << SEP << "index.xml";

		TiXmlDocument doc;
		if (!doc.LoadFile(filename.c_str(), TIXML_ENCODING_UTF8))
		{
//			logs.error() << "impossible to read the index";
			return false;
		}
		return true;
	}


} // anonymous namespace



int main(int argc, char** argv)
{
	String src = "../../../docs/tmp/doxygen/xml";

	if (!ReadIndex(src))
	{
	}
	return 0;
}
