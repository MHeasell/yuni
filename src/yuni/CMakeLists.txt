Project(YUNI)

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
set(SRC "")

# Misc
set(SRC ${SRC}
				misc/string.h misc/string.cpp
				misc/paths.h misc/paths.cpp
				misc/files.h misc/files.cpp
				misc/version.h misc/version.cpp
				misc/static.h
				misc/math.h)

# Hash
set(SRC ${SRC}
				hash/checksum/abstract.h hash/checksum/abstract.cpp
				hash/checksum/md5.h hash/checksum/md5.cpp
				hash/std.hashmap.h
				hash/key.h
				hash/table.h hash/table.hxx
				hash/dictionary.h)

# System
set(SRC ${SRC}
                system/stdint.h system/os.h
                system/windows.hdr.h  system/windows/gettimeofday.h
                system/sleep.h system/sleep.cpp) 
If(WIN32 AND MSVC)
    set(SRC ${SRC} system/windows/gettimeofday.cpp)
EndIF(WIN32 AND MSVC)

# Devices
set(SRC ${SRC}
				system/devices/devices.h system/devices/display.cpp
				system/devices/monitor.h system/devices/monitor.cpp
				system/devices/resolution.h system/devices/resolution.cpp) 

# Threads
set(SRC ${SRC}
				threads/mutex.h threads/mutex.cpp
				threads/abstract.thread.h threads/abstract.thread.cpp
				threads/thread.h threads/thread.cpp
				threads/timer.h threads/timer.cpp
				threads/jobs.abstract.h threads/jobs.abstract.cpp
				threads/cpu.cpp)

# Application
set(SRC ${SRC}
				application/abstract.h application/abstract.cpp
				application/console.h application/console.cpp
				application/gfx3d.h application/gfx3d.cpp)

# Gfx
set(SRC ${SRC}
				gfx/device.h gfx/device.cpp
				gfx/point2D.h gfx/point3D.h
				gfx/color.converters.h gfx/color.converters.cpp
				gfx/rgba.h
				gfx/vertex.h gfx/triangle.h gfx/edge.h)

# User Interface
set(SRC ${SRC}
				gfx/ui/window.h gfx/ui/window.cpp
				gfx/ui/component.h gfx/ui/component.cpp)


# External Lib: Irrlicht
#Set(SRC ${SRC}
#				private/gfx3d/irrlicht/irrlicht-for-yuni.h private/gfx3d/irrlicht/irrlicht-for-yuni.cpp)




Add_Library(yuni STATIC ${SRC})


