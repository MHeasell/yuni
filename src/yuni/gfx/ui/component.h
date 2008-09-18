#ifndef __YUNI_GFX_UI_COMPONENTS_H__
# define __YUNI_GFX_UI_COMPONENTS_H__

# include "../../yuni.h"
# include "../../string.h"
# include "../../threads/mutex.h"
# include "../../misc/sharedptr.h"
# include <list>
# include <vector>
# include "../../misc/event.h"


namespace Yuni
{
namespace Gfx
{
namespace UI
{


	/*!
	** \brief Base class for any UI component
	*/
	class Component : public Event::Receiver
	{
	public:
		//! State of the component
		enum State
		{
			//! The component is loading its data (constructor)
			csLoading = 0,
			//! The component is ready to perform operations
			csReady,
			//! The component is currently updating
			csUpdating,
			//! The component is no longer valid
			csDestroying
		};

		//! Vector of components
		typedef std::vector< SharedPtr<Component> >  Vector;
		//! List of components
		typedef std::list< SharedPtr<Component> >  List;

	public:
		//! \name Constructors & Destructor
		//@{

		/*!
		** \brief Constructor
		**
		** \param prnt Parent for this component
		*/
		template<class C>
		Component(const SharedPtr<C>& prnt)
			:Event::Receiver(), pState(csLoading), pParent(), pName()
		{
			if (prnt.valid())
			{
				if (dynamic_cast<Component*>(prnt.get()))
				{
					SharedPtr<Component> transform(dynamic_cast<Component*>(prnt.get()));
					parent(transform);
				}
			}
			pState = csReady;
		}

		//! Destructor
		virtual ~Component();

		//@}

		//! \name State
		//@{

		//! Get the state of the component
		State state();

		//! Get if the component is valid
		virtual bool valid();

		/*!
		** \brief Indicates that the component will be destroyed and it should not be longer considered
		** as valid
		*/
		void destroying();

		//@}

		//! \name Type
		//@{
		//! Get the string representation of the type of component
		virtual const String& type() const = 0; 
		//@}

		//! \name Parent
		//@{

		/*!
		** \brief Parent of this component
		*/
		SharedPtr<Component> parent() {return pParent;}

		/*!
		** \brief Assign a new parent
		*/
		bool parent(const SharedPtr<Component>& newParent);

		/*!
		** \brief Detach the component from its parent
		**
		** As this component will no longer belong to any another component, it won't be
		** drawn if it is a visual component. It would be like if the component would not exist.
		*/
		void detachFromParent();

		//@}

		//! \name Name
		//@{
		//! Get the name of the component
		String name();
		//! Set the name of the component
		void name(const String& n);
		//@}


		//! \name Children
		//@{

		/*!
		** \brief Delete all children
		*/
		void clear();

		//! Get the count of children
		uint32 childrenCount();

		/*!
		** \brief Get a child according its index
		**
		** it is safe to use a out of bounds value. The result will not be valid, that's all.
		**
		** \return A reference to the component, null if it does not exist
		*/
		SharedPtr<Component> child(const uint32 indx);
		/*!
		** \brief Try to find a child according its pointer address
		**
		** \param[in,out] out The component if found, unchanged otherwise
		** \param toFind The pointer to find
		** \param recursive True to Iterate all sub-children
		** \return True if the component was found, false otherwise
		*/
		bool findChildFromPtr(SharedPtr<Component>& out, const void* toFind, const bool recursive = true);

		/*!
		** \brief Try to find a child according its pointer address
		**
		** In this case, we don't really care of the component itself. We are only interrested in
		** if it exists or not.
		**
		** \param toFind The pointer to find
		** \param recursive True to Iterate all sub-children
		** \return True if the component was found, false otherwise
		*/
		bool existsChildFromPtr(const void* toFind, const bool recursive = true);

		/*!
		** \brief Try to find a child according its name
		**
		** \param[in,out] out The component if found, unchanged otherwise
		** \param toFind The pointer to find
		** \param recursive True to Iterate all sub-children
		** \return True if the component was found, false otherwise
		*/
		bool findChildFromName(SharedPtr<Component>& out, const String& toFind, const bool recursive = true);

		//@}


		//! \name Operators
		//@{

		//! Get a child component from its index (null if not found)
		SharedPtr<Component> operator [] (const uint32 indx) {return child(indx);}
		//! Get a child component from its name (null if not foud)
		SharedPtr<Component> operator [] (const String& nm);

		//@}

		//! \name Updates
		//@{

		void beginUpdate();

		void endUpdate();

		//@}
	protected:
		/*!
		** \brief Event: Called before the component is really destroyed
		** 
		** \return True to continue to broadcast the event to derived classes
		*/
		virtual bool onBeforeDestruction();

		/*!
		** \brief Broadcast the event onBeforeDestruction to all children (not thread safe)
		*/
		void broadcastOnBeforeDestruction();

		/*!
		** \brief Try to find a child according its pointer address (not thread-safe)
		**
		** \param[in,out] out The component if found, unchanged otherwise
		** \param toFind The pointer to find
		** \param recursive True to Iterate all sub-children
		** \return True if the component was found, false otherwise
		*/
		bool internalFindChildFromPtr(SharedPtr<Component>& out, const void* toFind, const bool recursive);
		/*!
		** \brief Try to find a child according its pointer address (not thread-safe)
		**
		** In this case, we don't really care of the component itself. We are only interrested in
		** if it exists or not.
		**
		** \param toFind The pointer to find
		** \param recursive True to Iterate all sub-children
		** \return True if the component was found, false otherwise
		*/
		bool internalExistsChildFromPtr(const void* toFind, const bool recursive);

		/*!
		** \brief Try to find a child according its name (not thread-safe)
		**
		** \param[in,out] out The component if found, unchanged otherwise
		** \param toFind The pointer to find
		** \param recursive True to Iterate all sub-children
		** \return True if the component was found, false otherwise
		*/
		bool internalFindChildFromString(SharedPtr<Component>& out, const String& toFind, const bool recursive);

		/*!
		** \brief Detach the component from its parent (not thread-safe)
		**
		** As this component will no longer belong to any another component, it won't be
		** drawn if it is a visual component. It would be like if the component would not exist.
		*/
		void internalDetachFromParent();

	protected:
		//! State of the component
		State pState;

	private:
		/*!
		** \brief Add a new child in the list
		** \param nc The new child
		*/
		void internalRegisterChild(Component* nc);
		/*!
		** \brief Add a new child in the list
		** \param nc The new child
		*/
		void internalRegisterChild(const SharedPtr<Component>& nc);
		/*!
		** \brief Remove a child from the list according its pointer address
		** \param nc Child to remove
		*/
		void internalUnregisterChild(Component* nc);

	private:
		//! Parent of this component
		SharedPtr<Component> pParent;
		//! Name of this component
		String pName;
		//! All children
		Component::Vector pChildren;

	}; // class Component




} // namespace UI
} // namespace Gfx
} // namespace Yuni



# include "updater.h"

#endif // __YUNI_GFX_UI_COMPONENTS_H__
