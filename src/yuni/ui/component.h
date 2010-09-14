#ifndef __YUNI_GFX_UI_COMPONENT_H__
# define __YUNI_GFX_UI_COMPONENT_H__

# include "../yuni.h"
# include "../thread/policy.h"
# include "../core/point2D.h"

namespace Yuni
{
namespace UI
{

	/*!
	** \brief Base class for all UI components
	**
	** Defines dimension and position of the component,
	** and various common behaviours.
	*/
	class IComponent : public IEventObserver<IComponent>
	{
	public:
		//! A class name is a string tag representing a type of component
		typedef CustomString<64, false, false> ClassName;
		//! Unique local identifier
		typedef sint64 ID;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Empty constructor
		*/
		IComponent() : pPosition(50, 50), pWidth(50), pHeight(50)
		{}

		/*!
		** \brief Constructor with dimensions
		*/
		IComponent(size_t width, size_t height)
			: pPosition(50, 50), pWidth(width), pHeight(height), pModified(true)
		{}

		/*!
		** \brief Full constructor
		*/
		template<typename T, typename U>
		IComponent(T x, U y, size_t width, size_t height)
			: pPosition(x, y), pWidth(width), pHeight(height), pModified(true)
		{}

		/*!
		** \brief Full constructor
		*/
		template<typename T>
		IComponent(Point2D<T>& pos, size_t width, size_t height)
			: pPosition(pos), pWidth(width), pHeight(height), pModified(true)
		{}

		//! Virtual destructor
		virtual ~IComponent() {}
		//@}


		//! \name Methods
		//@{
		/*!
		** \brief Resize the window
		**
		** This is implementation-dependent
		*/
		virtual void resize(size_t width, size_t height)
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pWidth = width;
			pHeight = height;
		}

		/*!
		** \brief Inform the component that other representations are up to date
		**
		** Once an internal representation of the component has been updated,
		** the component should not be marked "modified" anymore.
		**
		** A clever trick will be required on call to avoid losing modifications
		** due to multiple threads updating the status.
		*/
		virtual void synchronized()
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pModified = false;
		}
		//@}


		//! \name Accessors
		//@{
		/*!
		** \brief Get the class name (identifier for the type of component)
		*/
		const ClassName& className() const
		{
			return pClass;
		}

		/*!
		** \brief Get the class name (identifier for the type of component)
		*/
		virtual void className(ClassName&)
		{
			pClass.clear(); // Invalid
		}
		//@}


	protected:
		/*!
		** \brief Unique local identifier
		*/
	    ID pID;

		/*!
		** \brief Class name for this component (type of component)
		*/
		ClassName pClass;

		/*!
		** \brief Position of the component relative to its parent
		*/
		Point2D<size_t> pPosition;

		/*!
		** \brief Width of the component
		*/
		size_t pWidth;

		/*!
		** \brief Height of the component
		*/
		size_t pHeight;

		/*!
		** \brief Store if the component has been modified
		*/
		bool pModified;

	}; // class IComponent


} // namespace UI
} // namespace Yuni


#endif // __YUNI_GFX_UI_COMPONENT_H__
