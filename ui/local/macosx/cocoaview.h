#ifndef __YUNI_PRIVATE_UI_LOCAL_MACOSX_COCOAVIEW_H__
# define __YUNI_PRIVATE_UI_LOCAL_MACOSX_COCOAVIEW_H__

# include "../osxwindow.h"
# include <Cocoa/Cocoa.h>

namespace Yuni
{
namespace Private
{
namespace UI
{
namespace Local
{
namespace MacOSX
{

@interface CocoaView : NSView
{
	OSXWindow* pWindow;
	bool pAppInitialized = false;
}

- (id)initWithGLOSXWindow:(OSXWindow*)w;

- (OSXWindow*)window;

- (void)setFrameSize:(NSSize)s;

@end

} // namespace MacOSX
} // namespace Local
} // namespace UI
} // namespace Private
} // namespace Yuni

#endif // !__YUNI_PRIVATE_UI_LOCAL_MACOSX_COCOAVIEW_H__
