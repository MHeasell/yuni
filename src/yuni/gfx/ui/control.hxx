#ifndef __YUNI_GFX_UI_CONTROL_HXX__
# define __YUNI_GFX_UI_CONTROL_HXX__


namespace Yuni
{
namespace Gfx
{
namespace UI
{

	template<class C>
	void Control::Anchor::sibling(const SharedPtr<C>& s)
	{
		pOwner->pMutex.lock();
		pSibling = s;
		pOwner->invalidateWL();
		pOwner->pMutex.unlock();
	}


} // namespace UI
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_UI_CONTROL_HXX__
