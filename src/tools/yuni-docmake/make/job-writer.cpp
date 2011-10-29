
#include "job-writer.h"
#include <yuni/io/directory.h>
#include <yuni/io/directory/system.h>
#include "job.h"
#include "../logs.h"
#include "../tinyxml/tinyxml.h"
#include <yuni/core/hash//checksum//md5.h>
#include <yuni/datetime/timestamp.h>
#include "indexes.h"
#include "webpage.hxx"
#include "program.h"
#include "dictionary.h"


using namespace Yuni;
using namespace Yuni::Tool::DocMake;

# define SEP IO::Separator


namespace // anonymous
{
	static Mutex gMutex;
	static std::vector<JobWriter*>  gJobList;
	static String gTemplateContent;


	class Chart
	{
	public:
		typedef SmartPtr<Chart> Ptr;
		typedef std::vector<Ptr> Vector;

		class Curve
		{
		public:
			typedef SmartPtr<Curve> Ptr;
			typedef std::vector<Ptr> Vector;
		public:
			Curve()
			{
				std::cout << "new curve\n";
			}

		public:
			CString<16,false> type;
			String caption;
			String::Vector x;
			String::Vector y;
		};
	public:
		Chart(TiXmlElement* parentNode) :
			xmlNode(parentNode)
		{
		}

		void generateJS(Clob& script, unsigned int id) const
		{
			script.clear();
			script
				<< "$(function () {\n";
			script
				<< "\t$.plot($(\"#dvchart_" << id << "\"), [\n";
			std::cout << curves.size() << std::endl;

			for (unsigned int i = 0; i != curves.size(); ++i)
			{
				const Curve& curve = *(curves[i]);
				if (i)
					script << ",\n";
				script
					<< "\t\t\{\n"
					<< "\t\t\tlabel: \"" << curve.caption << "\",\n"
					<< "\t\t\tdata: [";

				unsigned int max = Math::Max(curve.x.size(), curve.y.size());
				std::cout << " >>> " << max << std::endl;
				for (unsigned int pt = 0; pt != max; ++pt)
				{
					if (pt)
						script << ", ";
					script << '[';
					if (pt < curve.x.size())
						script << curve.x[pt];
					else
						script << '0';
					script << ',';
					if (pt < curve.y.size())
						script << curve.y[pt];
					else
						script << '0';
					script << ']';
				}
				script << "],\n"
					<< "\t\t\t" << curve.type << ": { show: true }\n"
					<< "\t\t}";
			}
			script << '\n';

			script
				<< "\t],\n"
				<< "\t{\n"
				<< "\t\txaxis: {\n"
				<< "\t\t},\n"
				<< "\t\tyaxis: {\n"
				<< "\t\t},\n"
				<< "\t\tgrid: {\n"
				<< "\t\t\tborderWidth: 1,\n"
				<< "\t\t\tborderColor: \"rgb(190,190,190)\",\n"
				<< "\t\t\tautoHighlight: true\n"
				<< "\t\t}\n"
				<< "\t});\n"
				<< "});";
		}

	public:
		//! The original XML node
		TiXmlElement* xmlNode;
		//!
		Curve::Ptr currentCurve;
		//!
		Curve::Vector curves;
	};


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

		void createAllCharts();
		void deleteUselessTags();

	private:
		//! XML document
		TiXmlDocument& pDocument;
		ArticleData& pArticle;
		std::vector<TiXmlElement*> pToDelete;

		//! \name Charting
		//@{
		Chart::Ptr pCurrentChart;
		Chart::Vector pCharts;
		//@}

		unsigned int pCurrentTOCItemIndex;
		unsigned int pH2Index;
		unsigned int pH3Index;

	}; // class XMLVisitor





	XMLVisitor::XMLVisitor(ArticleData& article, TiXmlDocument& document) :
		pDocument(document),
		pArticle(article),
		pCurrentTOCItemIndex(0),
		pH2Index(0),
		pH3Index(0)
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
		const Dictionary::Tag tag = name.c_str();
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
		if (!(!pCurrentChart))
		{
			if (tag == "curve")
			{
				pCurrentChart->currentCurve = new Chart::Curve();
				pCurrentChart->curves.push_back(pCurrentChart->currentCurve);
				pCurrentChart->currentCurve->caption = element.Attribute("label");
				const StringAdapter type = element.Attribute("type");
				if (!type || (type != "lines" && type != "bars"))
				{
					if (type.notEmpty())
						logs.warning() << "invalid curve type, got '" << type << "'";
					pCurrentChart->currentCurve->type = "lines";
				}
				else
					pCurrentChart->currentCurve->type = type;
				return true;
			}
			if (tag == "x")
			{
				if (!pCurrentChart->currentCurve)
					return false;
				const StringAdapter value = element.GetText();
				if (value.notEmpty())
					value.split(pCurrentChart->currentCurve->x, " ,;\t\r\n|");
				return true;
			}
			if (tag == "y")
			{
				if (!pCurrentChart->currentCurve)
					return false;
				const StringAdapter value = element.GetText();
				if (value.notEmpty())
					value.split(pCurrentChart->currentCurve->y, " ,;\t\r\n|");
				return true;
			}
			// Invalid tag within a chart
			return false;
		}
		if (tag == "chart")
		{
			// This node must be removed at the final end
			pToDelete.push_back(const_cast<TiXmlElement*>(&element));
			pCurrentChart = new Chart(const_cast<TiXmlElement*>(&element));
			pCharts.push_back(pCurrentChart);
			return true;
		}
		if (tag == "title" || tag == "tag" || tag.startsWith("pragma:"))
		{
			pToDelete.push_back(const_cast<TiXmlElement*>(&element));
			return true;
		}
		if (tag == "h2" || tag == "h3")
		{
			// Forcing the id
			if (pCurrentTOCItemIndex < pArticle.tocItems.size())
			{
				e->SetAttribute("id", pArticle.tocItems[pCurrentTOCItemIndex]->hrefID.c_str());
				++pCurrentTOCItemIndex;
			}
			if (tag[1] == '2')
			{
				++pH2Index;
				pH3Index = 0;
			}
			else
				++pH3Index;
			return true;
		}
		if (tag == "source")
		{
			CString<16,false> type = e->Attribute("type");
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



	bool XMLVisitor::VisitExit(const TiXmlElement& element)
	{
		const TIXML_STRING& name = element.ValueTStr();
		const Dictionary::Tag tag = name.c_str();

		if (!(!pCurrentChart))
		{
			if (tag == "chart")
			{
				pCurrentChart = nullptr;
				return true;
			}
			if (tag == "curve")
			{
				if (!(!pCurrentChart))
					pCurrentChart->currentCurve = nullptr;
				return true;
			}
		}
		return true;
	}


	void XMLVisitor::createAllCharts()
	{
		if (pCharts.empty())
			return;
		Clob script;
		String id;
		for (unsigned int i = 0; i != pCharts.size(); ++i)
		{
			id.clear() << "dvchart_" << i;
			const Chart& chart = *(pCharts[i]);
			chart.generateJS(script, i);
			std::cout << script << std::endl;

			TiXmlElement td("td");
			td.SetAttribute("id", id.c_str());
			td.SetAttribute("style", "width:600px;height:300px");

			TiXmlElement emptytd("td");
			emptytd.InsertEndChild(TiXmlText(" "));

			TiXmlElement tr("tr");
			tr.InsertEndChild(emptytd);
			tr.InsertEndChild(td);
			tr.InsertEndChild(emptytd);

			TiXmlElement table("table");
			table.SetAttribute("class", "nostyle");
			table.SetAttribute("style", "width:100%");
			table.InsertEndChild(tr);
			chart.xmlNode->Parent()->InsertBeforeChild(chart.xmlNode, table);

			TiXmlElement js("script");
			js.SetAttribute("type", "text/javascript");
			TiXmlText text(script.c_str());
			js.InsertEndChild(text);
			chart.xmlNode->Parent()->InsertBeforeChild(chart.xmlNode, js);
		}
	}



} // anonymous namespace


void JobWriter::SEOBuildAllTermReferences()
{
	String filename;
	filename << Program::htdocs << SEP << "seo" << SEP << "data.js";
	IO::File::Stream file;

	if (file.openRW(filename))
	{
		Clob data;
		data << "if(1){var f=function(id,n,d) {SEO.termNames[n]=id;SEO.terms[id]=d};";
		DocIndex::BuildSEOTermReference(data);
		data << " }\n";
		file << data;
	}
	else
		logs.error() << "impossible to write " << filename;
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
		Dictionary::WordID* wordIDs = new Dictionary::WordID[newArticle.wordCount.size()];
		float* weights = new float[newArticle.wordCount.size()];
		int* countInArticle = new int[newArticle.wordCount.size()];

		// Registering all new terms
		unsigned int wIx = 0;
		const Dictionary::WordsCount::const_iterator end = newArticle.wordCount.end();
		Dictionary::WordsCount::const_iterator i = newArticle.wordCount.begin();
		for (; i != end; ++i, ++wIx)
		{
			// The word itself
			const Dictionary::Word& word = i->first;
			const Dictionary::WordStat& stats = i->second;

			countInArticle[wIx] = stats.count;
			weights[wIx] = stats.coeff;

			Dictionary::WordID newWordID = Dictionary::FindWordID(word);
			if (newWordID < 0)
			{
				Yuni::MutexLocker locker(Dictionary::mutex);
				++registrationCount;
				newWordID = DocIndex::RegisterWordReference(word);
				Dictionary::allWords[word] = newWordID;
				wordIDs[wIx] = newWordID;
			}
			else
				wordIDs[wIx] = newWordID;
		}

		DocIndex::RegisterWordIDsForASingleArticle(articleID, wordIDs, countInArticle, weights, wIx);

		delete[] weights;
		delete[] countInArticle;
		delete[] wordIDs;
	}

	if (registrationCount && Program::debug)
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
}


JobWriter::~JobWriter()
{
}


void JobWriter::prepareVariables(const String& filenameInHtdocs)
{
	String tmp;
	pVars.clear();

	//! @{MODIFIED}
	{
		pVars["MODIFIED_TIMESTAMP"] = pArticle.modificationTime;
		DateTime::TimestampToString(pVars["MODIFIED"], "%A, %B %e, %Y", pArticle.modificationTime);
	}
	//! @{MODIFIED_ISO8601}
	{
		DateTime::TimestampToString(pVars["MODIFIED_ISO8601"], "%Y-%m-%d", pArticle.modificationTime);
	}

	// @{LANG}
	pVars["LANG"] = pArticle.language;

	// @{INDEX}
	if (Program::shortUrl)
		pVars["INDEX"] = nullptr;
	else
		pVars["INDEX"] = Program::indexFilename;

	// @{TITLE}
	pVars["TITLE"] = pArticle.title;

	// @{DESCRIPTION}
	pVars["DESCRIPTION"] = "";

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
			visitor.createAllCharts();
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
			String path;
			String caption;
			if (!list.empty())
			{
				for (unsigned int i = 0; i < list.size(); ++i)
				{
					tmp << '/' << list[i];
					path.clear() << root << tmp;
					if (!i)
						continue;
					address << "<li><a href=\"" << root << tmp << '/' << pVars["INDEX"] << "\">";
					caption.clear();
					if (!DocIndex::AppendArticleTitleFromPath(caption, tmp))
						caption << list[i];
					address << caption << "</a>";

					IO::ExtractFilePath(path, tmp);
					DocIndex::AppendChildrenList(address, path, caption);
					address << "</li>\n";
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

	// @{TAGS_BEGIN,...}
	// The tags may have been changed because of the dependancies
	pArticle.reloadTagsFromDatabase();
	if (pArticle.tags.empty())
	{
		pVars["TAGS_BEGIN"] = "<!--";
		pVars["TAGS_END"]   = "-->";
		pVars["TAGS_LIST"]  = nullptr;
	}
	else
	{
		pVars["TAGS_BEGIN"] = nullptr;
		pVars["TAGS_END"]   = nullptr;
		String& list = pVars["TAGS_LIST"];
		list << "\n\n\n\n\t<div class=\"tagindex\">\n";
		switch (pArticle.tags.size())
		{
			case 0:  list << "0 tag : ";break;
			case 1:  list << "1 tag : ";break;
			default: list << pArticle.tags.size() << " tags : ";break;
		}

		Dictionary::TagSet::const_iterator end = pArticle.tags.end();
		bool first = true;
		for (Dictionary::TagSet::const_iterator i = pArticle.tags.begin(); i != end; ++i)
		{
			if (!first)
				list += "\t\t, ";
			else
				list += "\t\t";
			list << "<a href=\"#\">" << *i << "</a>\n";
			first = false;
		}
		list << "\t</div>\n\n";
	}

	// @{TOC_...}
	if (pArticle.showTOC && pArticle.tocItems.size() > 1)
	{
		pVars["TOC_BEGIN"] = nullptr;
		pVars["TOC_END"]   = nullptr;
	}
	else
	{
		pVars["TOC_BEGIN"] = "<!--";
		pVars["TOC_END"]   = "-->";
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
		Clob data;
		DocIndex::BuildDirectoryIndex(data, pArticle.directoryIndex);
		pVars["DIRECTORY_INDEX"] = data;
	}
	else
		pVars["DIRECTORY_INDEX"] = "";
}


bool JobWriter::articleIDIndatabase()
{
	pArticleID = DocIndex::FindArticleID(pArticle.htdocsFilename);
	return (pArticleID >= 0);
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
	// @{DESCRIPTION}
	content.replace("@{DESCRIPTION}", pVars["DESCRIPTION"]);

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
	content.replace("@{TAGS_BEGIN}", pVars["TAGS_BEGIN"]);
	content.replace("@{TAGS_LIST}", pVars["TAGS_LIST"]);
	content.replace("@{TAGS_END}", pVars["TAGS_END"]);

	// @{CONTENT}
	content.replace("@{CONTENT}", pVars["CONTENT"]);

	// @{LANG}
	content.replace("@{LANG}", pVars["LANG"]);

	// @{MODIFIED}
	content.replace("@{MODIFIED}", pVars["MODIFIED"]);
	content.replace("@{MODIFIED_TIMESTAMP}", pVars["MODIFIED_TIMESTAMP"]);
	content.replace("@{MODIFIED_ISO8601}", pVars["MODIFIED_ISO8601"]);

	// Directory Index
	content.replace("@{DIRECTORY_INDEX}",  pVars["DIRECTORY_INDEX"]);

	// The replacement of the variable "root" must be done after all replacement
	content.replace("@{ROOT}",  root);
	// The index filename
	content.replace("@{INDEX}", pVars["INDEX"]);

	// Replace all pseudo linefeed
	content.replace("&#x0A;", "\n");
	content.replace("&#x09;", "\t");
	content.replace("&quot;", "\"");

	if (!IO::File::SaveToFile(filenameInHtdocs, content))
	{
		logs.error() << "impossible to generate '" << pArticle.htdocsFilename
			<< "' into '" << filenameInHtdocs << "'";
	}
}



