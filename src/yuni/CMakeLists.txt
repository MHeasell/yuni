
Message(STATUS "")
Message(STATUS "Modules")
Message(STATUS "")

Include("${CMAKE_CURRENT_SOURCE_DIR}/../CommonSettings.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../Modules.cmake")

Message(STATUS "Module: Core")



Set(SRC_TOOLBOX_PREPROCESSOR
				toolbox/preprocessor/std.h
				toolbox/preprocessor/capabilities.h
				toolbox/preprocessor/enum.h)
source_group(ToolBox\\Preprocessor FILES ${SRC_TOOLBOX_PREPROCESSOR})

Set(SRC_TOOLBOX_STATIC
				toolbox/static/if.h
				toolbox/static/remove.h
				toolbox/static/assert.h
				toolbox/static/types.h
				toolbox/static/moveconstructor.h)
source_group(ToolBox\\Static FILES ${SRC_TOOLBOX_STATIC})

Set(SRC_TOOLBOX_EXCEPTIONS
				toolbox/exceptions.h
				toolbox/exceptions/badcast.h )
source_group(ToolBox\\Exceptions FILES ${SRC_TOOLBOX_EXCEPTIONS})

Set(SRC_TOOLBOX_FUNCTION
				toolbox/function/function.h toolbox/function/function.hxx
				toolbox/function.h )
source_group(ToolBox\\Function FILES ${SRC_TOOLBOX_FUNCTION})

Set(SRC_TOOLBOX_DYNAMICLIBRARY
				toolbox/dynamiclibrary/file.h	toolbox/dynamiclibrary/file.hxx
				toolbox/dynamiclibrary/file.cpp
				toolbox/dynamiclibrary/symbol.h toolbox/dynamiclibrary/symbol.hxx
				toolbox/dynamiclibrary.h )
source_group(ToolBox\\DynamicLibrary FILES ${SRC_TOOLBOX_DYNAMICLIBRARY})




Set(SRC_TOOLBOX_STRING
				toolbox/string/string.h toolbox/string/string.hxx
				toolbox/string/string.converters.from.hxx toolbox/string/string.converters.to.hxx
				toolbox/string/string.forward.h
				toolbox/string/string.private.hxx
				toolbox/string/string.iterators.hxx
				toolbox/string.h)
source_group(ToolBox\\String FILES ${SRC_TOOLBOX_STRING})

Set(SRC_TOOLBOX_STL
				toolbox/stl/algorithm.h)
source_group(ToolBox\\Stl FILES ${SRC_TOOLBOX_STL})

Set(SRC_TOOLBOX_ANY
				toolbox/any.h
				toolbox/any/any.h
				toolbox/any/any.private.h
				toolbox/any/any.hxx
				toolbox/any/any.cpp)
source_group(ToolBox\\Any FILES ${SRC_TOOLBOX_ANY})

Set(SRC_TOOLBOX_VARIANT
				toolbox/variant.h
				toolbox/variant/variant.h
				toolbox/variant/variant.hxx
				toolbox/variant/variant.cpp
				toolbox/variant/variant.private.h
				toolbox/variant/variant.private.hxx)
source_group(ToolBox\\Variant FILES ${SRC_TOOLBOX_VARIANT})

Set(SRC_TOOLBOX_POLICIES
				toolbox/policies/threading.h
				toolbox/policies/checking.h
				toolbox/policies/ownership.h
				toolbox/policies/storage.h
				toolbox/policies/constness.h)
source_group(ToolBox\\Policies FILES ${SRC_TOOLBOX_SMARTPTR})


Set(SRC_TOOLBOX_SMARTPTR
				toolbox/smartptr/sharedptr.h toolbox/smartptr/sharedptr.hxx
				toolbox/smartptr/scopeptr.h
				toolbox/smartptr/smartptr.h  toolbox/smartptr/smartptr.hxx
				)
source_group(ToolBox\\SmartPtr FILES ${SRC_TOOLBOX_SMARTPTR})

Set(SRC_TOOLBOX_TREE_N
				toolbox/tree/treeN.h  toolbox/tree/treeN.hxx
				toolbox/tree/treeN.iterator.def.h  toolbox/tree/treeN.iterator.undef.h
				toolbox/tree/treeN.iterator.h
				)
source_group(ToolBox\\Tree FILES ${SRC_TOOLBOX_TREE_N})


Set(SRC_TOOLBOX_UNIT
				toolbox/unit/define.h toolbox/unit/undef.h
				toolbox/unit/unit.h toolbox/unit/unit.hxx
				toolbox/unit.h
				toolbox/unit/angle.h
				toolbox/unit/length.h
				toolbox/unit/length/length.h
				toolbox/unit/length/metric.h
				toolbox/unit/length/extra.h
				toolbox/unit/luminance.h
)
source_group(ToolBox\\Unit FILES ${SRC_TOOLBOX_UNIT})


Set(SRC_TOOLBOX_EVENT
				toolbox/event/event.h toolbox/event/event.hxx
				toolbox/event/event.declaration.h
				toolbox/event/event.defines.h toolbox/event/event.undef.h
				toolbox/event.h)
source_group(ToolBox\\Event FILES ${SRC_TOOLBOX_EVENT})

Set(SRC_TOOLBOX_URI
				toolbox/uri/uri.private.h  toolbox/uri/uri.private.cpp
				toolbox/uri/uri.h  toolbox/uri/uri.cpp
				toolbox/uri.h)
source_group(ToolBox\\Event FILES ${SRC_TOOLBOX_EVENT})


Set(SRC_TOOLBOX_MATH
				# Standard functions
				toolbox/math/math.h 	toolbox/math.h
				# Log(N)
				toolbox/math/log.h toolbox/math/log.hxx
				# Trigonometric functions
				toolbox/math/trigonometric.h toolbox/math/trigonometric.hxx
				# Exponential functions
				toolbox/math/exponential.h toolbox/math/exponential.hxx
				# Random number generators
				toolbox/math/random/distribution.h  toolbox/math/random/distribution.hxx
				toolbox/math/random/default.h  toolbox/math/random/default.hxx
				toolbox/math/random/range.h  toolbox/math/random/range.hxx
				toolbox/math/random/constant.h
)
source_group(ToolBox\\Math FILES ${SRC_TOOLBOX_MATH})

Set(SRC_TOOLBOX_FS
				toolbox/fs/paths.h toolbox/fs/paths.cpp  toolbox/paths.h
				toolbox/fs/files.h toolbox/fs/files.cpp  toolbox/files.h)
source_group(ToolBox\\FileSystem FILES ${SRC_TOOLBOX_FS})


Set(SRC_TOOLBOX_GETOPT
				toolbox/getopt/getopt.h
				toolbox/getopt/option.h toolbox/getopt/option.hxx toolbox/getopt/option.cpp
				toolbox/getopt/parser.h toolbox/getopt/parser.hxx toolbox/getopt/parser.cpp)
source_group(ToolBox\\GetOpt FILES ${SRC_TOOLBOX_GETOPT})


Set(SRC_VERSION	toolbox/version/version.h  toolbox/version/version.cpp)
source_group(ToolBox\\Version FILES ${SRC_VERSION})


# Hash - Checksums
Set(SRC_TOOLBOX_HASH_CHECKSUM
				toolbox/hash/checksum/checksum.h toolbox/hash/checksum/checksum.cpp
				toolbox/hash/checksum/md5.h toolbox/hash/checksum/md5.cpp)
source_group(ToolBox\\Hash\\Checksum FILES ${SRC_TOOLBOX_HASH_CHECKSUM})

# hash
Set(SRC_TOOLBOX_HASH
				toolbox/hash/std.hashmap.h
				toolbox/hash/key.h
				toolbox/hash/table.h toolbox/hash/table.hxx
				toolbox/hash/dictionary.h)
source_group(ToolBox\\Hash FILES ${SRC_TOOLBOX_HASH})

# System
Set(SRC_TOOLBOX_SYSTEM
				toolbox/system/stdint.h toolbox/system/capabilities.h
				toolbox/system/sleep.h toolbox/system/sleep.cpp
				toolbox/system/endian.h)
source_group(ToolBox\\System FILES ${SRC_TOOLBOX_SYSTEM})


# System - Microsoft Windows
Set(SRC_TOOLBOX_SYSTEM_WINDOWS toolbox/system/windows.hdr.h  toolbox/system/windows/gettimeofday.h)
If(WIN32 AND MSVC)
	Set(SRC_TOOLBOX_SYSTEM_WINDOWS ${SRC_TOOLBOX_SYSTEM_WINDOWS} toolbox/system/windows/gettimeofday.cpp)
EndIF(WIN32 AND MSVC)
source_group(ToolBox\\System\\Windows FILES ${SRC_TOOLBOX_SYSTEM_WINDOWS})


# Threads
Set(SRC_THREADS
				threads/mutex.h threads/mutex.cpp
				threads/abstract.thread.h threads/abstract.thread.cpp
				threads/thread.h threads/thread.cpp
				threads/timer.h threads/timer.cpp
				threads/cpu.cpp)
source_group(Threads FILES ${SRC_THREADS})

# Jobs
Set(SRC_JOBS
				jobs.h
				jobs/job.h jobs/job.cpp)
source_group(Jobs FILES ${SRC_THREADS})


# Application
Set(SRC_APPLICATION
				application/application.h application/application.cpp
				application/console.h application/console.cpp)
source_group(Application FILES ${SRC_APPLICATION})

Set(SRC_GFX_CORE
		gfx/color.proxy.h gfx/color.proxy.cpp
		gfx/point2D.h gfx/point3D.h gfx/vector3D.h
		gfx/octree.h gfx/octree.cpp
		gfx/rgba.h gfx/rgb.h)
source_group(Gfx FILES ${SRC_RGB})

# Devices
Set(SRC_DEVICES
		system/devices/devices.h system/devices/display.cpp
		system/devices/monitor.h system/devices/monitor.cpp
		system/devices/resolution.h system/devices/resolution.cpp)
source_group(System\\Devices FILES ${SRC_DEVICES})

Set(SRC_APPLICATION_GFX
		application/gfx3d.h application/gfx3d.cpp)
source_group(Application FILES ${SRC_APPLICATION_GFX})

# Gfx
Set(SRC_GFX
		gfx/device.h gfx/device.cpp
		gfx/vertex.h gfx/triangle.h gfx/edge.h
		gfx/object3D.h gfx/object3D.cpp
		gfx/objectmodel.h gfx/scene.h gfx/scene.cpp
		gfx/skeleton.h gfx/mesh.h gfx/mesh.cpp gfx/mesh.proxy.h
		gfx/implicitsurface.h gfx/implicitsurface.cpp gfx/implicitsurfmanager.h
		gfx/metaobject.h gfx/metaball.h  gfx/metaball.cpp  gfx/metabox.h
		gfx/boundingbox.h gfx/boundingbox.hxx
		gfx/polygonizer.h gfx/marchingcubes.h gfx/marchingcubes.cpp
		gfx/engine.h gfx/engine.cpp)
source_group(Gfx FILES ${SRC_GFX})


# External Lib: Irrlicht
Set(SRC_EXTERNAL_3D_IRRLICHT
		private/gfx3d/irrlicht/irr.h
		private/gfx3d/irrlicht/irr.engine.h private/gfx3d/irrlicht/irr.engine.cpp
		private/gfx3d/irrlicht/irr.mesh.h private/gfx3d/irrlicht/irr.mesh.cpp)
source_group("Private\\Gfx3D\\Irrlicht" FILES ${SRC_EXTERNAL_3D_IRRLICHT})

Set(SRC_EXTERNAL_3D
		private/gfx3d/abstract.h private/gfx3d/abstract.cpp
		${YUNI_EXT_IRRLICHT_SRC}  # From DevPack 'irrlicht-headers'
		${SRC_EXTERNAL_3D_IRRLICHT})


#
# The core library
#
Add_Library(yuni-static-core STATIC
			${SRC_TOOLBOX_PREPROCESSOR}
			${SRC_TOOLBOX_STATIC}
			${SRC_TOOLBOX_STRING}
			${SRC_TOOLBOX_URI}
			${SRC_TOOLBOX_UNIT}
			${SRC_TOOLBOX_EXCEPTIONS}
			${SRC_TOOLBOX_FUNCTION}
			${SRC_TOOLBOX_DYNAMICLIBRARY}
			${SRC_TOOLBOX_STL}
			${SRC_TOOLBOX_ANY}
			${SRC_TOOLBOX_VARIANT}
			${SRC_TOOLBOX_POLICIES}
			${SRC_TOOLBOX_SMARTPTR}
			${SRC_TOOLBOX_TREE_N}
			${SRC_TOOLBOX_EVENT} ${SRC_VERSION}
			${SRC_TOOLBOX_MATH} ${SRC_TOOLBOX_GETOPT} ${SRC_TOOLBOX_FS}
			${SRC_TOOLBOX_HASH_CHECKSUM} ${SRC_TOOLBOX_HASH}
			${SRC_TOOLBOX_SYSTEM} ${SRC_TOOLBOX_SYSTEM_WINDOWS}
			${SRC_THREADS} ${SRC_JOBS}
			${SRC_APPLICATION} ${SRC_GFX_CORE} )



#
# Module : Network
#
If(YUNI_MODULE_NET)

	Message(STATUS "Module: Network")

	# Scripts
	Set(SRC_NET
			net/protocol.h  net/protocol.cpp
		)
	source_group("Network\\Protocol" FILES ${SRC_NET})

	Add_Library(yuni-static-net STATIC
				${SRC_NET}
				)

EndIf(YUNI_MODULE_NET)




#
# Module : GFX 3D
#
If(YUNI_MODULE_GFX3D)

	Message(STATUS "Module: Gfx3D")

	if(YUNI_EXTERNAL_3D_IRRLICHT)
		Message(STATUS "Module: Gfx3D::Irrlicht")
		# Headers for Irrlicht
		DEVPACK_IMPORT_IRRLICHT()

		Set(SRC_EXTERNAL_3D
			${SRC_EXTERNAL_3D}
			${YUNI_EXT_IRRLICHT_SRC}  # From DevPack 'irrlicht-headers'
			)

	Endif(YUNI_EXTERNAL_3D_IRRLICHT)

	Add_Library(yuni-static-gfx3d STATIC
				${SRC_DEVICES} ${SRC_APPLICATION_GFX}
				${SRC_GFX}
				${SRC_EXTERNAL_3D}
				)

EndIf(YUNI_MODULE_GFX3D)

#
# Module : Script
#
If(YUNI_MODULE_SCRIPT)

	Message(STATUS "Module: Script")

	# Scripts
	Set(SRC_SCRIPT
				script.h
				script/script.h script/script.cpp
				private/script/script.defines.h private/script/script.undefs.h
		)
	source_group("Script\\Script Abstraction" FILES ${SRC_SCRIPT})

	# External Lib: Lua script
	if(YUNI_EXTERNAL_SCRIPT_LUA)
		Message(STATUS "Module: Script::Lua")
		# Headers for Lua
		DEVPACK_IMPORT_LUA()
		Set(SRC_EXTERNAL_SCRIPT_LUA
				${YUNI_EXT_LUA_SRC}  # From DevPack 'lua'
				script/lua.h script/lua.cpp
				private/script/lua.proxy.h private/script/lua.proxy.cpp
			)
		source_group("Script\\Script Lua language support" FILES ${SRC_EXTERNAL_SCRIPT_LUA})

	Endif(YUNI_EXTERNAL_SCRIPT_LUA)

	Add_Library(yuni-static-script STATIC
				${SRC_SCRIPT}
				${SRC_EXTERNAL_SCRIPT_LUA}
				)

EndIf(YUNI_MODULE_SCRIPT)


#
# Module : User Interface
#
If(YUNI_MODULE_UI)

	Message(STATUS "Module: UI::Core (User Interface)")

	# User Interface
	Set(SRC_GFX_UI
				ui/component.h ui/component.cpp
				ui/control.h ui/control.cpp ui/anchor.cpp
				ui/controller.h ui/controller.cpp)
	source_group("Gfx\\User Interface" FILES ${SRC_GFX_UI})

	Add_Library(yuni-static-ui-core STATIC
				${SRC_GFX_UI}
				)

	IF(YUNI_MODULE_UI_DUMMY)

		Message(STATUS "Module: UI::Dummy")

	ENDIF(YUNI_MODULE_UI_DUMMY)


	IF(YUNI_MODULE_UI_3D)

		Message(STATUS "Module: UI::Gfx3D")

	ENDIF(YUNI_MODULE_UI_3D)

EndIf(YUNI_MODULE_UI)




#
# Module : Database
#
If(YUNI_MODULE_DATABASEI)

	Message(STATUS "Module: Database::Core")

	# Database
	Set(SRC_DB
			sql/driver.h
			sql/database.h  sql/database.cpp)
	source_group("Database" FILES ${SRC_DB})

	Add_Library(yuni-static-database-core STATIC ${SRC_DB})

	IF(YUNI_MODULE_DB_PSQL)
		Set(SRC_DB_PSQL	 private/sql/postgresql/driver.h  private/sql/postgresql/driver.cpp)
		Add_Library(yuni-static-database-postgresql STATIC ${SRC_DB_PSQL})
		Message(STATUS "Module: Database::PostgreSQL")
	ENDIF(YUNI_MODULE_DB_PSQL)

EndIf(YUNI_MODULE_DATABASEI)




#
# Misc
#
Add_definitions("-DYUNI_LIBRARY_STATIC")
Include_directories(${YUNI_INCLUDE})


