#ifndef __YUNI_USER_INTERFACE_COMPONENT_H__
# define __YUNI_USER_INTERFACE_COMPONENT_H__

# include <yuni/yuni.h>
# include <yuni/gfx/point2d.h>
# include <vector>
# include <yuni/gfx/ui/window.h>
# include <yuni/string.h>
# include <yuni/misc/sharedptr.h>



namespace Yuni
{
namespace Gfx
{
namespace UI
{

	class Window;

	class Component
	{
	public:
		/*!
		** \brief Component List
		*/
		class Items
		{
		public:
			//! \name Constructor & Destructor
			//@{
			//! Default constructor
			Items();
			//! Destructor
			~Items();
			//@}

			/*!
			** \brief Add a component in the list
			*/
			void add(Component* c);

			/*!
			** \brief Remove
			*/
			void remove(Component* c);

			/*!
			** \brief Clear all sub components
			*/
			void clear();

			/*!
			** \brief Get if a component is already in the list
			*/
			bool exists(Component* c);

			/*!
			** \brief Get the size of the list
			*/
			uint32 size() const {return pList.size();}

		private:
			typedef std::vector<Component*> List;
			List pList;

		}; // class Items


	public:
		//! \name Constructor & Destructor
		//@{

		/*!
		** \brief Constructor
		**
		** \param wnd The parent window
		** \param o The parent component, if any
		*/
		Component(Window& wnd, Component* o = NULL);

		//! Destructor
		virtual ~Component();

		//@}


		//! The owner of this component
		Component* owner() const {return pOwner;}

		//! The position of the component
		const Point2D<int>& position() const {return pPosition;}
		Point2D<int>& position() {return pPosition;}

		//! The dimension
		const Point2D<int> size() const {return pSize;}
		Point2D<int> size() {return pSize;}

		//! Name of the component
		const String& name() const {return pName;}
		void name(const String& n);

		//! All sub-components
		Items items;


	protected:
		//! The parent window
		Window& pWindow;
		//! The owner of this component
		Component* pOwner;
		//! Name of the component
		String pName;
		//! Position
		Point2D<int> pPosition;
		//! Size
		Point2D<int> pSize;

	}; // class Component




} // namespace UI
} // namespace Gfx
} // namespace Yuni

#endif // __YUNI_USER_INTERFACE_COMPONENT_H__
