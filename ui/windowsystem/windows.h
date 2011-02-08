#ifndef __YUNI_UI_WINDOWSYSTEM_WINDOWS_H__
# define __YUNI_UI_WINDOWSYSTEM_WINDOWS_H__

# include "../../yuni.h"
# include "../queueservice.h"

namespace Yuni
{
namespace UI
{
namespace WindowSystem
{

	/*!
	** \brief Microsoft Windows implementation for a window system main loop
	*/
	class Windows: public IQueueService<Windows>
	{
	public:
		//! Static override for onLoop, called on each loop turn
		bool onLoop();

		//! Show a window asynchronously
		bool showWindowDispatched(ShowWindowParams::Ptr params);

		//! Close a window asynchronously
		bool closeWindowDispatched(ModifyWindowParams::Ptr params);

		//! Resize a window asynchronously
		bool resizeWindowDispatched(ResizeWindowParams::Ptr params);
	};



} // namespace WindowSystem
} // namespace UI
} // namespace Yuni


#endif // __YUNI_UI_WINDOWSYSTEM_WINDOWS_H__
