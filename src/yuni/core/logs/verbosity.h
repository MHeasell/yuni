#ifndef __YUNI_TOOLBOX_LOGS_VERBOSITY_H__
# define __YUNI_TOOLBOX_LOGS_VERBOSITY_H__




namespace Yuni
{
namespace Logs
{
namespace Verbosity
{


	struct Unknown
	{
		static const char* Name() {return "";}
		template<class U> static void AppendName(U&) {}
		enum
		{
			level = 0,
			shouldUsesStdCerr = 0,
			hasName = 0,
			enabled = 1,
			checkpoint = 0,
		};
		template<class U> static void AppendUnixColor(U&) {}
	};


	struct Fatal
	{
		static const char* Name() {return "!!fatal";}
		template<class U> static void AppendName(U& u) {u << "fatal";}
		enum
		{
			level = 1000,
			shouldUsesStdCerr = 1,
			hasName = 1,
			enabled = 1,
			checkpoint = 0,
		};
		template<class U> static void AppendUnixColor(U& u) {u << "[1;31m";}
	};


	struct Error
	{
		static const char* Name() {return "error";}
		template<class U> static void AppendName(U& u) {u << "error";}
		enum
		{
			level = 2000,
			shouldUsesStdCerr = 1,
			hasName = 1,
			enabled = 1,
			checkpoint = 0,
		};
		template<class U> static void AppendUnixColor(U& u) {u << "[1;31m";}
	};


	struct Warning
	{
		static const char* Name() {return "warning";}
		template<class U> static void AppendName(U& u) {u << "warns";}
		enum
		{
			level = 3000,
			shouldUsesStdCerr = 1,
			hasName = 1,
			enabled = 1,
			checkpoint = 0,
		};
		template<class U> static void AppendUnixColor(U& u) {u << "[1;33m";}
	};


	struct Checkpoint
	{
		static const char* Name() {return "checkpoint";}
		template<class U> static void AppendName(U& u) {u << "check";}

		enum
		{
			level = 4000,
			shouldUsesStdCerr = 0,
			hasName = 1,
			enabled = 1,
			checkpoint = 1,
		};
		template<class U> static void AppendUnixColor(U& u) {u << "[1;32m";}
	};


	struct Notice
	{
		static const char* Name() {return "notice";}
		template<class U> static void AppendName(U& u) {u << "infos";}

		enum
		{
			level = 5000,
			shouldUsesStdCerr = 0,
			hasName = 1,
			enabled = 1,
			checkpoint = 0,
		};
		template<class U> static void AppendUnixColor(U& u) {u << "[1;32m";}
	};


	struct Debug
	{
		static const char* Name() {return "debug";}
		template<class U> static void AppendName(U& u) {u << "debug";}

		enum
		{
			level = 10000,
			shouldUsesStdCerr = 0,
			hasName = 1,
			# ifdef NDEBUG // The debug messages must be disabled
			enabled = 0,
			# else
			enabled = 1,
			# endif
			checkpoint = 0,
		};
		template<class U> static void AppendUnixColor(U&) {}
	};




} // namespace Verbosity
} // namespace Logs
} // namespace Yuni


#endif // __YUNI_TOOLBOX_LOGS_VERBOSITY_H__
