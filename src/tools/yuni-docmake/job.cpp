
#include "job.h"
#include "logs.h"
#include <yuni/core/io/io.h>
#include "tinyxml/tinyxml.h"
#include <iostream>
#include <yuni/core/slist.h>
#include "indexes.h"
#include "job-writer.h"
#include "program.h"


#define SEP  Core::IO::Separator

using namespace Yuni;
using namespace Yuni::Tool::DocMake;


Yuni::Job::QueueService<>  queueService;

static Yuni::Atomic::Int<>  gCompileJobCount = 0;


namespace // anonymous
{

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

		bool error() const {return pArticle.error;}

	private:
		void pushCoeff(float coeff);

		void popCoeff();

		void pushCoeffFromString(const TIXML_STRING& name);

		void seo(const StringAdapter& string);

	private:
		//! Within a paragraph
		bool pWithinParagraph;
		//! XML document
		TiXmlDocument& pDocument;
		//! XML Filename
		const String& pFilename;
		//! Current state
		ArticleData::State pState;
		//!
		float pCoeff;
		//! The coefficient stack
		ArticleData::CoeffStack  pCoeffStack;

		ArticleData& pArticle;

		//! Last TOC level (1: h1, 2: h2...)
		unsigned int pLastTOCLevel;
		String pTOCCaption;

	}; // class XMLVisitor





	XMLVisitor::XMLVisitor(ArticleData& article, TiXmlDocument& document) :
		pWithinParagraph(false),
		pDocument(document),
		pFilename(article.relativeFilename),
		pArticle(article),
		pLastTOCLevel(0)
	{
		pState = ArticleData::stNone;
		pCoeff = 1.0f;
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

		pushCoeffFromString(name);
		switch (pState)
		{
			case ArticleData::stNone:
				{
					if (tag.startsWith("pragma:"))
					{
						bool value;
						if (tag == "pragma:toc")
						{
							if (TIXML_SUCCESS == element.QueryBoolAttribute("value", &value))
								pArticle.showTOC = value;
							else
								logs.error() << pFilename << ": invalid value for pragma:toc";
						}
						else if (tag == "pragma:quicklinks")
						{
							if (TIXML_SUCCESS == element.QueryBoolAttribute("value", &value))
								pArticle.showQuickLinks = value;
							else
								logs.error() << pFilename << ": invalid value for pragma:quicklinks";
						}
						else if (tag == "pragma:history")
						{
							if (TIXML_SUCCESS == element.QueryBoolAttribute("value", &value))
								pArticle.showHistory = value;
							else
								logs.error() << pFilename << ": invalid value for pragma:history";
						}
						else if (tag == "pragma:directoryindex")
						{
							String src = pArticle.htdocsFilename;
							const StringAdapter string = element.Attribute("src");
							src << SEP << string;
							Core::IO::Normalize(pArticle.directoryIndex, src);
						}
						else if (tag == "pragma:accesspath")
						{
							CustomString<32,false> string = element.Attribute("value");
							string.toLower();
							if (string != "quicklinks")
								logs.error() << pFilename << ": invalid access path overlay";
							else
								pArticle.accessPath = string;
						}
						else
							logs.warning() << pFilename << ": unknown setting: " << tag;
					}
					else
					{
						if (tag == "title")
						{
							pState = ArticleData::stTitle;
							pArticle.title.clear();
						}
						else if (tag == "h1")
						{
							pLastTOCLevel = 1;
							pTOCCaption.clear();
							pState = ArticleData::stTOCItem;
						}
						else if (tag == "h2")
						{
							pTOCCaption.clear();
							if (!pLastTOCLevel)
							{
								logs.error() << "found h2 without h1. Adding an empty h1";
								pArticle.tocAppend(1, pTOCCaption);
							}
							pLastTOCLevel = 2;
							pState = ArticleData::stTOCItem;
						}
					}
					if (pWithinParagraph && pArticle.allowedTagsInParagraph.find(tag) == pArticle.allowedTagsInParagraph.end())
					{
						logs.error() << pFilename << ": invalid tag within a paragraph";
						pArticle.error = true;
						return false;
					}
					if (tag == "p")
						pWithinParagraph = true;
					break;
				}
			case ArticleData::stTitle:
				{
					logs.error() << pFilename << ": invalid nested tag for 'title'";
					pArticle.error = true;
					return false;
				}
			case ArticleData::stTOCItem:
				{
					if (tag == "h1" || tag == "h2")
					{
						logs.error() << "invalid nested header  (h1,h2)";
						return false;
					}
					break;
				}
			default:
				break;
		}
		return true;
	}


	bool XMLVisitor::Visit(const TiXmlText& node)
	{
		const TIXML_STRING& text = node.ValueTStr();

		switch (pState)
		{
			case ArticleData::stTitle:
				{
					if (!pArticle.title.empty() && pArticle.title.last() != ' ')
						pArticle.title += ' ';
					pArticle.title += text.c_str();
					pArticle.title.trim();
					break;
				}
			case ArticleData::stTOCItem:
				{
					if (!pTOCCaption.empty() && pTOCCaption.last() != ' ')
						pTOCCaption += ' ';
					pTOCCaption += text.c_str();
					pTOCCaption.trim();
					break;
				}
			default:
				if (!text.empty())
				{
					StringAdapter adapter;
					adapter.adapt(text.c_str(), (unsigned int) text.size());
					seo(adapter);
				}
				break;
		}
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



	bool XMLVisitor::VisitExit(const TiXmlElement& element)
	{
		const TIXML_STRING& name = element.ValueTStr();

		switch (pState)
		{
			case ArticleData::stNone:
				{
					if (name == "p")
						pWithinParagraph = false;
				}
			case ArticleData::stTitle:
				{
					if (name == "title")
					{
						pState = ArticleData::stNone;
						StringAdapter s = pArticle.title;

						float oldCoeff = pCoeff;
						pCoeff = 3.f;
						seo(s);
						pCoeff = oldCoeff;
					}
					break;
				}
			case ArticleData::stTOCItem:
				{
					if (name == "h1" || name == "h2")
					{
						pState = ArticleData::stNone;
						float oldCoeff = pCoeff;
						pCoeff = (pLastTOCLevel == 1) ? 2.5f : 2.f;
						StringAdapter s = pTOCCaption;
						seo(s);
						pCoeff = oldCoeff;
						pArticle.tocAppend(pLastTOCLevel, pTOCCaption);
						pTOCCaption.clear();
					}
					break;
				}
			default:
				break;
		}

		popCoeff();
		return true;
	}


	void XMLVisitor::pushCoeff(float coeff)
	{
		pCoeffStack.push_back(coeff);
		pCoeff *= coeff;
	}


	void XMLVisitor::popCoeff()
	{
		pCoeffStack.pop_back();
		pCoeff = 1.0f;
		ArticleData::CoeffStack::const_iterator end = pCoeffStack.end();
		for (ArticleData::CoeffStack::const_iterator i = pCoeffStack.begin(); i != end; ++i)
			pCoeff *= *i;
	}


	void XMLVisitor::pushCoeffFromString(const TIXML_STRING& name)
	{
		if (name.empty())
		{
			pushCoeff(1.f);
			return;
		}
		if (name == "h1")
		{
			pushCoeff(2.5f);
			return;
		}
		if (name == "h2")
		{
			pushCoeff(2.0f);
			return;
		}
		if (name == "h3")
		{
			pushCoeff(1.25f);
			return;
		}
		if (name == "h4")
		{
			pushCoeff(1.20f);
			return;
		}
		if (name == "b")
		{
			pushCoeff(1.1f);
			return;
		}
		if (name == "i")
		{
			pushCoeff(1.05f);
			return;
		}
		if (name == "var")
		{
			pushCoeff(0.f);
			return;
		}
		pushCoeff(1.f);
	}


	void XMLVisitor::seo(const StringAdapter& string)
	{
		if (pCoeff < 0.1f)
			return;
		typedef LinkedList<String> List;
		List list;
		string.split(list, " \r\n\t:;!@#$%^&*()_+{}[]|\"'\\/.,?><=-");
		if (list.empty())
			return;

		ArticleData::Word word;
		const List::const_iterator end = list.end();
		for (List::const_iterator i = list.begin(); i != end; ++i)
		{
			word = *i;
			word.toLower();

			ArticleData::WordStat& stat = pArticle.wordCount[word];
			++stat.count;
			if (pCoeff > stat.coeff)
				stat.coeff = pCoeff;
		}
	}




} // namespace anonymous









CompileJob::CompileJob(const Yuni::String& input, const Yuni::String& htdocs) :
	pInput(input),
	pHtdocs(htdocs)
{
	++gCompileJobCount;
}


CompileJob::~CompileJob()
{
	--gCompileJobCount;
}


bool CompileJob::SomeRemain()
{
	return !(!gCompileJobCount);
}


bool CompileJob::extractOrder(const String& path)
{

	// Getting the raw folder name
	// For the following URL :
	// /Users/milipili/projects/yuni/sources/docs/docs/src/001-en/300-developers/100-recommended-softwares/article.xml
	// We will get
	// /Users/milipili/projects/yuni/sources/docs/docs/src/001-en/300-developers/100-recommended-softwares
	Core::IO::ExtractFilePath(pTmp, path);

	// Looking for the final slash
	const String::Size offset = pTmp.find_last_of("/\\");
	if (offset == String::npos || offset + 4 >= pTmp.size())
		return false;
	// We only want to match string like /XXX-xxxxxx...
	if (pTmp[offset + 4] != '-')
		return false;

	// We are optimistic. The first 3 chars should be a number most of the time
	CustomString<8,false> s;
	s.resize(3);
	s[2] = pTmp[offset + 3];
	s[1] = pTmp[offset + 2];
	s[0] = pTmp[offset + 1];
	if (!s.to(pArticle.order))
		return false;
	return (pArticle.order < 1000u);
}


void CompileJob::onExecute()
{
	String target;
	const String::Vector::const_iterator end = pSources.end();
	for (String::Vector::const_iterator i = pSources.begin(); i != end; ++i)
	{
		const String& entry = *i;

		// Resetting data related to the article
		pArticle.reset();
		// The original filename (absolute)
		pArticle.originalFilename = entry;
		// The relative filename, from the source folder
		pArticle.relativeFilename.assign(entry.c_str() + pInput.size() + 1, entry.size() - pInput.size() - 1);

		// The final filename within the htdocs folder
		pArticle.htdocsFilename.clear() << '/' << pArticle.relativeFilename;
		pArticle.htdocsFilename.replace('\\', '/');
		{
			String::Size offset = pArticle.htdocsFilename.find_last_of('/');
			if (offset != String::npos)
				pArticle.htdocsFilename.resize(offset);
		}
		if (!pArticle.htdocsFilename)
			pArticle.htdocsFilename = "/";

		String::Size offset = 0;
		do
		{
			offset = pArticle.htdocsFilename.find('/', offset);
			if (pArticle.htdocsFilename.size() < 4 || offset > pArticle.htdocsFilename.size() - 4)
				break;
			++offset;
			if (pArticle.htdocsFilename[offset + 3] != '-')
				break;

			bool isDigit = true;
			for (unsigned int i = offset; i < offset + 3; ++i)
			{
				if (!String::IsDigit(pArticle.htdocsFilename[i]))
				{
					isDigit = false;
					break;
				}
			}
			if (isDigit)
				pArticle.htdocsFilename.erase(offset, 4);
		}
		while (true);

		// Post analyzis about the article
		analyzeArticle();
		if (pArticle.error)
			continue;

		// Writing the article in the database
		DocIndex::Write(pArticle);

		// Preparing a new job, with a copy of the data related to the article
		JobWriter::Add(pInput, pHtdocs, pArticle);
	}
}


void CompileJob::analyzeArticle()
{
	if (Program::verbose)
		logs.info() << "extracting " << pArticle.relativeFilename;

	// Article order
	{
		if (!extractOrder(pArticle.originalFilename))
			pArticle.order = 1000u;
		if (Program::debug)
			logs.info() << "  :: " << pArticle.relativeFilename << ", order = " << pArticle.order;
	}

	TiXmlDocument doc;
	if (!doc.LoadFile(pArticle.originalFilename.c_str(), TIXML_ENCODING_UTF8))
	{
		logs.error() << pArticle.relativeFilename << ", l" << doc.ErrorRow() << ": " << doc.ErrorDesc();
		return;
	}

	// Analyze the XML document
	XMLVisitor visitor(pArticle, doc);
	if (!doc.Accept(&visitor) || visitor.error())
	{
		pArticle.error = true;
		return;
	}
	if (!pArticle.title)
		Core::IO::ExtractFileName(pArticle.title, pArticle.htdocsFilename, false);

	// TOC refactoring
	pArticle.tocRefactoring();
}


