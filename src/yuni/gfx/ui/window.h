#ifndef __YUNI_USER_INTERFACE_FORM_H__
# define __YUNI_USER_INTERFACE_FORM_H__

# include <yuni/yuni.h>
# include <yuni/gfx/point2d.h>
# include <vector>
# include <yuni/gfx/ui/component.h>
# include <yuni/hash/dictionary.h>
# include <yuni/misc/sharedptr.h>



namespace Yuni
{
namespace Gfx
{
namespace UI
{

	class Component;



	/*!
	** \brief Window
	*/
	class Window
	{
		friend class Component;
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
		String title();
		void title(const String& s);

		String name(); 
		void name(const String& s);

		//! \name Components
		//@{

		/*!
		** \brief Delete all components
		*/
		void clear();

		/*!
		** \brief Remove a component and all its children
		**
		** \param comName Name of the component
		*/
		void remove(const String& comName);
		/*!
		** \brief Remove a component and all its children
		** 
		** As the pointer is managed by a ref counter, the component will be really
		** destroyed when all references are released, in the best case
		** at the end of the call to this method. However, after the call to
		** this method, the component must be considered as destroyed.

		** \param c Reference to the 
		*/
		void remove(SharedPtr<Component> c);

		/*!
		** \brief Find a component by its name
		**
		** \param comName Name of the component
		** \return A shared pointer to the component, the pointer may be null if not found
		*/
		ShredPtr<Component> find(const String& comName);

		/*!
		** \brief Find a component by its pointer
		**
		** \param comPtr Pointer of the component
		** \return A shared pointer to the component, the pointer may be null if not found
		*/
		ShredPtr<Component> find(Component* comPtr);

		//@}
		
	private:
		//! Table of all components indexed by their name
		typedef Hash::Dictionary< SharedPtr<Component>, Hash::optIgnoreCase>  ComponentsByName;

	private:
		/*!
		** \brief Register a component to the list of all components (thread-safe)
		** \param c The component to register
		*/
		void internalRegisterComponent(Component* c);

		/*!
		** \brief Register a component by its name (thread-safe)
		**
		** This routine must be used with the method `internalRegisterComponent()`
		** and they are complementary
		**
		** \param c Pointer to the component. Nothing will be done if equals to null
		** \param prevName The previous name of the component
		** \param newName The new name of the component
		**
		** \see internalRegisterComponent()
		*/
		void internalReRegisterComName(Component* c, const String& prevName, const String& newName);

		/*!
		** \brief Find a component by its pointer (not thread-safe)
		**
		** \param comPtr Pointer of the component
		** \return A shared pointer to the component, the pointer may be null if not found
		*/
		ShredPtr<Component> internalFindComponent(Component* comPtr);

		/*!
		** \brief Find a component by its name (not thread-safe)
		**
		** \param comName Name of the component
		** \return A shared pointer to the component, the pointer may be null if not found
		*/
		ShredPtr<Component> internalFindComponent(const String& comName);

		/*!
		** \brief Remove a component by its pointer (not thread-safe)
		**
		** As the pointer is managed by a ref counter, the component will be really
		** destroyed when all references are released, in the best case
		** at the end of the call to this method. However, after the call to
		** this method, the component must be considered as destroyed.
		**
		** \param c Reference to the component
		*/
		void internalRemove(SharedPtr<Component>& c);



	private:
		//! Mutex
		Mutex pMutex;
		//! Title of the window
		String pTitle;
		//! Name of the window
		String pName;

		//! All components
		Component::List pAllComponents;
		//! All references to components that have a non-empty name
		ComponentsByName pRefComponents;

	}; // class Window



} // namespace UI
} // namespace Gfx
} // namespace Yuni


#endif // __YUNI_USER_INTERFACE_FORM_H__
