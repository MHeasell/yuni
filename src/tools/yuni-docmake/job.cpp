
#include "job.h"
#include "logs.h"
#include <yuni/core/io/io.h>
#include "tinyxml/tinyxml.h"
#include <deque>
#include <set>
#include <map>
#include <iostream>
#include <yuni/core/slist.h>


#define SEP  Core::IO::Separator

using namespace Yuni;

Yuni::Job::QueueService<>  queueService;


namespace // anonymous
{

	class XMLVisitor : public TiXmlVisitor
	{
	public:
		enum State
		{
			stNone = 0,
			stTitle,
		};

	public:
		XMLVisitor(TiXmlDocument& document, const String& filename);

		virtual ~XMLVisitor();

		virtual bool VisitEnter(const TiXmlDocument& /*doc*/ );

		virtual bool VisitExit(const TiXmlDocument& /*doc*/);

		virtual bool VisitEnter(const TiXmlElement& element, const TiXmlAttribute* attr);

		virtual bool VisitExit(const TiXmlElement& element);

		virtual bool Visit(const TiXmlDeclaration& /*declaration*/);
		virtual bool Visit(const TiXmlText& /*text*/);
		virtual bool Visit(const TiXmlComment& /*comment*/);
		virtual bool Visit(const TiXmlUnknown& /*unknown*/);

		bool error() const {return pError;}

	private:
		typedef std::deque<float>  CoeffStack;
		typedef CustomString<16,false>  Tag;
		typedef std::set<Tag>  TagSet;
		typedef CustomString<32,false>  Word;

		class WordStat
		{
		public:
			WordStat()
				:coeff(0.f), count(0)
			{}
			float coeff;
			unsigned int count;
		};

		typedef std::map<Word, WordStat>  WordCount;

	private:
		void pushCoeff(float coeff);

		void popCoeff();

		void pushCoeffFromString(const TIXML_STRING& name);

		void seo(const StringAdapter& string);

	private:
		//!
		TagSet  pAllowedTagsInParagraph;
		//! The coefficient stack
		CoeffStack  pCoeffStack;
		//! The current coefficient
		float pCoeff;
		//! Current state
		State pState;
		//! Title of the page
		String pTitle;
		//! An error has occured
		bool pError;
		//! Within a paragraph
		bool pWithinParagraph;
		//! XML document
		TiXmlDocument& pDocument;
		//! XML Filename
		const String& pFilename;

		//! \name SEO
		//@{
		Word pWord;
		//!
		WordCount pWordCount;
		//@}

	}; // class XMLVisitor





	XMLVisitor::XMLVisitor(TiXmlDocument& document, const String& filename) :
		pCoeff(1.f),
		pState(stNone),
		pError(false),
		pWithinParagraph(false),
		pDocument(document),
		pFilename(filename)
	{
		pAllowedTagsInParagraph.insert("a");
		pAllowedTagsInParagraph.insert("b");
		pAllowedTagsInParagraph.insert("i");
		pAllowedTagsInParagraph.insert("u");
		pAllowedTagsInParagraph.insert("br");
		pAllowedTagsInParagraph.insert("code");
		pAllowedTagsInParagraph.insert("sub");
		pAllowedTagsInParagraph.insert("sup");
		pAllowedTagsInParagraph.insert("big");
		pAllowedTagsInParagraph.insert("button");
		pAllowedTagsInParagraph.insert("em");
		pAllowedTagsInParagraph.insert("img");
		pAllowedTagsInParagraph.insert("input");
		pAllowedTagsInParagraph.insert("kbd");
		pAllowedTagsInParagraph.insert("small");
		pAllowedTagsInParagraph.insert("span");
		pAllowedTagsInParagraph.insert("strong");
		pAllowedTagsInParagraph.insert("textarea");
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
		Tag tag = name.c_str();

		pushCoeffFromString(name);
		switch (pState)
		{
			case stNone:
				{
					if (tag == "title")
					{
						pState = stTitle;
						pTitle.clear();
					}
					if (pWithinParagraph && pAllowedTagsInParagraph.find(tag) == pAllowedTagsInParagraph.end())
					{
						logs.error() << pFilename << ": invalid tag within a paragraph";
						pError = true;
						return false;
					}
					if (tag == "p")
						pWithinParagraph = true;
					break;
				}
			case stTitle:
				{
					logs.error() << pFilename << ": invalid nested tag for 'title'";
					pError = true;
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
			case stTitle:
				{
					if (!pTitle.empty() && pTitle.last() != ' ')
						pTitle += ' ';
					pTitle += text.c_str();
					pTitle.trim();
					break;
				}
			default:
				if (!text.empty())
				{
					StringAdapter adapter;
					adapter.adapt(text.c_str(), text.size());
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
			case stNone:
				{
					if (name == "p")
						pWithinParagraph = false;
				}
			case stTitle:
				{
					if (name == "title")
						pState = stNone;
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
		CoeffStack::const_iterator end = pCoeffStack.end();
		for (CoeffStack::const_iterator i = pCoeffStack.begin(); i != end; ++i)
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

		const List::const_iterator end = list.end();
		for (List::const_iterator i = list.begin(); i != end; ++i)
		{
			pWord = *i;
			pWord.toLower();

			WordStat& stat = pWordCount[pWord];
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


void CompileJob::onExecute()
{
	String target;
	String relative;
	const String::Vector::const_iterator end = pSources.end();
	for (String::Vector::const_iterator i = pSources.begin(); i != end; ++i)
	{
		const String& entry = *i;
		relative.assign(entry.c_str() + pInput.size() + 1, entry.size() - pInput.size() - 1);
		target.clear() << pHtdocs << SEP << relative;
		target.replace("article.xml", "index.html");
		generate(relative, entry, target);
	}
}


void CompileJob::generate(const String& rel, const String& src, const String& /*target*/)
{
	logs.info() << "building " << rel;
	TiXmlDocument doc(src.c_str());
	if (!doc.LoadFile())
	{
		logs.error() << src << ", l" << doc.ErrorRow() << ": " << doc.ErrorDesc();
		return;
	}

	// Analyze the XML document
	XMLVisitor visitor(doc, rel);
	if (!doc.Accept(&visitor) || visitor.error())
		return;
}


