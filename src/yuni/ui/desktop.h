#ifndef __YUNI_UI_DESKTOP_H__
# define __YUNI_UI_DESKTOP_H__

# include "../yuni.h"
# include "../core/smartptr.h"
# include "fwd.h"
# include "application.h"


namespace Yuni
{
namespace UI
{


	/*!
	** \brief Virtual desktop meant to receive one or several applications
	*/
	class Desktop
	{
	public:
		//! Smart pointer
		typedef SmartPtr<Desktop> Ptr;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		Desktop();
		//! Destructor
		~Desktop();
		//@}


		//! \name Applications
		//@{
		/*!
		** \brief Add an application to this desktop
		*/
		void add(const Application::Ptr& app);

		/*!
		** \brief
		*/
		template<typename StringT> void remove(const StringT& id);
		//!
		void remove(const Application::Ptr& app);
		//@}

		//! Update a component's local representation
		void updateComponentWL(const IComponent::ID& componentID) const;

		/*!
		** \brief Quit the desktop and all its applications
		*/
		void quit();


		//! \name Operators
		//@{
		//! Register a new application
		//! \see add()
		Desktop& operator += (const Application::Ptr& app);
		//! Register a new application
		//! \see add()
		Desktop& operator << (const Application::Ptr& app);

		//! Remove an application from its guid
		//! \see remove()
		template<typename StringT> Desktop& operator -= (const StringT& id);
		//! Remove an application from its pointer
		//! \see remove()
		Desktop& operator -= (const Application::Ptr& app);
		//@}

	private:
		Application::Map pApps;

	}; // class Desktop



} // namespace UI
} // namespace Yuni

# include "queueservice.h"
# include "desktop.hxx"

#endif // __YUNI_UI_DESKTOP_H__
