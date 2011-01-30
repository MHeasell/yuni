#ifndef __YUNI_EXTRA_MARKDOWN_DATA_H__
# define __YUNI_EXTRA_MARKDOWN_DATA_H__

# include "../../yuni.h"
# include "../../core/string.h"
# include "signature.h"
# include "fwd.h"


namespace Yuni
{
namespace Private
{
namespace Markdown
{

	class ReaderData
	{
	public:
		//! Node
		typedef Yuni::Markdown::Node  Node;

		enum
		{
			defaultLinePosition = 1,
			defaultColumnPosition = 0,
			debug = Yuni::Markdown::markdownDebug,
			stackLimit = Yuni::Markdown::stackLimit,
		};

	public:
		ReaderData()
		{}

		~ReaderData()
		{}


		void reset();


		void parse(const StringAdapter& text);


		void flush();


	public:
		unsigned int column;
		unsigned int line;
		String filename;

	private:
		void parseLine();
		unsigned int signatureForTheCurrentLine();
		bool executePragma();
		void updateStack();

	private:
		CustomString<4096> pLine;
		bool pHasLineBreak;
		unsigned int pQuoteLevel;
		Signature pCurrentLineSignature;
		Signature pLastSignature;
		unsigned int pStackSize;
		Node::Ptr  pStack[stackLimit];

	}; // ReaderData





} // namespace Markdown
} // namespace Private
} // namespace Yuni

#endif // __YUNI_EXTRA_MARKDOWN_DATA_H__
