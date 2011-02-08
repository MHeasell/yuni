#ifndef __YUNI_UI_WINDOWSYSTEM_H__
# define __YUNI_UI_WINDOWSYSTEM_H__

# include "../yuni.h"
# include "windowsystem/cocoa.h"
# include "windowsystem/windows.h"
# include "windowsystem/x11.h"
// Include native last, it requires the rest since it aliases on them
# include "windowsystem/native.h"


#endif // __YUNI_UI_WINDOWSYSTEM_H__
