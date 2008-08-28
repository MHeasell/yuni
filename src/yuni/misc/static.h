#ifndef __YUNI_MISC_STATIC_IF_H__
# define __YUNI_MISC_STATIC_IF_H__


namespace Yuni
{
namespace Static
{

	namespace Remove
	{
		template <typename T> struct Reference { typedef T t; };
		template <typename T> struct Reference<T&> { typedef T t; };
		template <typename T> struct Reference<const T&> { typedef const T t; };


		template <typename T> struct Const { typedef T t; };
		template <typename T> struct Const<const T> { typedef T t; };

	} // namespace Remove



	template <bool b, typename IfTrue, typename IfFalse>
	struct If
	{
		typedef IfTrue t;
		typedef typename Remove::Const<typename Remove::Reference<IfTrue>::t>::t  RetTrue;
		typedef typename Remove::Const<typename Remove::Reference<IfFalse>::t>::t RetFalse;

		static RetTrue& choose (RetTrue& tr, RetFalse&)
		{return tr;}
		
		static const RetTrue& choose (const RetTrue& tr, const RetFalse&)
		{ return tr; }
	};

	template <typename IfTrue, typename IfFalse>
	struct If<false, IfTrue, IfFalse>
	{
		typedef IfFalse t;
		typedef typename Remove::Const<typename Remove::Reference<IfTrue>::t>::t  RetTrue;
		typedef typename Remove::Const<typename Remove::Reference<IfFalse>::t>::t RetFalse;

		static RetFalse& choose (RetTrue&, RetFalse& fa)
		{ return fa; }
		
		static const RetFalse& choose (const RetTrue&, const RetFalse& fa)
		{ return fa; }
	};

} // namespace Static
} // namespaec Yuni

#endif // __YUNI_MISC_STATIC_IF_H__
