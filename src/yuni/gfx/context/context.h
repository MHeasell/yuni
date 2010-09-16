#ifndef __YUNI_GFX_CONTEXT_CONTEXT_H__
# define __YUNI_GFX_CONTEXT_CONTEXT_H__

# include "../window/window.h"
# include "../../ui/desktop.h"

namespace Yuni
{
namespace Gfx
{
namespace Context
{


	/*!
	** \brief Abstract context
	*/
	class Context
	{
	public:
		//! \name Constructors and destructors
		//@{
		//! Default empty constructor
		Context() {}

		//! Virtual destructor
		virtual ~Context() {}
		//@}

		//! \name Accessors
		//@{
		Desktop::Ptr desktop() const { return pDesktop; }
		void desktop(Desktop::Ptr& newDesktop) const { pDesktop = newDesktop; }
		//@}

	public:
		//! Desktop containing all UI
		Desktop::Ptr pDesktop;

		//! All windows
		IWindow::Map pWindows;
	};

} // namespace Context
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_CONTEXT_CONTEXT_H__
