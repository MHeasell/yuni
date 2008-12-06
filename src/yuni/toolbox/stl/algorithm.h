#ifndef __YUNI_TOOLBOX_STL_ALGORITHM_H__
# define __YUNI_TOOLBOX_STL_ALGORITHM_H__

# include <algorithm>
# include "../static.h"


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
	**
	** \code
	** typedef std::vector<int> List;
	** List list;
	** Yuni::ToolBox::STL::DeleteAndClear<int, List>(list);
	** \endcode
	*/
	template <typename T, typename U>
	inline void DeleteAndClear(U& container)
	{
		// The original type
		typedef typename Static::Remove::All<T>::Type Type;

		// Delete each item
		std::for_each(container.begin(), container.end(), Delete<Type>());
		// Clear the container
		container.clear();
	}



} // namespace STL
} // namespace ToolBox
} // namespace Yuni


#endif // __YUNI_TOOLBOX_STL_ALGORITHM_H__
