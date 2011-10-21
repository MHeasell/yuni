
#include "job-compound-writer.h"
#include <yuni/core/system/suspend.h>
#include <yuni/datetime/timestamp.h>
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

		static Atomic::Int<> GenerationNumericID;



		template<class StringT>
		static void ArrangeTypename(StringT& str)
		{
			str.replace(" *", "*");
			str.replace(" &amp;", "&amp;");
			str.replace(" &lt; ", "&lt;");
			str.replace(" &gt; ", "&gt;");
			str.replace(" &gt;","&gt;");
			str.replace(" , ", ", ");
		}


	} // anonymous namespace



	void CompoundWriter::Dispatch()
	{
		// Write articles
		{
			unsigned int count = (unsigned int) allSymbolsByRefID.size();
			switch (count)
			{
				case 0:  logs.info() << "No article";break;
				case 1:  logs.info() << "writing 1 article";break;
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
		if (!pCompound->name || pCompound->name.contains('@'))
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
			String id;
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
			out << "<pragma:toc visible=\"false\" />\n";
			out << "<tag name=\"doxygen\" />\n";
			out << "<tag name=\"dox:class\" />\n";
			out << "\n\n\n";

			out << "<h2><code>" << pageTitle << "</code></h2>";
			out << "<table class=\"doxygen_table\">\n";

			bool isAbstract = (pageTitle.first() == 'I');

			unsigned int count = (unsigned int) pCompound->sections.size();
			for (unsigned int i = 0; i != count; ++i)
			{
				const Section::Ptr& sectionptr = pCompound->sections[i];
				const Section& section = *sectionptr;

				if (section.kind.startsWith("public-"))
					visibility = "Public";
				else if (section.kind.startsWith("protected-"))
					visibility = "Protected";
				else if (section.kind.startsWith("private-"))
				{
					visibility = "Private";
					// Skipping all private members
					continue;
				}
				else
					visibility = "Public";

				// Protected and private data should not be displayed when the class is not inherited
				if (!isAbstract && visibility != "Public")
					continue;

				out << "<tr><td class=\"doxnone\"></td><td class=\"doxnone\">";
				/*
				// if (lastVisibility != visibility)
				if (0)
				{
					out << "<div class=\"visibility\">" << visibility << "</div>";
					lastVisibility = visibility;
				}
				out << "</td>\n<td>";
				*/
				if (section.caption.notEmpty())
				{
					HtmlEntities(tmp, section.caption);
					out << "<h3 class=\"doxygen_section\">" << tmp << " <code class=\"doxygen_visibility\">" << visibility << "</code></h3>\n";
				}
				else
					out << "<h3 class=\"doxygen_section\">" << visibility << " <code class=\"doxygen_visibility\">" << visibility << "</code></h3>\n";
				out << "</td></tr>\n";

				unsigned int memcount = (unsigned int) section.members.size();
				for (unsigned int j = 0; j != memcount; ++j)
				{
					const Member::Ptr& memberptr = section.members[j];
					const Member& member = *memberptr;
					if (member.name == "YUNI_STATIC_ASSERT")
						continue;

					out << "<tr>";


					id.clear() << member.name << '_' << (++GenerationNumericID) << DateTime::CurrentTimestamp();
					id.replace('-', '_'); // prevent against int overflow
					HtmlEntities(tmp, member.name);
					HtmlEntities(type, member.type);
					ArrangeTypename(type);
					HtmlEntities(brief, member.brief);

					switch (member.kind)
					{
						case kdFunction: out << "<td class=\"doxygen_fun\">";break;
						case kdTypedef:  out << "<td class=\"doxygen_typedef\">";break;
						case kdVariable: out << "<td class=\"doxygen_var\">";break;
						case kdEnum:     out << "<td class=\"doxygen_enum\">";break;
						default: out << "<td>";break;
					}
					out << "</td><td class=\"doxnone\">";

					if (brief.notEmpty())
						out << brief << "<div class=\"doxygen_name_spacer\"></div>\n";
					out << "<code>";

					switch (member.kind)
					{
						case kdFunction:
							{
								if (!member.templates.empty())
								{
									out << "<div id=\"" << id << "_templ\" style=\"display:none\">";
									out << "<span class=\"keyword\">template</span>&lt;";
									for (unsigned int p = 0; p != member.templates.size(); ++p)
									{
										if (p)
											out << ", ";
										const Parameter::Ptr& paramstr = member.templates[p];
										const Parameter& param = *paramstr;
										HtmlEntities(paramType, param.type);
										HtmlEntities(paramName, param.name);
										ArrangeTypename(paramType);
										out << paramType << ' ' << paramName;
									}
									out << "&gt;</div>\n";
								}
								if (tmp.first() == '~')
								{
									String t = tmp;
									t.replace("~", "<b> ~ </b>");
									out << " <span class=\"method\"><a href=\"#\">" << t << "</a></span>";
								}
								else
								{
									out << " <span class=\"method\"><a href=\"#\">" << tmp << "</a></span>";
								}

								out << ": ";

								if (member.isStatic)
									out << "<span class=\"keyword\">static</span> ";

								out << type << " (";

								for (unsigned int p = 0; p != member.parameters.size(); ++p)
								{
									if (p)
										out << ", ";
									const Parameter::Ptr& paramstr = member.parameters[p];
									const Parameter& param = *paramstr;
									HtmlEntities(paramType, param.type);
									HtmlEntities(paramName, param.name);
									ArrangeTypename(paramType);
									out << paramType << ' ' << paramName;
								}
								out << ')';
								if (member.isConst)
									out << " <span class=\"keyword\">const</span>";
								out << ";\n";
								break;
							}
						case kdTypedef:
							{
								out << "<span class=\"method\"><a href=\"#\">" << tmp << "</a></span>";
								out << ": <span class=\"keyword\">typedef</span> ";
								out << type;
								out << ';';
								break;
							}
						case kdVariable:
							{
								out << "<span class=\"method\"><a href=\"#\">" << tmp << "</a></span>";
								out << ": " << type;
								out << ';';
								break;
							}
						default:
		//					Compound::AppendKindToString(std::cout, member.kind);
		//					std::cout << '\n';
							out << "<i>(unmanaged tag: " << (unsigned int) member.kind << ")</i>";
							break;
					}
					out << "</code>\n";
					out << "</td>";
					out << "</tr>\n";
				}
			}

			out << "</table>\n\n\n";

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
			file << "<tag name=\"dox:namespace\" />\n";
			file << "\n\n";
		}
	}







} // namespace Job
} // namespace Dox2Article
} // namespace Edalene
} // namespace Yuni

