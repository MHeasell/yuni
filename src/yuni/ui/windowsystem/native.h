#ifndef __YUNI_UI_WINDOWSYSTEM_NATIVE_H__
# define __YUNI_UI_WINDOWSYSTEM_NATIVE_H__


namespace Yuni
{
namespace UI
{
namespace WindowSystem
{


# ifdef YUNI_OS_MAC
	typedef Cocoa Native;
# else
#	ifdef YUNI_OS_WINDOWS
	typedef Windows Native;
#	else
#		ifdef YUNI_OS_UNIX
	typedef X11 Native;
#		else
#			error No window system available for your platform !
#		endif // YUNI_OS_UNIX
#	endif // YUNI_OS_WINDOWS
# endif // YUNI_OS_MAC


} // namespace WindowSystem
} // namespace UI
} // namespace Yuni


#endif // __YUNI_UI_WINDOWSYSTEM_NATIVE_H__
