#ifndef __YUNI_GFX_IMAGE_H__
# define __YUNI_GFX_IMAGE_H__

# include "../yuni.h"


namespace Yuni
{
namespace Gfx
{


	/*!
	** \brief An image can be used for any kind of 2D image (texture, font, icon, ...)
	** \ingroup Gfx
	*/
	template<typename T>
	class Image
	{
	public:
		//! \name Constructors and destructors
		//@{
		Image(unsigned int width, unsigned int height);
		Image(unsigned int width, unsigned int height, T** data);
		Image(const Image& other);
		~Image();
		//@}


		//! \name Operators
		//@{
		/*!
		** \brief Comparison operator (equal with)
		**
		** \param other The other image to compare with
		** \return True if the two images have the same width, height and pixels
		*/
		bool operator == (const Image<T>& other) const;

		/*!
		** \brief Comparison operator (non equal with)
		**
		** \param other The other image to compare with
		** \return True if the two images have different width, height or pixels
		*/
		bool operator != (const Image<T>& other) const
		{ return !(*this == other); }
		//@}

		//! \name Accessors
		//@{
		//! \brief Width of the image
		unsigned int width() const { return pWidth; }
		//! \brief Height of the image
		unsigned int height() const { return pHeight; }
		/*!
		** \brief Get the actual data (pixels) of the image
		*/
		const T* const * data() const { return pData; }
		T** data() { return pData; }
		//@}

	private:
		//! Width of the image
		unsigned int pWidth;
		//! Height of the image
		unsigned int pHeight;
		//! Pixels of the image
		T** pData;

	}; // Image

} // namespace Gfx
} // namespace Yuni

# include "image.hxx"

#endif // __YUNI_GFX_IMAGE_H__
