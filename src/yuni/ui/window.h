#ifndef __YUNI_GFX_UI_WINDOW_H__
# define __YUNI_GFX_UI_WINDOW_H__

# include "../yuni.h"
# include "../toolbox/smartptr/sharedptr.h"
# include "../toolbox/string.h"



namespace Yuni
{
namespace Gfx
{
namespace UI
{


	/*!
	** \brief
	** \ingroup ui
	*/
	class Window : public Control
	{
	public:
		//! \name Constructor & Destructor
		//@{

		/*!
		** \brief Constructor
		*/
		Window(const SharedPtr<Control>& prnt);

		//! Destructor
		~Window();

		//@}

		//! \name Type
		//@{
		//! Get the string representation of the type of component
		virtual String type() const {return "Window";}
		//@}


		//! \name Caption
		//@{
		//! Get the caption of the window
		String caption();
		//! Set the caption of the window
		void caption(const String& c);
		//@}
	

	protected:
		virtual bool onBeforeDestructionWL();

	protected:
		//! Caption of the window
		String pCaption;

	}; // class Window




} // namespace UI
} // namespace Gfx
} // namespace Yuni


#endif // __YUNI_GFX_UI_WINDOW_H__
