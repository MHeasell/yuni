
#include <yuni/yuni.h>
#include <yuni/core/io/file.h>
#include "tinyxml/tinyxml.h"
#include "logs.h"
#include <map>
#include <deque>
#include <yuni/job/job.h>
#include <yuni/job/queue.h>
#include <yuni/core/system/suspend.h>

using namespace Yuni;

#define SEP Core::IO::Separator


Yuni::Job::QueueService<>  queueService;

namespace Options
{

	String src = "../../../docs/tmp/doxygen/xml";
	String target = "../../../docs/src/001-en/200-documentation/002-v0.2/500-doxygen";


} // namespace Options

namespace // anonymous
{

	static Yuni::Atomic::Int<>  gJobCount = 0;

	static bool SomeJobRemain()
	{
		return !(!gJobCount);
	}

	class Compound
	{
	public:
		typedef CustomString<256,false> RefID;
		//!
		typedef SmartPtr<Compound>  Ptr;
		//!
		typedef std::map<RefID, Ptr>  Map;
		//!
		typedef std::deque<Ptr>  Deque;

		enum Kind
		{
			kdUnknown = 0,
			kdNamespace,
			kdClass,
			kdFunction,
			kdVariable,
			kdTypedef,
			kdEnum,
			kdFile,
			kdFolder,
			kdGroup,
			kdMax
		};

	public:
		template<class StringT> static Kind  StringToKind(const StringT& str);
		template<class StreamT> static void AppendKindToString(StreamT& out, Kind kind);

	public:
		//! Kind of compound
		Kind kind;
		//! Reference ID
		RefID refid;
		//!
		String name;
	};



	static Compound::Map  allSymbols;


	class CompoundBuilderJob : public Yuni::Job::IJob
	{
	public:
		static bool SomeRemain();

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Constructor
		*/
		explicit CompoundBuilderJob(Compound::Ptr& compound)
			:pCompound(compound)
		{
			++gJobCount;
		}
		//! Destructor
		virtual ~CompoundBuilderJob()
		{
			--gJobCount;
		}
		//@}

	private:
		virtual void onExecute()
		{
			switch (pCompound->kind)
			{
				case Compound::kdNamespace: buildNamespace();break;
				case Compound::kdClass: break;
				case Compound::kdFunction: break;
				case Compound::kdVariable: break;
				case Compound::kdTypedef: break;
				case Compound::kdEnum: break;
				case Compound::kdFile: break;
				case Compound::kdFolder: break;
				case Compound::kdGroup: break;
				case Compound::kdUnknown: break;
				case Compound::kdMax: break;
			}
		}


		void buildNamespace()
		{
			String folder;
			folder << Options::target << SEP << "namespace" << SEP << pCompound->refid;
			std::cout << folder << std::endl;
		}

	private:
		Compound::Ptr pCompound;

	}; // class CompoundBuilderJob



	class XMLIndexVisitor : public TiXmlVisitor
	{
	public:
		//! \name Constructor
		//@{
		/*!
		** \brief Constructor
		*/
		XMLIndexVisitor(TiXmlDocument& document);
		//! Destructor
		virtual ~XMLIndexVisitor();
		//@}

		virtual bool VisitEnter(const TiXmlDocument& /*doc*/ );

		virtual bool VisitExit(const TiXmlDocument& /*doc*/);

		virtual bool VisitEnter(const TiXmlElement& element, const TiXmlAttribute* attr);

		virtual bool VisitExit(const TiXmlElement& element);

		virtual bool Visit(const TiXmlDeclaration& /*declaration*/);
		virtual bool Visit(const TiXmlText& /*text*/);
		virtual bool Visit(const TiXmlComment& /*comment*/);
		virtual bool Visit(const TiXmlUnknown& /*unknown*/);


	private:
		//! XML document
		TiXmlDocument& pDocument;
		//!
		Compound::Deque  pStack;
		//! Stats
		unsigned int pStats[Compound::kdMax];
		//!
		bool pInName;

	}; // class XMLIndexVisitor




	template<class StringT>
	Compound::Kind  Compound::StringToKind(const StringT& str)
	{
		if (str == "class")
			return kdClass;
		else if (str == "struct")
			return kdClass;
		else if (str == "function")
			return kdFunction;
		else if (str == "variable")
			return kdVariable;
		else if (str == "typedef")
			return kdTypedef;
		else if (str == "file")
			return kdFile;
		else if (str == "namespace")
			return kdNamespace;
		else if (str == "dir")
			return kdFolder;
		else if (str == "group")
			return kdGroup;

		return kdUnknown;
	}


	template<class StreamT>
	void Compound::AppendKindToString(StreamT& out, Kind kind)
	{
		switch (kind)
		{
			case kdClass:      out += "class";break;
			case kdNamespace:  out += "namespace";break;
			case kdFunction:   out += "function";break;
			case kdTypedef:    out += "typedef";break;
			case kdEnum:       out += "enum";break;
			case kdVariable:   out += "variable";break;
			case kdFile:       out += "file";break;
			case kdFolder:     out += "folder";break;
			case kdGroup:      out += "group";break;
			case kdUnknown:
			case kdMax:break;
		}
	}


	XMLIndexVisitor::XMLIndexVisitor(TiXmlDocument& document) :
		pDocument(document),
		pInName(false)
	{
		for (unsigned int i = 0; i != Compound::kdMax; ++i)
			pStats[i] = 0;
	}


	XMLIndexVisitor::~XMLIndexVisitor()
	{
		CustomString<128,false>  result;
		CustomString<64,false>  name;

		logs.info() << "Compound statistics from index";
		for (unsigned int i = 1; i != Compound::kdMax; ++i)
		{
			name.clear();
			Compound::AppendKindToString(name, (Compound::Kind) i);

			result.clear();
			result.resize(20, ' ');
			result.overwriteRight(name);

			logs.info() << result << " : " << pStats[i];
		}
	}


	bool XMLIndexVisitor::VisitEnter(const TiXmlDocument& /*doc*/ )
	{
		return true;
	}


	bool XMLIndexVisitor::VisitExit(const TiXmlDocument& /*doc*/)
	{
		return true;
	}


	bool XMLIndexVisitor::VisitEnter(const TiXmlElement& element, const TiXmlAttribute* /*attr*/)
	{
		const TIXML_STRING& strname = element.ValueTStr();

		if (strname == "compound")
		{
			Compound* compound = new Compound();
			const StringAdapter  kind = element.Attribute("kind");
			compound->kind = Compound::StringToKind(kind);
			const StringAdapter  refid = element.Attribute("refid");
			compound->refid = refid;

			pStack.push_front(compound);
		}
		else
		{
			if (!pStack.empty())
			{
				if (strname == "name")
					pInName = true;
			}
		}

		return true;
	}


	bool XMLIndexVisitor::Visit(const TiXmlText& text)
	{
		if (pInName && !pStack.empty())
		{
			Compound::Ptr compound = pStack.front();

			const TIXML_STRING& name = text.ValueTStr();
			compound->name.append(name.c_str(), name.size());
		}
		return true;
	}


	bool XMLIndexVisitor::Visit(const TiXmlComment&)
	{
		return true;
	}


	bool XMLIndexVisitor::Visit(const TiXmlDeclaration&)
	{
		return true;
	}


	bool XMLIndexVisitor::Visit(const TiXmlUnknown&)
	{
		return true;
	}



	bool XMLIndexVisitor::VisitExit(const TiXmlElement& element)
	{
		const TIXML_STRING& strname = element.ValueTStr();

		if (strname == "compound")
		{
			if (pStack.empty()) // strange - should never happen
				return true;
			Compound::Ptr compound = pStack.front();

			const Compound::Kind kind = compound->kind;
			if (kind != Compound::kdUnknown && compound->name.notEmpty())
			{
				++pStats[kind];
				allSymbols[compound->refid] = compound;
			}
			pStack.pop_front();
		}
		else
		{
			if (strname == "name")
				pInName = false;
		}

		return true;
	}






	static bool ReadIndex(const String& folder)
	{
		String filename;
		filename << folder << SEP << "index.xml";

		TiXmlDocument doc;
		if (!doc.LoadFile(filename.c_str(), TIXML_ENCODING_UTF8))
		{
			logs.error() << "impossible to read the index";
			return false;
		}

		// Analyze the XML document
		XMLIndexVisitor visitor(doc);
		if (!doc.Accept(&visitor))
			return false;

		return true;
	}


} // anonymous namespace



int main(int /*argc*/, char** /*argv*/)
{
	if (ReadIndex(Options::src))
	{
		queueService.start();
		// Creating all jobs
		Compound::Map::iterator end = allSymbols.end();
		for (Compound::Map::iterator i = allSymbols.begin(); i != end; ++i)
		{
			Compound::Ptr& compound = i->second;
			CompoundBuilderJob* job = new CompoundBuilderJob(compound);
			queueService += job;
		}

		queueService.wait();
		while (SomeJobRemain())
			Yuni::SuspendMilliSeconds(150);
		queueService.stop();
	}
	return 0;
}

