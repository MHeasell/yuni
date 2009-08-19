

Message(STATUS "[Module] Core")

Set(SRC_CORE_ALLOCATOR
				core/allocator/chunk.h
				core/allocator/chunk.cpp
				core/allocator/allocator.h
				core/allocator/allocator.cpp
				core/allocator/smallobjallocator.h
				core/allocator/smallobjallocator.hxx
				core/allocator/smallobject.h
				core/allocator/smallobject.hxx
				core/allocator/smallobject.cpp
				core/smallobject.h)
source_group(Core\\Allocator FILES ${SRC_CORE_ALLOCATOR})


Set(SRC_CORE_ATOMIC
				core/atomic/int.h
				core/atomic/int.hxx
				core/atomic/traits.h)
source_group(Core\\Atomic FILES ${SRC_CORE_ATOMIC})


Set(SRC_CORE_PREPROCESSOR
				core/preprocessor/std.h
				core/preprocessor/capabilities.h
				core/preprocessor/capabilities/unixes.h
				core/preprocessor/capabilities/windows.h
				core/preprocessor/enum.h)
source_group(Core\\Preprocessor FILES ${SRC_CORE_PREPROCESSOR})


Set(SRC_CORE_STATIC
				core/static/if.h
				core/static/remove.h
				core/static/assert.h
				core/static/types.h
				core/static/moveconstructor.h)
source_group(Core\\Static FILES ${SRC_CORE_STATIC})


Set(SRC_CORE_EXCEPTIONS
				core/exceptions.h
				core/exceptions/badcast.h )
source_group(Core\\Exceptions FILES ${SRC_CORE_EXCEPTIONS})


Set(SRC_CORE_FUNCTION
				core/function/function.h core/function/function.hxx
				core/function.h )
source_group(Core\\Function FILES ${SRC_CORE_FUNCTION})

Set(SRC_CORE_VALIDATOR
				core/validator/text/default.h
				core/validator/text/default.hxx
				core/validator/text/default.private.h
				core/validator/text/validator.h
				core/validator/validator.h)
source_group(Core\\Validator FILES ${SRC_CORE_VALIDATOR})



Set(SRC_CORE_STRING
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
				core/logs/null.h	core/logs/stream.h
				# Handlers
				core/logs/handlers/stdcout.h
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
				core/dynamiclibrary.h )
source_group(Core\\DynamicLibrary FILES ${SRC_CORE_DYNAMICLIBRARY})


Set(SRC_CORE_BIND
				core/bind/bind.h core/bind/bind.hxx
				core/bind/traits.h
				core/bind.h
				)
source_group(Core\\Bind FILES ${SRC_CORE_BIND})


Set(SRC_CORE_EVENT
				core/event/event.h core/event/event.hxx
				core/event/interfaces.h core/event/interfaces.hxx
				core/event/traits.h
				core/event/observer/observer.h core/event/observer/observer.hxx
				core/event.h
				)
source_group(Core\\Event FILES ${SRC_CORE_EVENT})


Set(SRC_CORE_MATH
				# Standard functions
				core/math/math.h 	core/math.h
				# Log(N)
				core/math/log.h core/math/log.hxx
				# Trigonometric functions
				core/math/trigonometric.h core/math/trigonometric.hxx
				# Exponential functions
				core/math/exponential.h core/math/exponential.hxx
				# Random number generators
				core/math/random/distribution.h  core/math/random/distribution.hxx
				core/math/random/default.h  core/math/random/default.hxx
				core/math/random/range.h  core/math/random/range.hxx
				core/math/random/constant.h
)
source_group(Core\\Math FILES ${SRC_CORE_MATH})


# Hash - Checksums
Set(SRC_CORE_HASH_CHECKSUM
				core/hash/checksum/checksum.hxx
				core/hash/checksum/md5.hxx
				core/hash/checksum/checksum.h core/hash/checksum/checksum.cpp
				core/hash/checksum/md5.h core/hash/checksum/md5.cpp)
source_group(Core\\Hash\\Checksum FILES ${SRC_CORE_HASH_CHECKSUM})


# System
Set(SRC_CORE_SYSTEM
				core/system/stdint.h core/system/nullptr.h core/system/capabilities.h
				core/system/sleep.h core/system/sleep.cpp
				core/sleep.h
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


Set(SRC_CORE_URI
				core/uri/uri.private.h  core/uri/uri.private.cpp
				core/uri/uri.h core/uri/uri.hxx core/uri/uri.cpp
				core/uri.h)
source_group(Core\\URI FILES ${SRC_CORE_URI})


Set(SRC_CORE_FS
				core/fs/paths.h core/fs/paths.cpp  core/paths.h
				core/fs/files.h core/fs/files.cpp  core/files.h)
source_group(Core\\FileSystem FILES ${SRC_CORE_FS})


Set(SRC_CORE_GETOPT
				core/getopt.h
				core/getopt/option.h core/getopt/option.cpp
				core/getopt/parser.h core/getopt/parser.hxx core/getopt/parser.cpp)
source_group(Core\\GetOpt FILES ${SRC_CORE_GETOPT})


Set(SRC_VERSION	core/version/version.h  core/version/version.cpp)
source_group(Core\\Version FILES ${SRC_VERSION})




# System - Microsoft Windows
Set(SRC_CORE_SYSTEM_WINDOWS core/system/windows.hdr.h  core/system/windows/gettimeofday.h)
If(WIN32 AND MSVC)
	Set(SRC_CORE_SYSTEM_WINDOWS ${SRC_CORE_SYSTEM_WINDOWS} core/system/windows/gettimeofday.cpp)
EndIF(WIN32 AND MSVC)
source_group(Core\\System\\Windows FILES ${SRC_CORE_SYSTEM_WINDOWS})




# Threads
Set(SRC_THREADS
				threads/policy.h
				threads/mutex.h threads/mutex.hxx
				threads/abstract.thread.hxx
				threads/abstract.thread.h threads/abstract.thread.cpp
				threads/thread.h threads/thread.cpp
				threads/timer.h threads/timer.cpp
				threads/condition.h threads/condition.cpp threads/condition.hxx
				threads/cpu.cpp)
source_group(Threads FILES ${SRC_THREADS})

# Jobs
Set(SRC_JOBS
				jobs.h
				jobs/job.h jobs/job.cpp)
source_group(Jobs FILES ${SRC_JOBS})


# Application
Set(SRC_APPLICATION
				application/application.h application/application.cpp
				application/console.h application/console.cpp)
source_group(Core\\Application FILES ${SRC_APPLICATION})


Set(SRC_GFX_CORE
		gfx/point2D.h gfx/point3D.h gfx/vector3D.h gfx/vector3D.hxx
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
		${SRC_CORE_ALLOCATOR}
		${SRC_CORE_ATOMIC}
		${SRC_CORE_PREPROCESSOR}
		${SRC_CORE_EXCEPTIONS}
		${SRC_CORE_FUNCTION}
		${SRC_CORE_STRING}
		${SRC_CORE_STL} ${SRC_CORE_VALIDATOR}
		${SRC_CORE_LOGS}
		${SRC_CORE_SMARTPTR}
		${SRC_CORE_ANY}
		${SRC_CORE_VARIANT}
		${SRC_CORE_DYNAMICLIBRARY}
		${SRC_CORE_BIND} ${SRC_CORE_EVENT}
		${SRC_CORE_MATH}
		${SRC_CORE_HASH_CHECKSUM}
		${SRC_CORE_TREE_N}
		${SRC_PREDICATES_RESULTS}
		${SRC_GFX_CORE}
		${SRC_CORE_UNIT}
		${SRC_CORE_URI}
		${SRC_CORE_FS}
		${SRC_CORE_GETOPT}
		${SRC_CORE_VERSION}
		${SRC_CORE_SYSTEM}
		${SRC_CORE_SYSTEM_WINDOWS}
		${SRC_CORE_SYSTEM_CONSOLE}
		${SRC_THREADS} ${SRC_JOBS}
		${SRC_APPLICATION}
	)

