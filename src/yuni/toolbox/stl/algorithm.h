#ifndef __YUNI_TOOLBOX_STL_ALGORITHM_H__
# define __YUNI_TOOLBOX_STL_ALGORITHM_H__

# include <algorithm>


namespace Yuni
{
namespace ToolBox
{
namespace STL
{


	/*!
	** \brief Functor to delete a pointer: used in automatic clearing of an STL container
	*/
	template <typename T>
	struct Delete
	{
		inline const Delete& operator () (T* ptr) const
		{
			delete ptr;
			return *this;
		}
	}; // class Delete



	/*!
	** \brief Syntactic sugar to free all pointers in an STL container and clear it
	*/
	template <typename T, typename U>
	inline void DeleteAndClear(U& container)
	{
		// Delete each item
		std::for_each(container.begin(), container.end(), Delete<T>());
		// Clear the container
		container.clear();
	}



} // namespace STL
} // namespace ToolBox
} // namespace Yuni


#endif // __YUNI_TOOLBOX_STL_ALGORITHM_H__
