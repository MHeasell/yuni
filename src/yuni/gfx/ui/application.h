#ifndef __YUNI_GFX_UI_APPLICATION_H__
# define __YUNI_GFX_UI_APPLICATION_H__

# include "../../yuni.h"
# include "../../core/smartptr.h"
# include "../../core/string.h"
# include "application.h"

namespace Yuni
{
namespace UI
{

	/*!
	** \brief Virtual application. Can contain one or several windows
	*/
	class Application
	{
	public:
		//! Smart pointer
		typedef SmartPtr<Application> Ptr;

		//! Map from unique string ID
		typedef std::map<String, Application> Map;

	public:
		/*!
		** \brief Main constructor
		*/
		Application() {}

	}; // class Application

} // namespace UI
} // namespace Yuni

#endif // __YUNI_GFX_UI_APPLICATION_H__
