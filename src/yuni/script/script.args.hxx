
// We are included in the script.h header.
// We are already in namespace Yuni::Script::Private::Bind.
// No system includes here.

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
	**
	** This class is empty, see script.args.language.hxx
	** for specializations.
	** The goal of this class is to get the Nth argument, forced to the
	** C++ type T, for the language Script.
	** 
	*/
	template <class TScript, class TArgType>
	struct NthArgument
	{
		static TArgType Get(TScript, unsigned int);
	};

	/*!
	** \brief Base class for ReturnValue pushers
	** \see NthArgument
	**
	** Same principle as NthArgument, but for pushing return
	** values in the script context.
	*/
	template <class TScript, class TValueType>
	struct ReturnValue
	{
		static void Push(TScript, const TValueType&);
	};

} // namespace Bind
} // namespace Private
} // namespace Script
} // namespace Yuni

