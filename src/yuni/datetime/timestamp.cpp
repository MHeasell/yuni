
#include "timestamp.h"
#include <time.h>
#include <cassert>



namespace Yuni
{
namespace DateTime
{

	Timestamp Now()
	{
		# ifdef YUNI_OS_MSVC
		return (sint64) ::_time64(NULL);
		# else
		return (sint64) ::time(NULL);
		# endif
	}



	static inline uint FormatString(char* buffer, uint size, const char* format, sint64 timestamp)
	{
		assert(format && '\0' != *format && "invalid format");

		uint written;

		// Note that unlike on (all?) POSIX systems, in the Microsoft
		// C library localtime() and gmtime() are multi-thread-safe, as the
		// returned pointer points to a thread-local variable. So there is no
		// need for localtime_r() and gmtime_r().

		// \note The variable stdtimestamp is used to ensure the compilation on
		//  32bits platforms

		# ifdef YUNI_OS_MINGW
		// MinGW
		time_t stdtimestamp = (time_t) timestamp;
		written = (uint)::strftime(buffer, size, format, ::localtime(&stdtimestamp));
		# else
		struct tm timeinfo;
		#	ifdef YUNI_OS_MSVC
		// Microsoft Visual Studio
		_localtime64_s(&timeinfo, &timestamp);
		written = (uint)::strftime(buffer, size, format, &timeinfo);
		#	else
		// Unixes
		time_t stdtimestamp = (time_t) timestamp;
		::localtime_r(&stdtimestamp, &timeinfo);
		written = (uint)::strftime(buffer, size, format, &timeinfo);
		#	endif
		# endif

		return (written && written < size) ? written : 0;
	}


	static inline char* FormatStringDynBuffer(uint size, const char* format, sint64 timestamp)
	{
		if (!timestamp)
		{
			# ifdef YUNI_OS_MSVC
			timestamp = (sint64) ::_time64(NULL);
			# else
			timestamp = (sint64) ::time(NULL);
			# endif
		}

		uint tick = 5;
		do
		{
			char* buffer = new char[size];
			if (FormatString(buffer, size, format, timestamp))
				return buffer;
			size += 256;
			delete[] buffer;
		}
		while (--tick);
		return nullptr;
	}


	template<class StringT>
	static inline bool TimestampToStringImpl(StringT& out, const AnyString& format, Timestamp timestamp, bool emptyBefore)
	{
		if (emptyBefore)
			out.clear();

		uint guesssize = format.size();
		if (!guesssize)
			return true;
		// valgrind / assert...
		assert(format.c_str()[format.size()] == '\0' && "format must be zero-terminated");

		guesssize += 128; // arbitrary value
		char* buffer = FormatStringDynBuffer(guesssize, format.c_str(), timestamp);
		if (buffer)
		{
			out += (const char*) buffer;
			delete[] buffer;
			return true;
		}
		return false;
	}


	bool TimestampToString(String& out, const AnyString& format, Timestamp timestamp, bool emptyBefore)
	{
		return TimestampToStringImpl(out, format, timestamp, emptyBefore);
	}

	bool TimestampToString(Clob& out, const AnyString& format, Timestamp timestamp, bool emptyBefore)
	{
		return TimestampToStringImpl(out, format, timestamp, emptyBefore);
	}




} // namespace DateTime
} // namespace Yuni


