#ifndef __YUNI_MISC_STL_FUNCTIONS_H__
# define __YUNI_MISC_STL_FUNCTIONS_H__

# include <algorithm>



namespace Yuni
{
namespace Misc
{

	/*!
	** \brief Functor to delete a pointer: used in automatic clearing of an STL container
	*/
	template <typename T>
	struct STLDelete
	{
		STLDelete& operator () (T* ptr)
		{
			delete ptr;
			return *this;
		}
	};



	/*!
	** \brief Syntactic sugar to free all pointers in an STL container and clear it
	*/
	template <typename T, typename U>
	void STLDeleteAndClear(U& container)
	{
		std::for_each(container.begin(), container.end(), STLDelete<T>());
		container.clear();
	}



} // Misc
} // Yuni

#endif // __YUNI_MISC_STL_FUNCTIONS_H__
