
namespace Yuni
{
namespace Gfx
{
namespace Window
{


	inline bool CairoMSW::refresh() { return true; }

	inline void CairoMSW::blitWL() { cairo_paint(pContext); }



} // namespace Window
} // namespace Gfx
} // namespace Yuni
