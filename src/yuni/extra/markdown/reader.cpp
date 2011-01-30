
#include "reader.h"
#include "data.h"
#include <cassert>


namespace Yuni
{
namespace Markdown
{

	Reader::Reader()
		:pDocumentStarted(false)
	{
		pData = new ReaderDataType();
	}


	Reader::~Reader()
	{
		delete pData;
	}


	const String& Reader::hintFilename() const
	{
		assert(pData != nullptr && "The internal state engine must be initialized at this point");
		return pData->filename;
	}


	void Reader::internalHintFilename(const StringAdapter& filename)
	{
		assert(pData != nullptr && "The internal state engine must be initialized at this point");
		String& s = pData->filename;

		s             = filename;
		pData->line   = ReaderDataType::defaultLinePosition;
		pData->column = ReaderDataType::defaultColumnPosition;
		// event
		onParseFilename(s);
	}


	void Reader::beginDocument()
	{
		if (pDocumentStarted)
			endDocument();

		pDocumentStarted = true;

		assert(pData != nullptr && "The internal state engine must be initialized at this point");
		pData->reset();

		// event
		onBeginDocument();
	}


	void Reader::endDocument()
	{
		if (pDocumentStarted)
		{
			// assert
			assert(pData != nullptr && "The internal state engine must be initialized at this point");

			// Flush any remaining buffer
			pData->flush();
			//
			pDocumentStarted = false;
			// event
			onEndDocument();
		}
	}


	void Reader::parse(const StringAdapter& text)
	{
		assert(pData != nullptr && "The internal state engine must be initialized at this point");

		// A document must be started
		if (!pDocumentStarted)
			beginDocument();
		// parse
		pData->parse(text);
	}





} // namespace Markdown
} // namespace Yuni

