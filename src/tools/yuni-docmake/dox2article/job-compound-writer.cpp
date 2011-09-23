
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

	namespace // anonymous
	{

		template<class StringT1, class StringT2>
		inline void HtmlEntities(StringT1& out, const StringT2& string)
		{
			out = string;
			out.replace("&", "&amp;");
			out.replace("<", "&lt;");
			out.replace(">", "&gt;");
		}


	} // anonymous namespace



	void CompoundWriter::Dispatch()
	{
		// Write articles
		{
			unsigned int count = (unsigned int) allSymbolsByRefID.size();
			switch (count)
			{
				case 0: logs.info() << "No article";break;
				case 1: logs.info() << "writing 1 article";break;
				default: logs.info() << "writing " << count << " articles";break;
			}
		}
		{
			Compound::Map::iterator end = allSymbolsByRefID.end();
			for (Compound::Map::iterator i = allSymbolsByRefID.begin(); i != end; ++i)
			{
				Compound::Ptr& compound = i->second;
				Edalene::Dox2Article::Job::queueService += new CompoundWriter(compound);
			}
		}

		queueService.wait();
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
			case kdFunction: break;
			case kdTypedef: break;
			case kdClass: buildClass();break;
			case kdNamespace: buildNamespace();break;
			case kdVariable: break;
			case kdEnum: break;
			case kdFile: break;
			case kdFolder: break;
			case kdGroup: break;
			case kdUnknown: break;
			case kdMax: break;
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
			String tmp;
			String visibility;
			String lastVisibility;
			String type;
			String brief;
			String paramType;
			String paramName;
			Clob out;
			// Getting the name
			const String& name = pCompound->name;

			String::Size offset = name.find_last_of(":\\/");
			String pageTitle;
			if (offset < name.size() && offset + 1 < name.size())
				pageTitle.append(name.c_str() + offset + 1, name.size() - (offset + 1));
			else
				pageTitle << name;
			out << "<title>" << pageTitle << "</title>\n";
			out << "<pragma:weight value=\"0.5\" />\n";
			out << "<tag name=\"doxygen\" />\n";
			out << "<tag name=\"class\" />\n";
			out << "\n\n\n";

			out << "<h2>Summary of the class <code>" << pageTitle << "</code></h2>";
			out << "<table class=\"nostyle\">\n";

			unsigned int count = (unsigned int) pCompound->sections.size();
			for (unsigned int i = 0; i != count; ++i)
			{
				const Section::Ptr& sectionptr = pCompound->sections[i];
				const Section& section = *sectionptr;

				if (section.kind.startsWith("public-"))
					visibility = "Public\n";
				else if (section.kind.startsWith("protected-"))
					visibility = "Protected\n";
				else if (section.kind.startsWith("private-"))
				{
					visibility = "Private";
					// Skipping all private members
					continue;
				}
				else visibility = "Public";

				out << "<tr><td>";
//				if (lastVisibility != visibility)
				{
					out << "<div class=\"visibility\">" << visibility << "</div>";
					lastVisibility = visibility;
				}
				out << "</td>\n<td>";
				if (section.caption.notEmpty())
				{
					HtmlEntities(tmp, section.caption);
					out << "<h3 class=\"h3noleftspace\">" << tmp << "</h3>\n";
				}
				else
					out << "<h3 class=\"h3noleftspace\">" << visibility << "</h3>\n";

				unsigned int memcount = (unsigned int) section.members.size();
				for (unsigned int j = 0; j != memcount; ++j)
				{
					const Member::Ptr& memberptr = section.members[j];
					const Member& member = *memberptr;
					if (member.name == "YUNI_STATIC_ASSERT")
						continue;
					HtmlEntities(tmp, member.name);
					HtmlEntities(type, member.type);
					HtmlEntities(brief, member.brief);

					switch (member.kind)
					{
						case kdFunction: out << "<p class=\"doxygen_fun\">";break;
						case kdTypedef:  out << "<p class=\"doxygen_typedef\">";break;
						case kdVariable: out << "<p class=\"doxygen_var\">";break;
						case kdEnum:     out << "<p class=\"doxygen_enum\">";break;
						default: out << "<p>";break;
					}

					if (brief.notEmpty())
						out << brief << "<br />\n";
					out << "<code>";

					switch (member.kind)
					{
						case kdFunction:
							{
								if (!member.templates.empty())
								{
									out << "<span class=\"keyword\">template</span>&lt;";
									for (unsigned int p = 0; p != member.templates.size(); ++p)
									{
										if (p)
											out << ", ";
										const Parameter::Ptr& paramstr = member.templates[p];
										const Parameter& param = *paramstr;
										HtmlEntities(paramType, param.type);
										HtmlEntities(paramName, param.name);
										paramType.replace(" &amp;", "<b>&amp;</b>");
										paramType.replace(" *", "<b>*</b>");
										out << paramType << ' ' << paramName;
									}
									out << "&gt;<br />";
								}
								if (member.isStatic)
									out << "<span class=\"keyword\">static</span> ";
								out << type;
								if (tmp.first() == '~')
								{
									String t = tmp;
									t.replace("~", "<b> ~ </b>");
									out << " <span class=\"method\"><a href=\"#\">" << t << "</a></span>(";
								}
								else
								{
									out << " <span class=\"method\"><a href=\"#\">" << tmp << "</a></span>(";
								}

								for (unsigned int p = 0; p != member.parameters.size(); ++p)
								{
									if (p)
										out << ", ";
									const Parameter::Ptr& paramstr = member.parameters[p];
									const Parameter& param = *paramstr;
									HtmlEntities(paramType, param.type);
									HtmlEntities(paramName, param.name);
									paramType.replace(" &amp;", "<b>&amp;</b>");
									paramType.replace(" *", "<b>*</b>");
									out << paramType << ' ' << paramName;
								}
								out << ')';
								if (member.isConst)
									out << " <span class=\"keyword\">const</span>";
								out << ';';
								break;
							}
						case kdTypedef:
							{
								out << "<span class=\"keyword\">typedef</span> ";
								out << type;
								out << " <span class=\"method\"><a href=\"#\">" << tmp << "</a></span>";
								out << ';';
								break;
							}
						case kdVariable:
							{
								out << type;
								out << " <span class=\"method\"><a href=\"#\">" << tmp << "</a></span>";
								out << ';';
								break;
							}
						default:
		//					Compound::AppendKindToString(std::cout, member.kind);
		//					std::cout << '\n';
							out << "<i>(unmanaged tag)</i>";
							break;
					}
					out << "</code></p>\n";
				}

				out << "</td>";
				out << "</tr>\n";
			}

			out << "</table>\n\n\n";
			out << "<h2>Detailed Description</h2>";
			out << '\n';

			// Writing the file
			file << out;
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
			file << "<pragma:weight value=\"0.40\" />\n";
			file << "<tag name=\"doxygen\" />\n";
			file << "<tag name=\"namespace\" />\n";
			file << "\n\n";
		}
	}







} // namespace Job
} // namespace Dox2Article
} // namespace Edalene
} // namespace Yuni

