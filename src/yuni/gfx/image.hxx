
#ifndef __YUNI_GFX_IMAGE_HXX__
# define __YUNI_GFX_IMAGE_HXX__

namespace Yuni
{
namespace Gfx
{

	template<typename T>
	inline
	Image<T>::Image(unsigned int width, unsigned int height) : pWidth(width), pHeight(height)
	{
		pData = new T*[width];
		for (unsigned int line = 0; line < width; ++line)
		{
			pData[line] = new T[width];
			for (unsigned int col = 0; col < height; ++col)
				pData[line][col] = T();
		}
	}

	template<typename T>
	inline
	Image<T>::Image(unsigned int width, unsigned int height, T** data) : pWidth(width), pHeight(height), pData(data)
	{
	}

	template<typename T>
	inline
	Image<T>::Image(const Image& other) : pWidth(other.width()), pHeight(other.height())
	{

	}

	template<typename T>
	Image<T>::~Image()
	{
		for (unsigned int line = 0; line < pWidth; ++line)
			delete[] pData[line];
		delete[] pData;
	}

	template<typename T>
	bool Image<T>::operator == (const Image<T>& other) const
	{
		T** data = other.data();
		if (pWidth != other.width() || pHeight != other.height())
			return false;
		for (unsigned int line = 0; line < pWidth; ++line)
			for (unsigned int col = 0; col < pHeight; ++col)
				if (pData[line][col] != data[line][col])
					return false;
		return true;
	}

} // Gfx
} // Yuni

#endif // __YUNI_GFX_IMAGE_HXX__