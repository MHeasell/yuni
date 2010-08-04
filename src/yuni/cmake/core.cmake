

YMESSAGE(":: [Module] Core")


# yuni-config
LIBYUNI_CONFIG_INCLUDE_PATH("core" "${CMAKE_CURRENT_SOURCE_DIR}/..")
LIBYUNI_CONFIG_LIB_PATH("core" "${LIBRARY_OUTPUT_PATH}")
LIBYUNI_CONFIG_LIB("core"       "yuni-static-core")
IF(APPLE)
	LIBYUNI_CONFIG_CFLAG("core"	"-fvisibility=hidden")
ENDIF(APPLE)

#
# PThreads
#
DEVPACK_IMPORT_PTHREADS()

INCLUDE(CheckCXXSourceCompiles)
INCLUDE(CheckIncludeFiles)
INCLUDE(CheckIncludeFileCXX)
INCLUDE(CheckCXXCompilerFlag)



# stdio.h
CHECK_INCLUDE_FILE_CXX(stdio.h YUNI_HAS_STDIO_H)
# String.h
CHECK_INCLUDE_FILE_CXX(string.h YUNI_HAS_STRING_H)
# time.h
CHECK_INCLUDE_FILE_CXX(time.h YUNI_HAS_TIME_H)
# assert.h
CHECK_INCLUDE_FILE_CXX(assert.h YUNI_HAS_ASSERT_H)
# errno.h
CHECK_INCLUDE_FILE_CXX(errno.h YUNI_HAS_ERRNO_H)
# cstddef
CHECK_INCLUDE_FILE_CXX(cstddef YUNI_HAS_CSTDDEF)

# climits
CHECK_INCLUDE_FILE_CXX(climits YUNI_HAS_CLIMITS)
# vector
CHECK_INCLUDE_FILE_CXX(vector YUNI_HAS_VECTOR)
# list
CHECK_INCLUDE_FILE_CXX(list YUNI_HAS_LIST)
# map
CHECK_INCLUDE_FILE_CXX(map YUNI_HAS_MAP)
# algorithm
CHECK_INCLUDE_FILE_CXX(algorithm YUNI_HAS_ALGORITHM)
# iostream
CHECK_INCLUDE_FILE_CXX(iostream YUNI_HAS_IOSTREAM)
# cassert
CHECK_INCLUDE_FILE_CXX(cassert YUNI_HAS_CASSERT)
# dirent.h
CHECK_INCLUDE_FILE_CXX(dirent.h YUNI_HAS_DIRENT_H)
# stdlib.h
CHECK_INCLUDE_FILE_CXX(stdlib.h YUNI_HAS_STDLIB_H)
# unistd.h
CHECK_INCLUDE_FILE_CXX(unistd.h YUNI_HAS_UNISTD_H)
# fcntl.h
CHECK_INCLUDE_FILE_CXX(fcntl.h YUNI_HAS_FCNTL_H)
# cstdlib
CHECK_INCLUDE_FILE_CXX(cstdlib YUNI_HAS_CSTDLIB)
# stdarg
CHECK_INCLUDE_FILE_CXX(stdarg.h YUNI_HAS_STDARG_H)
# Macro va_copy
CHECK_CXX_SOURCE_COMPILES("#include <stdarg.h>
	int main() {va_list a, b; va_copy(a, b);}" YUNI_HAS_VA_COPY)




IF(NOT MSVC)
	# sys/types.h
	CHECK_INCLUDE_FILE_CXX("sys/types.h" YUNI_HAS_SYS_TYPES_H)
ENDIF(NOT MSVC)
IF(WIN32 OR WIN64)
	# cstddef
	CHECK_INCLUDE_FILE_CXX(winsock2.h YUNI_HAS_WINSOCK_2)
	# ShellApi.h
	CHECK_INCLUDE_FILE_CXX(shellapi.h YUNI_HAS_SHELLAPI_H)
ENDIF(WIN32 OR WIN64)




# C++0x
CHECK_CXX_COMPILER_FLAG("-std=c++0x" YUNI_HAS_GCC_CPP0X_SUPPORT)


# int64
CHECK_CXX_SOURCE_COMPILES("#include <stdint.h>
	int main() {int64_t a; return 0;}" YUNI_HAS_INT64_T)
# int128
CHECK_CXX_SOURCE_COMPILES("#include <stdint.h>
	int main() {int128_t a; return 0;}" YUNI_HAS_INT128_T)

# C++0x nullptr
CHECK_CXX_SOURCE_COMPILES("
	class A {}; int main() {A* a = nullptr;return 0;}" YUNI_HAS_NULLPTR)

# long
IF(MSVC)
	CHECK_CXX_SOURCE_COMPILES(
		"#include <iostream>
		#include <stdio.h>
		void foo(unsigned int a) {std::cout << a;}
		void foo(int a) {std::cout << a;}
		void foo(unsigned long a) {std::cout << a;}
		void foo(long a) {std::cout << a;}
		void foo(__int64 a) {std::cout << a;}
		int main() {return 0;}"
		YUNI_HAS_LONG)
ELSE(MSVC)
	IF(YUNI_HAS_SYS_TYPES_H)
		CHECK_CXX_SOURCE_COMPILES(
			"#include <iostream>
			#include <sys/types.h>
			#include <stdio.h>
			void foo(unsigned int a) {std::cout << a;}
			void foo(int a) {std::cout << a;}
			void foo(unsigned long a) {std::cout << a;}
			void foo(long a) {std::cout << a;}
			void foo(int64_t a) {std::cout << a;}
			int main() {return 0;}"
			YUNI_HAS_LONG)
	ELSE(YUNI_HAS_SYS_TYPES_H)
		CHECK_CXX_SOURCE_COMPILES(
			"#include <iostream>
			#include <stdio.h>
			void foo(unsigned int a) {std::cout << a;}
			void foo(int a) {std::cout << a;}
			void foo(unsigned long a) {std::cout << a;}
			void foo(long a) {std::cout << a;}
			void foo(int64_t a) {std::cout << a;}
			int main() {return 0;}"
			YUNI_HAS_LONG)
	ENDIF(YUNI_HAS_SYS_TYPES_H)
ENDIF(MSVC)



#
# Generating informations about the platform
#
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform.cmake ${CMAKE_CURRENT_SOURCE_DIR}/platform.h)

Set(SRC_CORE_ATOMIC
				core/atomic/int.h
				core/atomic/int.hxx
				core/atomic/traits.h)
source_group(Core\\atomic FILES ${SRC_CORE_ATOMIC})


Set(SRC_CORE_PREPROCESSOR
				core/preprocessor/std.h
				core/preprocessor/capabilities.h
				core/preprocessor/capabilities/unixes.h
				core/preprocessor/capabilities/windows.h
				core/preprocessor/enum.h)
source_group(Core\\preprocessor FILES ${SRC_CORE_PREPROCESSOR})

Set(SRC_CORE_ITERATOR
				core/iterator.h
				core/iterator/iterator.h
				core/iterator/iterator.hxx
				)
source_group(Core\\iterator FILES ${SRC_CORE_ITERATOR})


Set(SRC_CORE_STATIC
				core/static/if.h
				core/static/remove.h
				core/static/assert.h
				core/static/types.h
				core/static/inherit.h
				core/static/dynamiccast.h
				core/static/moveconstructor.h)
source_group(Core\\static FILES ${SRC_CORE_STATIC})

Set(SRC_CORE_TRAITS
				core/traits/cstring.h
				core/traits/extension/into-cstring.h
				core/traits/extension/length.h
				core/traits/length.h)
source_group(Core\\traits FILES ${SRC_CORE_TRAITS})


Set(SRC_CORE_EXCEPTIONS
				core/exceptions.h
				core/exceptions/badcast.h )
source_group(Core\\exceptions FILES ${SRC_CORE_EXCEPTIONS})


Set(SRC_CORE_VALIDATOR
				core/validator/text/default.h
				core/validator/text/default.hxx
				core/validator/text/default.private.h
				core/validator/text/validator.h
				core/validator/validator.h)
source_group(Core\\validator FILES ${SRC_CORE_VALIDATOR})

Set(SRC_CORE_SLIST
				core/slist/iterator.h
				core/slist/slist.h
				core/slist/slist.hxx
				core/slist.h)
source_group(Core\\linkedList FILES ${SRC_CORE_SLIST})



Set(SRC_CORE_STRING
				core/customstring/customstring.h
				core/customstring/customstring.hxx
				core/customstring/iterator.h
				core/customstring/iterator.hxx
				core/customstring/utf8char.h
				core/customstring/utf8char.hxx
				core/customstring/traits/append.h
				core/customstring/traits/assign.h
				core/customstring/traits/fill.h
				core/customstring/traits/integer.h
				core/customstring/traits/vnsprintf.h
				core/customstring/traits/traits.h
				core/customstring/traits/traits.cpp
				core/customstring/traits/traits.hxx
				core/customstring/traits/into.h

				core/string/string.h core/string/string.hxx
				core/string/converters.from.hxx core/string/converters.to.hxx
				core/string/forward.h
				core/string/traits.hxx
				core/string/iterators.hxx
				core/string/traits/countchar.hxx  core/string/traits/find.hxx
				core/string/traits/haschar.hxx    core/string/traits/length.hxx
				core/string/traits/remove.hxx     core/string/traits/vsprintf.hxx
				core/string/traits/findlastof.hxx core/string/traits/findfirstof.hxx
				core/string.h)
source_group(Core\\String FILES ${SRC_CORE_STRING})


Set(SRC_CORE_STL
				core/stl/algorithm.h)
source_group(Core\\Stl FILES ${SRC_CORE_STL})


Set(SRC_CORE_LOGS
				core/logs/logs.h core/logs/logs.hxx core/logs/verbosity.h
				core/logs/null.h
				core/logs/buffer.h
				# Handlers
				core/logs/handlers/stdcout.h
				core/logs/handlers/file.h
				core/logs/handlers/callback.h
				# Decorators
				core/logs/decorators/verbositylevel.h
				core/logs/decorators/time.h
				core/logs/decorators/time.cpp
				core/logs/decorators/applicationname.h
				core/logs/decorators/message.h
				core/logs.h)
source_group(Core\\Logs FILES ${SRC_CORE_LOGS})



Set(SRC_CORE_SMARTPTR
				core/smartptr/policies/checking.h
				core/smartptr/policies/ownership.h
				core/smartptr/policies/storage.h
				core/smartptr/policies/constness.h
				core/smartptr/smartptr.h  core/smartptr/smartptr.hxx
				)
source_group(Core\\SmartPtr FILES ${SRC_CORE_SMARTPTR})


Set(SRC_CORE_ANY
				core/any.h
				core/any/any.h
				core/any/any.private.h
				core/any/any.hxx
				core/any/any.cpp)
source_group(Core\\Any FILES ${SRC_CORE_ANY})

Set(SRC_CORE_VARIANT
				core/variant.h
				core/variant/variant.h
				core/variant/variant.hxx
				core/variant/variant.cpp
				core/variant/variant.private.h
				core/variant/variant.private.hxx)
source_group(Core\\Variant FILES ${SRC_CORE_VARIANT})



Set(SRC_CORE_DYNAMICLIBRARY
				core/dynamiclibrary/file.h	core/dynamiclibrary/file.hxx
				core/dynamiclibrary/file.cpp
				core/dynamiclibrary/symbol.h core/dynamiclibrary/symbol.hxx
				core/dynamiclibrary.h)
source_group(Core\\DynamicLibrary FILES ${SRC_CORE_DYNAMICLIBRARY})


Set(SRC_CORE_BIND
				core/bind/bind.h core/bind/bind.hxx
				core/bind/traits.h
				core/bind.h
				)
source_group(Core\\Bind FILES ${SRC_CORE_BIND})

Set(SRC_CORE_CHARSET
				core/charset/charset.h core/charset/charset.hxx
				core/charset/charset.cpp
				)
source_group(Core\\Charset FILES ${SRC_CORE_CHARSET})


Set(SRC_CORE_EVENT
				core/event/event.h core/event/event.hxx
				core/event/interfaces.h core/event/interfaces.hxx
				core/event/traits.h
				core/event/observer/observer.h core/event/observer/observer.hxx
				core/event.h

				# Event loop
				core/event/loop.h core/event/loop.hxx
				core/event/loop.fwd.h
				core/event/flow
				core/event/flow/continuous.h
				core/event/flow/timer.h
				core/event/statistics
				core/event/statistics/none.h
				)
source_group(Core\\Event FILES ${SRC_CORE_EVENT})


Set(SRC_CORE_MATH
				# Standard functions
				core/math/math.h 	core/math.h  core/math/math.hxx core/math/msvc.hxx
				core/math/base.h
				# Log(N)
				core/math/log.h core/math/log.hxx
				# Trigonometric functions
				core/math/trigonometric.h core/math/trigonometric.hxx
				# Exponential functions
				core/math/exponential.h core/math/exponential.hxx
				core/math/complex.h  core/math/complex.hxx
				# Random number generators
				core/math/random/distribution.h  core/math/random/distribution.hxx
				core/math/random/default.h  core/math/random/default.hxx
				core/math/random/range.h  core/math/random/range.hxx
				core/math/random/constant.h

				core/rect2D.h core/math/geometry/rect2D.h core/math/geometry/rect2D.hxx
				core/vector3D.h core/math/geometry/vector3D.h core/math/geometry/vector3D.hxx
				core/point2D.h core/math/geometry/point2D.h
				core/point3D.h core/math/geometry/point3D.h
)
source_group(Core\\Math FILES ${SRC_CORE_MATH})

Set(SRC_CORE_BIT
				core/bit.h
				core/bit/bit.h core/bit/bit.hxx
				core/bit/array.h
				core/bit/array.hxx
				core/bit/array.cpp
				)
source_group("Core\\Bit" FILES ${SRC_CORE_BIT})


# Singleton
Set(SRC_CORE_SINGLETON
				core/singleton/singleton.h
				core/singleton/singleton.hxx
				core/singleton/policies/creation.h
				core/singleton/policies/lifetime.h
				)
source_group(Core\\Singleton FILES ${SRC_CORE_SINGLETON})



# Hash - Checksums
Set(SRC_CORE_HASH_CHECKSUM
				core/hash/checksum/checksum.h
				core/hash/checksum/checksum.hxx
				core/hash/checksum/md5.hxx
				core/hash/checksum/md5.h core/hash/checksum/md5.cpp)
source_group(Core\\Hash\\Checksum FILES ${SRC_CORE_HASH_CHECKSUM})


# System
Set(SRC_CORE_SYSTEM
				core/system/stdint.h core/system/nullptr.h core/system/capabilities.h
				core/system/sleep.h core/system/sleep.cpp
				core/sleep.h
				core/fwd.h
				core/system/cpu.h core/system/cpu.cpp
				core/system/memory.h core/system/memory.hxx core/system/memory.cpp
				core/system/environment.h core/system/environment.hxx
				core/system/endian.h)
source_group(Core\\System FILES ${SRC_CORE_SYSTEM})


Set(SRC_CORE_TREE_N
				core/tree/treeN.h  core/tree/treeN.hxx
				core/tree/treeN.iterator.def.h  core/tree/treeN.iterator.undef.h
				core/tree/treeN.iterator.h
				)
source_group(Core\\Tree FILES ${SRC_CORE_TREE_N})


Set(SRC_CORE_UNIT
				core/unit/define.h core/unit/undef.h
				core/unit/unit.h core/unit/unit.hxx
				core/unit.h
				core/unit/angle.h
				core/unit/length.h
				core/unit/length/length.h
				core/unit/length/metric.h
				core/unit/length/extra.h
				core/unit/luminance.h
)
source_group(Core\\Unit FILES ${SRC_CORE_UNIT})

Set(SRC_CORE_UTILS
				core/utils/utils.h
				core/utils/hexdump.h core/utils/hexdump.hxx core/utils/hexdump.cpp
)
source_group(Core\\Utils FILES ${SRC_CORE_UTILS})

Set(SRC_CORE_URI
				core/uri/uri.private.h  core/uri/uri.private.cpp
				core/uri/uri.h core/uri/uri.hxx core/uri/uri.cpp
				core/uri.h)
source_group(Core\\URI FILES ${SRC_CORE_URI})


Set(SRC_CORE_IO_FILENAME
				core/io/io.h core/io/io.cpp core/io/exists.cpp
				core/io/io.hxx)
source_group(Core\\IO FILES ${SRC_CORE_IO_FILENAME})



Set(SRC_CORE_IO_DIRECTORY
				core/io/directory.h core/io/directory/directory.hxx
				core/io/directory/commons.h
				core/io/directory/remove.cpp
				core/io/directory/current.cpp
				core/io/directory/make.cpp
				core/io/directory/copy.cpp

				core/io/directory/info.h
				core/io/directory/info/iterator.cpp
				core/io/directory/info/iterator.h
				core/io/directory/info/info.h
				core/io/directory/info/info.hxx
				core/io/directory/info/info.cpp
				core/io/directory/info/platform.cpp
				core/io/directory/info/platform.h

				core/io/directory/iterator.h
				core/io/directory/iterator/iterator.cpp
				core/io/directory/iterator/iterator.h
				core/io/directory/iterator/iterator.hxx
				core/io/directory/iterator/detachedthread.h
				)
source_group(Core\\IO\\Directory FILES ${SRC_CORE_IO_DIRECTORY})


Set(SRC_CORE_IO_FILE
				core/io/file/openmode.h core/io/file/openmode.cpp
				core/io/file/stream.h core/io/file/stream.hxx
				core/io/file/stream.cpp
				core/io/file.h core/io/file/file.hxx core/io/file/file.cpp
				core/io/file/load.cpp
				)
source_group(Core\\IO\\File FILES ${SRC_CORE_IO_FILE})


Set(SRC_CORE_GETOPT
				core/getopt.h
				core/getopt/option.h core/getopt/option.cpp
				core/getopt/parser.h core/getopt/parser.hxx core/getopt/parser.cpp)
source_group(Core\\GetOpt FILES ${SRC_CORE_GETOPT})


Set(SRC_CORE_VERSION	core/version/version.h  core/version/version.cpp core/version/version.hxx)
source_group(Core\\Version FILES ${SRC_CORE_VERSION})




# System - Microsoft Windows
Set(SRC_CORE_SYSTEM_WINDOWS core/system/windows.hdr.h  core/system/gettimeofday.h)
If(WIN32 AND MSVC)
	Set(SRC_CORE_SYSTEM_WINDOWS ${SRC_CORE_SYSTEM_WINDOWS} core/system/gettimeofday.cpp)
EndIF(WIN32 AND MSVC)
source_group(Core\\System\\Windows FILES ${SRC_CORE_SYSTEM_WINDOWS})




# Threads
Set(SRC_THREADS
				thread/policy.h
				thread/pthread.h
				thread/mutex.h     thread/mutex.hxx
				thread/thread.h    thread/thread.hxx    thread/thread.cpp
				thread/timer.h     thread/timer.hxx     thread/timer.cpp
				thread/condition.h thread/condition.cpp thread/condition.hxx
				thread/array.h     thread/array.hxx)
source_group(Threads FILES ${SRC_THREADS})

# Jobs
Set(SRC_JOBS
				job/enum.h
				job/forward.h
				job/job.h job/job.hxx job/job.cpp
				job/queue.h job/queue/queue.h job/queue/queue.hxx
				job/queue/thread.h
				job/queue/waitingroom.h job/queue/waitingroom.hxx
				job/queue/waitingroom.cpp

				# Scheduler
				job/scheduler/highestpriorityfirst.h job/scheduler/highestpriorityfirst.hxx
				)
source_group(Jobs FILES ${SRC_JOBS})


# Application
Set(SRC_APPLICATION
				application/application.h
				application/application.hxx application/application.cpp
				application/console.h application/console.cpp)
source_group(Core\\Application FILES ${SRC_APPLICATION})


Set(SRC_GFX_CORE
		gfx/octree.h gfx/octree.cpp
		# Color
		gfx/core/color/rgba.h gfx/core/color/rgb.h
		gfx/core/color/proxy.h gfx/core/color/proxy.cpp
		)
source_group(Gfx FILES ${SRC_GFX_CORE})

Set(SRC_CORE_PREDICATES_RESULTS
		core/predicate/result/sum.h
		core/predicate/result/and.h
		core/predicate/result/or.h
		)
source_group(Core\\Predicate\\Result FILES ${SRC_CORE_PREDICATES_RESULTS})


Set(SRC_CORE_SYSTEM_CONSOLE
		core/system/console.h
		core/system/console/console.h
		core/system/console/console.hxx
		)
source_group(Core\\System\\Console FILES ${SRC_CORE_SYSTEM_CONSOLE})



ADD_LIBRARY(yuni-static-core STATIC
		yuni.h
		${SRC_CORE_PREDICATES_RESULTS}
		${SRC_CORE_STATIC}
		${SRC_CORE_ITERATOR}
		${SRC_CORE_TRAITS}
		${SRC_CORE_PREPROCESSOR}
		${SRC_CORE_BIT}
		${SRC_CORE_EXCEPTIONS}
		${SRC_CORE_SYSTEM}
		${SRC_CORE_SYSTEM_WINDOWS}
		${SRC_CORE_SYSTEM_CONSOLE}
		${SRC_CORE_STRING}
		${SRC_CORE_STL} ${SRC_CORE_VALIDATOR}
		${SRC_CORE_IO_FILENAME}
		${SRC_CORE_IO_DIRECTORY}
		${SRC_CORE_IO_FILE}
		${SRC_CORE_LOGS}
		${SRC_CORE_ATOMIC}
		${SRC_CORE_SMARTPTR}
		${SRC_CORE_ANY}
		${SRC_CORE_SLIST}
		${SRC_CORE_VARIANT}
		${SRC_CORE_DYNAMICLIBRARY}
		${SRC_CORE_BIND}
		#${SRC_CORE_CHARSET}
		${SRC_CORE_EVENT}
		${SRC_CORE_MATH}
		${SRC_CORE_SINGLETON}
		${SRC_CORE_HASH_CHECKSUM}
		${SRC_CORE_TREE_N}
		${SRC_CORE_VERSION}
		${SRC_CORE_UNIT}
		${SRC_CORE_UTILS}
		${SRC_CORE_URI}
		${SRC_CORE_GETOPT}
		${SRC_GFX_CORE}
		${SRC_PREDICATES_RESULTS}
		${SRC_THREADS} ${SRC_JOBS}
		${SRC_APPLICATION}
	)
INSTALL(TARGETS yuni-static-core ARCHIVE DESTINATION lib/${VERSIONED_INST_PATH})

# Install Core-related headers
INSTALL(
	DIRECTORY core
	DESTINATION include/${VERSIONED_INST_PATH}
	FILES_MATCHING
		PATTERN "*.h"
		PATTERN "*.hxx"
	PATTERN ".svn" EXCLUDE
	PATTERN "CMakeFiles" EXCLUDE
	PATTERN "cmake" EXCLUDE
)

# Install other core-related base files
INSTALL(FILES
	Doxygen.txt
	doxygen.h
	platform.h
	yuni.config.gcc
	yuni.h
	yuni.version
		DESTINATION include/${VERSIONED_INST_PATH})

