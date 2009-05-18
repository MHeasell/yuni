#include <yuni/yuni.h>
#include <yuni/gfx/core/color/rgba.h>


using namespace Yuni;

int main(void)
{
	// Only two types should be used : uint8 and float. The other ones are not recommended

	// Standards colors when using an uint8.
	// The limits are : 0..255 (`0` means 0%, `255` means 100%).
	Gfx::Color::RGBA<uint8> b_red(   255, 0,   0,   255); // By default, a color is opaque
	Gfx::Color::RGBA<uint8> b_green( 0,   255, 0);
	Gfx::Color::RGBA<uint8> b_blue(  0,   0,   255, 255);

	// The same colors when using a float (OpenGL uses float for the colors)
	// The limits are : 0..1 (`0.0f` means 0%, `1.0f` means 100%)
	Gfx::Color::RGBA<float> f_red(   1.0f,  0.0f, 0.0f, 1.0f); // By default, a color is opaque
	Gfx::Color::RGBA<float> f_green( 0.0f,  1.0f, 0.0f);
	Gfx::Color::RGBA<float> f_blue(  0.0f,  0.0f, 1.0f, 1.0f);

	// A color completely transparent
	Gfx::Color::RGBA<float> f_transparent(0.3f, 0.72f, 0.2345f, 0.3f);
	std::cout << "Transparent : " << f_transparent << std::endl;

	// Convertions
	Gfx::Color::RGBA<float> f_convert (Gfx::Color::RGBA<uint8>(242, 24, 183, 255));
	std::cout << "Convert 1 : " << f_convert << std::endl;

	Gfx::Color::RGBA<uint8> f_convert2 (Gfx::Color::RGBA<float>(0.1f, 0.9f, 0.24f, 0.3f));
	std::cout << "Convert 2 : " << f_convert2 << std::endl;
	Gfx::Color::RGBA<uint8> f_convert3 (Gfx::Color::RGBA<float>(0.1f, 0.9f, 0.24f, 0.3f));
	std::cout << "Convert 3 : " << f_convert3.toString() << std::endl;

	// Compare 2 color models
	std::cout << (f_red == f_green) << std::endl;
	std::cout << (f_convert2 == f_convert) << std::endl;

	return 0;
}
