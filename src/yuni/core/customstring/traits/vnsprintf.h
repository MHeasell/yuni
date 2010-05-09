#ifndef __YUNI_CORE_MEMORY_BUFFER_TRAITS_VSPRINTF_H__
# define __YUNI_CORE_MEMORY_BUFFER_TRAITS_VSPRINTF_H__

# include "../../traits/length.h"
# include "integer.h"



namespace Yuni
{
namespace Private
{
namespace CustomStringImpl
{


	/*!
	** \brief Generic implementation of vsnprintf
	*/
	template<class C>
	int vnsprintf(C* buffer, size_t bufferSize, const C* format, va_list argptr);


	template<>
	inline int
	vnsprintf<char>(char* buffer, size_t bufferSize, const char* format, va_list argptr)
	{
		# if defined YUNI_OS_MSVC
		#	ifdef YUNI_MSVC_SECURE_VSPRINTF
		return ::_vsnprintf_s(buffer, bufferSize - 1, _TRUNCATE, format, argptr);
		#	else
		return ::_vsnprintf(buffer, bufferSize - 1, format, argptr);
		#	endif
		# else // YUNI_OS_MSVC
		return ::vsnprintf(buffer, bufferSize - 1, format, argptr);
		# endif
	}

	template<>
	inline int
	vnsprintf<wchar_t>(wchar_t* buffer, size_t bufferSize, const wchar_t* format, va_list argptr)
	{
		# ifdef YUNI_OS_WINDOWS
		# 	if defined YUNI_OS_MSVC
		#		ifdef YUNI_MSVC_SECURE_VSPRINTF
		return ::_vsnwprintf_s(buffer, bufferSize - 1, _TRUNCATE, format, argptr);
		#		else
		return ::_vsnwprintf(buffer, bufferSize - 1, format, argptr);
		#		endif
		# 	else // YUNI_OS_MSVC
		return ::vsnwprintf(buffer, bufferSize - 1, format, argptr);
		# 	endif
		# else // YUNI_OS_WINDOWS
		return ::vswprintf(buffer, bufferSize - 1, format, argptr);
		# endif
	}





} // namespace CustomStringImpl
} // namespace Private
} // namespace Yuni

#endif // __YUNI_CORE_MEMORY_BUFFER_TRAITS_VSPRINTF_H__
