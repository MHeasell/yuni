#ifndef __YUNI_GFX_COLOR_PROXY_H__
# define __YUNI_GFX_COLOR_PROXY_H__

# include <iostream>
# include "../yuni.h"
# include "../toolbox/string.h"


namespace Yuni
{
namespace Gfx
{
namespace Color
{

	// Forward declaration
	template<typename T> class RGBA;
	template<typename T> class RGB;

} // namespace Gfx
} // namespace Color
} // namespace Yuni



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



	/*! \class Values
	**
	** \brief Convert a Color model into another
	*/
	template<typename T, typename U>
	struct Values
	{
		/*!
		** \brief Assign the values between Yuni::Gfx::Color::RGB Color Models from a single argument
		**
		** \param th The instance where assignation will be done
		** \param a1 The value
		** \return Always `th`
		*/
		static T& Assign(T& th, const U& a1);

		/*!
		** \brief Assign the values between Yuni::Gfx::Color::RGB Color Models from 2 arguments
		**
		** \param th The instance where assignation will be done
		** \param a1 The value
		** \param a2 The second value
		** \return Always `th`
		*/
		static T& Assign(T& th, const U& a1, const U& a2);

		/*!
		** \brief Assign the values between Yuni::Gfx::Color::RGB Color Models from 3 arguments
		**
		** \param th The instance where assignation will be done
		** \param a1 The first value
		** \param a2 The second value
		** \param a3 The third value
		** \return Always `th`
		*/
		static T& Assign(T& th, const U& a1, const U& a2, const U&a3);

		/*!
		** \brief Assign the values between Yuni::Gfx::Color::RGB Color Models from 4 arguments
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


	# ifndef YUNI_OS_MSVC // see C2910 (http://msdn.microsoft.com/en-us/library/cx7k7hcf.aspx)
	template<>
	# endif
	template<typename A, typename B>
	struct Values< Yuni::Gfx::Color::RGB<A>, Yuni::Gfx::Color::RGBA<B> > 
	{
		inline static Yuni::Gfx::Color::RGB<A>& Assign(Yuni::Gfx::Color::RGB<A>& th, const Yuni::Gfx::Color::RGBA<B>& a1)
		{
			return th.assign(a1.red, a1.green, a1.blue);
		}

		inline static Yuni::Gfx::Color::RGB<A>& Inc(Yuni::Gfx::Color::RGB<A>& to, const Yuni::Gfx::Color::RGBA<B>& inc)
		{
			return (to += Yuni::Gfx::Color::RGB<A>(inc));
		}

	};

	# ifndef YUNI_OS_MSVC // see C2910 (http://msdn.microsoft.com/en-us/library/cx7k7hcf.aspx)
	template<>
	# endif
	template<typename A, typename B>
	struct Values< Yuni::Gfx::Color::RGBA<A>, Yuni::Gfx::Color::RGB<B> > 
	{
		inline static Yuni::Gfx::Color::RGBA<A>& Assign(Yuni::Gfx::Color::RGBA<A>& th, const Yuni::Gfx::Color::RGB<B>& a1)
		{
			return th.assign(a1.red, a1.green, a1.blue);
		}

		inline static Yuni::Gfx::Color::RGBA<A>& Inc(Yuni::Gfx::Color::RGBA<A>& to, const Yuni::Gfx::Color::RGB<B>& inc)
		{
			return (to += Yuni::Gfx::Color::RGBA<A>(inc));
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




	# ifndef YUNI_OS_MSVC // see C2910 (http://msdn.microsoft.com/en-us/library/cx7k7hcf.aspx)
	template<>
	# endif
	template<typename S>
	struct Streamer< Yuni::Gfx::Color::RGBA<S> >
	{
		inline static std::ostream& toOStream(std::ostream& out, const Yuni::Gfx::Color::RGBA<S>& th)
		{
			out << "r:" << th.red << ",g:" << th.green << ",b:" << th.blue << ",a:" << th.alpha;
			return out;
		}

		inline static String toString(const Yuni::Gfx::Color::RGBA<S>& th)
		{
			return String() << "r:" << th.red << ",g:" << th.green << ",b:" << th.blue << ",a:" << th.alpha;
		}
	};


	# ifndef YUNI_OS_MSVC // see C2910 (http://msdn.microsoft.com/en-us/library/cx7k7hcf.aspx)
	template<>
	# endif
	template<typename S>
	struct Streamer< Yuni::Gfx::Color::RGB<S> >
	{
		inline static std::ostream& toOStream(std::ostream& out, const Yuni::Gfx::Color::RGB<S>& th)
		{
			out << "r:" << th.red << ",g:" << th.green << ",b:" << th.blue;
			return out;
		}

		inline static String toString(const Yuni::Gfx::Color::RGB<S>& th)
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

	// Compare Yuni::Gfx::Color::RGBA with the same type
	template<typename V>
	struct Compare< Yuni::Gfx::Color::RGBA<V>, Yuni::Gfx::Color::RGBA<V> >
	{
		inline static bool equals(const Yuni::Gfx::Color::RGBA<V>& lhs, const Yuni::Gfx::Color::RGBA<V>& rhs)
		{ return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue && lhs.alpha == rhs.alpha; }
	};
	
	// Compare Yuni::Gfx::Color::RGBA with not the same type
	template<typename V, typename W>
	struct Compare< Yuni::Gfx::Color::RGBA<V>, Yuni::Gfx::Color::RGBA<W> >
	{
		inline static bool equals(const Yuni::Gfx::Color::RGBA<V>& lhs, const Yuni::Gfx::Color::RGBA<W>& rhs)
		{ return Compare< Yuni::Gfx::Color::RGBA<V>, Yuni::Gfx::Color::RGBA<V> >::equals(lhs, Yuni::Gfx::Color::RGBA<V>(rhs)); }
	};


	// Compare Yuni::Gfx::Color::RGB with the same type
	template<typename V>
	struct Compare< Yuni::Gfx::Color::RGB<V>, Yuni::Gfx::Color::RGB<V> >
	{
		inline static bool equals(const Yuni::Gfx::Color::RGB<V>& lhs, const Yuni::Gfx::Color::RGB<V>& rhs)
		{ return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue; }
	};

	// Compare Yuni::Gfx::Color::RGB with not the same type
	template<typename V, typename W>
	struct Compare< Yuni::Gfx::Color::RGB<V>, Yuni::Gfx::Color::RGB<W> >
	{
		inline static bool equals(const Yuni::Gfx::Color::RGB<V>& lhs, const Yuni::Gfx::Color::RGB<W>& rhs)
		{ return Compare< Yuni::Gfx::Color::RGB<V>, Yuni::Gfx::Color::RGB<V> >::equals(lhs.red, Yuni::Gfx::Color::RGB<V>(rhs)); }
	};

	// Compare Yuni::Gfx::Color::RGBA - Yuni::Gfx::Color::RGB
	template<typename V>
	struct Compare< Yuni::Gfx::Color::RGBA<V>, Yuni::Gfx::Color::RGB<V> >
	{
		inline static bool equals(const Yuni::Gfx::Color::RGBA<V>& lhs, const Yuni::Gfx::Color::RGB<V>& rhs)
		{ return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue; }
	};

	// Compare Yuni::Gfx::Color::RGB - Yuni::Gfx::Color::RGBA
	template<typename V>
	struct Compare< Yuni::Gfx::Color::RGB<V>, Yuni::Gfx::Color::RGBA<V> >
	{
		inline static bool equals(const Yuni::Gfx::Color::RGB<V>& lhs, const Yuni::Gfx::Color::RGBA<V>& rhs)
		{ return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue; }
	};


	
} // namespace Proxy
} // namespace Color
} // namespace Gfx
} // namespace Private
} // namespace Yuni

#endif // __YUNI_GFX_COLOR_PROXY_H__
