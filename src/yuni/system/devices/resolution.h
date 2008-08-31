#ifndef __YUNI_SYSTEM_DEVICES_DISPLAY_RESOLUTION_H__
# define __YUNI_SYSTEM_DEVICES_DISPLAY_RESOLUTION_H__

# include <vector>
# include <list>
# include "../../yuni.h"
# include "../../string.h"
# include "../../misc/sharedptr.h"



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
		typedef std::vector< SharedPtr<Resolution> >  Vector;
		//! List of resolutions
		typedef std::list< SharedPtr<Resolution> >  List;

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

#endif // __YUNI_SYSTEM_DEVICES_DISPLAY_RESOLUTION_H__
