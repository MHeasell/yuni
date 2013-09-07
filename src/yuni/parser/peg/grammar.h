#ifndef __YUNI_PARSER_GENERATOR_GRAMMAR_H__
# define __YUNI_PARSER_GENERATOR_GRAMMAR_H__

# include "../../yuni.h"
# include "../../core/string.h"
# include "../../core/noncopyable.h"
# include "../../core/event/event.h"
# include <map>


namespace Yuni
{
namespace Parser
{
namespace PEG
{

	enum RuleType
	{
		rtRule,
		rtGroup,
		rtModifier,
		rtString,
		rtListOfChars,
	};

	template<class StreamT> void RuleTypeToString(StreamT& out, RuleType type);


	class Grammar final : private NonCopyable<Grammar>
	{
	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		Grammar();
		//! Destructor
		~Grammar();
		//@}

		bool loadFromFile(const AnyString& filename);
		bool loadFromString(const AnyString& content);


	public:
		//! Event: warning
		Event<void (const AnyString&)> onWarning;
		//! Event: error
		Event<void (const AnyString&)> onError;

	private:
		bool loadFromData(const AnyString& content, const AnyString& source);

	}; // class Grammar




} // namespace PEG
} // namespace Parser
} // namespace Yuni

# include "grammar.hxx"

#endif // __YUNI_PARSER_GENERATOR_GRAMMAR_H__
