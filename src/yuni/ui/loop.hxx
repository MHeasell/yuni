#ifndef __YUNI_UI_LOOP_HXX__
# define __YUNI_UI_LOOP_HXX__

namespace Yuni
{
namespace UI
{


	inline Loop::Loop()
	{
		device = new Gfx::Device();
	}


	inline Loop::~Loop()
	{
		// Call stop, running it twice is properly managed
		// and you can never be sure it has been done properly.
		stop();
	}



} // namespace UI
} // namespace Yuni

#endif // __YUNI_UI_LOOP_HXX__
