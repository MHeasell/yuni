
#include "data.h"
#include "node.h"
#include "fwd.h"
#include "../../core/math.h"


namespace Yuni
{
namespace Private
{
namespace Markdown
{


	void ReaderData::reset()
	{
		filename.clear();
		line   = defaultLinePosition;
		column = defaultColumnPosition;
		pQuoteLevel = 0;

		pLine.clear();
		if (pLine.capacity() > 4096)
			pLine.shrink();

		pLastSignature.clear();
		pStackSize = 1;
		// creating the root node
		pStack[0] = new Node(Node::document);
	}


	void ReaderData::parse(const StringAdapter& text)
	{
		// readline
		StringAdapter::Size offset = 0;
		do
		{
			const StringAdapter::Size p = text.find('\n', offset);
			if (p == StringAdapter::npos)
			{
				// The EOL has not been found, keeping the piece of string for later
				pLine.append(text, text.size() - offset, offset);
				return;
			}

			pLine.append(text, p - offset, offset);

			parseLine();

			// go to the next line
			++line;
			pLine.clear();
			offset = p + 1;
		}
		while (true);
	}


	void ReaderData::flush()
	{
		if (pLine.notEmpty())
			parseLine();

		// releasing the stack
		// (however the first node must not be released yet)
		for (unsigned int i = 1; i != stackLimit; ++i)
			pStack[i] = nullptr;

		// printing the root node
		pStack[0]->dump(std::cout);
	}


	void ReaderData::parseLine()
	{
		// removing any \r
		if (pLine.notEmpty() && pLine.last() == '\r')
			pLine.removeLast();

		// Trimming the right side
		// Determine in the same time if a line break is present (at least
		// two spaces)
		{
			const unsigned int oldSize = pLine.size();
			pLine.trimRight(" \t");
			pHasLineBreak = (pLine.size() + 3) > oldSize;
		}
	
		// Getting the signature of the current line
		// This signature will help us to build the parse tree
		// In the same time, the position of the first usefull character will be
		// retrieved (inner text)
		const unsigned int x = signatureForTheCurrentLine();

		// According the final type of node, we may have to add a paragraph node
		if (Node::ShouldAppendAParagraphNode(pCurrentLineSignature.lastType()))
			pCurrentLineSignature.add(Node::paragraph, pCurrentLineSignature.lastOffset());

		// The current line may refer to a pragma command
		// Try to find it and to execute it
		if (executePragma())
		{
			// A pragma command has been found. The current line must be ignored
			return;
		}

		// No pragma command. We can go on !
		if (debug)
		{
			CustomString<100,false> strline = line;
			strline << ", @=" << x << ' ';
			if (strline.size() < 20)
				strline.resize(20, '.');
			strline += ' ';
			std::cout << "[markdown:debug] " << filename << ":" << strline;
			pCurrentLineSignature.print(std::cout);
		}

		// Updating the stack accordingly (based on the current and the last signature)
		updateStack();

		// text
		{
			StringAdapter text;
			if (x < pLine.size())
				text.adapt(pLine.c_str() + x, pLine.size() - x);

			// asserts
			assert(pStackSize > 1);
			// alias to the last node in the stack
			const Node::Ptr& lastNode = pStack[pStackSize - 1];
			// alias to the text of the last available node
			String& nodeText = lastNode->innerText;

			if (!text)
			{
				// Empty line. We may have to start a new paragraph
				// (only if innerText is empty however - to reduce useless memory allocation)
				if (pCurrentLineSignature.lastType() == Node::paragraph && nodeText.notEmpty())
				{
					const Node::Ptr& beforeLastNode = pStack[pStackSize - 2];
					Node::Ptr newParagraph = new Node(Node::paragraph);
					*beforeLastNode += newParagraph;
					pStack[pStackSize - 1] = newParagraph;
				}
			}
			else
			{
				// adding the text to the last node within the stack
				nodeText += text;
			}
		}

		// We have done with the current line
		// Keeping some data for the next one
		pLastSignature = pCurrentLineSignature;
	}


	unsigned int ReaderData::signatureForTheCurrentLine()
	{
		// Signature for the current line
		Signature& signature = pCurrentLineSignature;
		signature.clear();

		// * > > *
		// **em**
		// * piko
		// *   sdfsdf
		// *   dsfsd
		for (unsigned int i = 0; i != pLine.size(); ++i)
		{
			const char c = pLine[i];
			switch (pLine[i])
			{
				case ' ':
					break;
				case '#':
					{
						unsigned int level = 1;
						unsigned int oldOffset = i;
						++i;
						while (pLine[i] == '#')
						{
							++i;
							++level;
						}
						if (level > 6)
							level = 6;
						static const Node::Type types[] =
						{
							Node::header1, // useless
							Node::header1,
							Node::header2,
							Node::header3,
							Node::header4,
							Node::header5,
							Node::header6,
						};
						signature.add(types[level], oldOffset);
						return i;
					}
				case '+':
				case '-':
				case '*':
					{
						if (signature.checkLast(Node::list, i - 1))
						{
							// can be **something**, or *** or --- or...
							if (pLine[i + 1] == c)
							{
								// found *** or --- or +++
								// maybe this is a fake horizontal line
								if (pLine[i + 2] != c)
								{
									signature.promote(Node::hzLine);
									return i + 2;
								}
							}
							// we previously got a bad token, something like **word**
							// reverting
							signature.pop();
							return i - 1;
						}
						signature.add(Node::list, i);
						break;
					}
				case '>':
					{
						signature.add(Node::quote, i);
						break;
					}
				case '_':
					{
						// can be **something**, or *** or --- or...
						if (pLine[i + 1] == '_' && pLine[i + 2] == '_' && pLine[i + 3] != '_')
						{
							signature.promote(Node::hzLine);
							return i + 3;
						}
						return i;
					}
				default:
					return i;
			}
		}
		return pLine.size();
	}



	bool ReaderData::executePragma()
	{
		// TODO implement pragma commands
		return false;
	}


	void ReaderData::updateStack()
	{
		// aliases to the signatures
		const Signature& old = pLastSignature;
		const Signature& cur = pCurrentLineSignature;
		if (old.size == 1 && cur.size == 1)
		{
			// nothing to do - empty
			return;
		}

		unsigned int oldI = 1; // starting from 1, the root node can be safely ignored
		unsigned int curI = 1;
		const unsigned int maxOffset = Math::Min<unsigned int>(old.size, cur.size);

		for (unsigned int i = 1; i < maxOffset; ++i)
		{
			if (cur.nodes[curI] == old.nodes[oldI] && cur.offsets[curI] == old.offsets[oldI])
			{
				// Oh ! Exactly the sames !
				++oldI;
				++curI;
				continue;
			}
			// Maybe we are still in the same block
		}

		// pop the stack
		if (oldI < old.size)
		{
			unsigned int newStackSize = pStackSize;
			for (unsigned int i = oldI; i < pStackSize; ++i)
			{
				// alias to the current node
				Node::Ptr& node = pStack[i];

				// decrease the pointer to the stacl
				--newStackSize;

				if (debug)
				{
					std::cout << "[markdown:debug]     - " << Node::TypeToCString(node->type)
						<< "   (stack size: " << newStackSize << ")\n";
				}
				// our algorithm may keep some unsed paragraph nodes
				if (node->type == Node::paragraph && !node->innerText)
					(node->parent())->remove(node);
			}
			pStackSize = oldI;
		}

		// creating the new nodes
		if (curI < cur.size)
		{
			assert(pStackSize > 0 && "The root node must exist");

			for (unsigned int i = curI; i < cur.size; ++i)
			{
				if (debug)
				{
					std::cout << "[markdown:debug]     + " << Node::TypeToCString(static_cast<Node::Type>(cur.nodes[i]))
						<< "   (stack size: " << pStackSize <<  ")\n";
				}

				// Creating the new node
				Node::Ptr node = new Node(static_cast<Node::Type>(cur.nodes[i]));
				// Adding as a new child of its parent
				*(pStack[pStackSize - 1]) += node;
				// adding it to the stack
				pStack[pStackSize] = node;
				++pStackSize;
			}
		}
	}





} // namespace Markdown
} // namespace Private
} // namespace Yuni


