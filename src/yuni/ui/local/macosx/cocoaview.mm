#include "cocoaview.h"

@implementation CocoaView

- (id)initWithGLOSXWindow:(OSXWindow*)w
{
	if ((self = [super initWithFrame:NSMakeRect(0, 0, w->getWidth(), w->getHeight())]))
	{
		if (!pAppInitialized)
		{
			NSApplicationLoad();
			pAppInitialized = true;
		}
		pWindow = w;
	}
	return self;
}

- (OSXWindow*)window
{
	return pWindow;
}

- (void)setFrameSize:(NSSize)s
{
	[super setFrameSize:s];
	if (pWindow)
		pWindow->windowMovedOrResized();
}

- (void)refresh:(NSRect)r
{
	if (pWindow)
		pWindow->update();
}

- (bool)initialize
{
	return true;
}

		virtual void resize(float width, float height);

- (void)close
{
	pWindow = 0;
}

- (bool)pollEvents
{
}

@end
