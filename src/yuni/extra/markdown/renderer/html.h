#ifndef __YUNI_EXTRA_MARKDOWN_RENDERER_HTML_H__
# define __YUNI_EXTRA_MARKDOWN_RENDERER_HTML_H__

# include "../../../yuni.h"
# include "../node.h"
# include "../../../core/string.h"


namespace Yuni
{
namespace Markdown
{
namespace Renderer
{


	class Html
	{
	public:
		enum
		{
			partBegin = 0,
			partEnd,
			partNewLine,
			partCount
		};

	public:
		//! Reset all default values
		void resetDefaultValues();

		void render(const Node::Ptr& document);

	public:
		//! Tags composition
		String composition[Node::maxType][partCount];

	private:

	};


} // namespace Renderer
} // namespace Markdown
} // namespace Yuni

#endif // __YUNI_EXTRA_MARKDOWN_RENDERER_HTML_H__
