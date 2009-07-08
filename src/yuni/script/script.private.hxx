#ifndef __YUNI_SCRIPT_SCRIPT_PRIVATE_HXX__
# define __YUNI_SCRIPT_SCRIPT_PRIVATE_HXX__

namespace Yuni
{
namespace Script
{
namespace Private
{
namespace Bind
{

	template <typename Fx, typename ReturnType>
	Binding<Fx, ReturnType>::Binding(const Fx& fPtr)
		: pRealFunction(fPtr.ptr())
	{

	}

	template <typename Fx, typename ReturnType>
	unsigned int Binding<Fx, ReturnType>::argumentCount() const
	{
		return Fx::argumentsCount;
	}

	template <typename Fx, typename ReturnType>
	int Binding<Fx, ReturnType>::performFunctionCall(Lua* luaContext)
	{
		/*	Lua::Private::Bind::ReturnValue<typename Fx::ReturnType>
			::Push(luaContext, callRealFunction<NthArgument>(context, 0));	*/

		pRealFunction. template callWithArgumentGetter<NthArgument, Lua*>(luaContext);
		std::cout << __FILE__ << ": Performing call, with return value." << std::endl;
		return 1;
	}


	template <typename Fx>
	Binding<Fx, void>::Binding(const Fx& fPtr)
		: pRealFunction(fPtr.ptr())
	{

	}

	template <typename Fx>
	unsigned int Binding<Fx, void>::argumentCount() const
	{
		return Fx::argumentsCount;
	}

	template <typename Fx>
	int Binding<Fx, void>::performFunctionCall(Lua* luaContext)
	{
		/*	Lua::Private::Bind::ReturnValue<typename Fx::ReturnType>
			::Push(luaContext, callRealFunction<NthArgument>(context, 0));	*/
		pRealFunction. template callWithArgumentGetter<NthArgument, Lua*>(luaContext);
		std::cout << __FILE__ << ": Performing call WITHOUT return value." << std::endl;
		return 0;
	}


} // namespace Bind
} // namespace Private
} // namespace Script
} // namespace Yuni

#endif // __YUNI_SCRIPT_SCRIPT_PRIVATE_HXX__
