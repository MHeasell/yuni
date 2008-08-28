
# include <yuni/yuni.h>
# include <yuni/gfx/point2d.h>
# include <yuni/gfx/ui/component.h>


namespace Yuni
{
namespace Gfx
{
namespace UI
{

	Component::Component(Window& wnd, Component* o)
		:pWindow(wnd), pOwner(o)
	{
		if (o)
			o->items.add(this);
	}

	Component::~Component()
	{
		items.clear();
		if (pOwner)
			pOwner->items.remove(this);
		pWindow.unregisterComponent(this);
	}

	void Component::name(const String& n)
	{
		pWindow.unregisterComponent(this);
		pName = n;
		pWindow.registerComponent(this);
	}



	Component::Items::Items()
		:pList()
	{}

	Component::Items::~Items()
	{
		// clear();  Already done by Component::~Component
	}


	void Component::Items::add(Component* c)
	{
		if (c && !this->exists(c))
			pList.push_back(c);
	}

	void Component::Items::remove(Component* c)
	{
		if (c)
		{
			for (List::iterator i = pList.begin(); i != pList.end(); ++i)
			{
				if (c == *i)
				{
					delete *i;
					pList.erase(i);
					return;
				}
			}
		}
	}


	bool Component::Items::exists(Component* c)
	{
		if (c)
		{
			for (List::const_iterator i = pList.begin(); i != pList.end(); ++i)
			{
				if (c == *i)
					return true;
			}
		}
		return false;
	}


	void Component::Items::clear()
	{
		for (List::iterator i = pList.begin(); i != pList.end(); ++i)
			delete *i;
		pList.clear();
	}



} // namespace UI
} // namespace Gfx
} // namespace Yuni


