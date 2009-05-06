#ifndef __YUNI_SYSTEM_DEVICES_DISPLAY_RESOLUTION_H__
# define __YUNI_SYSTEM_DEVICES_DISPLAY_RESOLUTION_H__

# include <vector>
# include <list>
# include "../../yuni.h"
# include "../../toolbox/string.h"
# include "../../toolbox/smartptr/smartptr.h"



namespace Yuni
{
namespace System
{
namespace Devices
{
namespace Display
{
	

	/*!
	** \brief Screen/Monitor resolution
	*/
	class Resolution
	{
	public:
		//! The smallest value allowed for the width of the screen
		static const uint32 MinWidth;
		//! The highest allowed for the width of the screen
		static const uint32 MaxWidth;
		//! The smallest allowed value for the height of the screen
		static const uint32 MinHeight;
		//! The highest allowed value for the height of the screen
		static const uint32 MaxHeight;

		//! Vector of resolutions
		typedef std::vector< SmartPtr<Resolution> >  Vector;
		//! List of resolutions
		typedef std::list< SmartPtr<Resolution> >  List;

	public:
		//! \name Constructors
		//@{

		/*!
		** \brief Constructor
		** 
		** \param w Width of the monitor/screen
		** \param h Height of the monitor/screen
		** \param b Bit per Pixel
		*/
		Resolution(const uint32 w, const uint32 h, const uint8 b = 32);
		
		/*!
		** \brief Constructor by copy
		** \param c The instance to copy
		*/
		Resolution(const Resolution& c);

		//@} Constructors


		/*!
		** \brief Convert these informations into an human readable string
		*/
		String toString() const;


		//! \name Information about the current mode
		//@{

		//! The width of the monitor/screen
		uint32 width() const {return pWidth;}
		//! The height of the monitor/screen
		uint32 height() const {return pHeight;}
		//! Bit per pixel
		uint8 bitPerPixel() const {return pBitsPerPixel;}

		//@}


		//! \name Operators
		//@{

		/*!
		** \brief Comparison operator (equal with)
		**
		** \param rhs The other resolution to compare with
		** \return True if the two resolution are equal
		*/
		bool operator == (const Resolution& rhs) const
		{ return rhs.pWidth == pWidth && rhs.pHeight == pHeight && rhs.pBitsPerPixel == pBitsPerPixel; }

		/*!
		** \brief Comparison operator (non equal with)
		**
		** \param rhs The other resolution to compare with
		** \return True if the two resolution are not equal
		*/
		bool operator != (const Resolution& rhs) const {return !(*this == rhs);}

		/*!
		** \brief Comparison operator (less than)
		**
		** \param rhs The other resolution to compare with
		** \return True if *this < rhs
		*/
		bool operator < (const Resolution& rhs) const;

		/*!
		** \brief Comparison operator (less than or equal)
		**
		** \param rhs The other resolution to compare with
		** \return True if *this <= rhs
		*/
		bool operator <= (const Resolution& rhs) const
		{ return pWidth <= rhs.pWidth && pHeight <= rhs.pHeight && pBitsPerPixel <= rhs.pBitsPerPixel; }

		/*!
		** \brief Comparison operator (greater than)
		**
		** \param rhs The other resolution to compare with
		** \return True if *this > rhs
		*/
		bool operator > (const Resolution& rhs) const;

		/*!
		** \brief Comparison operator (greater than or equal)
		**
		** \param rhs The other resolution to compare with
		** \return True if *this >= rhs
		*/
		bool operator >= (const Resolution& rhs) const
		{ return pWidth >= rhs.pWidth && pHeight >= rhs.pHeight && pBitsPerPixel >= rhs.pBitsPerPixel; }

		/*!
		** \brief Assign new values from another resolution 
		**
		** \param p The new values
		** \return Always *this
		*/
		Resolution& operator = (const Resolution& p)
		{ pWidth = p.pWidth; pHeight = p.pHeight; pBitsPerPixel = p.pBitsPerPixel; return (*this); }

		//@}

		//! \name Stream printing
		//@{

		/*!
		** \brief Print the resolution
		**
		** \param[in,out] out An output stream
		** \return The output stream `out`
		*/
		std::ostream& print(std::ostream& out) const;

		//@}

	private:
		//! Height of the screen
		uint32 pWidth;
		//! Width of the screen
		uint32 pHeight;
		//! Bits per pixel
		uint8 pBitsPerPixel;

	}; // class Resolution




} // namespace Display
} // namespace Devices
} // namespace System
} // namespace Yuni



//! \name Operator overload for stream printing
//@{

inline std::ostream& operator << (std::ostream& out, const Yuni::System::Devices::Display::Resolution& rhs)
{ return rhs.print(out); }
inline std::ostream& operator << (std::ostream& out, const Yuni::SmartPtr<Yuni::System::Devices::Display::Resolution>& rhs)
{ return rhs->print(out); }


//@}


#endif // __YUNI_SYSTEM_DEVICES_DISPLAY_RESOLUTION_H__
