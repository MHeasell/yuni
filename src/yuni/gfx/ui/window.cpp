
# include <yuni/yuni.h>
# include <yuni/gfx/ui/window.h>



namespace Yuni
{
namespace Gfx
{
namespace UI
{

    Window::Window()
    {}

    Window::~Window()
    {}

    
    void Window::registerComponent(Component* comPtr)
    {
        if (comPtr && !(comPtr->name().empty()))
            pRefComponents[comPtr->name()] = comPtr;
    }

    void Window::unregisterComponent(const Component* comPtr)
    {
        if (comPtr && !(comPtr->name().empty()))
            pRefComponents.erase(comPtr->name());
    }
    
    Component* Window::findComponent(const String& comName)
    {
        return comName.empty() ? NULL : pRefComponents.value(comName, NULL);
    }
 

    void Window::name(const String& s)
    {
        pName = s;
    }

    void Window::title(const String& s)
    {
        pTitle = s;
    }


} // namespace UI
} // namespace Gfx
} // namespace Yuni


