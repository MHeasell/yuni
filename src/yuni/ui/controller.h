#ifndef __YUNI_GFX_UI_CONTROLLER_H__
# define __YUNI_GFX_UI_CONTROLLER_H__

# include "../yuni.h"
# include "../toolbox/smartptr/sharedptr.h"
# include "../toolbox/string.h"
# include "../threads/mutex.h"
# include "component.h"
# include "control.h"
# include "window.h"


namespace Yuni
{
namespace Gfx
{
namespace UI
{


	class Controller
	{
	public:
		static Controller* Instance();

	private:
		Controller();
		~Controller();

		void clearAllUIControls();

		SharedPtr<Window> createNewWindow();

	private:
		class Root : public Control
		{
		public:
			Root() : Control() {}
			virtual ~Root() {}
			virtual String type() const {return "root";}
		}; // class Root

	private:
		Mutex pMutex;
		SharedPtr<Root> pRoot;

	}; // class Controller


} // namespace UI
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_UI_CONTROLLER_H__
