#ifndef __YUNI_GFX_COLOR_PROXY_H__
# define __YUNI_GFX_COLOR_PROXY_H__

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
		** \brief Assign the values between RGB Color Models from 2 arguments
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

	template<>
	template<typename A, typename B>
	struct Values< RGB<A>, RGBA<B> > 
	{
		inline static RGB<A>& Assign(RGB<A>& th, const RGBA<B>& a1)
		{
			return th.assign(a1.red, a1.green, a1.blue);
		}

		inline static RGB<A>& Inc(RGB<A>& to, const RGBA<B>& inc)
		{
			return (to += RGB<A>(inc));
		}

	};

	template<>
	template<typename A, typename B>
	struct Values< RGBA<A>, RGB<B> > 
	{
		inline static RGBA<A>& Assign(RGBA<A>& th, const RGB<B>& a1)
		{
			return th.assign(a1.red, a1.green, a1.blue);
		}

		inline static RGBA<A>& Inc(RGBA<A>& to, const RGB<B>& inc)
		{
			return (to += RGBA<A>(inc));
		}

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


	template<>
	template<typename S>
	struct Streamer< RGBA<S> >
	{
		inline static std::ostream& toOStream(std::ostream& out, const RGBA<S>& th)
		{
			out << "r:" << th.red << ",g:" << th.green << ",b:" << th.blue << ",a:" << th.alpha;
			return out;
		}

		inline static String toString(const RGBA<S>& th)
		{
			return String() << "r:" << th.red << ",g:" << th.green << ",b:" << th.blue << ",a:" << th.alpha;
		}
	};

	template<>
	template<typename S>
	struct Streamer< RGB<S> >
	{
		inline static std::ostream& toOStream(std::ostream& out, const RGB<S>& th)
		{
			out << "r:" << th.red << ",g:" << th.green << ",b:" << th.blue;
			return out;
		}

		inline static String toString(const RGB<S>& th)
		{
			return String() << "r:" << th.red << ",g:" << th.green << ",b:" << th.blue;
		}
	};








	template<typename T, typename U>
	struct Compare
	{
		/*!
		** \brief Test if two Color models are equal
		*/
		static bool equals(const T& lhs, const U& rhs);
	};

	// Compare RGBA with the same type
	template<typename V>
	struct Compare< RGBA<V>, RGBA<V> >
	{
		inline static bool equals(const RGBA<V>& lhs, const RGBA<V>& rhs)
		{ return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue && lhs.alpha == rhs.alpha; }
	};
	
	// Compare RGBA with not the same type
	template<typename V, typename W>
	struct Compare< RGBA<V>, RGBA<W> >
	{
		inline static bool equals(const RGBA<V>& lhs, const RGBA<W>& rhs)
		{ return Compare< RGBA<V>, RGBA<V> >::equals(lhs, RGBA<V>(rhs)); }
	};


	// Compare RGB with the same type
	template<typename V>
	struct Compare< RGB<V>, RGB<V> >
	{
		inline static bool equals(const RGB<V>& lhs, const RGB<V>& rhs)
		{ return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue; }
	};

	// Compare RGB with not the same type
	template<typename V, typename W>
	struct Compare< RGB<V>, RGB<W> >
	{
		inline static bool equals(const RGB<V>& lhs, const RGB<W>& rhs)
		{ return Compare< RGB<V>, RGB<V> >::equals(lhs.red, RGB<V>(rhs)); }
	};

	// Compare RGBA - RGB
	template<typename V>
	struct Compare< RGBA<V>, RGB<V> >
	{
		inline static bool equals(const RGBA<V>& lhs, const RGB<V>& rhs)
		{ return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue; }
	};

	// Compare RGB - RGBA
	template<typename V>
	struct Compare< RGB<V>, RGBA<V> >
	{
		inline static bool equals(const RGB<V>& lhs, const RGBA<V>& rhs)
		{ return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue; }
	};


	
} // namespace Proxy
} // namespace Color
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_COLOR_PROXY_H__
