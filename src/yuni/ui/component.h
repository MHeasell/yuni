#ifndef __YUNI_UI_COMPONENT_H__
# define __YUNI_UI_COMPONENT_H__

# include "../yuni.h"
# include "../core/smartptr.h"
# include "../core/event.h"
# include "../thread/policy.h"
# include "../core/point2D.h"
# include "../core/customstring.h"

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
	class IComponent
		: public IEventObserver<IComponent, Policy::ObjectLevelLockable>
	{
	public:
		template <class T>
		struct SmartPtrInfo
		{
			typedef SmartPtr<T> Type;
		};

		typedef SmartPtrInfo<IComponent>::Type  Ptr;

		//! Ancestor type
		typedef IEventObserver<IComponent, Policy::ObjectLevelLockable> EventObserverType;
		//! Threading policy
		typedef EventObserverType::ThreadingPolicy ThreadingPolicy;

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
		IComponent(unsigned int width, unsigned int height)
			: pPosition(50, 50), pWidth(width), pHeight(height)
		{}

		/*!
		** \brief Full constructor
		*/
		IComponent(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
			: pPosition(x, y), pWidth(width), pHeight(height)
		{}

		/*!
		** \brief Full constructor
		*/
		template<typename T>
		IComponent(Point2D<T>& pos, unsigned int width, unsigned int height)
			: pPosition(pos), pWidth(width), pHeight(height)
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
		virtual void resize(unsigned int width, unsigned int height)
		{
			ThreadingPolicy::MutexLocker lock(*this);
			pWidth = width;
			pHeight = height;
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
		Point2D<unsigned int> pPosition;

		/*!
		** \brief Width of the component
		*/
		unsigned int pWidth;

		/*!
		** \brief Height of the component
		*/
		unsigned int pHeight;

	}; // class IComponent





} // namespace UI
} // namespace Yuni


#endif // __YUNI_GFX_UI_COMPONENT_H__
