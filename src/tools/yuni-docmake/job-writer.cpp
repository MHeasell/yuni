
#include "job-writer.h"
#include <yuni/core/io/directory.h>
#include "job.h"
#include "logs.h"
#include "tinyxml/tinyxml.h"
#include <yuni/core/hash//checksum//md5.h>
#include "indexes.h"


using namespace Yuni;

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
		unsigned int i = pToDelete.size();
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
	bool res = (Core::IO::ioErrNone == Core::IO::File::LoadFromFile(gTemplateContent,
		"/Users/milipili/projects/yuni/sources/docs/src/tools/yuni-docmake/templates/yuni/index.html"));
	if (!res)
		logs.error() << "impossible to load template";
	return res;
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


void JobWriter::onExecute()
{
	logs.debug() << "writing " << pArticle.htdocsFilename;

	String s;

	if (pArticle.htdocsFilename != "/")
	{
		s << pHtdocs << SEP << pArticle.htdocsFilename;
		# ifdef YUNI_OS_WINDOWS
		s.replace('/', '\\');
		# endif
		if (!Core::IO::Directory::Create(s))
		{
			logs.error() << "impossible to create " << s;
			return;
		}
	}

	s << SEP << "index.html";
	String content = gTemplateContent;

	content.replace("@{TITLE}", pArticle.title);
	// Root folder
	String tmp;
	String root;
	{
		unsigned int c = pArticle.htdocsFilename.countChar('/');
		if (!c)
			root = ".";
		else
		{
			root << "..";
			for (unsigned int i = 1; i != c; ++i)
				root << "/..";
		}
	}


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

	// @{URL}
	{
		content.replace("@{URL}",  pArticle.htdocsFilename);
	}

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
					address << "<li><a href=\"" << root << tmp << "\">";
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
				address << "<li><a href=\"@{ROOT}/en/documentation/\">Documentation</a></li>\n";
				address << "<li><a href=\"@{ROOT}/en/downloads/\">Downloads</a></li>\n";
				address << "<li><a href=\"@{ROOT}/en/developpers/\">Developpers</a></li>\n";
				address << "<li><a href=\"@{ROOT}/en/links/\">Links</a></li>\n";
				address << "<li><a href=\"@{ROOT}/en/contacts/\">Contacts</a></li>\n";
			}
		}
		content.replace("@{URL_PARTS}",  address);
	}

	// TOC
	if (pArticle.showTOC)
	{
		content.replace("@{TOC_BEGIN}", "");
		content.replace("@{TOC_END}", "");
	}
	else
	{
		content.replace("@{TOC_BEGIN}", "<!--");
		content.replace("@{TOC_END}", "-->");
	}

	// Quick links
	if (pArticle.showQuickLinks)
	{
		content.replace("@{QUICKLINKS_BEGIN}", "");
		content.replace("@{QUICKLINKS_END}", "");
	}
	else
	{
		content.replace("@{QUICKLINKS_BEGIN}", "<!--");
		content.replace("@{QUICKLINKS_END}", "-->");
	}

	// Tags
	{
		content.replace("@{TAGFIELD_BEGIN}", "<!--");
		content.replace("@{TAGFIELD_COUNT}", "0 tag");
		content.replace("@{TAGFIELD_END}", "-->");
	}

	// content
	if (pArticle.originalFilename.notEmpty())
	{
		# ifdef YUNI_OS_WINDOWS
		tmp.clear() << "/tmp/yuni-doc-tmp-";
		# else
		tmp.clear() << "C:\\yuni-doc-tmp-";
		# endif
		Hash::Checksum::MD5 md5;
		tmp << md5[s];
		doc.SaveFile(tmp.c_str());
		String srcContent;
		Core::IO::File::LoadFromFile(srcContent, tmp);
		Core::IO::File::Delete(tmp);

		content.replace("@{CONTENT}",  srcContent);
	}
	else
		content.replace("@{CONTENT}",  "");

	// Directory Index
	if (pArticle.directoryIndex.notEmpty())
	{
		DocIndex::BuildDirectoryIndex(tmp, pArticle.directoryIndex);
		content.replace("@{DIRECTORY_INDEX}",  tmp);
	}
	else
		content.replace("@{DIRECTORY_INDEX}",  "");


	// Replace all pseudo linefeed
	content.replace("&#x0A;", "\n");
	// The replacement of the variable "root" must be done after all replacement
	content.replace("@{ROOT}",  root);

	if (!Core::IO::File::SaveToFile(s, content))
		logs.error() << "impossible to write " << s;
}



