#ifndef __YUNI_GFX_UI_CONTEXT_OPENGL3D_H__
# define __YUNI_GFX_UI_CONTEXT_OPENGL3D_H__

# include "../ui/desktop.h"

namespace Yuni
{
namespace UI
{
namespace Context
{


	/*!
	** \brief Abstract context
	*/
	class Context
	{
	public:
		//! Default empty constructor
		Context()
			: desktop(NULL)
		{}

		//! Virtual destructor
		virtual ~Context() {}

	public:
		Desktop::Ptr desktop;
	};

} // namespace Context
} // namespace UI
} // namespace Yuni

#endif // __YUNI_GFX_UI_CONTEXT_OPENGL3D_H__
