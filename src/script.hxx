#ifndef __YUNI_SCRIPT_SCRIPT_HXX__
# define __YUNI_SCRIPT_SCRIPT_HXX__


/*!
** \internal This file is automatically generated by 'script.hxx.generator.hpp'.
** Please make any modifications you wish to this script instead of
** this file, as they will otherwise be lost at the next generation.
*/



namespace Yuni
{
namespace Script
{



	template<typename T>
	inline bool AScript::isBound(const T& functionName) const
	{
		ThreadingPolicy::MutexLocker locker(*this);
		return pBoundFunctions.end() != pBoundFunctions.find(functionName);
	}


	template <class FunctionT, typename U>
	bool AScript::bind(const U& functionName, FunctionT funcPtr)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Bind<FunctionT>  BindTypeT;

			BindTypeT b;
			b.bind(funcPtr);
			Private::ScriptImpl::Bind::IBinding* intF = new Private::ScriptImpl::Bind::Binding<BindTypeT>(b);

			// TODO: check return value
			if (!internalBindWL(Traits::CString<String>::Perform(functionName), intF))
			{
				delete intF;
				return false;
			}
			pBoundFunctions.insert(std::pair<String, Private::ScriptImpl::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}


	template <class ClassT, class MemberT, typename U>
	bool AScript::bind(const U& functionName, ClassT* object, MemberT member)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Bind<MemberT, ClassT>  BindTypeT;

			BindTypeT b;
			b.bind<ClassT>(object, member);
			Private::ScriptImpl::Bind::IBinding* intF = new Private::ScriptImpl::Bind::Binding<BindTypeT>(b);

			// TODO: check return value
			if (!internalBindWL(Traits::CString<String>::Perform(functionName), intF))
			{
				delete intF;
				return false;
			}
			pBoundFunctions.insert(std::pair<String, Private::ScriptImpl::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;

	}





	template<typename T>
	bool AScript::unbind(const T& fName)
	{
		ThreadingPolicy::MutexLocker locker(*this);

		BoundFunctions::iterator i = pBoundFunctions.find(fName);
		if (i != pBoundFunctions.end())
		{
			internalUnbindWL(fName);
			delete i->second;
			pBoundFunctions.erase(i);
			return true;
		}
		return false;
	}





} // namespace Script
} // namespace Yuni

#endif // __YUNI_SCRIPT_SCRIPT_HXX__
