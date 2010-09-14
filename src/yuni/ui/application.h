#ifndef __YUNI_UI_APPLICATION_H__
# define __YUNI_UI_APPLICATION_H__

# include "../yuni.h"
# include "../core/smartptr.h"
# include "../core/string.h"
# include "window.h"

namespace Yuni
{
namespace UI
{


	/*!
	** \brief Virtual application. Can contain one or several windows.
	*/
	class Application
	{
	public:
		//! Smart pointer
		typedef SmartPtr<Application> Ptr;

		//! String identifier type
		typedef CustomString<40, false, false> StaticString;

		//! Map from a unique ID
		typedef std::map<StaticString, Application::Ptr> Map;


	public:
		/*!
		** \brief Constructor
		*/
		template<typename StringT, typename StringT2>
		Application(const StringT& id, const StringT2& name): pID(id), pName(name)
		{}


		/*!
		** \brief Get the identifier for this application
		*/
		const StaticString& ID() { return pID; }

		/*!
		** \brief Get the name of this application
		*/
		const StaticString& Name() { return pName; }


	private:
		//! Application string identifier
		StaticString pID;

		//! Application name, used for display
		StaticString pName;

		//! Application windows
		Window::Vector pWindows;

	}; // class Application



} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_APPLICATION_H__
