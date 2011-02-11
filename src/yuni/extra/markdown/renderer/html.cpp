
#include "html.h"


namespace Yuni
{
namespace Markdown
{
namespace Renderer
{

	void Html::resetDefaultValues()
	{
		// reset all
		for (unsigned int t = 0; t != static_cast<unsigned int>(Node::maxType); ++t)
		{
			for (unsigned int p = 0; p != static_cast<unsigned int>(partCount); ++p)
				composition[t][p].clear();
		}

		// Document
		composition[Node::document][partBegin]
			<< "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
			<< "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">\n"
			<< "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"fr\" lang=\"fr\">\n";
		composition[Node::document][partEnd] = "</html>\n";

		composition[Node::body][partBegin] = "<body>\n\n\n";
		composition[Node::body][partEnd] = "\n\n\n\n</body>\n";


		// Paragraph
		composition[Node::paragraph][partBegin] = "<p>\n";
		composition[Node::paragraph][partEnd] = "</p>\n";
		// Quote
		composition[Node::quote][partBegin] = "<quote>\n";
		composition[Node::quote][partNewLine] = '\t';
		composition[Node::quote][partEnd] = "</quote>\n";

		composition[Node::header1][partBegin] = "<h1>";
		composition[Node::header1][partEnd]   = "</h1>\n";
		composition[Node::header2][partBegin] = "<h2>";
		composition[Node::header2][partEnd]   = "</h2>\n";
		composition[Node::header3][partBegin] = "<h3>";
		composition[Node::header3][partEnd]   = "</h3>\n";
		composition[Node::header4][partBegin] = "<h4>";
		composition[Node::header4][partEnd]   = "</h4>\n";
		composition[Node::header5][partBegin] = "<h5>";
		composition[Node::header5][partEnd]   = "</h5>\n";
		composition[Node::header6][partBegin] = "<h6>";
		composition[Node::header6][partEnd]   = "</h6>\n";

		// Bold
		composition[Node::bold][partBegin]   = "<strong>";
		composition[Node::bold][partEnd]   = "</strong>";

		composition[Node::unorderedList][partBegin]   = "<ul>\n";
		composition[Node::unorderedList][partNewLine] = '\t';
		composition[Node::unorderedList][partEnd]     = "</ul>\n";
		composition[Node::orderedList][partBegin]   = "<ol>\n";
		composition[Node::orderedList][partNewLine] = '\t';
		composition[Node::orderedList][partEnd]     = "</ol>\n";
		composition[Node::listItem][partBegin]   = "<li>\n";
		composition[Node::listItem][partNewLine] = '\t';
		composition[Node::listItem][partEnd]     = "</li>\n";

		// Line break
		composition[Node::linebreak][partBegin]     = "\n<br />";
	}




} // namespace Renderer
} // namespace Markdown
} // namespace Yuni

