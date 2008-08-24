#ifndef __YUNI_USER_INTERFACE_FORM_H__
# define __YUNI_USER_INTERFACE_FORM_H__

# include <yuni/yuni.h>
# include <yuni/gfx/point2d.h>
# include <vector>
# include <yuni/gfx/ui/component.h>
# include <yuni/hash/dictionary.h>


namespace Yuni
{
namespace Gfx
{
namespace UI
{

    class Component;



    /*! \class Window
    **  \brief Window
    */
    class Window
    {
    public:
        //! \name Constructor & Destructor
        //@{
        //! Default constructor
        Window();
        //! Destructor
        ~Window();
        //@}

        /*!
        ** \brief Get the title of the window
        */
        const String& title() const {return pTitle;}
        void title(const String& s);

        const String& name() const {return pName;}
        void name(const String& s);

        //! \name Components
        //@{

        /*!
        ** \brief Find a component in the window
        **
        ** \param name Name of the component
        ** \return The component, NULL if not found
        */
        Component* findComponent(const String& comName);

        /*!
        ** \brief Register a component
        **
        ** The registration is used to have a direct link between
        ** the name of the component and the component itself
        **
        ** \param comPtr The component to register
        */
        void registerComponent(Component* comPtr);

        /*!
        ** \brief Unregister a component
        **
        ** \param comPtr The component to unregister
        */
        void unregisterComponent(const Component* comPtr);

        //@}
        
    private:
        //! Title of the window
        String pTitle;
        //! Name of the window
        String pName;
        //! All references to components that have a non-empty name
        Hash::Dictionary<Component*, Hash::optIgnoreCase> pRefComponents;

    }; // class Window



} // namespace UI
} // namespace Gfx
} // namespace Yuni


#endif // __YUNI_USER_INTERFACE_FORM_H__
