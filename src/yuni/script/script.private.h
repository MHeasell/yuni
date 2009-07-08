#ifndef __YUNI_SCRIPT_SCRIPT_PRIVATE_H__
# define __YUNI_SCRIPT_SCRIPT_PRIVATE_H__

namespace Yuni
{
namespace Script
{
namespace Private
{
namespace Bind
{

	/*!
	** \brief Base class for Argument getters
	** \tparam TScript The script engine type (Lua, ...)
	** \tparam TArgType The desired type of the argument.
	**
	** This class is empty, see script.args.language.hxx
	** for specializations.
	** The goal of this class is to get the Nth argument, forced to the
	** C++ type TArgType, for the language TScript. If the argument is not
	** compatible with TArgType, it will be set to the value of TArgType()
	*/
	template <class TScript, class TArgType>
	struct NthArgument;

	/*!
	** \brief Base class for ReturnValue pushers
	** \see NthArgument
	** \tparam TScript The script engine type (Lua, ...)
	** \tparam TValueType The type of the value to push.
	**
	** Same principle as NthArgument, but for pushing return
	** values in the script context.
	*/
	template <class TScript, class TValueType>
	struct ReturnValue;

	/*!
	** \brief Abstract proxy for C++ function binding into languages.
	** 
	** \todo document this.
	*/
	struct IBinding
	{
		//! Dtor
		virtual ~IBinding();

		//! Returns the contained function's arguement count
		virtual unsigned int argumentCount() const = 0;

		//! Performs the actual function call for Lua implementation
		virtual int performFunctionCall(Lua * /* context */) = 0;

		// Adding a language ?
		// Insert here more function call overloads for your own script types
	};

	/*!
	** \brief Concrete templated binding implementation.
	** \tparam Fx The right Yuni::Function for the function pointer passed.
	** \tparam ReturnType The passed function return type.
	**
	** This is the only descendant of IBinding. IBinding exists only
	** because we want to be able to call the performFunctionCall method
	** without knowing exactly which instanciation was made of this class.
	*/
	template <typename Fx, typename ReturnType>
	class Binding : public IBinding
	{
	public:
		Binding(const Fx& fPtr);
		unsigned int argumentCount() const;
		int performFunctionCall(Lua* luaContext);

	private:
		Fx pRealFunction;
	};

	/*!
	** \brief Specialization of Binding for functions returning void.
	*/
	template <typename Fx>
	class Binding<Fx, void> : public IBinding
	{
	public:
		Binding(const Fx& fPtr);
		unsigned int argumentCount() const;
		int performFunctionCall(Lua* luaContext);

	private:
		Fx pRealFunction;
	};


} // namespace Bind
} // namespace Private
} // namespace Script
} // namespace Yuni

# include "script.private.hxx"

#endif // __YUNI_SCRIPT_SCRIPT_PRIVATE_H__
