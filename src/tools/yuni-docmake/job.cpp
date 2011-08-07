
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

	}; // class XMLVisitor





	XMLVisitor::XMLVisitor(ArticleData& article, TiXmlDocument& document) :
		pWithinParagraph(false),
		pDocument(document),
		pFilename(article.relativeFilename),
		pArticle(article)
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
						pState = ArticleData::stNone;
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
		string.split(list, " \r\n\t:;!@#$%^&*()_+{}|\"'\\/.,?><=-");
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
}


CompileJob::~CompileJob()
{
}


bool CompileJob::extractOrder(const String& path)
{
	Core::IO::ExtractFilePath(pTmp, path);
	String::Size offset = pTmp.find_last_of("-/\\");
	if (offset == String::npos)
		return false;
	if (pTmp[offset] != '-' || offset < 2)
		return false;
	CustomString<8,false> s;
	s.resize(3);
	s[2] = pTmp[offset - 1];
	s[1] = pTmp[offset - 2];
	s[0] = pTmp[offset - 3];
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

		pArticle.reset();
		pArticle.originalFilename = entry;
		pArticle.relativeFilename.assign(entry.c_str() + pInput.size() + 1, entry.size() - pInput.size() - 1);

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

		// Generate the
		analyzeArticle();
		if (pArticle.error)
			continue;
		DocIndex::Write(pArticle);

		JobWriter::Add(pInput, pHtdocs, pArticle);
	}
}


void CompileJob::analyzeArticle()
{
	if (Program::verbose)
		logs.info() << "extracting " << pArticle.relativeFilename;

	if (!extractOrder(pArticle.originalFilename))
		pArticle.order = 1000;

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
}


