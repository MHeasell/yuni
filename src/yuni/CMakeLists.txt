
Message(STATUS "")
Message(STATUS "Modules")
Message(STATUS "")

Include("${CMAKE_CURRENT_SOURCE_DIR}/../CommonSettings.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../Modules.cmake")

Message(STATUS "Module: Core")



Set(SRC_CORE_PREPROCESSOR
				core/preprocessor/std.h
				core/preprocessor/capabilities.h
				core/preprocessor/capabilities/unixes.h
				core/preprocessor/capabilities/windows.h
				core/preprocessor/enum.h)
source_group(ToolBox\\Preprocessor FILES ${SRC_CORE_PREPROCESSOR})

Set(SRC_CORE_STATIC
				core/static/if.h
				core/static/remove.h
				core/static/assert.h
				core/static/types.h
				core/static/moveconstructor.h)
source_group(ToolBox\\Static FILES ${SRC_CORE_STATIC})

Set(SRC_CORE_EXCEPTIONS
				core/exceptions.h
				core/exceptions/badcast.h )
source_group(ToolBox\\Exceptions FILES ${SRC_CORE_EXCEPTIONS})

Set(SRC_CORE_FUNCTION
				core/function/function.h core/function/function.hxx
				core/function.h )
source_group(ToolBox\\Function FILES ${SRC_CORE_FUNCTION})

Set(SRC_CORE_DYNAMICLIBRARY
				core/dynamiclibrary/file.h	core/dynamiclibrary/file.hxx
				core/dynamiclibrary/file.cpp
				core/dynamiclibrary/symbol.h core/dynamiclibrary/symbol.hxx
				core/dynamiclibrary.h )
source_group(ToolBox\\DynamicLibrary FILES ${SRC_CORE_DYNAMICLIBRARY})



Set(SRC_CORE_STRING
				core/string/string.h core/string/string.hxx
				core/string/converters.from.hxx core/string/converters.to.hxx
				core/string/forward.h
				core/string/traits.hxx
				core/string/iterators.hxx
				core/string.h)
source_group(ToolBox\\String FILES ${SRC_CORE_STRING})


Set(SRC_CORE_LOGS
				core/logs/logs.h core/logs/logs.hxx core/logs/verbosity.h
				core/logs/null.h	core/logs/stream.h
				# Handlers
				core/logs/handlers/stdcout.h
				# Decorators
				core/logs/decorators/verbositylevel.h
				core/logs/decorators/time.h
				core/logs/decorators/applicationname.h
				core/logs/decorators/message.h
				core/logs.h)
source_group(ToolBox\\Logs FILES ${SRC_CORE_LOGS})


Set(SRC_CORE_STL
				core/stl/algorithm.h)
source_group(ToolBox\\Stl FILES ${SRC_CORE_STL})

Set(SRC_CORE_ANY
				core/any.h
				core/any/any.h
				core/any/any.private.h
				core/any/any.hxx
				core/any/any.cpp)
source_group(ToolBox\\Any FILES ${SRC_CORE_ANY})

Set(SRC_CORE_VARIANT
				core/variant.h
				core/variant/variant.h
				core/variant/variant.hxx
				core/variant/variant.cpp
				core/variant/variant.private.h
				core/variant/variant.private.hxx)
source_group(ToolBox\\Variant FILES ${SRC_CORE_VARIANT})

Set(SRC_CORE_POLICIES
				core/policies/threading.h
				core/policies/checking.h
				core/policies/ownership.h
				core/policies/storage.h
				core/policies/constness.h)
source_group(ToolBox\\Policies FILES ${SRC_CORE_SMARTPTR})


Set(SRC_CORE_SMARTPTR
				core/smartptr/sharedptr.h core/smartptr/sharedptr.hxx
				core/smartptr/scopeptr.h
				core/smartptr/smartptr.h  core/smartptr/smartptr.hxx
				)
source_group(ToolBox\\SmartPtr FILES ${SRC_CORE_SMARTPTR})

Set(SRC_CORE_TREE_N
				core/tree/treeN.h  core/tree/treeN.hxx
				core/tree/treeN.iterator.def.h  core/tree/treeN.iterator.undef.h
				core/tree/treeN.iterator.h
				)
source_group(ToolBox\\Tree FILES ${SRC_CORE_TREE_N})


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
source_group(ToolBox\\Unit FILES ${SRC_CORE_UNIT})


Set(SRC_CORE_EVENT
				core/event/event.h core/event/event.hxx
				core/event/event.declaration.h
				core/event/event.defines.h core/event/event.undef.h
				core/event.h)
source_group(ToolBox\\Event FILES ${SRC_CORE_EVENT})

Set(SRC_CORE_URI
				core/uri/uri.private.h  core/uri/uri.private.cpp
				core/uri/uri.h  core/uri/uri.cpp
				core/uri.h)
source_group(ToolBox\\Event FILES ${SRC_CORE_EVENT})


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
source_group(ToolBox\\Math FILES ${SRC_CORE_MATH})

Set(SRC_CORE_FS
				core/fs/paths.h core/fs/paths.cpp  core/paths.h
				core/fs/files.h core/fs/files.cpp  core/files.h)
source_group(ToolBox\\FileSystem FILES ${SRC_CORE_FS})


Set(SRC_CORE_GETOPT
				core/getopt/getopt.h
				core/getopt/option.h core/getopt/option.hxx core/getopt/option.cpp
				core/getopt/parser.h core/getopt/parser.hxx core/getopt/parser.cpp)
source_group(ToolBox\\GetOpt FILES ${SRC_CORE_GETOPT})


Set(SRC_VERSION	core/version/version.h  core/version/version.cpp)
source_group(ToolBox\\Version FILES ${SRC_VERSION})


# Hash - Checksums
Set(SRC_CORE_HASH_CHECKSUM
				core/hash/checksum/checksum.hxx
				core/hash/checksum/md5.hxx
				core/hash/checksum/checksum.h core/hash/checksum/checksum.cpp
				core/hash/checksum/md5.h core/hash/checksum/md5.cpp)
source_group(ToolBox\\Hash\\Checksum FILES ${SRC_CORE_HASH_CHECKSUM})

# System
Set(SRC_CORE_SYSTEM
				core/system/stdint.h core/system/capabilities.h
				core/system/sleep.h core/system/sleep.cpp
				core/system/endian.h)
source_group(ToolBox\\System FILES ${SRC_CORE_SYSTEM})


# System - Microsoft Windows
Set(SRC_CORE_SYSTEM_WINDOWS core/system/windows.hdr.h  core/system/windows/gettimeofday.h)
If(WIN32 AND MSVC)
	Set(SRC_CORE_SYSTEM_WINDOWS ${SRC_CORE_SYSTEM_WINDOWS} core/system/windows/gettimeofday.cpp)
EndIF(WIN32 AND MSVC)
source_group(ToolBox\\System\\Windows FILES ${SRC_CORE_SYSTEM_WINDOWS})


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
		gfx/point2D.h gfx/point3D.h gfx/vector3D.h gfx/vector3D.hxx
		gfx/octree.h gfx/octree.cpp
		# Color
		gfx/core/color/rgba.h gfx/core/color/rgb.h
		gfx/core/color/proxy.h gfx/core/color/proxy.cpp
		)
source_group(Gfx FILES ${SRC_GFX_CORE})

# Devices
Set(SRC_GFX_CORE_DEVICES
		device/display/list/list.h device/display/list/list.cpp
		device/display/list/list.hxx device/display/list.h
		device/display/list/windows.hxx device/display/list/macosx.hxx
		device/display/list/linux.hxx
		device/display/monitor.h device/display/monitor.cpp
		device/display/resolution.h device/display/resolution.cpp)
source_group(Devices\\Display FILES ${SRC_GFX_CORE_DEVICES})

Set(SRC_APPLICATION_GFX
		application/gfx3d.h application/gfx3d.cpp)
source_group(Application FILES ${SRC_APPLICATION_GFX})

# Gfx
Set(SRC_GFX
		gfx/device.h gfx/device.cpp
		gfx/vertex.h gfx/triangle.h gfx/edge.h
		gfx/imagescaler.h gfx/image.h gfx/image.hxx
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

# External Lib: Ogre3D
Set(SRC_EXTERNAL_3D_OGRE
		private/gfx3d/ogre/ogre.h
		private/gfx3d/ogre/ogre.engine.h private/gfx3d/ogre/ogre.engine.cpp
		private/gfx3d/ogre/ogre.mesh.h private/gfx3d/ogre/ogre.mesh.cpp)
source_group("Private\\Gfx3D\\Ogre" FILES ${SRC_EXTERNAL_3D_OGRE})

IF(YUNI_EXTERNAL_3D_IRRLICHT)
	Set(SRC_EXTERNAL_3D
		private/gfx3d/abstract.h private/gfx3d/abstract.cpp
		${YUNI_EXT_IRRLICHT_SRC}  # From DevPack 'irrlicht-headers'
		${SRC_EXTERNAL_3D_IRRLICHT})
ENDIF(YUNI_EXTERNAL_3D_IRRLICHT)

IF(YUNI_EXTERNAL_3D_OGRE)
	Set(SRC_EXTERNAL_3D
		private/gfx3d/abstract.h private/gfx3d/abstract.cpp
		${YUNI_EXT_OGRE_SRC}  # From DevPack 'ogre-headers'
		${SRC_EXTERNAL_3D_OGRE})
ENDIF(YUNI_EXTERNAL_3D_OGRE)



Add_Library(yuni-static-gfx-core STATIC
			${SRC_GFX_CORE} ${SRC_GFX_CORE_DEVICES}
)
target_link_libraries(yuni-static-gfx-core yuni-static-core)


#
# The core library
#
Add_Library(yuni-static-core STATIC
			${SRC_CORE_PREPROCESSOR}
			${SRC_CORE_STATIC}
			${SRC_CORE_STRING}
			${SRC_CORE_LOGS}
			${SRC_CORE_URI}
			${SRC_CORE_UNIT}
			${SRC_CORE_EXCEPTIONS}
			${SRC_CORE_FUNCTION}
			${SRC_CORE_DYNAMICLIBRARY}
			${SRC_CORE_STL}
			${SRC_CORE_ANY}
			${SRC_CORE_VARIANT}
			${SRC_CORE_POLICIES}
			${SRC_CORE_SMARTPTR}
			${SRC_CORE_TREE_N}
			${SRC_CORE_EVENT} ${SRC_VERSION}
			${SRC_CORE_MATH} ${SRC_CORE_GETOPT} ${SRC_CORE_FS}
			${SRC_CORE_HASH_CHECKSUM} ${SRC_CORE_HASH}
			${SRC_CORE_SYSTEM} ${SRC_CORE_SYSTEM_WINDOWS}
			${SRC_THREADS} ${SRC_JOBS}
			${SRC_APPLICATION})



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

	If(YUNI_EXTERNAL_3D_IRRLICHT)
		Message(STATUS "Module: Gfx3D::Irrlicht")
		# Headers for Irrlicht
		DEVPACK_IMPORT_IRRLICHT()

		Set(SRC_EXTERNAL_3D
			${SRC_EXTERNAL_3D}
			${YUNI_EXT_IRRLICHT_SRC}  # From DevPack 'irrlicht-headers'
			)
	Endif(YUNI_EXTERNAL_3D_IRRLICHT)

	If(YUNI_EXTERNAL_3D_OGRE)
		Message(STATUS "Module: Gfx3D::Ogre")
		# Headers for Ogre
		DEVPACK_IMPORT_OGRE()

		Set(SRC_EXTERNAL_3D
			${SRC_EXTERNAL_3D}
			${YUNI_EXT_OGRE_SRC}  # From DevPack 'ogre-headers'
			)
	Endif(YUNI_EXTERNAL_3D_OGRE)

	Add_Library(yuni-static-gfx3d STATIC
				${SRC_GFX}
				${SRC_APPLICATION_GFX}
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


