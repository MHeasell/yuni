#ifndef __YUNI_GFX_UI_CONTROL_HXX__
# define __YUNI_GFX_UI_CONTROL_HXX__


namespace Yuni
{
namespace Gfx
{
namespace UI
{


	template<class C>
	Control::Control(const SharedPtr<C>& prnt)
		:Component(), pChildren(), pParent(), pPosition(), pSize(50, 50),
		pVisible(true), pEnabled(true),
		pIsInvalidate(true), pAutosize(false), pUpdateSessionRefCount(0)
	{
		anchors[Anchor::akLeft].pOwner = this;
		anchors[Anchor::akTop].pOwner = this;
		anchors[Anchor::akRight].pOwner = this;
		anchors[Anchor::akBottom].pOwner = this;
	}


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
