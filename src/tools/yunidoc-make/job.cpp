
#include "job.h"
#include "logs.h"
#include <yuni/core/io/io.h>
#include "tinyxml/tinyxml.h"
#include <deque>
#include <iostream>


#define SEP  Core::IO::Separator

using namespace Yuni;

Yuni::Job::QueueService<>  queueService;


namespace // anonymous
{

	class XMLVisitor : public TiXmlVisitor
	{
	public:
		XMLVisitor()
		{
			pCoeff = 1.0f;
		}

		virtual ~XMLVisitor()
		{
		}

		virtual bool VisitEnter(const TiXmlDocument& /*doc*/ )
		{
			return true;
		}
		
		virtual bool VisitExit(const TiXmlDocument& /*doc*/)
		{
			return true;
		}

		virtual bool VisitEnter(const TiXmlElement& element, const TiXmlAttribute* attr)
		{
			const TIXML_STRING& name = element.ValueTStr();
			if (name == "h1")
			{
				pushCoeff(2.5f);
				return true;
			}
			if (name == "h2")
			{
				pushCoeff(2.0f);
				return true;
			}
			if (name == "h3")
			{
				pushCoeff(1.25f);
				return true;
			}
			if (name == "h4")
			{
				pushCoeff(1.20f);
				return true;
			}
			if (name == "b")
			{
				pushCoeff(1.1f);
				return true;
			}
			if (name == "i")
			{
				pushCoeff(1.05f);
				return true;
			}
			pushCoeff(1.f);
			return true;
		}

		virtual bool VisitExit(const TiXmlElement& element)
		{
			popCoeff();
			return true;
		}


	private:
		typedef std::deque<float>  CoeffStack;

	private:
		void pushCoeff(float coeff)
		{
			pCoeffStack.push_back(coeff);
			pCoeff *= coeff;
		}

		void popCoeff()
		{
			pCoeffStack.pop_back();
			pCoeff = 1.0f;
			CoeffStack::const_iterator end = pCoeffStack.end();
			for (CoeffStack::const_iterator i = pCoeffStack.begin(); i != end; ++i)
				pCoeff *= *i;
		}

	private:
		CoeffStack  pCoeffStack;
		float pCoeff;

	}; // class XMLVisitor


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


void CompileJob::generate(const String& rel, const String& src, const String& target)
{
	logs.info() << "building " << rel;
	TiXmlDocument doc(src.c_str());
	if (!doc.LoadFile())
	{
		logs.error() << src << ", l" << doc.ErrorRow() << ": " << doc.ErrorDesc();
		return;
	}
	XMLVisitor* visitor = new XMLVisitor();
	if (!doc.Accept(visitor))
	{
		delete visitor;
		return;
	}
	delete visitor;
}


