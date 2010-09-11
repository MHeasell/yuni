#ifndef __YUNI_GFX_CORE_COLOR_RGBA_H__
# define __YUNI_GFX_CORE_COLOR_RGBA_H__

# include "proxy.h"


namespace Yuni
{
namespace Color
{


	/*!
	** \brief 32Bits RGB Color Model with alpha channel (Additive color model + transparency)
	** \ingroup ColorModels
	*/
	template<typename T>
	class RGBA
	{
	public:
		//! \name Constructors
		//@{
		//! Default Constructor
		RGBA() : red(), green(), blue(), alpha() {}

		/*!
		** \brief Constructor by copy
		*/
		template<typename U>
		RGBA(const U& c) {Private::Color::Proxy::Values< RGBA<T> , U >::Assign(*this, c);}

		/*!
		** \brief Constructor with default color components
		**
		** \param r The default value for the `red` channel
		** \param g The default value for the `green` channel
		** \param b The default value for the `blue` channel
		*/
		template<typename U>
		RGBA(const U& r, const U& g, const U& b)
		{ Private::Color::Proxy::Values< RGBA<T>, U >::Assign(*this, r, g, b); }

		/*!
		** \brief Constructor with default color components
		**
		** \param r The default value for the `red` channel
		** \param g The default value for the `green` channel
		** \param b The default value for the `blue` channel
		** \param a The default value for the `alpha` channel
		*/
		template<typename U>
		RGBA(const U& r, const U& g, const U& b, const U& a)
		{Private::Color::Proxy::Values< RGBA<T>, U >::Assign(*this, r, g, b, a);}
		//@}


		/*!
		** \brief Get if the color is visible (merely if the color is completely transparent)
		*/
		bool visible() const {return alpha != 0;}


		//! \name Reset Values
		//@{
		/*!
		** \brief Reset all color components
		**
		** \param rhs The new values
		** \return Always `*this`
		*/
		template<typename U>
		RGBA<T>& assign(const U& rhs)  { return Private::Color::Proxy::Values< RGBA<T>, U >::Assign(*this, rhs); }

		/*!
		** \brief Reset all color components
		**
		** \param r The new color component `red`
		** \param g The new color component `green`
		** \param b The new color component `blue`
		** \return Always `*this`
		*/
		template<typename U>
		RGBA<T>& assign(const U& r, const U& g, const U& b)
		{ return Private::Color::Proxy::Values< RGBA<T>, U >::Assign(*this, r, g, b); }

		/*!
		** \brief Reset all color components
		**
		** \param r The new color component `red`
		** \param g The new color component `green`
		** \param b The new color component `blue`
		** \param a The new color component `alpha`
		** \return Always `*this`
		*/
		template<typename U>
		RGBA<T>& assign(const U& r, const U& g, const U& b, const U& a)
		{ return Private::Color::Proxy::Values< RGBA<T>, U >::Assign(*this, r, g, b, a); }
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
		RGBA<T>& operator () (const U& rhs)
		{ return Private::Color::Proxy::Values< RGBA<T>, U >::Assign(*this, rhs); }


		/*!
		** \brief Reset all color components
		**
		** \param r The new color component `red`
		** \param g The new color component `green`
		** \param b The new color component `blue`
		** \param a The new color component `alpha`
		** \return Always `*this`
		*/
		template<typename U>
		RGBA<T>& operator () (const U& r, const U& g, const U& b, const U& a)
		{ return Private::Color::Proxy::Values< RGBA<T>, U >::Assign(r, g, b, a); }

		/*!
		** \brief Increase all color components
		**
		** \param rhs Value to add to all colors components
		** \return Always *this
		*/
		template<typename U>
		RGBA<T>& operator += (const U& rhs) { return Private::Color::Proxy::Values< RGBA<T>, U >::Inc(*this, rhs);}


		template<typename U>
		bool operator == (const U& rhs) const {return Private::Color::Proxy::Compare< RGBA<T> , U >::equals(*this, rhs);}

		bool operator != (const RGBA<T>& rhs) const
		{ return !(*this == rhs); }

		/*!
		** \brief Assign new values from an another RGBA class
		** \param rhs The new values
		** \return Always *this
		*/
		template<typename U> RGBA<T>& operator = (const U& rhs)
		{ return Private::Color::Proxy::Values< RGBA<T> , U >::Assign(*this, rhs); }
		//@}


		/*!
		** \brief Print the RGBA Value
		*/
		std::ostream& print(std::ostream& out) const { return Private::Color::Proxy::Streamer< RGBA<T> >::toOStream(out, *this); }

		/*!
		** \brief Convert the RGBA value into a human readable string
		*/
		String toString() const { return Private::Color::Proxy::Streamer< RGBA<T> >::toString(*this); }

	public:
		//! The red channel
		T red;
		//! The green channel
		T green;
		//! The blue channel
		T blue;
		//! The alpha channel
		T alpha;

	}; // class RGBA





} // namespace Color
} // namespace Yuni





//! name Operator overload for stream printing
//@{
template<typename T>
inline std::ostream& operator << (std::ostream& out, const Yuni::Color::RGBA<T>& p)
{ return p.print(out); }

template<typename T>
inline const Yuni::Color::RGBA<T> operator + (const Yuni::Color::RGBA<T>& lhs, const Yuni::Color::RGBA<T>& rhs)
{ return Yuni::Color::RGBA<T>(lhs) += rhs; }
//@}


#endif // __YUNI_GFX_CORE_COLOR_RGBA_H__
