#ifndef __YUNI_CORE_EVENT_EVENT_DECLARATION_H__
# define __YUNI_CORE_EVENT_EVENT_DECLARATION_H__

# include <vector>
# include <list>
# include "../preprocessor/enum.h"




# define YUNI_EVENT_FRIEND_DECL_E(N) \
	template<class YUNI_JOIN(R,N), YUNI_ENUM(N, class U_ ## N),\
		template<class> class YUNI_JOIN(TP,N)> friend class YUNI_JOIN(E,N)


# define YUNI_EVENT_ALLFRIEND_DECL_E \
	template<class R0, template<class> class TP0> friend class E0; \
	YUNI_EVENT_FRIEND_DECL_E(1);\
	YUNI_EVENT_FRIEND_DECL_E(2);\
	YUNI_EVENT_FRIEND_DECL_E(3);\
	YUNI_EVENT_FRIEND_DECL_E(4);\
	YUNI_EVENT_FRIEND_DECL_E(5);\
	YUNI_EVENT_FRIEND_DECL_E(6);\
	YUNI_EVENT_FRIEND_DECL_E(7);\
	YUNI_EVENT_FRIEND_DECL_E(8);\
	YUNI_EVENT_FRIEND_DECL_E(9);\
	YUNI_EVENT_FRIEND_DECL_E(10);\
	YUNI_EVENT_FRIEND_DECL_E(11);\
	YUNI_EVENT_FRIEND_DECL_E(12);\




namespace Yuni
{
namespace Event
{

	class IEvent;

	class IObserver;

	template<class D, template<class> class TP> class Observer;



# define YUNI_EVENT_FORWARD_DECL_E(N) \
	template<class R, YUNI_ENUM(N, class A), template<class> class TP = Policy::ObjectLevelLockable> class YUNI_JOIN(E,N)

	template<class R = void, template<class> class TP = Policy::ObjectLevelLockable> class E0;
	YUNI_EVENT_FORWARD_DECL_E(1);
	YUNI_EVENT_FORWARD_DECL_E(2);
	YUNI_EVENT_FORWARD_DECL_E(3);
	YUNI_EVENT_FORWARD_DECL_E(4);
	YUNI_EVENT_FORWARD_DECL_E(5);
	YUNI_EVENT_FORWARD_DECL_E(6);
	YUNI_EVENT_FORWARD_DECL_E(7);
	YUNI_EVENT_FORWARD_DECL_E(8);
	YUNI_EVENT_FORWARD_DECL_E(9);
	YUNI_EVENT_FORWARD_DECL_E(10);
	YUNI_EVENT_FORWARD_DECL_E(11);
	YUNI_EVENT_FORWARD_DECL_E(12);

# undef YUNI_EVENT_FORWARD_DECL_E


} // namespace Event
} // namespace Yuni

#endif // __YUNI_CORE_EVENT_EVENT_DECLARATION_H__
