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
		template<typename T>
		T* NearestNeighbour(const T* const image, uint32 width, uint32 height) const
		{
			// Allocate the data
			T* scaled = new T[width * height * 4];
			// Loop on lines
			for (unsigned int line = 0; line < width; ++line)
				// Loop on columns
				for (unsigned int col = 0; col < height; ++col)
				{
					// All four new pixels have the same identical colour as the original pixel
					T color = image[line * width + col];
					scaled[line * width * 4 + col * 2] = color;
					scaled[line * width * 4 + col * 2 + 1] = color;
					scaled[(line * 2 + 1) * width * 2 + col * 2] = color;
					scaled[(line * 2 + 1) * width * 2 + col * 2 + 1] = color;
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
		** \brief Use the Scale2X / AdvMAME2x algorithm
		**
		** EPX / Scale2X / AdvMAME2x:
		**   A    --\ 1 2
		** C P B  --/ 3 4
		**   D
		**  1=P, 2=P, 3=P, 4=P
		**  IF C == A AND C != D AND A != B => 1=A
		**  IF A == B AND A != C AND B != D => 2=B
		**  IF B == D AND B != A AND D != C => 4=D
		**  IF D == C AND D != B AND C != A => 3=C
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
					bool LeftBorder = (col <= 0);
					bool RightBorder = (col >= width - 1);
					bool TopBorder = (line <= 0);
					bool BottomBorder = (line >= height - 1);
					bool AeqB = (!RightBorder && !TopBorder && image[line - 1][col] == image[line][col + 1]);
					bool AeqC = (!LeftBorder && !TopBorder && image[line - 1][col] == image[line][col - 1]);
					bool BeqD = (!RightBorder && !BottomBorder && image[line][col + 1] == image[line + 1][col]);
					bool CeqD = (!LeftBorder && !BottomBorder && image[line][col - 1] == image[line + 1][col]);
					// The Scale2X algorithm cleans diagonals
					// If the two old neighbours of a new pixel are the same colour, this colour is chosen
					// However, if three neighbours have the same colour, do not change the colour

					// Top-left pixel
					if (AeqC && !AeqB && !CeqD)
						scaled[line * 2    ][col * 2    ] = image[line - 1][col]; // A equals C, use A
					else
						scaled[line * 2    ][col * 2    ] = image[line    ][col]; // Nearest neighbour colour

					// Top-right pixel
					if (AeqB && !AeqC && !BeqD)
						scaled[line * 2    ][col * 2 + 1] = image[line - 1][col]; // A equals B, use A
					else
						scaled[line * 2    ][col * 2 + 1] = image[line    ][col]; // Nearest neighbour colour

					// Bottom-left pixel
					if (CeqD && !AeqC && !BeqD)
						scaled[line * 2 + 1][col * 2    ] = image[line + 1][col]; // C equals D, use D
					else
						scaled[line * 2 + 1][col * 2    ] = image[line    ][col]; // Nearest neighbour colour

					// Bottom-right pixel
					if (BeqD && !AeqB && !CeqD)
						scaled[line * 2 + 1][col * 2    ] = image[line + 1][col]; // B equals D, use D
					else
						scaled[line * 2 + 1][col * 2 + 1] = image[line    ][col]; // Nearest neighbour colour
				}
			return scaled;
		}

		/*!
		** \brief Use the Eagle algorithm developed by Dirk Stevens
		**
		** Eagle:
		** S T U  --\ 1 2
		** V P W  --/ 3 4
		** X Y Z
		**  1=P, 2=P, 3=P, 4=P
		**  IF V == S == T => 1=S
		**  IF T == U == W => 2=U
		**  IF V == X == Y => 3=X
		**  IF W == Z == Y => 4=Z
		*/
		template<typename T>
		T** Eagle(T** image, uint32 width, uint32 height) const
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
					bool LeftBorder = (col <= 0);
					bool RightBorder = (col >= width - 1);
					bool TopBorder = (line <= 0);
					bool BottomBorder = (line >= height - 1);

					// T == V && T == S
					if (!LeftBorder && !TopBorder
						&& image[line - 1][col] == image[line][col - 1]
						&& image[line - 1][col] == image[line - 1][col - 1])
						scaled[line * 2    ][col * 2    ] = image[line - 1][col]; // Use T
					else
						scaled[line * 2    ][col * 2    ] = image[line][col]; // Nearest neighbour colour
					// T == W && T == U
					if (!RightBorder && !TopBorder
						&& image[line - 1][col] == image[line][col + 1]
						&& image[line - 1][col] == image[line - 1][col + 1])
						scaled[line * 2    ][col * 2 + 1] = image[line - 1][col]; // Use T
					else
						scaled[line * 2    ][col * 2 + 1] = image[line][col]; // Nearest neighbour colour
					// V == X && V == Y
					if (!LeftBorder && !BottomBorder
						&& image[line][col - 1] == image[line + 1][col - 1]
						&& image[line][col - 1] == image[line + 1][col])
						scaled[line * 2 + 1][col * 2    ] = image[line][col - 1]; // Use V
					else
						scaled[line * 2 + 1][col * 2    ] = image[line][col]; // Nearest neighbour colour
					// W == Y && W == Z
					if (!RightBorder && !BottomBorder
						&& image[line][col + 1] == image[line + 1][col]
						&& image[line][col + 1] == image[line + 1][col + 1])
						scaled[line * 2 + 1][col * 2    ] = image[line][col + 1]; // Use W
					else
						scaled[line * 2 + 1][col * 2 + 1] = image[line][col]; // Nearest neighbour colour
				}
			return scaled;
		}

		//@}

	}; // ImageScaler


} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_GFX_IMAGE_SCALER_H__
