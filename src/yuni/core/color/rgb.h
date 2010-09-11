#ifndef __YUNI__CORE_COLOR_RGB_H__
# define __YUNI__CORE_COLOR_RGB_H__

# include "../../yuni.h"
# include "proxy.h"


namespace Yuni
{
namespace Color
{


	/*!
	** \brief 32Bits RGB Color Model (Additive color model)
    **
	** \ingroup ColorModels
	*/
	template<typename T>
	class RGB
	{
	public:
		//! \name Constructors
		//@{
		//! Default Constructor
		RGB() : red(), green(), blue() {}

		/*!
		** \brief Constructor by copy
		*/
		template<typename U>
		RGB(const U& c) {Private::Color::Proxy::Values< RGB<T> , U >::Assign(*this, c);}

		/*!
		** \brief Constructor with default color components
		**
		** \param r The default value for the `red` channel
		** \param g The default value for the `green` channel
		** \param b The default value for the `blue` channel
		*/
		template<typename U>
		RGB(const U& r, const U& g, const U& b)
		{ Private::Color::Proxy::Values< RGB<T>, U >::Assign(*this, r, g, b); }

		/*!
		** \brief Constructor with default color components
		**
		** \param r The default value for the `red` channel
		** \param g The default value for the `green` channel
		** \param b The default value for the `blue` channel
		*/
		template<typename U>
		RGB(const U& r, const U& g, const U& b, const U& /*a*/)
		{Private::Color::Proxy::Values< RGB<T>, U >::Assign(*this, r, g, b);}
		//@}


		/*!
		** \brief Get if the color is visible (merely if the color is completely transparent)
		*/
		bool visible() const {return true;}


		//! \name Reset Values
		//@{
		/*!
		** \brief Reset all color components
		**
		** \param rhs The new values
		** \return Always `*this`
		*/
		template<typename U>
		RGB<T>& assign(const U& rhs)  { return Private::Color::Proxy::Values< RGB<T>, U >::Assign(*this, rhs); }

		/*!
		** \brief Reset all color components
		**
		** \param r The new color component `red`
		** \param g The new color component `green`
		** \param b The new color component `blue`
		** \return Always `*this`
		*/
		template<typename U>
		RGB<T>& assign(const U& r, const U& g, const U& b)
		{ return Private::Color::Proxy::Values< RGB<T>, U >::Assign(*this, r, g, b); }

		/*!
		** \brief Reset all color components
		**
		** \param r The new color component `red`
		** \param g The new color component `green`
		** \param b The new color component `blue`
		** \return Always `*this`
		*/
		template<typename U>
		RGB<T>& assign(const U& r, const U& g, const U& b, const U& /*a*/)
		{ return Private::Color::Proxy::Values< RGB<T>, U >::Assign(*this, r, g, b); }
		//@}


		//! \name Operators
		//@{
		/*!
		** \brief Reset all color components
		**
		** \param rhs The new values
		** \return Always `*this`
		*/
		template<typename U>
		RGB<T>& operator () (const U& rhs)
		{ return Private::Color::Proxy::Values< RGB<T>, U >::Assign(*this, rhs); }


		/*!
		** \brief Reset all color components
		**
		** \param r The new color component `red`
		** \param g The new color component `green`
		** \param b The new color component `blue`
		** \return Always `*this`
		*/
		template<typename U>
		RGB<T>& operator () (const U& r, const U& g, const U& b, const U& /*a*/)
		{ return Private::Color::Proxy::Values< RGB<T>, U >::Assign(r, g, b); }

		/*!
		** \brief Increase all color components
		**
		** \param rhs Value to add to all colors components
		** \return Always *this
		*/
		template<typename U>
		RGB<T>& operator += (const U& rhs) { return Private::Color::Proxy::Values< RGB<T>, U >::Inc(*this, rhs);}


		template<typename U>
		bool operator == (const U& rhs) const {return Private::Color::Proxy::Compare< RGB<T> , U >::equals(*this, rhs);}

		bool operator != (const RGB<T>& rhs) const
		{ return !(*this == rhs); }

		/*!
		** \brief Assign new values from an another RGBA class
		** \param rhs The new values
		** \return Always *this
		*/
		template<typename U> RGB<T>& operator = (const U& rhs)
		{ return Private::Color::Proxy::Values< RGB<T> , U >::Assign(*this, rhs); }
		//@}


		/*!
		** \brief Print the RGBA Value
		*/
		std::ostream& print(std::ostream& out) const { return Private::Color::Proxy::Streamer< RGB<T> >::toOStream(out, *this); }

		/*!
		** \brief Convert the RGBA value into a human readable string
		*/
		String toString() const { return Private::Color::Proxy::Streamer< RGB<T> >::toString(*this); }

	public:
		//! The red channel
		T red;
		//! The green channel
		T green;
		//! The blue channel
		T blue;

	}; // class RGB




} // namespace Color
} // namespace Yuni





//! name Operator overload for stream printing
//@{
template<typename T>
inline std::ostream& operator << (std::ostream& out, const Yuni::Color::RGB<T>& p)
{ return p.print(out); }

template<typename T>
inline const Yuni::Color::RGB<T> operator + (const Yuni::Color::RGB<T>& lhs, const Yuni::Color::RGB<T>& rhs)
{ return Yuni::Color::RGB<T>(lhs) += rhs; }
//@}


#endif // __YUNI__CORE_COLOR_RGB_H__
