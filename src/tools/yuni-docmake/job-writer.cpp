
#include "job-writer.h"
#include <yuni/core/io/directory.h>
#include <yuni/core/io/directory/system.h>
#include "job.h"
#include "logs.h"
#include "tinyxml/tinyxml.h"
#include <yuni/core/hash//checksum//md5.h>
#include "indexes.h"
#include "webpage.hxx"
#include "program.h"


using namespace Yuni;
using namespace Yuni::Tool::DocMake;

# define SEP Core::IO::Separator


namespace // anonymous
{
	static Mutex gMutex;
	static std::vector<JobWriter*>  gJobList;
	static String gTemplateContent;



	class XMLVisitor : public TiXmlVisitor
	{
	public:
		//! \name Constructor
		//@{
		/*!
		** \brief Constructor
		*/
		XMLVisitor(ArticleData& article, TiXmlDocument& document);
		//! Destructor
		virtual ~XMLVisitor();
		//@}

		virtual bool VisitEnter(const TiXmlDocument& /*doc*/ );

		virtual bool VisitExit(const TiXmlDocument& /*doc*/);

		virtual bool VisitEnter(const TiXmlElement& element, const TiXmlAttribute* attr);

		virtual bool VisitExit(const TiXmlElement& element);

		virtual bool Visit(const TiXmlDeclaration& /*declaration*/);
		virtual bool Visit(const TiXmlText& /*text*/);
		virtual bool Visit(const TiXmlComment& /*comment*/);
		virtual bool Visit(const TiXmlUnknown& /*unknown*/);

		void deleteUselessTags();

	private:
		//! XML document
		TiXmlDocument& pDocument;
		ArticleData& pArticle;
		std::vector<TiXmlElement*> pToDelete;

	}; // class XMLVisitor





	XMLVisitor::XMLVisitor(ArticleData& article, TiXmlDocument& document) :
		pDocument(document),
		pArticle(article)
	{
	}


	XMLVisitor::~XMLVisitor()
	{
	}


	bool XMLVisitor::VisitEnter(const TiXmlDocument& /*doc*/ )
	{
		return true;
	}


	bool XMLVisitor::VisitExit(const TiXmlDocument& /*doc*/)
	{
		return true;
	}


	bool XMLVisitor::VisitEnter(const TiXmlElement& element, const TiXmlAttribute* /*attr*/)
	{
		const TIXML_STRING& name = element.ValueTStr();
		ArticleData::Tag tag = name.c_str();

		if (tag == "title" || tag == "tag" || tag.startsWith("pragma:"))
			pToDelete.push_back(const_cast<TiXmlElement*>(&element));
		else
		{
			if (tag == "source")
			{
				TiXmlElement* e = const_cast<TiXmlElement*>(&element);
				e->SetValue("pre");
				e->RemoveAttribute("type");
				e->SetAttribute("class", "brush: cpp; gutter: false; class-name: 'class_name_pre'");
			}
		}

		return true;
	}

	void XMLVisitor::deleteUselessTags()
	{
		if (pToDelete.empty())
			return;
		// start from the last item to delete
		unsigned int i = (unsigned int) pToDelete.size();
		do
		{
			--i;
			TiXmlElement* element = pToDelete[i];
			element->Parent()->RemoveChild(element);
		}
		while (i);
	}


	bool XMLVisitor::Visit(const TiXmlText&)
	{
		return true;
	}


	bool XMLVisitor::Visit(const TiXmlComment&)
	{
		return true;
	}


	bool XMLVisitor::Visit(const TiXmlDeclaration&)
	{
		return true;
	}


	bool XMLVisitor::Visit(const TiXmlUnknown&)
	{
		return true;
	}



	bool XMLVisitor::VisitExit(const TiXmlElement&)
	{
		return true;
	}



} // anonymous namespace





void JobWriter::Add(const Yuni::String& input, const Yuni::String& htdocs, const ArticleData& article)
{
	JobWriter* job = new JobWriter(input, htdocs, article);
	gMutex.lock();
	gJobList.push_back(job);
	gMutex.unlock();
}


void JobWriter::PushAllInQueue()
{
	gMutex.lock();
	for (unsigned int i = 0; i != gJobList.size(); ++i)
		queueService += gJobList[i];
	gJobList.clear();
	gMutex.unlock();
}


bool JobWriter::ReadTemplateIndex()
{
	PrepareWebPageHtml(gTemplateContent);
	return true;
}


JobWriter::JobWriter(const Yuni::String& input, const Yuni::String& htdocs, const ArticleData& article) :
	pInput(input),
	pHtdocs(htdocs),
	pArticle(article)
{
}


JobWriter::~JobWriter()
{
}


void JobWriter::prepareVariables(const String& filenameInHtdocs)
{
	String tmp;
	pVars.clear();

	// @{INDEX}
	if (Program::shortUrl)
		pVars["INDEX"] = nullptr;
	else
		pVars["INDEX"] = Program::indexFilename;

	// @{TITLE}
	pVars["TITLE"] = pArticle.title;

	TiXmlDocument doc;
	doc.SetTabSize(4);

	if (pArticle.originalFilename.notEmpty())
	{
		if (!doc.LoadFile(pArticle.originalFilename.c_str(), TIXML_ENCODING_UTF8))
		{
			logs.error() << pArticle.relativeFilename << ", l" << doc.ErrorRow() << ": " << doc.ErrorDesc();
			return;
		}
		{
			XMLVisitor visitor(pArticle, doc);
			doc.Accept(&visitor);
			visitor.deleteUselessTags();
		}
	}

	// @{ROOT}
	String& root = pVars["ROOT"];
	{
		unsigned int c = pArticle.htdocsFilename.countChar('/');
		if (!c)
			root = ".";
		else
		{
			tmp.clear() << "..";
			for (unsigned int i = 1; i != c; ++i)
				tmp << "/..";
			root = tmp;
		}
	}

	// @{URL}
	pVars["URL"] = pArticle.htdocsFilename;

	// @{URL_PARTS}
	{
		String address;
		if (pArticle.accessPath.empty())
		{
			String::Vector list;
			pArticle.htdocsFilename.split(list, "/");
			tmp.clear();
			if (!list.empty())
			{
				for (unsigned int i = 0; i < list.size() - 1; ++i)
				{
					tmp << '/' << list[i];
					address << "<li><a href=\"" << root << tmp << '/' << pVars["INDEX"] << "\">";
					if (!DocIndex::AppendArticleTitleFromPath(address, tmp))
						address << list[i];
					address << "</a></li>\n";
				}
			}
		}
		else
		{
			if (pArticle.accessPath == "quicklinks")
			{
				address << "<li><a href=\"@{ROOT}/en/documentation/" << pVars["INDEX"] << "\">Documentation</a></li>\n";
				address << "<li><a href=\"@{ROOT}/en/downloads/" << pVars["INDEX"] << "\">Downloads</a></li>\n";
				address << "<li><a href=\"@{ROOT}/en/developers/" << pVars["INDEX"] << "\">Developpers</a></li>\n";
				address << "<li><a href=\"@{ROOT}/en/links/" << pVars["INDEX"] << "\">Links</a></li>\n";
				address << "<li><a href=\"@{ROOT}/en/contacts/" << pVars["INDEX"] << "\">Contacts</a></li>\n";
			}
		}
		pVars["URL_PARTS"] = address;
	}


	// @{TOC_...}
	if (pArticle.showTOC)
	{
		pVars["TOC_BEGIN"] = "";
		pVars["TOC_END"] = "";
	}
	else
	{
		pVars["TOC_BEGIN"] = "<!--";
		pVars["TOC_END"] = "-->";
	}

	// Quick links
	if (pArticle.showQuickLinks)
	{
		pVars["QUICKLINKS_BEGIN"] = "";
		pVars["QUICKLINKS_END"] = "";
	}
	else
	{
		pVars["QUICKLINKS_BEGIN"] = "<!--";
		pVars["QUICKLINKS_END"] = "-->";
	}

	// @{CONTENT}
	if (pArticle.originalFilename.notEmpty())
	{
		if (Core::IO::Directory::System::Temporary(tmp))
		{
			tmp << SEP << "yuni-doc-tmp-";
			Hash::Checksum::MD5 md5;
			tmp << md5[filenameInHtdocs];
			doc.SaveFile(tmp.c_str());
			String srcContent;
			Core::IO::File::LoadFromFile(srcContent, tmp);
			Core::IO::File::Delete(tmp);

			pVars["CONTENT"] = srcContent;
		}
		else
		{
			pVars["CONTENT"] = nullptr;
			logs.error() << "impossible to retrieve the temporary folder location";
		}
	}
	else
		pVars["CONTENT"] = nullptr;

	// @{DIRECTORY_INPUT}
	if (pArticle.directoryIndex.notEmpty())
	{
		DocIndex::BuildDirectoryIndex(tmp, pArticle.directoryIndex);
		pVars["DIRECTORY_INDEX"] = tmp;
	}
	else
		pVars["DIRECTORY_INDEX"] = "";

}


void JobWriter::onExecute()
{
	// Looking for the target filename
	String filenameInHtdocs;
	{
		String s = pHtdocs;
		if (pArticle.htdocsFilename != "/")
		{
			s << SEP << pArticle.htdocsFilename;
			# ifdef YUNI_OS_WINDOWS
			s.replace('/', '\\');
			# endif
			if (!Core::IO::Directory::Create(s))
			{
				logs.error() << "impossible to create the directory " << s;
				return;
			}
		}

		s << SEP << Program::indexFilename;
		Core::IO::Normalize(filenameInHtdocs, s);
	}

	// Console verbose / debug
	{
		if (Program::debug)
			logs.info() << "generating " << pArticle.htdocsFilename << " -> " << filenameInHtdocs;
		else
		{
			if (Program::verbose)
				logs.info() << "generating " << pArticle.htdocsFilename;
		}
	}

	// Prepare all variables
	prepareVariables(filenameInHtdocs);

	String content = gTemplateContent;
	const String& root = pVars["ROOT"];

	// @{TITLE}
	content.replace("@{TITLE}", pVars["TITLE"]);

	String tmp;

	// @{URL}
	content.replace("@{URL}", pVars["URL"]);

	// @{URL_PARTS}
	content.replace("@{URL_PARTS}",  pVars["URL_PARTS"]);

	// TOC
	content.replace("@{TOC_BEGIN}", pVars["TOC_BEGIN"]);
	content.replace("@{TOC_END}", pVars["TOC_END"]);

	// Quick links
	content.replace("@{QUICKLINKS_BEGIN}", pVars["QUICKLINKS_BEGIN"]);
	content.replace("@{QUICKLINKS_END}", pVars["QUICKLINKS_END"]);

	// Tags
	{
		content.replace("@{TAGFIELD_BEGIN}", "<!--");
		content.replace("@{TAGFIELD_COUNT}", "0 tag");
		content.replace("@{TAGFIELD_END}", "-->");
	}

	// @{CONTENT}
	content.replace("@{CONTENT}", pVars["CONTENT"]);
	
	// Directory Index
	content.replace("@{DIRECTORY_INDEX}",  pVars["DIRECTORY_INDEX"]);

	// The replacement of the variable "root" must be done after all replacement
	content.replace("@{ROOT}",  root);
	// The index filename
	content.replace("@{INDEX}", pVars["INDEX"]);

	// Replace all pseudo linefeed
	content.replace("&#x0A;", "\n");

	if (!Core::IO::File::SaveToFile(filenameInHtdocs, content))
	{
		logs.error() << "impossible to generate '" << pArticle.htdocsFilename << "' into '" << filenameInHtdocs << "'";
	}
}



