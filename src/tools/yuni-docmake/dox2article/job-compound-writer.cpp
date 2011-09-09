
#include "job-compound-writer.h"
#include <yuni/core/system/suspend.h>
#include "../logs.h"
#include "options.h"


#define SEP IO::Separator



namespace Yuni
{
namespace Edalene
{
namespace Dox2Article
{
namespace Job
{

	void CompoundWriter::Dispatch()
	{
		// Write articles
		logs.info() << "writing articles";
		{
			Compound::Map::iterator end = allSymbolsByRefID.end();
			for (Compound::Map::iterator i = allSymbolsByRefID.begin(); i != end; ++i)
			{
				Compound::Ptr& compound = i->second;
				Edalene::Dox2Article::Job::queueService += new CompoundWriter(compound);
			}
		}

		queueService.wait();
		while (!QueueServiceIsEmpty())
			Yuni::SuspendMilliSeconds(200);
	}





	CompoundWriter::CompoundWriter(Compound::Ptr& compound) :
		pCompound(compound)
	{
	}


	CompoundWriter::~CompoundWriter()
	{
	}



	void CompoundWriter::onExecute()
	{
		if (pCompound->name.empty() || pCompound->name.contains('@'))
			return;

		switch (pCompound->kind)
		{
			case Compound::kdFunction: break;
			case Compound::kdTypedef: break;
			case Compound::kdClass: buildClass();break;
			case Compound::kdNamespace: buildNamespace();break;
			case Compound::kdVariable: break;
			case Compound::kdEnum: break;
			case Compound::kdFile: break;
			case Compound::kdFolder: break;
			case Compound::kdGroup: break;
			case Compound::kdUnknown: break;
			case Compound::kdMax: break;
		}
	}


	void CompoundWriter::buildClass()
	{
		if (pCompound->name.find_first_of("<@") != String::npos)
			return;

		String filename;
		filename << Options::target << SEP << pCompound->htdocs;
		if (!IO::Directory::Create(filename))
			return;
		filename << SEP << "article.xml";

		IO::File::Stream file;
		if (file.openRW(filename))
		{
			// Getting the name
			const String& name = pCompound->name;

			file << "<title>";
			String::Size offset = name.find_last_of(":\\/");
			if (offset < name.size() && offset + 1 < name.size())
				file.write(name.c_str() + offset + 1, name.size() - (offset + 1));
			else
				file << name;
			file << "</title>\n";
			file << "<pragma:weight value=\"0.5\" />\n";
			file << "<tag name=\"doxygen\" />\n";
			file << "<tag name=\"class\" />\n";
			file << "\n\n";
		}
	}


	void CompoundWriter::buildNamespace()
	{
		if (pCompound->name.find_first_of("<@") != String::npos)
			return;

		String filename;
		filename << Options::target << SEP << pCompound->htdocs;
		if (!IO::Directory::Create(filename))
			return;
		filename << SEP << "article.xml";

		IO::File::Stream file;
		if (file.openRW(filename))
		{
			// Getting the name
			const String& name = pCompound->name;

			file << "<title>";
			String::Size offset = name.find_last_of(":\\/");
			if (offset < name.size() && offset + 1 < name.size())
				file.write(name.c_str() + offset + 1, name.size() - (offset + 1));
			else
				file << name;
			file << "</title>\n";
			file << "<pragma:weight value=\"0.45\" />\n";
			file << "<tag name=\"doxygen\" />\n";
			file << "<tag name=\"namespace\" />\n";
			file << "\n\n";
		}
	}







} // namespace Job
} // namespace Dox2Article
} // namespace Edalene
} // namespace Yuni

