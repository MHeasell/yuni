
namespace Yuni
{
namespace Gfx
{
namespace Window
{


	inline bool CairoX11::refresh() { return true; }

	inline void CairoX11::blitWL() { cairo_paint(pContext); }



} // namespace Window
} // namespace Gfx
} // namespace Yuni
