
#include "color.proxy.h"
#include "../toolbox/math.h"
#include "rgba.h"
#include "rgb.h"



namespace Yuni
{
namespace Private
{
namespace Gfx
{
namespace Color
{
namespace Proxy
{


	/*
	 * --- Streamer ---
	 */

	template<>
	std::ostream& Streamer< Yuni::Gfx::Color::RGBA<uint8> >::toOStream(std::ostream& out, const Yuni::Gfx::Color::RGBA<uint8>& th)
	{
		out << "r:" << (int)th.red << ",g:" << (int)th.green << ",b:" << (int)th.blue << ",a:" << (int)th.alpha;
		return out;
	}

	template<>
	std::ostream& Streamer< Yuni::Gfx::Color::RGB<uint8> >::toOStream(std::ostream& out, const Yuni::Gfx::Color::RGB<uint8>& th)
	{
		out << "r:" << (int)th.red << ",g:" << (int)th.green << ",b:" << (int)th.blue;
		return out;
	}

	template<>
	String Streamer< Yuni::Gfx::Color::RGBA<uint8> >::toString(const Yuni::Gfx::Color::RGBA<uint8>& th)
	{
		return String() << "r:" << (int)th.red << ",g:" << (int)th.green << ",b:" << (int)th.blue << ",a:" << (int)th.alpha;
	}

	template<>
	String Streamer< Yuni::Gfx::Color::RGB<uint8> >::toString(const Yuni::Gfx::Color::RGB<uint8>& th)
	{
		return String() << "r:" << (int)th.red << ",g:" << (int)th.green << ",b:" << (int)th.blue;
	}











	/*
	 * --- Assign ---
	 */

	template<>
	Yuni::Gfx::Color::RGBA<uint8>& Values< Yuni::Gfx::Color::RGBA<uint8>, uint8 >::Assign(Yuni::Gfx::Color::RGBA<uint8>& th, const uint8& a1, const uint8& a2, const uint8& a3, const uint8& a4)
	{
		th.red   = a1;
		th.green = a2;
		th.blue  = a3;
		th.alpha = a4;
		return th;
	}

	template<>
	Yuni::Gfx::Color::RGBA<uint8>& Values< Yuni::Gfx::Color::RGBA<uint8>, uint8 >::Assign(Yuni::Gfx::Color::RGBA<uint8>& th, const uint8& a1, const uint8& a2, const uint8& a3)
	{
		th.red   = a1;
		th.green = a2;
		th.blue  = a3;
		th.alpha = 255;
		return th;
	}


	template<>
	Yuni::Gfx::Color::RGBA<float>& Values< Yuni::Gfx::Color::RGBA<float>, float >::Assign(Yuni::Gfx::Color::RGBA<float>& th, const float& a1, const float& a2, const float& a3, const float& a4)
	{
		th.red   = Math::MinMax<float>(a1, 0.0f, 1.0f);
		th.green = Math::MinMax<float>(a2, 0.0f, 1.0f);
		th.blue  = Math::MinMax<float>(a3, 0.0f, 1.0f);
		th.alpha = Math::MinMax<float>(a4, 0.0f, 1.0f);
		return th;
	}

	template<>
	Yuni::Gfx::Color::RGBA<float>& Values< Yuni::Gfx::Color::RGBA<float>, float >::Assign(Yuni::Gfx::Color::RGBA<float>& th, const float& a1, const float& a2, const float& a3)
	{
		th.red   = Math::MinMax<float>(a1, 0.0f, 1.0f);
		th.green = Math::MinMax<float>(a2, 0.0f, 1.0f);
		th.blue  = Math::MinMax<float>(a3, 0.0f, 1.0f);
		th.alpha = 1.0f;
		return th;
	}


	template<>
	Yuni::Gfx::Color::RGBA<float>& Values< Yuni::Gfx::Color::RGBA<float>, uint8 >::Assign(Yuni::Gfx::Color::RGBA<float>& th, const uint8& r, const uint8& g, const uint8& b, const uint8& a)
	{
		th.red   = (float)r / 255.0f;
		th.green = (float)g / 255.0f;
		th.blue  = (float)b / 255.0f;
		th.alpha = (float)a / 255.0f;
		return th;
	}

	template<>
	Yuni::Gfx::Color::RGBA<float>& Values< Yuni::Gfx::Color::RGBA<float>, Yuni::Gfx::Color::RGBA<uint8> >::Assign(Yuni::Gfx::Color::RGBA<float>& th, const Yuni::Gfx::Color::RGBA<uint8>& a1)
	{
		th.red   = (float)a1.red   / 255.0f;
		th.green = (float)a1.green / 255.0f;
		th.blue  = (float)a1.blue  / 255.0f;
		th.alpha = (float)a1.alpha / 255.0f;
		return th;
	}


	template<>
	Yuni::Gfx::Color::RGB<float>& Values< Yuni::Gfx::Color::RGB<float>, float >::Assign(Yuni::Gfx::Color::RGB<float>& th, const float& a1, const float& a2, const float& a3, const float& /*a4*/)
	{
		th.red   = Math::MinMax<float>(a1, 0.0f, 1.0f);
		th.green = Math::MinMax<float>(a2, 0.0f, 1.0f);
		th.blue  = Math::MinMax<float>(a3, 0.0f, 1.0f);
		return th;
	}

	template<>
	Yuni::Gfx::Color::RGB<float>& Values< Yuni::Gfx::Color::RGB<float>, float >::Assign(Yuni::Gfx::Color::RGB<float>& th, const float& a1, const float& a2, const float& a3)
	{
		th.red   = Math::MinMax<float>(a1, 0.0f, 1.0f);
		th.green = Math::MinMax<float>(a2, 0.0f, 1.0f);
		th.blue  = Math::MinMax<float>(a3, 0.0f, 1.0f);
		return th;
	}



	template<>
	Yuni::Gfx::Color::RGBA<uint8>& Values< Yuni::Gfx::Color::RGBA<uint8>, Yuni::Gfx::Color::RGBA<float> >::Assign(Yuni::Gfx::Color::RGBA<uint8>& th, const Yuni::Gfx::Color::RGBA<float>& a1)
	{
		th.red   = (uint8) (a1.red   * 255.0f);
		th.green = (uint8) (a1.green * 255.0f);
		th.blue  = (uint8) (a1.blue  * 255.0f);
		th.alpha = (uint8) (a1.alpha * 255.0f);
		return th;
	}

	template<>
	Yuni::Gfx::Color::RGB<uint8>& Values< Yuni::Gfx::Color::RGB<uint8>, uint8 >::Assign(Yuni::Gfx::Color::RGB<uint8>& th, const uint8& a1, const uint8& a2, const uint8& a3, const uint8& /*a4*/)
	{
		th.red   = a1;
		th.green = a2;
		th.blue  = a3;
		return th;
	}

	template<>
	Yuni::Gfx::Color::RGB<uint8>& Values< Yuni::Gfx::Color::RGB<uint8>, uint8 >::Assign(Yuni::Gfx::Color::RGB<uint8>& th, const uint8& a1, const uint8& a2, const uint8& a3)
	{
		th.red   = a1;
		th.green = a2;
		th.blue  = a3;
		return th;
	}


	template<>
	Yuni::Gfx::Color::RGB<float>& Values< Yuni::Gfx::Color::RGB<float>, uint8 >::Assign(Yuni::Gfx::Color::RGB<float>& th, const uint8& r, const uint8& g, const uint8& b, const uint8& /*a*/)
	{
		th.red   = (float) r / 255.0f;
		th.green = (float) g / 255.0f;
		th.blue  = (float) b / 255.0f;
		return th;
	}

	template<>
	Yuni::Gfx::Color::RGB<float>& Values< Yuni::Gfx::Color::RGB<float>, Yuni::Gfx::Color::RGB<uint8> >::Assign(Yuni::Gfx::Color::RGB<float>& th, const Yuni::Gfx::Color::RGB<uint8>& a1)
	{
		th.red   = (float) a1.red   / 255.0f;
		th.green = (float) a1.green / 255.0f;
		th.blue  = (float) a1.blue  / 255.0f;
		return th;
	}

	template<>
	Yuni::Gfx::Color::RGB<uint8>& Values< Yuni::Gfx::Color::RGB<uint8>, Yuni::Gfx::Color::RGB<float> >::Assign(Yuni::Gfx::Color::RGB<uint8>& th, const Yuni::Gfx::Color::RGB<float>& a1)
	{
		th.red   = (uint8) (a1.red   * 255.0f);
		th.green = (uint8) (a1.green * 255.0f);
		th.blue  = (uint8) (a1.blue  * 255.0f);
		return th;
	}



	template<>
	Yuni::Gfx::Color::RGB<uint8>& Values< Yuni::Gfx::Color::RGB<uint8>, float >::Assign(Yuni::Gfx::Color::RGB<uint8>& th, const float& a1, const float& a2, const float& a3)
	{
		th.red   = (uint8) (a1 * 255.0f);
		th.green = (uint8) (a2 * 255.0f);
		th.blue  = (uint8) (a3 * 255.0f);
		return th;
	}


# define YUNI_CONVERT_UN_SIGNED_VALUE_MT(S, O) \
	template<> \
	Yuni::Gfx::Color::RGB< S >& Values< Yuni::Gfx::Color::RGB< S >, float >::Assign(Yuni::Gfx::Color::RGB< S >& th, const O & a1, const O & a2, const O & a3) \
	{ \
		th.red   = ( S ) (Math::MinMax< O >(a1, 0.0f, 1.0f) * 255.0f); \
		th.green = ( S ) (Math::MinMax< O >(a2, 0.0f, 1.0f) * 255.0f); \
		th.blue  = ( S ) (Math::MinMax< O >(a3, 0.0f, 1.0f) * 255.0f); \
		return th; \
	} \
	\
	template<> \
	Yuni::Gfx::Color::RGB< S >& Values< Yuni::Gfx::Color::RGB< S >, float >::Assign(Yuni::Gfx::Color::RGB< S >& th, const O & a1, const O & a2, const O & a3, const O &) \
	{ \
		th.red   = ( S ) (Math::MinMax< O >(a1, 0.0f, 1.0f) * 255.0f); \
		th.green = ( S ) (Math::MinMax< O >(a2, 0.0f, 1.0f) * 255.0f); \
		th.blue  = ( S ) (Math::MinMax< O >(a3, 0.0f, 1.0f) * 255.0f); \
		return th; \
	} \
	template<> \
	Yuni::Gfx::Color::RGBA< S >& Values< Yuni::Gfx::Color::RGBA< S >, float >::Assign(Yuni::Gfx::Color::RGBA< S >& th, const O & a1, const O & a2, const O & a3) \
	{ \
		th.red   = ( S ) (Math::MinMax< O >(a1, 0.0f, 1.0f) * 255.0f); \
		th.green = ( S ) (Math::MinMax< O >(a2, 0.0f, 1.0f) * 255.0f); \
		th.blue  = ( S ) (Math::MinMax< O >(a3, 0.0f, 1.0f) * 255.0f); \
		th.alpha = 255; \
		return th; \
	} \
	\
	template<> \
	Yuni::Gfx::Color::RGBA< S >& Values< Yuni::Gfx::Color::RGBA< S >, float >::Assign(Yuni::Gfx::Color::RGBA< S >& th, const O & a1, const O & a2, const O & a3, const O & a4) \
	{ \
		th.red   = ( S ) (Math::MinMax< O >(a1, 0.0f, 1.0f) * 255.0f); \
		th.green = ( S ) (Math::MinMax< O >(a2, 0.0f, 1.0f) * 255.0f); \
		th.blue  = ( S ) (Math::MinMax< O >(a3, 0.0f, 1.0f) * 255.0f); \
		th.alpha = ( S ) (Math::MinMax< O >(a4, 0.0f, 1.0f) * 255.0f); \
		return th; \
	}


	YUNI_CONVERT_UN_SIGNED_VALUE_MT(uint16, float)
	YUNI_CONVERT_UN_SIGNED_VALUE_MT(uint32, float)
	YUNI_CONVERT_UN_SIGNED_VALUE_MT(uint64, float)
	YUNI_CONVERT_UN_SIGNED_VALUE_MT(sint16, float)
	YUNI_CONVERT_UN_SIGNED_VALUE_MT(sint32, float)
	YUNI_CONVERT_UN_SIGNED_VALUE_MT(sint64, float)



# define YUNI_CONVERT_SIGNED_VALUE_FOR_FLOAT(O,T) \
	template<> \
	Yuni::Gfx::Color::RGBA< O >& Values< Yuni::Gfx::Color::RGBA< O >, T >::Assign(Yuni::Gfx::Color::RGBA< O >& th, const T& a1, const T& a2, const T& a3, const T& a4) \
	{ \
		th.red   = (O) Math::MinMax< T >(a1, 0, 255) / 255.0f; \
		th.green = (O) Math::MinMax< T >(a2, 0, 255) / 255.0f; \
		th.blue  = (O) Math::MinMax< T >(a3, 0, 255) / 255.0f; \
		th.alpha = (O) Math::MinMax< T >(a4, 0, 255) / 255.0f; \
		return th; \
	} \
	\
	template<> \
	Yuni::Gfx::Color::RGBA< O >& Values< Yuni::Gfx::Color::RGBA< O >, T >::Assign(Yuni::Gfx::Color::RGBA< O >& th, const T& a1, const T& a2, const T& a3) \
	{ \
		th.red   = (O) Math::MinMax< T >(a1, 0, 255) / 255.0f; \
		th.green = (O) Math::MinMax< T >(a2, 0, 255) / 255.0f; \
		th.blue  = (O) Math::MinMax< T >(a3, 0, 255) / 255.0f; \
		th.alpha = 1.0f; \
		return th; \
	} \
	\
	template<> \
	Yuni::Gfx::Color::RGB< O >& Values< Yuni::Gfx::Color::RGB< O >, T >::Assign(Yuni::Gfx::Color::RGB< O >& th, const T& a1, const T& a2, const T& a3, const T& /*a4*/) \
	{ \
		th.red   = (O) Math::MinMax< T >(a1, 0, 255) / 255.0f; \
		th.green = (O) Math::MinMax< T >(a2, 0, 255) / 255.0f; \
		th.blue  = (O) Math::MinMax< T >(a3, 0, 255) / 255.0f; \
		return th; \
	} \
	\
	template<> \
	Yuni::Gfx::Color::RGB< O >& Values< Yuni::Gfx::Color::RGB< O >, T >::Assign(Yuni::Gfx::Color::RGB< O >& th, const T& a1, const T& a2, const T& a3) \
	{ \
		th.red   = (O) Math::MinMax< T >(a1, 0, 255) / 255.0f; \
		th.green = (O) Math::MinMax< T >(a2, 0, 255) / 255.0f; \
		th.blue  = (O) Math::MinMax< T >(a3, 0, 255) / 255.0f; \
		return th; \
	}

	YUNI_CONVERT_SIGNED_VALUE_FOR_FLOAT(float, sint16)
	YUNI_CONVERT_SIGNED_VALUE_FOR_FLOAT(float, sint32)
	YUNI_CONVERT_SIGNED_VALUE_FOR_FLOAT(float, sint64)


# define YUNI_CONVERT_UNSIGNED_VALUE_FOR_FLOAT(O,T) \
	template<> \
	Yuni::Gfx::Color::RGBA< O >& Values< Yuni::Gfx::Color::RGBA< O >, T >::Assign(Yuni::Gfx::Color::RGBA< O >& th, const T& a1, const T& a2, const T& a3, const T& a4) \
	{ \
		th.red   = (O) Math::Max< T >(a1, 255) / 255.0f; \
		th.green = (O) Math::Max< T >(a2, 255) / 255.0f; \
		th.blue  = (O) Math::Max< T >(a3, 255) / 255.0f; \
		th.alpha = (O) Math::Max< T >(a4, 255) / 255.0f; \
		return th; \
	} \
	\
	template<> \
	Yuni::Gfx::Color::RGBA< O >& Values< Yuni::Gfx::Color::RGBA< O >, T >::Assign(Yuni::Gfx::Color::RGBA< O >& th, const T& a1, const T& a2, const T& a3) \
	{ \
		th.red   = (O) Math::Max< T >(a1, 255) / 255.0f; \
		th.green = (O) Math::Max< T >(a2, 255) / 255.0f; \
		th.blue  = (O) Math::Max< T >(a3, 255) / 255.0f; \
		th.alpha = 1.0f; \
		return th; \
	} \
	\
	template<> \
	Yuni::Gfx::Color::RGB< O >& Values< Yuni::Gfx::Color::RGB< O >, T >::Assign(Yuni::Gfx::Color::RGB< O >& th, const T& a1, const T& a2, const T& a3, const T& /*a4*/) \
	{ \
		th.red   = (O) Math::Max< T >(a1, 255) / 255.0f; \
		th.green = (O) Math::Max< T >(a2, 255) / 255.0f; \
		th.blue  = (O) Math::Max< T >(a3, 255) / 255.0f; \
		return th; \
	} \
	\
	template<> \
	Yuni::Gfx::Color::RGB< O >& Values< Yuni::Gfx::Color::RGB< O >, T >::Assign(Yuni::Gfx::Color::RGB< O >& th, const T& a1, const T& a2, const T& a3) \
	{ \
		th.red   = (O) Math::Max< T >(a1, 255) / 255.0f; \
		th.green = (O) Math::Max< T >(a2, 255) / 255.0f; \
		th.blue  = (O) Math::Max< T >(a3, 255) / 255.0f; \
		return th; \
	}


	YUNI_CONVERT_UNSIGNED_VALUE_FOR_FLOAT(float, uint16)
	YUNI_CONVERT_UNSIGNED_VALUE_FOR_FLOAT(float, uint32)
	YUNI_CONVERT_UNSIGNED_VALUE_FOR_FLOAT(float, uint64)


# define YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(O,T) \
	template<> \
	Yuni::Gfx::Color::RGBA< O >& Values< Yuni::Gfx::Color::RGBA< O >, T >::Assign(Yuni::Gfx::Color::RGBA< O >& th, const T& a1, const T& a2, const T& a3, const T& a4) \
	{ \
		th.red   = (O) Math::MinMax<T>(a1, 0, 255); \
		th.green = (O) Math::MinMax<T>(a2, 0, 255); \
		th.blue  = (O) Math::MinMax<T>(a3, 0, 255); \
		th.alpha = (O) Math::MinMax<T>(a4, 0, 255); \
		return th; \
	} \
	\
	template<> \
	Yuni::Gfx::Color::RGBA< O >& Values< Yuni::Gfx::Color::RGBA< O >, T >::Assign(Yuni::Gfx::Color::RGBA< O >& th, const T& a1, const T& a2, const T& a3) \
	{ \
		th.red   = (O) Math::MinMax<T>(a1, 0, 255); \
		th.green = (O) Math::MinMax<T>(a2, 0, 255); \
		th.blue  = (O) Math::MinMax<T>(a3, 0, 255); \
		th.alpha = 255; \
		return th; \
	} \
	\
	template<> \
	Yuni::Gfx::Color::RGB< O >& Values< Yuni::Gfx::Color::RGB< O >, T >::Assign(Yuni::Gfx::Color::RGB< O >& th, const T& a1, const T& a2, const T& a3, const T&) \
	{ \
		th.red   = (O) Math::MinMax<T>(a1, 0, 255); \
		th.green = (O) Math::MinMax<T>(a2, 0, 255); \
		th.blue  = (O) Math::MinMax<T>(a3, 0, 255); \
		return th; \
	} \
	\
	template<> \
	Yuni::Gfx::Color::RGB< O >& Values< Yuni::Gfx::Color::RGB< O >, T >::Assign(Yuni::Gfx::Color::RGB< O >& th, const T& a1, const T& a2, const T& a3) \
	{ \
		th.red   = (O) Math::MinMax<T>(a1, 0, 255); \
		th.green = (O) Math::MinMax<T>(a2, 0, 255); \
		th.blue  = (O) Math::MinMax<T>(a3, 0, 255); \
		return th; \
	}


	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint8,  sint16)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint8,  sint32)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint8,  sint64)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint16, sint16)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint16, sint32)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint16, sint64)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint32, sint16)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint32, sint32)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint32, sint64)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint64, sint16)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint64, sint32)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint64, sint64)





# define YUNI_CONVERT_UNSIGNED_VALUE_FOR_UINT8(O,T) \
	template<> \
	Yuni::Gfx::Color::RGBA< O >& Values< Yuni::Gfx::Color::RGBA< O >, T >::Assign(Yuni::Gfx::Color::RGBA< O >& th, const T& a1, const T& a2, const T& a3, const T& a4) \
	{ \
		th.red   = (O) Math::Max<T>(a1, 255); \
		th.green = (O) Math::Max<T>(a2, 255); \
		th.blue  = (O) Math::Max<T>(a3, 255); \
		th.alpha = (O) Math::Max<T>(a4, 255); \
		return th; \
	} \
	\
	template<> \
	Yuni::Gfx::Color::RGBA< O >& Values< Yuni::Gfx::Color::RGBA< O >, T >::Assign(Yuni::Gfx::Color::RGBA< O >& th, const T& a1, const T& a2, const T& a3) \
	{ \
		th.red   = (O) Math::Max<T>(a1, 255); \
		th.green = (O) Math::Max<T>(a2, 255); \
		th.blue  = (O) Math::Max<T>(a3, 255); \
		th.alpha = 255; \
		return th; \
	} \
	\
	template<> \
	Yuni::Gfx::Color::RGB< O >& Values< Yuni::Gfx::Color::RGB< O >, T >::Assign(Yuni::Gfx::Color::RGB< O >& th, const T& a1, const T& a2, const T& a3, const T&) \
	{ \
		th.red   = (O) Math::Max<T>(a1, 255); \
		th.green = (O) Math::Max<T>(a2, 255); \
		th.blue  = (O) Math::Max<T>(a3, 255); \
		return th; \
	} \
	\
	template<> \
	Yuni::Gfx::Color::RGB< O >& Values< Yuni::Gfx::Color::RGB< O >, T >::Assign(Yuni::Gfx::Color::RGB< O >& th, const T& a1, const T& a2, const T& a3) \
	{ \
		th.red   = (O) Math::Max<T>(a1, 255); \
		th.green = (O) Math::Max<T>(a2, 255); \
		th.blue  = (O) Math::Max<T>(a3, 255); \
		return th; \
	}


	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint8,  uint16)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint8,  uint32)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint8,  uint64)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint16, uint16)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint16, uint32)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint16, uint64)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint32, uint16)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint32, uint32)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint32, uint64)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint64, uint16)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint64, uint32)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint64, uint64)










	/*
	 * --- Compare ---
	 */

	template<>
	bool Compare< Yuni::Gfx::Color::RGBA<float>, Yuni::Gfx::Color::RGBA<float> >::equals(const Yuni::Gfx::Color::RGBA<float>& lhs, const Yuni::Gfx::Color::RGBA<float>& rhs)
	{
		return Math::Abs(lhs.red - rhs.red) < 0.0001 && Math::Abs(lhs.green - rhs.green) < 0.0001
			&& Math::Abs(lhs.blue - rhs.blue) < 0.0001 && Math::Abs(lhs.alpha - rhs.alpha) < 0.0001;
	}

	template<>
	bool Compare< Yuni::Gfx::Color::RGB<float>, Yuni::Gfx::Color::RGB<float> >::equals(const Yuni::Gfx::Color::RGB<float>& lhs, const Yuni::Gfx::Color::RGB<float>& rhs)
	{
		return Math::Abs(lhs.red - rhs.red) < 0.0001 && Math::Abs(lhs.green - rhs.green) < 0.0001
			&& Math::Abs(lhs.blue - rhs.blue) < 0.0001;
	}




} // namespace Proxy
} // namespace Color
} // namespace Gfx
} // namespace Private
} // namespace Yuni

