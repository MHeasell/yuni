
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

	typedef std::vector<std::pair<uint, AnyString> > VectorPairYAndLine;

	class SubRulePart final
	{
	public:
		typedef std::vector<SubRulePart> Vector;
	public:
		SubRulePart() :
			type(rtRule)
		{}

		SubRulePart(const NullPtr&) :
			type(rtRule)
		{}

		bool empty() const
		{
			return type == rtRule && text.empty();
		}

	public:
		String text;
		RuleType type;

	}; // class SubRulePart

	class TempRuleInfo final
	{
	public:
		void reset()
		{
			pragmas.clear();
			subrules.clear();
		}

	public:
		VectorPairYAndLine pragmas;
		VectorPairYAndLine subrules;

	}; // class TempRuleInfo


	class RuleParser final
	{
	public:
		RuleParser(Grammar& grammar);

		bool analyze();


	public:
		//! Original content
		AnyString content;
		//! Source
		AnyString source;

	private:
		bool analyzeEachRule();
		bool prepareRuleIdentifier(AnyString& line, uint lineIndex);
		bool error(String& message);
		void warns(String& message);

	private:
		//! The original grammar
		Grammar& grammar;
		//! Error message
		String errmsg;
		//! The current line
		AnyString line;
		//! The current rule name
		String currentRuleName;

		// rules (pragma list, subrule)
		typedef std::map<String, TempRuleInfo> TempRuleList;
		TempRuleList rules;

	}; // class RuleParser






	static inline bool CheckIdentifier(const AnyString& text)
	{
		if (text.empty())
			return false;

		if (String::IsDigit(text[0]))
			return false;

		for (uint i = 0; i != text.size(); ++i)
		{
			if (not String::IsAlpha(text[i]) and text[i] != '-')
				return false;
		}
		return true;
	}



	inline RuleParser::RuleParser(Grammar& grammar) :
		grammar(grammar)
	{}


	inline bool RuleParser::error(String& message)
	{
		grammar.onError(message);
		return false;
	}


	inline void RuleParser::warns(String& message)
	{
		grammar.onWarning(message);
	}


	inline bool RuleParser::prepareRuleIdentifier(AnyString& line, uint lineIndex)
	{
		if (line.last() != ':')
		{
			errmsg.clear() << source << ": l" << lineIndex << ": invalid rule name, missing semicolon";
			return error(errmsg);
		}

		line.removeLast();
		if (not CheckIdentifier(line))
		{
			errmsg.clear() << source << ": l" << lineIndex << ": invalid rule identifier '" << line << "'";
			return error(errmsg);
		}

		return true;
	}




	bool RuleParser::analyze()
	{
		// current offset
		AnyString::Size offset = 0;
		// current line
		uint lineIndex = 0;

		do
		{
			++lineIndex;
			AnyString::Size next = content.find('\n', offset);

			// re-adapt the current line
			if (next < content.size())
				line.adapt(content, next - offset, offset);
			else
				line.adapt(content, content.size() - offset, offset);

			offset = next + 1;

			if (line.empty())
				continue;

			if (not AnyString::IsSpace(line[0]))
			{
				// new rule
				line.trimRight();

				if (not prepareRuleIdentifier(line, lineIndex))
					return false;

				currentRuleName = line;
				if (rules.count(currentRuleName) != 0)
				{
					errmsg.clear() << source << ": l" << lineIndex << ": rule '" << currentRuleName << "' already exists";
					return error(errmsg);
				}

				rules[currentRuleName].reset();
			}
			else
			{
				// continue the previous rule
				line.trim();

				if (not line.startsWith("@pragma "))
				{
					rules[currentRuleName].subrules.push_back(std::make_pair(lineIndex, line));
				}
				else
				{
					AnyString pragma(line, 8);
					rules[currentRuleName].pragmas.push_back(std::make_pair(lineIndex, pragma));
				}
			}
		}
		while (offset < content.size());

		return analyzeEachRule();
	}


	bool RuleParser::analyzeEachRule()
	{
		enum State
		{
			stDefault,
			stInString,
			stInCharList
		};
		// each rule
		TempRuleList::iterator end = rules.end();
		TempRuleList::iterator i = rules.begin();

		SubRulePart::Vector newsubrules;
		newsubrules.push_back(nullptr);

		for (; i != end; ++i)
		{
			currentRuleName = i->first;
			std::cout << std::endl << "@" << currentRuleName << std::endl;
			newsubrules.clear();
			newsubrules.push_back(nullptr);
			State state = stDefault;
			uint instringStartUtf8 = 0;
			bool hasBackslash = false;
			uint bracketDepth = 0;
			char stringQuote = '\0';

			// for each line of the rule
			VectorPairYAndLine::const_iterator send = i->second.subrules.end();
			VectorPairYAndLine::const_iterator si   = i->second.subrules.begin();
			for (; si != send; ++si)
			{
				uint lineIndex = si->first;
				AnyString::const_utf8iterator cend = si->second.utf8end();
				AnyString::const_utf8iterator ci   = si->second.utf8begin();
				uint offset = 0;
				uint offsetutf8 = 0;

				for (; ci != cend; ++ci)
				{
					++offsetutf8;
					offset += ci->size();
					char c = *ci;

					switch (state)
					{
						case stDefault:
						{
							switch (c)
							{
								case '\'':
								case '"':
								{
									state = stInString;
									hasBackslash = false;
									instringStartUtf8 = offsetutf8;
									if (not newsubrules.back().empty())
										newsubrules.push_back(nullptr);
									stringQuote = c;
									newsubrules.back().type = rtString;
									break;
								}
								case '[':
								{
									state = stInCharList;
									hasBackslash = false;
									instringStartUtf8 = offsetutf8;
									bracketDepth = 1;
									if (not newsubrules.back().empty())
										newsubrules.push_back(nullptr);
									newsubrules.back().type = rtListOfChars;
									break;
								}
								case '^':
								case '*':
								case '+':
								{
									if (not newsubrules.back().empty())
										newsubrules.push_back(nullptr);
									newsubrules.back().text = c;
									newsubrules.back().type = rtModifier;
									newsubrules.push_back(nullptr);
									break;
								}
								case '|':
								case '(':
								case ')':
								{
									if (not newsubrules.back().empty())
										newsubrules.push_back(nullptr);
									newsubrules.back().text = c;
									newsubrules.back().type = rtGroup;
									newsubrules.push_back(nullptr);
									break;
								}
								case '\t':
								case ' ':
								case '\r':
								case '\n':
								{
									if (not newsubrules.back().empty())
										newsubrules.push_back(nullptr);
									break;
								}
								default:
								{
									newsubrules.back().text += *ci;
									break;
								}
							}
							break;
						}
						case stInString:
						{
							// in string
							switch (c)
							{
								case '"':
								case '\'':
								{
									if (c == stringQuote)
									{
										if (hasBackslash)
										{
											newsubrules.back().text += stringQuote;
											hasBackslash = false;
										}
										else
										{
											if (not newsubrules.back().empty())
											{
												newsubrules.push_back(nullptr);
											}
											else
												warns(errmsg.clear() << source << ": l" << lineIndex << ": empty string at " << instringStartUtf8);

											state = stDefault;
										}
									}
									break;
								}
								case '\\':
								{
									if (hasBackslash)
									{
										newsubrules.back().text += '\\';
										hasBackslash = false;
									}
									else
										hasBackslash = true;
									break;
								}
								default:
								{
									if (hasBackslash)
									{
										switch (c)
										{
											case '\\': newsubrules.back().text += '\\';break;
											case 't': newsubrules.back().text += '\t';break;
											case 'n': newsubrules.back().text += '\n';break;
											case 'r': newsubrules.back().text += '\r';break;
											case 'v': newsubrules.back().text += '\v';break;
											case 'f': newsubrules.back().text += '\f';break;
											default:
											{
												error(errmsg.clear() << source << ": l" << lineIndex << ": invalid escape sequence at " << offsetutf8);
												return false;
											}
										}
										hasBackslash = false;
									}
									else
									{
										newsubrules.back().text.append(*ci);
									}
								}
							}
							break;
						}

						case stInCharList:
						{
							// in a list of chars
							switch (c)
							{
								case '[':
								{
									if (hasBackslash)
										hasBackslash = false;
									else
										++bracketDepth;

									newsubrules.back().text += '[';
									break;
								}
								case ']':
								{
									if (hasBackslash)
									{
										newsubrules.back().text += ']';
										hasBackslash = false;
									}
									else
									{
										if (--bracketDepth == 0)
										{
											if (not newsubrules.back().empty())
											{
												newsubrules.push_back(nullptr);
											}
											else
												warns(errmsg.clear() << source << ": l" << lineIndex << ": empty list of chars at " << instringStartUtf8);

											state = stDefault;
										}
										else
										newsubrules.back().text += ']';
									}
									break;
								}
								case '\\':
								{
									if (hasBackslash)
									{
										newsubrules.back().text += '\\';
										hasBackslash = false;
									}
									else
										hasBackslash = true;
									break;
								}
								default:
								{
									if (hasBackslash)
									{
										switch (c)
										{
											case '\\': newsubrules.back().text += '\\';break;
											case 't': newsubrules.back().text += '\t';break;
											case 'n': newsubrules.back().text += '\n';break;
											case 'r': newsubrules.back().text += '\r';break;
											case 'v': newsubrules.back().text += '\v';break;
											case 'f': newsubrules.back().text += '\f';break;
											default:
											{
												error(errmsg.clear() << source << ": l" << lineIndex << ": invalid escape sequence at " << offsetutf8);
												return false;
											}
										}
										hasBackslash = false;
									}
									else
									{
										newsubrules.back().text.append(*ci);
									}
								}
							}

							break;
						}

					} // switch state

				} // each utf8 char

				switch (state)
				{
					case stInString:
					{
						error(errmsg.clear() << source << ": l" << lineIndex << ": unfinished string at offset " << instringStartUtf8);
						return false;
					}
					case stInCharList:
					{
						error(errmsg.clear() << source << ": l" << lineIndex << ": unfinished list of char at offset " << instringStartUtf8);
						return false;
					}
					default: // ignored
					{
					}
				}
			} // each subrule

			// remove the empty last item
			if (newsubrules.back().empty())
				newsubrules.pop_back();

			for (uint i = 0; i != newsubrules.size(); ++i)
			{
				std::cout << "  :: ";
				RuleTypeToString(std::cout, newsubrules[i].type);
				std::cout << " -> " << newsubrules[i].text << std::endl;
			}
		}

		return true;
	}




} // anonymous namespace






	Grammar::Grammar()
	{
	}


	Grammar::~Grammar()
	{
	}


	bool Grammar::loadFromFile(const AnyString& filename)
	{
		Clob content;
		if (IO::errNone != IO::File::LoadFromFile(content, filename))
			return false;

		// try to load the grammar file
		return loadFromData(content, filename);
	}


	bool Grammar::loadFromData(const AnyString& content, const AnyString& source)
	{
		RuleParser parser(*this);
		parser.source  = source;
		parser.content = content;
		return parser.analyze();
	}





} // namespace PEG
} // namespace Parser
} // namespace Yuni
