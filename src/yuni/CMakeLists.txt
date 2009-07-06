
Message(STATUS "")
Message(STATUS "Modules")
Message(STATUS "")

Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/CommonSettings.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Modules.cmake")


# Generating yuni.h
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/yuni.h.cmake ${CMAKE_CURRENT_SOURCE_DIR}/yuni.h)



IF(YUNI_MODULE_CORE)
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/core.cmake")
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/gfx-core.cmake")
ENDIF(YUNI_MODULE_CORE)

IF(YUNI_MODULE_DEVICES)
	IF(YUNI_MODULE_DEVICE_DISPLAY)
		Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/device-display.cmake")
	ENDIF(YUNI_MODULE_DEVICE_DISPLAY)
	IF(YUNI_MODULE_DEVICE_KEYBOARD)
	ENDIF(YUNI_MODULE_DEVICE_KEYBOARD)
	IF(YUNI_MODULE_DEVICE_MOUSE)
	ENDIF(YUNI_MODULE_DEVICE_MOUSE)
ENDIF(YUNI_MODULE_DEVICES)

IF(YUNI_MODULE_GFX3D)
	Message(STATUS "[Module] Gfx3D")
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/gfx3d.cmake")
	IF(YUNI_EXTERNAL_3D_IRRLICHT)
		Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/gfx3d-irrlicht.cmake")
	ENDIF(YUNI_EXTERNAL_3D_IRRLICHT)
	IF(YUNI_EXTERNAL_3D_OGRE)
		Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/gfx3d-ogre.cmake")
	ENDIF(YUNI_EXTERNAL_3D_OGRE)
ENDIF(YUNI_MODULE_GFX3D)








#
# Module : Network
#
If(YUNI_MODULE_NET)

	Message(STATUS "[Module] Network")

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
# Module : Script
#
If(YUNI_MODULE_SCRIPT)

	Message(STATUS "[Module] Script")

	# Scripts
	Set(SRC_SCRIPT
				script.h
				script/script.h script/script.hxx script/script.cpp
				private/script/script.defines.h private/script/script.undefs.h
		)
	source_group("Script\\Script Abstraction" FILES ${SRC_SCRIPT})

	# External Lib: Lua script
	if(YUNI_EXTERNAL_SCRIPT_LUA)
		Message(STATUS "[Module] Script::Lua")
		# Headers for Lua
		DEVPACK_IMPORT_LUA()
		Set(SRC_EXTERNAL_SCRIPT_LUA
				${YUNI_EXT_LUA_SRC}  # From DevPack 'lua'
				script/lua.h script/lua.cpp script/script.args.lua.cpp
				private/script/lua.proxy.h private/script/lua.proxy.cpp
			)
		source_group("Script\\Script Lua language support" FILES ${SRC_EXTERNAL_SCRIPT_LUA})

	Endif(YUNI_EXTERNAL_SCRIPT_LUA)

	Add_Library(yuni-static-script STATIC
				${SRC_SCRIPT}
				${SRC_EXTERNAL_SCRIPT_LUA}
				)
	#TEST_BEGIN("yuni::scripts" "Yuni Framework" "Scripts")
	#	TEST_ADD_TARGET("yuni-static-scripts")
	#TEST_END()

EndIf(YUNI_MODULE_SCRIPT)


#
# Module : User Interface
#
#If(YUNI_MODULE_UI)

#	Message(STATUS "[Module] UI::Core (User Interface)")

	# User Interface
#	Set(SRC_GFX_UI
#				ui/component.h ui/component.cpp
#				ui/control.h ui/control.cpp ui/anchor.cpp
#				ui/controller.h ui/controller.cpp)
#	source_group("Gfx\\User Interface" FILES ${SRC_GFX_UI})

#	Add_Library(yuni-static-ui-core STATIC
#				${SRC_GFX_UI}
#				)

#	IF(YUNI_MODULE_UI_DUMMY)

#		Message(STATUS "[Module] UI::Dummy")

#	ENDIF(YUNI_MODULE_UI_DUMMY)


#	IF(YUNI_MODULE_UI_3D)

#		Message(STATUS "[Module] UI::Gfx3D")

#	ENDIF(YUNI_MODULE_UI_3D)

#EndIf(YUNI_MODULE_UI)




#
# Module : Database
#
If(YUNI_MODULE_DATABASEI)

	Message(STATUS "[Module] Database::Core")

	# Database
	Set(SRC_DB
			sql/driver.h
			sql/database.h  sql/database.cpp)
	source_group("Database" FILES ${SRC_DB})

	Add_Library(yuni-static-database-core STATIC ${SRC_DB})

	IF(YUNI_MODULE_DB_PSQL)
		Set(SRC_DB_PSQL	 private/sql/postgresql/driver.h  private/sql/postgresql/driver.cpp)
		Add_Library(yuni-static-database-postgresql STATIC ${SRC_DB_PSQL})
		Message(STATUS "[Module] Database::PostgreSQL")
	ENDIF(YUNI_MODULE_DB_PSQL)

EndIf(YUNI_MODULE_DATABASEI)


IF(YUNI_MODULE_ALGORITHMS)
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/algorithms.cmake")
ENDIF(YUNI_MODULE_ALGORITHMS)



#
# Misc
#
Add_definitions("-DYUNI_LIBRARY_STATIC")
Include_directories(${YUNI_INCLUDE})


Message(STATUS "")

