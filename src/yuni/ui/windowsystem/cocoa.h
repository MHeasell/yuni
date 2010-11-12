#ifndef __YUNI_UI_WINDOWSYSTEM_COCOA_H__
# define __YUNI_UI_WINDOWSYSTEM_COCOA_H__

# include "../../yuni.h"
# include "../queueservice.h"

namespace Yuni
{
namespace UI
{
namespace WindowSystem
{

	/*!
	** \brief Mac OS X Cocoa implementation for a window system main loop
	*/
	class Cocoa: public IQueueService<Cocoa>
	{
	public:
		//! Static override for onLoop, called on each loop turn
		bool onLoop() { return true; }
	};



} // namespace WindowSystem
} // namespace UI
} // namespace Yuni


#endif // __YUNI_UI_WINDOWSYSTEM_COCOA_H__
