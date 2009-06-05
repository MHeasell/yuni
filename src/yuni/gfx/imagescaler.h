#ifndef __YUNI_GFX_IMAGE_SCALER_H__
# define __YUNI_GFX_IMAGE_SCALER_H__

# include <vector>
# include "core/color/rgba.h"

namespace Yuni
{
namespace Gfx
{
	/*!
	** \brief An image scaler is able to scale twice an image
	**
	** This is an abstract class.
	** \ingroup Gfx
	*/
	class ImageScaler
	{
	public:
		//! \name Constructors and destructors
		//@{
		/*!
		** \brief Default constructor
		*/
		ImageScaler()
		{}
		//@}

		//! \name Scaling methods
		//@{
		/*!
		** \brief Use the standard naive Nearest Neighbour algorithm
		*/
		template<typename T>
		T** NearestNeighbour(const T* const* const image, uint32 width, uint32 height) const
		{
			// Allocate the data
			T** scaled = new T*[width * 2];
			for (uint32 line = 0; line < width * 2; ++line)
				scaled[line] = new T[height * 2];
			// Loop on lines
			for (unsigned int line = 0; line < width; ++line)
				// Loop on columns
				for (unsigned int col = 0; col < height; ++col)
				{
					// All four new pixels have the same identical colour as the original pixel
					scaled[line * 2    ][col * 2    ] = image[line][col];
					scaled[line * 2    ][col * 2 + 1] = image[line][col];
					scaled[line * 2 + 1][col * 2    ] = image[line][col];
					scaled[line * 2 + 1][col * 2 + 1] = image[line][col];
				}
			return scaled;
		}

		/*!
		** \brief Use the standard naive Nearest Neighbour algorithm
		*/
		template<template<typename T> class C, typename U>
		C<U> NearestNeighbour(const C<U> image, uint32 width, uint32 height) const
		{
			return C<U>(width * 2, height * 2, NearestNeighbour(image.data(), width, height));
		}

		/*!
		** \brief Use the Scale2X algorithm developed for AdvancedMame
		*/
		template<typename T>
		T** Scale2X(T** image, uint32 width, uint32 height) const
		{
			// Allocate the data
			T** scaled = new T*[width * 2];
			for (unsigned int line = 0; line < width * 2; ++line)
				scaled[line] = new T[height * 2];
			// Loop on lines
			for (unsigned int line = 0; line < width; ++line)
				// Loop on columns
				for (unsigned int col = 0; col < height; ++col)
				{
					bool LeftBorder = (line <= 0);
					bool RightBorder = (line >= width - 1);
					bool TopBorder = (col <= 0);
					bool BottomBorder = (col >= height - 1);
					// The Scale2X algorithm cleans diagonals
					// If the two old neighbours of a new pixel are the same colour, this colour is chosen
					if (!LeftBorder && !TopBorder && image[line - 1][col] == image[line][col - 1])
						scaled[line * 2    ][col * 2    ] = image[line - 1][col];
					else
						scaled[line * 2    ][col * 2    ] = image[line][col];
					if (!RightBorder && !TopBorder && image[line + 1][col] == image[line][col + 1])
						scaled[line * 2    ][col * 2 + 1] = image[line - 1][col];
					else
						scaled[line * 2    ][col * 2 + 1] = image[line][col];
					if (!LeftBorder && !BottomBorder && image[line - 1][col] == image[line][col + 1])
						scaled[line * 2 + 1][col * 2    ] = image[line + 1][col];
					else
						scaled[line * 2 + 1][col * 2    ] = image[line][col];
					if (!RightBorder && !BottomBorder && image[line + 1][col] == image[line][col + 1])
						scaled[line * 2 + 1][col * 2    ] = image[line + 1][col];
					else
						scaled[line * 2 + 1][col * 2 + 1] = image[line][col];
				}
			return scaled;
		}
		//@}

	}; // ImageScaler


} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_IMAGE_SCALER_H__
