
#include "grammar.h"
#include "../../io/file.h"


namespace Yuni
{
namespace Parser
{
namespace PEG
{
	namespace // anonymous
	{

		class CPPConverter
		{
		public:
			CPPConverter(const Node::Map& rules) : rules(rules) {}
			bool initialize(const AnyString& name);
			void startHeaderheaderGuardID();
			void endHeaderheaderGuardID();
			void generateH();
			void generateHXX();
			void generateCPP();
			bool writeFiles(const AnyString& root) const;

		public:
			//! Original rules
			const Node::Map& rules;

			//! Code in the .h file
			Clob h;
			//! Code in the .hxx file
			Clob hxx;
			//! Code in the .cpp file
			Clob cpp;

			//! Header guard ID
			String headerGuardID;
			//! Class name
			String classname;
			//! Namespace
			String::Vector namespaces;

		}; // class CPPConverter



		template<class StringT>
		static inline void EnumIDToClassname(StringT& out, const String& enumID)
		{
			out = "Node";
			out << enumID;
			out[4] = (char) String::ToUpper(out[4]);
		}


		static inline void SingleInstructionType(Clob& cpp, uint64 rulecount)
		{
			cpp << "\t//! A single instruction type\n";
			cpp << "\ttypedef ";
			if (rulecount < 255)
				cpp << "uint8";
			else if (rulecount < 65535)
				cpp << "uint16";
			else if (rulecount < (uint32) -1)
				cpp << "uint32";
			else
				cpp << "uint64";

			cpp << " SingleInstruction;\n\n\n\n";
		}


		inline bool CPPConverter::initialize(const AnyString& name)
		{
			name.split(namespaces, "/\\:");
			return true;
		}


		inline void CPPConverter::generateH()
		{
			const Node::Map::const_iterator end = rules.end();
			h << "#ifndef " << headerGuardID << "_H__\n";
			h << "# define " << headerGuardID << "_H__\n";
			h << "\n";
			h << "# include <yuni/yuni.h>\n";
			h << "# include <yuni/core/string.h>\n";
			h << "\n\n";

			for (uint i = 0; i != namespaces.size(); ++i)
				h << "namespace " << namespaces[i] << "\n{\n";
			h << "\n\n";

			h << "\tenum Rule\n";
			h << "\t{\n";
			for (Node::Map::const_iterator i = rules.begin(); i != end; ++i)
			{
				h << "\t\t//! enum for the rule `" << i->first << "`\n";
				h << "\t\t" << i->second.enumID << ",\n";
			}

			h << "\t\t//! enum for the final rule\n";
			h << "\t\trgEOF\n";

			h << "\t}\n";
			h << '\n';


			// rule count
			h << "\tenum\n";
			h << "\t{\n";
			h << "\t\t//! The total number of rules\n";
			h << "\t\truleCount = " << (1 + rules.size()) << '\n';
			h << "\t};\n";
			h << "\n\n\n";

			String nodename;

			for (Node::Map::const_iterator i = rules.begin(); i != end; ++i)
			{
				EnumIDToClassname(nodename, i->second.enumID);

				h << "\tclass " << nodename << " final\n";
				h << "\t{\n";
				h << "\tpublic:\n";
				h << "\t\t//! rule enum id\n";
				h << "\t\tstatic inline Rule rule()  { return " << i->second.enumID << "; }\n";
				h << "\t};\n\n\n";
			}

			h << "\n\n";

			h << "\tclass Parser final\n";
			h << "\t{\n";
			h << "\tpublic:\n";
			h << "\t\tParser();\n";
			h << "\t\t~Parser();\n";
			h << '\n';
			h << "\t\tvoid begin();\n";
			h << "\t\tvoid readChunks();\n";
			h << "\t\tvoid end();\n";
			h << '\n';
			h << "\tpublic:\n";
			h << "\t\t//! Event: ask for reading a new chunk\n";
			h << "\t\tYuni::Bind<void (Yuni::Clob&)> onRead;\n";
			h << '\n';
			h << "\tprivate:\n";
			h << "\t\tclass Internals;\n";
			h << "\t\tInternals* pInternals;\n";
			h << '\n';
			h << "\t}; // class Parser\n";

		}


		inline void CPPConverter::generateHXX()
		{
			hxx << "#ifndef " << headerGuardID << "_HXX__\n";
			hxx << "# define " << headerGuardID << "_HXX__\n";
			hxx << "\n\n\n";

			for (uint i = 0; i != namespaces.size(); ++i)
				hxx << "namespace " << namespaces[i] << "\n{\n";
			hxx << "\n\n";
		}


		inline void CPPConverter::generateCPP()
		{
			const Node::Map::const_iterator end = rules.end();
			cpp << "\n";
			cpp << "#include \"\"\n";
			cpp << "#include <cassert>\n";
			cpp << '\n';
			cpp << "using namespace Yuni;\n";
			cpp << "\n\n";

			for (uint i = 0; i != namespaces.size(); ++i)
				cpp << "namespace " << namespaces[i] << "\n{\n";

			cpp << "\n\n";
			SingleInstructionType(cpp, rules.size());

			cpp << "\t//! List of instructions\n";
			cpp << "\ttypedef SingleInstruction*  Instructions;\n\n\n";

			cpp << "\tenum\n";
			cpp << "\t{\n";
			cpp << "\t\t//! Chunk size\n";
			cpp << "\t\tchunkSize = 1024,\n";
			cpp << "\t};\n\n\n";

			cpp << "\tstatic inline void RuleDispatcher()\n";
			cpp << "\t{\n";
			cpp << "\t\t// threaded code dispatch\n";
			cpp << "\t\t//\n";
			cpp << "\t\t// All instructions, with an initial capacity\n";
			cpp << "\t\tInstructions instrs = (SingleInstruction*)::malloc(chunkSize * sizeof(SingleInstruction));\n";
			cpp << "\t\t// pointer to the current instruction\n";
			cpp << "\t\tuint vp = 0;\n";
			cpp << '\n';
			cpp << "\t\t// jump to the first instruction\n";
			cpp << "\t\tgoto i_rgStart;\n";
			cpp << "\n";
			cpp << "\t\t// all instructions\n";
			for (Node::Map::const_iterator i = rules.begin(); i != end; ++i)
			{
				cpp << "\t\ti_" << i->second.enumID << ":\n";
				cpp << "\t\t{\n";
				i->second.exportCPP(cpp, 3);
				cpp << "\t\t}\n\n";
			}

			cpp << "\t\ti_EOF:\n";
			cpp << "\t\t{\n";
			cpp << "\t\t}\n\n";

			cpp << "\t\ti_ERROR:\n";
			cpp << "\t\t{\n";
			cpp << "\t\t}\n\n";

			cpp << "\t}\n";
			cpp << "\n\n\n\n";

			cpp << "\tclass Parser::Internals final\n";
			cpp << "\t{\n";
			cpp << "\t};\n";
			cpp << "\n\n\n";

			cpp << "\tParser::Parser() :\n";
			cpp << "\t\tpInternals(nullptr)\n";
			cpp << "\t{\n";
			cpp << "\t}\n\n\n";

			cpp << "\tParser::~Parser()\n";
			cpp << "\t{\n";
			cpp << "\t\tdelete pInternals;\n";
			cpp << "\t}\n\n\n";

			cpp << "\tvoid Parser::begin()\n";
			cpp << "\t{\n";
			cpp << "\t\tdelete pInternals;\n";
			cpp << "\t\tpInternals = new Internals();\n";
			cpp << "\t}\n\n\n";

			cpp << "\tvoid Parser::readChunks()\n";
			cpp << "\t{\n";
			cpp << "\t\tassert(pInternals and \"the method `begin()` must be called first\");\n";
			cpp << "\t\tdo\n";
			cpp << "\t\t{\n";
			cpp << "\t\t}\n";
			cpp << "\t\twhile (true);\n";
			cpp << "\t}\n\n\n";

			cpp << "\tvoid Parser::end()\n";
			cpp << "\t{\n";
			cpp << "\t\tassert(pInternals and \"the method `begin()` must be called first\");\n";
			cpp << "\t}\n\n\n";
		}


		inline void CPPConverter::startHeaderheaderGuardID()
		{
			headerGuardID = "__HEADER";

			for (uint i = 0; i != namespaces.size(); ++i)
				headerGuardID << '_' << namespaces[i];
			headerGuardID << "_GRAMMAR";
			headerGuardID.toUpper();
		}


		inline void CPPConverter::endHeaderheaderGuardID()
		{
			h << "\n\n\n\n\n";
			hxx << "\n\n\n\n\n";
			cpp << "\n\n\n\n\n";

			if (not namespaces.empty())
			{
				uint i = (uint) namespaces.size();
				do
				{
					--i;
					h << "} // namespace " << namespaces[i] << '\n';
					hxx << "} // namespace " << namespaces[i] << '\n';
					cpp << "} // namespace " << namespaces[i] << '\n';
				}
				while (i > 0);
			}

			h << '\n' << "# include \"grammar.hxx\"\n\n";
			h << "#endif // " << headerGuardID << "_H__\n";

			hxx << "\n#endif // " << headerGuardID << "_HXX__\n";
		}


		inline bool CPPConverter::writeFiles(const AnyString& root) const
		{
			String file;
			file.clear() << root << "h";
			if (not IO::File::SetContent(file, h))
				return false;

			file.clear() << root << "hxx";
			if (not IO::File::SetContent(file, hxx))
				return false;

			file.clear() << root << "cpp";
			if (not IO::File::SetContent(file, cpp))
				return false;

			return true;
		}


	} // anonymous namespace






	bool Grammar::exportToCPP(const AnyString& rootfilename, const AnyString& name) const
	{
		CPPConverter data(pRules);
		if (not data.initialize(name))
			return false;

		data.startHeaderheaderGuardID();
		data.generateH();
		data.generateHXX();
		data.generateCPP();
		data.endHeaderheaderGuardID();
		return data.writeFiles(rootfilename);
	}





} // namespace PEG
} // namespace Parser
} // namespace Yuni

