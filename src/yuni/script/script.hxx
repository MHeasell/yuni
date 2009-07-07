#ifndef __YUNI_SCRIPT_SCRIPT_HXX__
# define __YUNI_SCRIPT_SCRIPT_HXX__

/*
**
** WARNING !
** -----------------------------------------------------------------
** This file was automatically generated by script.hxx.generator.hpp.
** Please make any modifications you wish to this script instead of
** this file, as they will otherwise be lost at the next generation.
** -----------------------------------------------------------------
**
*/

// Included from script.h
// No system headers here !

namespace Yuni
{
namespace Script
{

	template <class R, typename U>
	bool AScript::bind(const U& functionName, R (*f)())
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F0<R> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F1<R, A0> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename A1, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0, A1))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F2<R, A0, A1> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename A1, typename A2, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0, A1, A2))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F3<R, A0, A1, A2> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename A1, typename A2, typename A3, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0, A1, A2, A3))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F4<R, A0, A1, A2, A3> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0, A1, A2, A3, A4))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F5<R, A0, A1, A2, A3, A4> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0, A1, A2, A3, A4, A5))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F6<R, A0, A1, A2, A3, A4, A5> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0, A1, A2, A3, A4, A5, A6))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F7<R, A0, A1, A2, A3, A4, A5, A6> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0, A1, A2, A3, A4, A5, A6, A7))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F8<R, A0, A1, A2, A3, A4, A5, A6, A7> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0, A1, A2, A3, A4, A5, A6, A7, A8))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F9<R, A0, A1, A2, A3, A4, A5, A6, A7, A8> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F10<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F11<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F12<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F13<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F14<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F15<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

	template <class R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename U>
	bool AScript::bind(const U& functionName, R (*f)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F16<R, A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(String::CString(functionName), intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}



} // namespace Script
} // namespace Yuni

#endif // __YUNI_SCRIPT_SCRIPT_HXX__
