#ifndef __YUNI_GFX_UI_UPDATER_H__
# define __YUNI_GFX_UI_UPDATER_H__


namespace Yuni
{
namespace Gfx
{
namespace UI
{


	class Updater
	{
	public:
		template<class C> Updater(const SharedPtr<C>& comObj)
			:pComObj(comObj.get())
		{
			pComObj->beginUpdate();
		}

		Updater(Component* comObj)
			:pComObj(comObj)
		{
			pComObj->beginUpdate();
		}

		Updater(const Updater& c)
			:pComObj(c.pComObj)
		{
			pComObj->beginUpdate();
		}


		~Updater() {pComObj->endUpdate();}

	private:
		Component* pComObj;
	};



} // namespace UI
} // namespace Gfx
} // namespace Yuni



#endif // __YUNI_GFX_UI_UPDATER_H__
