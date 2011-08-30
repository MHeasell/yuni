
#include "job-writer.h"
#include <yuni/io/directory.h>
#include <yuni/io/directory/system.h>
#include "job.h"
#include "logs.h"
#include "tinyxml/tinyxml.h"
#include <yuni/core/hash//checksum//md5.h>
#include "indexes.h"
#include "webpage.hxx"
#include "program.h"


using namespace Yuni;
using namespace Yuni::Tool::DocMake;

# define SEP IO::Separator


namespace // anonymous
{
	static Mutex gMutex;
	static std::vector<JobWriter*>  gJobList;
	static String gTemplateContent;

	static Yuni::Atomic::Int<>  gCompileJobCount = 0;

	//! Structure for storing all existing words within the whole documentation
	typedef std::map<ArticleData::Word, int>  AllWords;
	static AllWords  gAllWords;


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

		unsigned int pCurrentTOCItemIndex;

	}; // class XMLVisitor





	XMLVisitor::XMLVisitor(ArticleData& article, TiXmlDocument& document) :
		pDocument(document),
		pArticle(article),
		pCurrentTOCItemIndex(0)
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
		TiXmlElement* e = const_cast<TiXmlElement*>(&element);

		// Attributes
		TiXmlAttribute* attr = const_cast<TiXmlAttribute*>(element.FirstAttribute());
		for (; attr; attr = attr->Next())
		{
			const StringAdapter e = attr->Value();
			if (e.contains("%%7B") || e.contains("%%7D"))
			{
				String s = e;
				s.replace("%%7B", "{");
				s.replace("%%7D", "}");
				attr->SetValue(s.c_str());
			}
		}


		if (tag == "title" || tag == "tag" || tag.startsWith("pragma:"))
			pToDelete.push_back(const_cast<TiXmlElement*>(&element));
		else
		{
			if (tag == "h1" || tag == "h2")
			{
				// Forcing the id
				if (pCurrentTOCItemIndex < pArticle.tocItems.size())
				{
					e->SetAttribute("id", pArticle.tocItems[pCurrentTOCItemIndex]->hrefID.c_str());
					++pCurrentTOCItemIndex;
				}
			}
			else if (tag == "source")
			{
				CustomString<16,false> type = e->Attribute("type");
				e->SetValue("pre");
				e->RemoveAttribute("type");

				type.toLower();
				if (type != "none")
				{
					if (!type || type == "cpp" || type == "c++")
						e->SetAttribute("class", "cpp");
					else if (type == "lua")
						e->SetAttribute("class", "lua");
					else if (type == "java")
						e->SetAttribute("class", "java");
				}
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
		/*
		const TIXML_STRING& name = text.ValueTStr();
		String v = name.c_str();
		if (v.contains("rarr"))
			std::cout << v << std::endl;
			*/
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


void JobWriter::SEOBuildAllTermReferences()
{
	String filename;
	filename << Program::htdocs << SEP << "seo" << SEP << "data.js";
	IO::File::Stream file;

	if (file.openRW(filename))
	{
		file << "if(1){var f=function(id,n,d) {SEO.termNames[n]=id;SEO.terms[id]=d};";
		Yuni::MutexLocker locker(gMutex);

		const AllWords::const_iterator end = gAllWords.end();
		for (AllWords::const_iterator i = gAllWords.begin(); i != end; ++i)
			DocIndex::BuildSEOTermReference(file, i->first, i->second);
		file << " }\n";
	}
}



void JobWriter::Add(const String& input, const String& htdocs, const ArticleData& article)
{
	// Preparing a new job
	// The article content will be copied
	JobWriter* job = new JobWriter(input, htdocs, article);
	// The new article
	const ArticleData& newArticle = job->article();

	// Keeping the new job in a safe place, for later use
	gMutex.lock();
	gJobList.push_back(job);
	gMutex.unlock();

	// Preparing the global word dictionary
	unsigned int registrationCount = 0;
	if (!newArticle.wordCount.empty())
	{
		// The article ID
		int articleID = DocIndex::FindArticleID(newArticle.htdocsFilename);

		// All word ids for the page
		int* wordIDs = new int[newArticle.wordCount.size()];
		float* weights = new float[newArticle.wordCount.size()];
		int* countInArticle = new int[newArticle.wordCount.size()];

		// Registering all new terms
		unsigned int wIx = 0;
		const ArticleData::WordCount::const_iterator end = newArticle.wordCount.end();
		ArticleData::WordCount::const_iterator i = newArticle.wordCount.begin();
		for (; i != end; ++i, ++wIx)
		{
			// The word itself
			const ArticleData::Word& word = i->first;
			const ArticleData::WordStat& stats = i->second;

			countInArticle[wIx] = stats.count;
			weights[wIx] = stats.coeff;

			const AllWords::const_iterator it = gAllWords.find(word);
			if (it == gAllWords.end())
			{
				++registrationCount;
				const int newWordID = DocIndex::RegisterWordReference(word);
				gAllWords[word] = newWordID;
				wordIDs[wIx] = newWordID;
			}
			else
				wordIDs[wIx] = it->second;
		}

		DocIndex::RegisterWordIDsForASingleArticle(articleID, wordIDs, countInArticle, weights, wIx);

		delete[] weights;
		delete[] countInArticle;
		delete[] wordIDs;
	}

	if (registrationCount && Program::verbose)
		logs.info() << "  :: registered " << registrationCount << " terms";
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


JobWriter::JobWriter(const String& input, const String& htdocs, const ArticleData& article) :
	pInput(input),
	pHtdocs(htdocs),
	pArticle(article),
	pArticleID(-1)
{
	++gCompileJobCount;
}


JobWriter::~JobWriter()
{
	--gCompileJobCount;
}


bool JobWriter::SomeRemain()
{
	return !(!gCompileJobCount);
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
				address << "<li><a href=\"@{ROOT}/en/developers/" << pVars["INDEX"] << "\">Developers</a></li>\n";
				address << "<li><a href=\"@{ROOT}/en/links/" << pVars["INDEX"] << "\">Links</a></li>\n";
				address << "<li><a href=\"@{ROOT}/en/contacts/" << pVars["INDEX"] << "\">Contacts</a></li>\n";
			}
		}
		pVars["URL_PARTS"] = address;
	}


	// @{TOC_...}
	if (pArticle.showTOC && pArticle.tocItems.size() > 1)
	{
		pVars["TOC_BEGIN"] = "";
		pVars["TOC_END"] = "";
	}
	else
	{
		pVars["TOC_BEGIN"] = "<!--";
		pVars["TOC_END"] = "-->";
	}

	// @{TOC_CONTENT}
	if (pArticle.tocItems.size() != 0 && pArticle.showTOC)
	{
		tmp.clear();
		tmp << "<ol>\n";
		bool hasOL = false;
		for (unsigned int i = 0; i != pArticle.tocItems.size(); ++i)
		{
			const ArticleData::TOCItem& item = *pArticle.tocItems[i];
			if (item.level == 2)
			{
				if (!hasOL)
				{
					hasOL = true;
					tmp << "\t<ol>\n";
				}
				tmp << "\t\t<li><a href=\"#" << item.hrefID << "\">"
					<< item.caption << "</a></li>\n";
				if (i + 1 == pArticle.tocItems.size())
					tmp << "\t</ol>\n\t</li>\n";
			}
			else
			{
				if (i)
				{
					if (hasOL)
						tmp << "\t</ol>\n";
					tmp << "\t</li>\n";
				}
				tmp << "\t<li><a href=\"#" << item.hrefID << "\">"
					<< item.caption << "</a>\n";
				hasOL = false;
				if (i + 1 == pArticle.tocItems.size())
					tmp << "\t</li>\n";
			}
		}
		tmp << "</ol>\n";
		pVars["TOC_CONTENT"] = tmp;
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
		if (IO::Directory::System::Temporary(tmp))
		{
			tmp << SEP << "yuni-doc-tmp-";
			Hash::Checksum::MD5 md5;
			tmp << md5[filenameInHtdocs];
			if (Program::debug)
				logs.info() << "  :: writing " << tmp;
			doc.SaveFile(tmp.c_str());
			String srcContent;
			IO::File::LoadFromFile(srcContent, tmp);
			IO::File::Delete(tmp);

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


bool JobWriter::articleIDIndatabase()
{
	pArticleID = DocIndex::FindArticleID(pArticle.htdocsFilename);
	if (pArticleID < 0)
		return false;
	return true;
}

void JobWriter::onExecute()
{
	if (!articleIDIndatabase())
		return;

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
			if (!IO::Directory::Create(s))
			{
				logs.error() << "impossible to create the directory " << s;
				return;
			}
		}

		s << SEP << Program::indexFilename;
		IO::Normalize(filenameInHtdocs, s);
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
	content.replace("@{TOC_CONTENT}", pVars["TOC_CONTENT"]);

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

	if (!IO::File::SaveToFile(filenameInHtdocs, content))
	{
		logs.error() << "impossible to generate '" << pArticle.htdocsFilename << "' into '" << filenameInHtdocs << "'";
	}
}



