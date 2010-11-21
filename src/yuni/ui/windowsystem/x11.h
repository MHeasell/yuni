#ifndef __YUNI_UI_WINDOWSYSTEM_X11_H__
# define __YUNI_UI_WINDOWSYSTEM_X11_H__

# include "../../yuni.h"
# include "../queueservice.h"

namespace Yuni
{
namespace UI
{
namespace WindowSystem
{

	/*!
	** \brief X11 implementation for a window system main loop
	*/
	class X11: public IQueueService<X11>
	{
	public:
		//! Static override for onLoop, called on each loop turn
		bool onLoop();

		//! Show a window asynchronously
		bool showWindowDispatched(ShowWindowParams::Ptr& params);
	};



} // namespace WindowSystem
} // namespace UI
} // namespace Yuni


#endif // __YUNI_UI_WINDOWSYSTEM_X11_H__
