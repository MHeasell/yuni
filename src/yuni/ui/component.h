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
		IComponent();

		/*!
		** \brief Constructor with dimensions
		*/
		IComponent(float width, float height);

		/*!
		** \brief Full constructor
		*/
		IComponent(float x, float y, float width, float height);

		/*!
		** \brief Full constructor
		*/
		template<class T>
		IComponent(const Point2D<T>& pos, float width, float height);


		//! Virtual destructor
		virtual ~IComponent();
		//@}


		//! \name Methods
		//@{
		/*!
		** \brief Resize the component
		*/
		void resize(float width, float height);
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
		** \brief Set the class name (identifier for the type of component)
		*/
		virtual void className(ClassName&)
		{
			pClass.clear(); // Invalid
		}

		//! Get the unique Identifier for this component
		ID id() const;

		/*!
		** \brief Get the width of the component
		*/
		float width() const;

		/*!
		** \brief Get the height of the component
		*/
		float height() const;

		/*!
		** \brief Get the position of the component
		*/
		Point2D<float> position() const;

		/*!
		** \brief Get the size of the component
		*/
		void size(float& width, float& height) const;

		/*!
		** \brief Get the X position of the component
		*/
		float y() const;

		/*!
		** \brief Get the Y position of the component
		*/
		float x() const;
		//@}


	protected:
		//! Protected resize, without locks
		virtual void resizeWL(float& newWidth, float& newHeight);


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
		Point2D<float> pPosition;

		/*!
		** \brief Width of the component
		*/
		float pWidth;

		/*!
		** \brief Height of the component
		*/
		float pHeight;

	}; // class IComponent





} // namespace UI
} // namespace Yuni

# include "component.hxx"

#endif // __YUNI_GFX_UI_COMPONENT_H__
