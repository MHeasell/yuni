#ifndef __YUNI_UI_WINDOWSYSTEM_WINDOWS_H__
# define __YUNI_UI_WINDOWSYSTEM_WINDOWS_H__

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
	};



} // namespace WindowSystem
} // namespace UI
} // namespace Yuni


#endif // __YUNI_UI_WINDOWSYSTEM_WINDOWS_H__
