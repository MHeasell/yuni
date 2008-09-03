Project(YUNI CXX)

Message(STATUS "")
Message(STATUS "The Yuni Framework")
Message(STATUS "")
CMake_minimum_required(VERSION 2.6)


Include("${PROJECT_SOURCE_DIR}/../CommonSettings.cmake")


#
# The target directory for static libs
#
Set(TARGET_LIBS "${PROJECT_SOURCE_DIR}/../../bin/static/")
Set(LIBRARY_OUTPUT_PATH "${TARGET_LIBS}")
Set(ARCHIVE_OUTPUT_DIRECTORY "${TARGET_LIBS}")



#
# The Yuni Library
#

# Misc
set(SRC_MISC
				misc/string.h misc/string.cpp
				misc/paths.h misc/paths.cpp
				misc/files.h misc/files.cpp
				misc/version.h misc/version.cpp
				misc/static.h
				misc/math.h)

source_group(Misc FILES ${SRC_MISC})



# hash
set(SRC_HASH
				hash/std.hashmap.h
				hash/key.h
				hash/table.h hash/table.hxx
				hash/dictionary.h)
source_group(Hash FILES ${SRC_HASH})

# Hash - Checksums
set(SRC_HASH_CHECKSUM
				hash/checksum/abstract.h hash/checksum/abstract.cpp
				hash/checksum/md5.h hash/checksum/md5.cpp)
source_group(Hash\\Checksum FILES ${SRC_HASH_CHECKSUM})



# System
set(SRC_SYSTEM
                system/stdint.h system/os.h
                system/sleep.h system/sleep.cpp) 
source_group(System FILES ${SRC_SYSTEM})

# System - Microsoft Windows
set(SRC_SYSTEM_WINDOWS system/windows.hdr.h  system/windows/gettimeofday.h)
If(WIN32 AND MSVC)
    set(SRC_SYSTEM_WINDOWS ${SRC_SYSTEM_WINDOWS} system/windows/gettimeofday.cpp)
EndIF(WIN32 AND MSVC)
source_group(System\\Windows FILES ${SRC_SYSTEM_WINDOWS})


# Devices
set(SRC_DEVICES
				system/devices/devices.h system/devices/display.cpp
				system/devices/monitor.h system/devices/monitor.cpp
				system/devices/resolution.h system/devices/resolution.cpp) 
source_group(System\\Devices FILES ${SRC_DEVICES})



# Threads
set(SRC_THREADS
				threads/mutex.h threads/mutex.cpp
				threads/abstract.thread.h threads/abstract.thread.cpp
				threads/thread.h threads/thread.cpp
				threads/timer.h threads/timer.cpp
				threads/jobs.abstract.h threads/jobs.abstract.cpp
				threads/cpu.cpp)
source_group(Threads FILES ${SRC_THREADS})



# Application
set(SRC_APPLICATION
				application/abstract.h application/abstract.cpp
				application/console.h application/console.cpp
				application/gfx3d.h application/gfx3d.cpp)
source_group(Application FILES ${SRC_APPLICATION})



# Gfx
set(SRC_GFX
				gfx/device.h gfx/device.cpp
				gfx/point2D.h gfx/point3D.h
				gfx/color.converters.h gfx/color.converters.cpp
				gfx/rgba.h
				gfx/vertex.h gfx/triangle.h gfx/edge.h)
source_group(Gfx FILES ${SRC_GFX})


# User Interface
set(SRC_GFX_UI
				gfx/ui/window.h gfx/ui/window.cpp
				gfx/ui/component.h gfx/ui/component.cpp)
source_group("Gfx\\User Interface" FILES ${SRC_GFX_UI})



# External Lib: Irrlicht
#Set(SRC ${SRC}
#				private/gfx3d/irrlicht/irrlicht-for-yuni.h private/gfx3d/irrlicht/irrlicht-for-yuni.cpp)




Add_Library(yuni STATIC
				${SRC_MISC}
				${SRC_HASH_CHECKSUM} ${SRC_HASH}
				${SRC_SYSTEM} ${SRC_SYSTEM_WINDOWS}
				${SRC_DEVICES}
				${SRC_THREADS}
				${SRC_APPLICATION}
				${SRC_GFX} ${SRC_GFX_UI}
				)


