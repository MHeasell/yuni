
#include "color.converters.h"
#include "../misc/math.h"
#include "rgba.h"
#include "rgb.h"



namespace Yuni
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
	std::ostream& Streamer< RGBA<uint8> >::toOStream(std::ostream& out, const RGBA<uint8>& th)
	{
		out << "r:" << (int)th.red << ",g:" << (int)th.green << ",b:" << (int)th.blue << ",a:" << (int)th.alpha;
		return out;
	}

	template<>
	std::ostream& Streamer< RGB<uint8> >::toOStream(std::ostream& out, const RGB<uint8>& th)
	{
		out << "r:" << (int)th.red << ",g:" << (int)th.green << ",b:" << (int)th.blue;
		return out;
	}

	template<>
	String Streamer< RGBA<uint8> >::toString(const RGBA<uint8>& th)
	{
		return String() << "r:" << (int)th.red << ",g:" << (int)th.green << ",b:" << (int)th.blue << ",a:" << (int)th.alpha;
	}

	template<>
	String Streamer< RGB<uint8> >::toString(const RGB<uint8>& th)
	{
		return String() << "r:" << (int)th.red << ",g:" << (int)th.green << ",b:" << (int)th.blue;
	}











	/*
	 * --- Assign ---
	 */

	template<>
	RGBA<uint8>& Values< RGBA<uint8>, uint8 >::Assign(RGBA<uint8>& th, const uint8& a1, const uint8& a2, const uint8& a3, const uint8& a4)
	{
		th.red   = a1;
		th.green = a2;
		th.blue  = a3;
		th.alpha = a4;
		return th;
	}

	template<>
	RGBA<uint8>& Values< RGBA<uint8>, uint8 >::Assign(RGBA<uint8>& th, const uint8& a1, const uint8& a2, const uint8& a3)
	{
		th.red   = a1;
		th.green = a2;
		th.blue  = a3;
		th.alpha = 255;
		return th;
	}


	template<>
	RGBA<float>& Values< RGBA<float>, float >::Assign(RGBA<float>& th, const float& a1, const float& a2, const float& a3, const float& a4)
	{
		th.red   = Math::MinMax<float>(a1, 0.0f, 1.0f);
		th.green = Math::MinMax<float>(a2, 0.0f, 1.0f);
		th.blue  = Math::MinMax<float>(a3, 0.0f, 1.0f);
		th.alpha = Math::MinMax<float>(a4, 0.0f, 1.0f);
		return th;
	}

	template<>
	RGBA<float>& Values< RGBA<float>, float >::Assign(RGBA<float>& th, const float& a1, const float& a2, const float& a3)
	{
		th.red   = Math::MinMax<float>(a1, 0.0f, 1.0f);
		th.green = Math::MinMax<float>(a2, 0.0f, 1.0f);
		th.blue  = Math::MinMax<float>(a3, 0.0f, 1.0f);
		th.alpha = 1.0f;
		return th;
	}


	template<>
	RGBA<float>& Values< RGBA<float>, uint8 >::Assign(RGBA<float>& th, const uint8& r, const uint8& g, const uint8& b, const uint8& a)
	{
		th.red   = r / 255.0f;
		th.green = g / 255.0f;
		th.blue  = b / 255.0f;
		th.alpha = a / 255.0f;
		return th;
	}

	template<>
	RGBA<float>& Values< RGBA<float>, RGBA<uint8> >::Assign(RGBA<float>& th, const RGBA<uint8>& a1)
	{
		th.red   = a1.red   / 255.0f;
		th.green = a1.green / 255.0f;
		th.blue  = a1.blue  / 255.0f;
		th.alpha = a1.alpha / 255.0f;
		return th;
	}

	template<>
	RGBA<uint8>& Values< RGBA<uint8>, RGBA<float> >::Assign(RGBA<uint8>& th, const RGBA<float>& a1)
	{
		th.red   = (uint8) (a1.red   * 255.0f);
		th.green = (uint8) (a1.green * 255.0f);
		th.blue  = (uint8) (a1.blue  * 255.0f);
		th.alpha = (uint8) (a1.alpha * 255.0f);
		return th;
	}




	template<>
	RGB<uint8>& Values< RGB<uint8>, uint8 >::Assign(RGB<uint8>& th, const uint8& a1, const uint8& a2, const uint8& a3, const uint8& /*a4*/)
	{
		th.red   = a1;
		th.green = a2;
		th.blue  = a3;
		return th;
	}

	template<>
	RGB<uint8>& Values< RGB<uint8>, uint8 >::Assign(RGB<uint8>& th, const uint8& a1, const uint8& a2, const uint8& a3)
	{
		th.red   = a1;
		th.green = a2;
		th.blue  = a3;
		return th;
	}


	template<>
	RGB<float>& Values< RGB<float>, float >::Assign(RGB<float>& th, const float& a1, const float& a2, const float& a3, const float& /*a4*/)
	{
		th.red   = Math::MinMax<float>(a1, 0.0f, 1.0f);
		th.green = Math::MinMax<float>(a2, 0.0f, 1.0f);
		th.blue  = Math::MinMax<float>(a3, 0.0f, 1.0f);
		return th;
	}

	template<>
	RGB<float>& Values< RGB<float>, float >::Assign(RGB<float>& th, const float& a1, const float& a2, const float& a3)
	{
		th.red   = Math::MinMax<float>(a1, 0.0f, 1.0f);
		th.green = Math::MinMax<float>(a2, 0.0f, 1.0f);
		th.blue  = Math::MinMax<float>(a3, 0.0f, 1.0f);
		return th;
	}


	template<>
	RGB<float>& Values< RGB<float>, uint8 >::Assign(RGB<float>& th, const uint8& r, const uint8& g, const uint8& b, const uint8& /*a*/)
	{
		th.red   = r / 255.0f;
		th.green = g / 255.0f;
		th.blue  = b / 255.0f;
		return th;
	}

	template<>
	RGB<float>& Values< RGB<float>, RGB<uint8> >::Assign(RGB<float>& th, const RGB<uint8>& a1)
	{
		th.red   = a1.red   / 255.0f;
		th.green = a1.green / 255.0f;
		th.blue  = a1.blue  / 255.0f;
		return th;
	}

	template<>
	RGB<uint8>& Values< RGB<uint8>, RGB<float> >::Assign(RGB<uint8>& th, const RGB<float>& a1)
	{
		th.red   = (uint8) (a1.red   * 255.0f);
		th.green = (uint8) (a1.green * 255.0f);
		th.blue  = (uint8) (a1.blue  * 255.0f);
		return th;
	}






# define YUNI_CONVERT_SIGNED_VALUE_FOR_FLOAT(O,T) \
	template<> \
	RGBA< O >& Values< RGBA< O >, T >::Assign(RGBA< O >& th, const T& a1, const T& a2, const T& a3, const T& a4) \
	{ \
		th.red   = (O) Math::MinMax< T >(a1, 0, 255) / 255.0f; \
		th.green = (O) Math::MinMax< T >(a2, 0, 255) / 255.0f; \
		th.blue  = (O) Math::MinMax< T >(a3, 0, 255) / 255.0f; \
		th.alpha = (O) Math::MinMax< T >(a4, 0, 255) / 255.0f; \
		return th; \
	} \
	\
	template<> \
	RGBA< O >& Values< RGBA< O >, T >::Assign(RGBA< O >& th, const T& a1, const T& a2, const T& a3) \
	{ \
		th.red   = (O) Math::MinMax< T >(a1, 0, 255) / 255.0f; \
		th.green = (O) Math::MinMax< T >(a2, 0, 255) / 255.0f; \
		th.blue  = (O) Math::MinMax< T >(a3, 0, 255) / 255.0f; \
		th.alpha = 1.0f; \
		return th; \
	} \
	\
	template<> \
	RGB< O >& Values< RGB< O >, T >::Assign(RGB< O >& th, const T& a1, const T& a2, const T& a3, const T& /*a4*/) \
	{ \
		th.red   = (O) Math::MinMax< T >(a1, 0, 255) / 255.0f; \
		th.green = (O) Math::MinMax< T >(a2, 0, 255) / 255.0f; \
		th.blue  = (O) Math::MinMax< T >(a3, 0, 255) / 255.0f; \
		return th; \
	} \
	\
	template<> \
	RGB< O >& Values< RGB< O >, T >::Assign(RGB< O >& th, const T& a1, const T& a2, const T& a3) \
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
	RGBA< O >& Values< RGBA< O >, T >::Assign(RGBA< O >& th, const T& a1, const T& a2, const T& a3, const T& a4) \
	{ \
		th.red   = (O) Math::Max< T >(a1, 255) / 255.0f; \
		th.green = (O) Math::Max< T >(a2, 255) / 255.0f; \
		th.blue  = (O) Math::Max< T >(a3, 255) / 255.0f; \
		th.alpha = (O) Math::Max< T >(a4, 255) / 255.0f; \
		return th; \
	} \
	\
	template<> \
	RGBA< O >& Values< RGBA< O >, T >::Assign(RGBA< O >& th, const T& a1, const T& a2, const T& a3) \
	{ \
		th.red   = (O) Math::Max< T >(a1, 255) / 255.0f; \
		th.green = (O) Math::Max< T >(a2, 255) / 255.0f; \
		th.blue  = (O) Math::Max< T >(a3, 255) / 255.0f; \
		th.alpha = 1.0f; \
		return th; \
	} \
	\
	template<> \
	RGB< O >& Values< RGB< O >, T >::Assign(RGB< O >& th, const T& a1, const T& a2, const T& a3, const T& /*a4*/) \
	{ \
		th.red   = (O) Math::Max< T >(a1, 255) / 255.0f; \
		th.green = (O) Math::Max< T >(a2, 255) / 255.0f; \
		th.blue  = (O) Math::Max< T >(a3, 255) / 255.0f; \
		return th; \
	} \
	\
	template<> \
	RGB< O >& Values< RGB< O >, T >::Assign(RGB< O >& th, const T& a1, const T& a2, const T& a3) \
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
	RGBA< O >& Values< RGBA< O >, T >::Assign(RGBA< O >& th, const T& a1, const T& a2, const T& a3, const T& a4) \
	{ \
		th.red   = (O) Math::MinMax<T>(a1, 0, 255); \
		th.green = (O) Math::MinMax<T>(a2, 0, 255); \
		th.blue  = (O) Math::MinMax<T>(a3, 0, 255); \
		th.alpha = (O) Math::MinMax<T>(a4, 0, 255); \
		return th; \
	} \
	\
	template<> \
	RGBA< O >& Values< RGBA< O >, T >::Assign(RGBA< O >& th, const T& a1, const T& a2, const T& a3) \
	{ \
		th.red   = (O) Math::MinMax<T>(a1, 0, 255); \
		th.green = (O) Math::MinMax<T>(a2, 0, 255); \
		th.blue  = (O) Math::MinMax<T>(a3, 0, 255); \
		th.alpha = 255; \
		return th; \
	} \
	\
	template<> \
	RGB< O >& Values< RGB< O >, T >::Assign(RGB< O >& th, const T& a1, const T& a2, const T& a3, const T&) \
	{ \
		th.red   = (O) Math::MinMax<T>(a1, 0, 255); \
		th.green = (O) Math::MinMax<T>(a2, 0, 255); \
		th.blue  = (O) Math::MinMax<T>(a3, 0, 255); \
		return th; \
	} \
	\
	template<> \
	RGB< O >& Values< RGB< O >, T >::Assign(RGB< O >& th, const T& a1, const T& a2, const T& a3) \
	{ \
		th.red   = (O) Math::MinMax<T>(a1, 0, 255); \
		th.green = (O) Math::MinMax<T>(a2, 0, 255); \
		th.blue  = (O) Math::MinMax<T>(a3, 0, 255); \
		return th; \
	}


	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint8, sint16)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint8, sint32)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint8, sint64)


# define YUNI_CONVERT_UNSIGNED_VALUE_FOR_UINT8(O,T) \
	template<> \
	RGBA< O >& Values< RGBA< O >, T >::Assign(RGBA< O >& th, const T& a1, const T& a2, const T& a3, const T& a4) \
	{ \
		th.red   = (O) Math::Max<T>(a1, 255); \
		th.green = (O) Math::Max<T>(a2, 255); \
		th.blue  = (O) Math::Max<T>(a3, 255); \
		th.alpha = (O) Math::Max<T>(a4, 255); \
		return th; \
	} \
	\
	template<> \
	RGBA< O >& Values< RGBA< O >, T >::Assign(RGBA< O >& th, const T& a1, const T& a2, const T& a3) \
	{ \
		th.red   = (O) Math::Max<T>(a1, 255); \
		th.green = (O) Math::Max<T>(a2, 255); \
		th.blue  = (O) Math::Max<T>(a3, 255); \
		th.alpha = 255; \
		return th; \
	} \
	\
	template<> \
	RGB< O >& Values< RGB< O >, T >::Assign(RGB< O >& th, const T& a1, const T& a2, const T& a3, const T&) \
	{ \
		th.red   = (O) Math::Max<T>(a1, 255); \
		th.green = (O) Math::Max<T>(a2, 255); \
		th.blue  = (O) Math::Max<T>(a3, 255); \
		return th; \
	} \
	\
	template<> \
	RGB< O >& Values< RGB< O >, T >::Assign(RGB< O >& th, const T& a1, const T& a2, const T& a3) \
	{ \
		th.red   = (O) Math::Max<T>(a1, 255); \
		th.green = (O) Math::Max<T>(a2, 255); \
		th.blue  = (O) Math::Max<T>(a3, 255); \
		return th; \
	}


	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint8, uint16)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint8, uint32)
	YUNI_CONVERT_SIGNED_VALUE_FOR_UINT8(uint8, uint64)








	/*
	 * --- Compare ---
	 */

	template<>
	bool Compare< RGBA<float>, RGBA<float> >::equals(const RGBA<float>& lhs, const RGBA<float>& rhs)
	{
		return Math::Abs(lhs.red - rhs.red) < 0.0001 && Math::Abs(lhs.green - rhs.green) < 0.0001
			&& Math::Abs(lhs.blue - rhs.blue) < 0.0001 && Math::Abs(lhs.alpha - rhs.alpha) < 0.0001;
	}

	template<>
	bool Compare< RGB<float>, RGB<float> >::equals(const RGB<float>& lhs, const RGB<float>& rhs)
	{
		return Math::Abs(lhs.red - rhs.red) < 0.0001 && Math::Abs(lhs.green - rhs.green) < 0.0001
			&& Math::Abs(lhs.blue - rhs.blue) < 0.0001;
	}




} // namespace Proxy
} // namespace Color
} // namespace Gfx
} // namespace Yuni

