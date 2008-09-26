#ifndef __YUNI_GFX_UI_UPDATER_H__
# define __YUNI_GFX_UI_UPDATER_H__

# include "control.h"
# include "../../sharedptr.h"


namespace Yuni
{
namespace Gfx
{
namespace UI
{


	/*!
	** \brief Prevent a control from drawing during the lifespan of an instance of this class
	*/
	class Updater
	{
	public:
		//! \name Constructors & Destructor
		//@{

		/*!
		** \brief Constructor
		*/
		template<class C> Updater(const SharedPtr<C>& comObj)
			:pCntrl(comObj)
		{
			pCntrl->beginUpdate();
		}

		/*!
		** \brief Copy constructor
		*/
		Updater(const Updater& c)
			:pCntrl(c.pCntrl)
		{
			pCntrl->beginUpdate();
		}

		/*!
		** \brief Destructor
		*/
		~Updater() {pCntrl->endUpdate();}

		//@}

	private:
		//! Reference to the control
		SharedPtr<Control> pCntrl;

	}; // class Updater




} // namespace UI
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_UI_UPDATER_H__
