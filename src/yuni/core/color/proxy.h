#ifndef __YUNI__CORE_COLOR_PROXY_H__
# define __YUNI__CORE_COLOR_PROXY_H__

# include <iostream>
# include "../../yuni.h"
# include "../string.h"
# include "../math/math.h"


// On some compile, a Macro RGB is already defined
# ifdef RGB
#   undef RGB
# endif


namespace Yuni
{
namespace Color
{

	// Forward declaration
	template<typename T> class RGBA;
	template<typename T> class RGB;

} // namespace Color
} // namespace Yuni



namespace Yuni
{
namespace Private
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
		** \brief Assign the values between Yuni::Color::RGB Color Models from a single argument
		**
		** \param th The instance where assignation will be done
		** \param a1 The value
		** \return Always `th`
		*/
		static T& Assign(T& th, const U& a1);

		/*!
		** \brief Assign the values between Yuni::Color::RGB Color Models from 2 arguments
		**
		** \param th The instance where assignation will be done
		** \param a1 The value
		** \param a2 The second value
		** \return Always `th`
		*/
		static T& Assign(T& th, const U& a1, const U& a2);

		/*!
		** \brief Assign the values between Yuni::Color::RGB Color Models from 3 arguments
		**
		** \param th The instance where assignation will be done
		** \param a1 The first value
		** \param a2 The second value
		** \param a3 The third value
		** \return Always `th`
		*/
		static T& Assign(T& th, const U& a1, const U& a2, const U&a3);

		/*!
		** \brief Assign the values between Yuni::Color::RGB Color Models from 4 arguments
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


	template<typename A, typename B>
	struct Values< Yuni::Color::RGB<A>, Yuni::Color::RGBA<B> >
	{
		inline static Yuni::Color::RGB<A>& Assign(Yuni::Color::RGB<A>& th, const Yuni::Color::RGBA<B>& a1)
		{
			return th.assign(a1.red, a1.green, a1.blue);
		}

		inline static Yuni::Color::RGB<A>& Inc(Yuni::Color::RGB<A>& to, const Yuni::Color::RGBA<B>& inc)
		{
			return (to += Yuni::Color::RGB<A>(inc));
		}

	};

	template<typename A, typename B>
	struct Values< Yuni::Color::RGBA<A>, Yuni::Color::RGB<B> >
	{
		inline static Yuni::Color::RGBA<A>& Assign(Yuni::Color::RGBA<A>& th, const Yuni::Color::RGB<B>& a1)
		{
			return th.assign(a1.red, a1.green, a1.blue);
		}

		inline static Yuni::Color::RGBA<A>& Inc(Yuni::Color::RGBA<A>& to, const Yuni::Color::RGB<B>& inc)
		{
			return (to += Yuni::Color::RGBA<A>(inc));
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




    // When sent into a stream, char and unsigned char must be cast into int
    template<class T>
    struct Cast { typedef T Type; };
    template<>
    struct Cast<sint8> { typedef int Type; };
    template<>
    struct Cast<uint8> { typedef unsigned int Type; };



	template<typename S>
	struct Streamer< Yuni::Color::RGBA<S> >
	{
		inline static std::ostream& toOStream(std::ostream& out, const Yuni::Color::RGBA<S>& th)
		{
			out <<  "r:" << (typename Cast<S>::Type) (th.red)
				<< ",g:" << (typename Cast<S>::Type) (th.green)
				<< ",b:" << (typename Cast<S>::Type) (th.blue)
				<< ",a:" << (typename Cast<S>::Type) (th.alpha)
				;
			return out;
		}

		inline static String toString(const Yuni::Color::RGBA<S>& th)
		{
			return String()
                <<  "r:" << (typename Cast<S>::Type) (th.red)
				<< ",g:" << (typename Cast<S>::Type) (th.green)
				<< ",b:" << (typename Cast<S>::Type) (th.blue)
				<< ",a:" << (typename Cast<S>::Type) (th.alpha)
				;
		}
	};


	template<typename S>
	struct Streamer< Yuni::Color::RGB<S> >
	{
		inline static std::ostream& toOStream(std::ostream& out, const Yuni::Color::RGB<S>& th)
		{
			out <<  "r:" << (typename Cast<S>::Type) (th.red)
				<< ",g:" << (typename Cast<S>::Type) (th.green)
				<< ",b:" << (typename Cast<S>::Type) (th.blue)
				;
			return out;
		}

		inline static String toString(const Yuni::Color::RGB<S>& th)
		{
			return String()
                <<  "r:" << (typename Cast<S>::Type) (th.red)
				<< ",g:" << (typename Cast<S>::Type) (th.green)
				<< ",b:" << (typename Cast<S>::Type) (th.blue)
				;

		}
	}; // class Streamer








	template<typename T, typename U>
	struct Compare
	{
		/*!
		** \brief Test if two Color models are equal
		*/
		static bool equals(const T& lhs, const U& rhs);
	};

	// Compare Yuni::Color::RGBA with the same type
	template<typename V>
	struct Compare< Yuni::Color::RGBA<V>, Yuni::Color::RGBA<V> >
	{
		inline static bool equals(const Yuni::Color::RGBA<V>& lhs, const Yuni::Color::RGBA<V>& rhs)
		{ return Math::Equals(lhs.red, rhs.red) && Math::Equals(lhs.green, rhs.green) && Math::Equals(lhs.blue, rhs.blue) && Math::Equals(lhs.alpha, rhs.alpha); }
	};

	// Compare Yuni::Color::RGBA with not the same type
	template<typename V, typename W>
	struct Compare< Yuni::Color::RGBA<V>, Yuni::Color::RGBA<W> >
	{
		inline static bool equals(const Yuni::Color::RGBA<V>& lhs, const Yuni::Color::RGBA<W>& rhs)
		{ return Compare< Yuni::Color::RGBA<V>, Yuni::Color::RGBA<V> >::equals(lhs, Yuni::Color::RGBA<V>(rhs)); }
	};


	// Compare Yuni::Color::RGB with the same type
	template<typename V>
	struct Compare< Yuni::Color::RGB<V>, Yuni::Color::RGB<V> >
	{
		inline static bool equals(const Yuni::Color::RGB<V>& lhs, const Yuni::Color::RGB<V>& rhs)
		{ return Math::Equals(lhs.red, rhs.red) && Math::Equals(lhs.green, rhs.green) && Math::Equals(lhs.blue, rhs.blue); }
	};

	// Compare Yuni::Color::RGB with not the same type
	template<typename V, typename W>
	struct Compare< Yuni::Color::RGB<V>, Yuni::Color::RGB<W> >
	{
		inline static bool equals(const Yuni::Color::RGB<V>& lhs, const Yuni::Color::RGB<W>& rhs)
		{ return Compare< Yuni::Color::RGB<V>, Yuni::Color::RGB<V> >::equals(lhs.red, Yuni::Color::RGB<V>(rhs)); }
	};

	// Compare Yuni::Color::RGBA - Yuni::Color::RGB
	template<typename V>
	struct Compare< Yuni::Color::RGBA<V>, Yuni::Color::RGB<V> >
	{
		inline static bool equals(const Yuni::Color::RGBA<V>& lhs, const Yuni::Color::RGB<V>& rhs)
		{ return Math::Equals(lhs.red, rhs.red) && Math::Equals(lhs.green, rhs.green) && Math::Equals(lhs.blue, rhs.blue); }
	};

	// Compare Yuni::Color::RGB - Yuni::Color::RGBA
	template<typename V>
	struct Compare< Yuni::Color::RGB<V>, Yuni::Color::RGBA<V> >
	{
		inline static bool equals(const Yuni::Color::RGB<V>& lhs, const Yuni::Color::RGBA<V>& rhs)
		{ return Math::Equals(lhs.red, rhs.red) && Math::Equals(lhs.green, rhs.green) && Math::Equals(lhs.blue, rhs.blue); }
	};






} // namespace Proxy
} // namespace Color
} // namespace Private
} // namespace Yuni

#endif // __YUNI__CORE_COLOR_PROXY_H__
