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

set(SRC_POLICIES
				policies/threads.h)
source_group(Policies FILES ${SRC_POLICIES})

# Misc
set(SRC_MISC
				misc/string.h misc/string.cpp
				misc/paths.h misc/paths.cpp
				misc/files.h misc/files.cpp
				misc/version.h misc/version.cpp
				misc/static.h
				misc/math.h
				misc/sharedptr.h misc/scopeptr.h
				misc/event.h misc/event.proxy.h misc/event.private.h misc/event.cpp)

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
                system/sleep.h system/sleep.cpp
				system/endian.h)
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
				threads/cpu.cpp)
source_group(Threads FILES ${SRC_THREADS})

# Jobs
set(SRC_JOBS
				jobs.h
				jobs/abstract.h jobs/abstract.cpp)
source_group(Jobs FILES ${SRC_THREADS})


# Application
set(SRC_APPLICATION
				application/abstract.h application/abstract.cpp
				application/console.h application/console.cpp
				application/gfx3d.h application/gfx3d.cpp)
source_group(Application FILES ${SRC_APPLICATION})



# Gfx
set(SRC_GFX
				gfx/device.h gfx/device.cpp
				gfx/point2D.h gfx/point3D.h gfx/vector3D.h
				gfx/color.proxy.h gfx/color.proxy.cpp
				gfx/rgba.h gfx/rgb.h
				gfx/boundingbox.h
				gfx/vertex.h gfx/triangle.h gfx/edge.h gfx/mesh.h
				gfx/implicitsurface.h gfx/implicitsurface.cpp gfx/implicitsurfmanager.h
				gfx/metaobject.h gfx/metaball.h
				gfx/polygonizer.h gfx/marchingcubes.h gfx/marchingcubes.cpp
				gfx/octree.h gfx/octree.hxx
				gfx/engine.h gfx/engine.cpp)
source_group(Gfx FILES ${SRC_GFX})


# User Interface
set(SRC_GFX_UI
				gfx/ui/component.h gfx/ui/component.cpp
				gfx/ui/control.h gfx/ui/control.cpp gfx/ui/anchor.cpp
				gfx/ui/controller.h gfx/ui/controller.cpp)
source_group("Gfx\\User Interface" FILES ${SRC_GFX_UI})



# External Lib: Irrlicht
#Set(SRC ${SRC}
#				private/gfx3d/irrlicht/irrlicht-for-yuni.h private/gfx3d/irrlicht/irrlicht-for-yuni.cpp)

set(SRC_EXTERNAL_3D_IRRLICHT
				private/gfx3d/irrlicht/irr.h
				private/gfx3d/irrlicht/irr.engine.h private/gfx3d/irrlicht/irr.engine.cpp)
source_group("Private\\Gfx3D\\Irrlicht" FILES ${SRC_EXTERNAL_3D_IRRLICHT})


if(YUNI_EXTERNAL_3D_IRRLICHT)
	Message(STATUS "External: 3D: The Irrlicht Engine")
	set(SRC_EXTERNAL_3D
				private/gfx3d/abstract.h private/gfx3d/abstract.cpp
				${SRC_EXTERNAL_3D_IRRLICHT})
Endif(YUNI_EXTERNAL_3D_IRRLICHT)



Add_definitions("-DYUNI_LIBRARY_STATIC")
Add_Library(yuni-static STATIC
				${SRC_POLICIES} ${SRC_MISC}
				${SRC_HASH_CHECKSUM} ${SRC_HASH}
				${SRC_SYSTEM} ${SRC_SYSTEM_WINDOWS}
				${SRC_DEVICES}
				${SRC_THREADS} ${SRC_JOBS}
				${SRC_APPLICATION}
				${SRC_GFX} ${SRC_GFX_UI}
				${SRC_EXTERNAL_3D}
				)

SET_TARGET_PROPERTIES(yuni-static PROPERTIES OUTPUT_NAME "yuni")

