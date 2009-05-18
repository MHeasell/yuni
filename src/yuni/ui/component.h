#ifndef __YUNI_GFX_UI_COMPONENTS_H__
# define __YUNI_GFX_UI_COMPONENTS_H__

# include <list>
# include <vector>
# include "../yuni.h"
# include "../core/policies/threading.h"
# include "../core/string.h"
# include "../core/smartptr/sharedptr.h"
# include "../core/event/event.h"



namespace Yuni
{
namespace Gfx
{
namespace UI
{

	// Foraward declaration
	class Control;




	/*!
	** \brief Base class for any UI component
	** \ingroup ui
	*/
	class AComponent : public Event::Observer<AComponent, Policy::ObjectLevelLockable>
	{
		friend class Control;
	public:
		//! State of the component
		//! \ingroup ui
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

	public:
		//! \name Constructors & Destructor
		//@{

		/*!
		** \brief Constructor
		*/
		AComponent();

		//! Destructor
		virtual ~AComponent();

		//@}

		//! \name State
		//@{

		//! Get the state of the component
		State state();

		//! Get if the component is ready to perform operations
		virtual bool ready();

		/*!
		** \brief Indicates that the component will be destroyed and it should not be longer considered
		** as valid
		**
		** \return False if the component already noticed that it will be deleted shortly
		*/
		bool destroying();

		//@}

		//! \name Type
		//@{
		//! Get the string representation of the type of component
		virtual String type() const = 0; 
		//@}

		//! \name Name
		//@{
		//! Get the name of the component
		String name();
		//! Set the name of the component
		void name(const String& n);
		//@}


	protected:
		/*!
		** \brief Event: Called before the component is really destroyed
		** 
		** \return True to continue to broadcast the event to derived classes
		*/
		virtual bool onBeforeDestructionWL();

	protected:
		//! State of the component
		State pState;

		//! Name of this component
		String pName;

	}; // class AComponent






} // namespace UI
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_UI_COMPONENTS_H__
