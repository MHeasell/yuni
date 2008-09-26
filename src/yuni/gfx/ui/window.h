#ifndef __YUNI_GFX_UI_WINDOW_H__
# define __YUNI_GFX_UI_WINDOW_H__

# include "../../yuni.h"
# include "../../sharedptr.h"
# include "../../string.h"



namespace Yuni
{
namespace Gfx
{
namespace UI
{


	class Window : public Control
	{
	public:
		//! \name Constructor & Destructor
		//@{

		/*!
		** \brief Constructor
		*/
		Window(const SharedPtr<Window>& prnt);

		//! Destructor
		~Window();

		//@}

		//! \name Caption
		//@{
		//! Get the caption of the window
		String caption();
		//! Set the caption of the window
		void caption(const String& c);
		//@}
	
		//! \name Z-Order
		//@{
		virtual void sendToBack();
		virtual void bringToFront();
		//@}

	protected:
		//! Caption of the window
		String pCaption;

	private:
		mutable void resetGroupParent(WindowsGroup* g);

	}; // class Window




} // namespace UI
} // namespace Gfx
} // namespace Yuni


#endif // __YUNI_GFX_UI_WINDOW_H__
