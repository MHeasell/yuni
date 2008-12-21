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
set(SRC_TOOLBOX_STATIC
				toolbox/static/if.h
				toolbox/static/remove.h
				toolbox/static/assert.h
				toolbox/static/types.h)
source_group(ToolBox\\Static FILES ${SRC_TOOLBOX_STATIC})


set(SRC_TOOLBOX_STRING
				toolbox/string/string.h toolbox/string/string.cpp
				toolbox/string.h)
source_group(ToolBox\\String FILES ${SRC_TOOLBOX_STRING})

set(SRC_TOOLBOX_STL
				toolbox/stl/algorithm.h)
source_group(ToolBox\\Stl FILES ${SRC_TOOLBOX_STL})


set(SRC_TOOLBOX_POLICIES
				toolbox/policies/threading.h
				toolbox/policies/checking.h
				toolbox/policies/ownership.h
				toolbox/policies/storage.h
				toolbox/policies/constness.h)
source_group(ToolBox\\Policies FILES ${SRC_TOOLBOX_SMARTPTR})


set(SRC_TOOLBOX_SMARTPTR
				toolbox/smartptr/sharedptr.h toolbox/smartptr/sharedptr.hxx
				toolbox/smartptr/scopeptr.h)
source_group(ToolBox\\SmartPtr FILES ${SRC_TOOLBOX_SMARTPTR})


set(SRC_TOOLBOX_EVENT
				toolbox/event/event.h toolbox/event/event.cpp
				toolbox/event/event.private.h toolbox/event/event.proxy.h
				toolbox/event.h)
source_group(ToolBox\\Event FILES ${SRC_TOOLBOX_EVENT})


set(SRC_TOOLBOX_MATH	toolbox/math/math.h  toolbox/math.h)
source_group(ToolBox\\Math FILES ${SRC_TOOLBOX_MATH})

set(SRC_TOOLBOX_FS
				toolbox/fs/paths.h toolbox/fs/paths.cpp  toolbox/paths.h
				toolbox/fs/files.h toolbox/fs/files.cpp  toolbox/files.h)
source_group(ToolBox\\FileSystem FILES ${SRC_TOOLBOX_FS})


set(SRC_TOOLBOX_GETOPT
				toolbox/getopt/getopt.h
				toolbox/getopt/convertions.h
				toolbox/getopt/convertions.hxx
				toolbox/getopt/option.h toolbox/getopt/option.hxx toolbox/getopt/option.cpp
				toolbox/getopt/parser.h toolbox/getopt/parser.hxx toolbox/getopt/parser.cpp)
source_group(ToolBox\\GetOpt FILES ${SRC_TOOLBOX_GETOPT})


set(SRC_VERSION	toolbox/version/version.h  toolbox/version/version.cpp)
source_group(ToolBox\\Version FILES ${SRC_VERSION})


# Hash - Checksums
set(SRC_TOOLBOX_HASH_CHECKSUM
				toolbox/hash/checksum/checksum.h toolbox/hash/checksum/checksum.cpp
				toolbox/hash/checksum/md5.h toolbox/hash/checksum/md5.cpp)
source_group(ToolBox\\Hash\\Checksum FILES ${SRC_TOOLBOX_HASH_CHECKSUM})

# hash
set(SRC_TOOLBOX_HASH
				toolbox/hash/std.hashmap.h
				toolbox/hash/key.h
				toolbox/hash/table.h toolbox/hash/table.hxx
				toolbox/hash/dictionary.h)
source_group(ToolBox\\Hash FILES ${SRC_TOOLBOX_HASH})

# System
set(SRC_TOOLBOX_SYSTEM
                toolbox/system/stdint.h toolbox/system/os.h
                toolbox/system/sleep.h toolbox/system/sleep.cpp
				toolbox/system/endian.h)
source_group(ToolBox\\System FILES ${SRC_TOOLBOX_SYSTEM})

# System - Microsoft Windows
set(SRC_TOOLBOX_SYSTEM_WINDOWS toolbox/system/windows.hdr.h  toolbox/system/windows/gettimeofday.h)
If(WIN32 AND MSVC)
    set(SRC_SYSTEM_WINDOWS ${SRC_TOOLBOX_SYSTEM_WINDOWS} toolbox/system/windows/gettimeofday.cpp)
EndIF(WIN32 AND MSVC)
source_group(ToolBox\\System\\Windows FILES ${SRC_TOOLBOX_SYSTEM_WINDOWS})








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
				jobs/job.h jobs/job.cpp)
source_group(Jobs FILES ${SRC_THREADS})


# Application
set(SRC_APPLICATION
				application/application.h application/application.cpp
				application/console.h application/console.cpp
				application/gfx3d.h application/gfx3d.cpp)
source_group(Application FILES ${SRC_APPLICATION})



# Gfx
set(SRC_GFX
				gfx/device.h gfx/device.cpp
				gfx/point2D.h gfx/point3D.h gfx/vector3D.h
				gfx/color.proxy.h gfx/color.proxy.cpp
				gfx/rgba.h gfx/rgb.h
				gfx/boundingbox.h gfx/boundingbox.hxx
				gfx/vertex.h gfx/triangle.h gfx/edge.h
				gfx/mesh.h gfx/mesh.cpp gfx/mesh.proxy.h
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

set(SRC_EXTERNAL_3D_IRRLICHT
				private/gfx3d/irrlicht/irr.h
				private/gfx3d/irrlicht/irr.engine.h private/gfx3d/irrlicht/irr.engine.cpp
				private/gfx3d/irrlicht/irr.mesh.h private/gfx3d/irrlicht/irr.mesh.cpp)
source_group("Private\\Gfx3D\\Irrlicht" FILES ${SRC_EXTERNAL_3D_IRRLICHT})


if(YUNI_EXTERNAL_3D_IRRLICHT)
	Message(STATUS "External: 3D: The Irrlicht Engine")
	# Headers for Irrlicht
	DEVPACK_IMPORT_IRRLICHT()
	Set(SRC_EXTERNAL_3D
				private/gfx3d/abstract.h private/gfx3d/abstract.cpp
				${YUNI_EXT_IRRLICHT_SRC}  # From DevPack 'irrlicht-headers'
				${SRC_EXTERNAL_3D_IRRLICHT})
Endif(YUNI_EXTERNAL_3D_IRRLICHT)


Add_definitions("-DYUNI_LIBRARY_STATIC")
Add_Library(yuni-static STATIC
				${SRC_TOOLBOX_STATIC} ${SRC_TOOLBOX_STRING} ${SRC_TOOLBOX_STL} ${SRC_TOOLBOX_POLICIES}
				${SRC_TOOLBOX_SMARTPTR}
				${SRC_TOOLBOX_EVENT} ${SRC_VERSION}
				${SRC_TOOLBOX_MATH} ${SRC_TOOLBOX_GETOPT} ${SRC_TOOLBOX_FS}
				${SRC_TOOLBOX_HASH_CHECKSUM} ${SRC_TOOLBOX_HASH}
				${SRC_TOOLBOX_SYSTEM} ${SRC_TOOLBOX_SYSTEM_WINDOWS}
				${SRC_DEVICES}
				${SRC_THREADS} ${SRC_JOBS}
				${SRC_APPLICATION}
				${SRC_GFX} ${SRC_GFX_UI}
				${SRC_EXTERNAL_3D}
				)

SET_TARGET_PROPERTIES(yuni-static PROPERTIES OUTPUT_NAME "yuni")

