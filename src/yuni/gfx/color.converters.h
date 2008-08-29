#ifndef __YUNI_GFX_COLOR_CONVERTERS_H__
# define __YUNI_GFX_COLOR_CONVERTERS_H__

# include <iostream>
# include "../yuni.h"
# include "../misc/string.h"
# include "../misc/math.h"


namespace Yuni
{
namespace Gfx
{
namespace Color
{

	// Forward declaration
	template<typename T> class RGBA;
	template<typename T> class RGB;


namespace Proxy
{



	/*! \class Values
	**
	** \brief Convert a Color model into another
	*/
	template<typename T, typename U>
	struct Values
	{
		/*!
		** \brief Assign the values between RGB Color Models from a single argument
		**
		** \param th The instance where assignation will be done
		** \param a1 The value
		** \return Always `th`
		*/
		static T& Assign(T& th, const U& a1);

		/*!
		** \brief Assign the values between RGB Color Models from a single argument
		**
		** \param th The instance where assignation will be done
		** \param a1 The value
		** \param a2 The second value
		** \return Always `th`
		*/
		static T& Assign(T& th, const U& a1, const U& a2);

		/*!
		** \brief Assign the values between RGB Color Models from 3 arguments
		**
		** \param th The instance where assignation will be done
		** \param a1 The first value
		** \param a2 The second value
		** \param a3 The third value
		** \return Always `th`
		*/
		static T& Assign(T& th, const U& a1, const U& a2, const U&a3);

		/*!
		** \brief Assign the values between RGB Color Models from 4 arguments
		**
		** \param th The instance where assignation will be done
		** \param a1 The first value
		** \param a2 The second value
		** \param a3 The third value
		** \param a4 The fourth value
		** \return Always `th`
		*/
		static T& Assign(T& th, const U& a1, const U& a2, const U& a3, const U& a4);


		static T& Inc(T& to, const U& inc);


	}; // class Values




	/*!
	** \brief Export the values of a Color Model
	*/
	template<typename T>
	struct Streamer
	{
		/*!
		** \brief Export the values of a Color Model to a stream
		**
		** \param[in,out] out The output stream
		** \param th The color model
		** \return The given output stream
		*/
		static std::ostream& toOStream(std::ostream& out, const T& th);

		/*!
		** \brief Export the values of a Color Model to a String
		**
		** \param th The color Model
		** \return An human-readable expr representing the color model
		*/
		static String toString(const T& th);
	};






	template<typename T, typename U>
	struct Compare
	{
		static bool check(const T& lhs, const U& rhs);
	};

	// Compare RGBA with the same type
	template<typename V>
	struct Compare< RGBA<V>, RGBA<V> >
	{
		inline static bool check(const RGBA<V>& lhs, const RGBA<V>& rhs)
		{ return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue && lhs.alpha == rhs.alpha; }
	};
	
	// Compare RGBA with not the same type
	template<typename V, typename W>
	struct Compare< RGBA<V>, RGBA<W> >
	{
		inline static bool check(const RGBA<V>& lhs, const RGBA<W>& rhs)
		{ return lhs == RGBA<V>(rhs); }
	};


	// Compare RGB with the same type
	template<typename V>
	struct Compare< RGB<V>, RGB<V> >
	{
		inline static bool check(const RGB<V>& lhs, const RGB<V>& rhs)
		{ return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue; }
	};

	// Compare RGBA - RGB
	template<typename V>
	struct Compare< RGBA<V>, RGB<V> >
	{
		inline static bool check(const RGBA<V>& lhs, const RGB<V>& rhs)
		{ return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue; }
	};

	// Compare RGB - RGBA
	template<typename V>
	struct Compare< RGB<V>, RGBA<V> >
	{
		inline static bool check(const RGB<V>& lhs, const RGBA<V>& rhs)
		{ return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue; }
	};


	
} // namespace Proxy
} // namespace Color
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_COLOR_CONVERTERS_H__
