#ifndef __YUNI_GFX_UI_DESKTOP_H__
# define __YUNI_GFX_UI_DESKTOP_H__

# include "../../yuni.h"
# include "../../core/smartptr.h"
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
		/*!
		** \brief Main constructor
		*/
		Desktop() {}

	private:
		Application::Map pApps;

	}; // class Desktop

} // namespace UI
} // namespace Yuni

#endif // __YUNI_GFX_UI_DESKTOP_H__
