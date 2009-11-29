
Message(STATUS "")
Message(STATUS "Modules")
Message(STATUS "")


#
# Preflight
#
Set(YUNI_COMPILED_WITH_SUPPORT_FOR_OPENGL  0)
Set(YUNI_COMPILED_WITH_SUPPORT_FOR_DIRECTX 0)
Set(YUNI_CMAKE_ERROR 0)


#
# Informations for libyuni-config
#
Set(LIBYUNI_CONFIG_ENABLED true)


Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/LibYuniConfig.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/CommonSettings.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Modules.cmake")




IF(YUNI_MODULE_CORE)
	# The header yuni.h must be available
	CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/yuni.h.cmake ${CMAKE_CURRENT_SOURCE_DIR}/yuni.h)
	# Core
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/core.cmake")
	# GfxCore
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/gfx-core.cmake")
ENDIF(YUNI_MODULE_CORE)




IF(YUNI_MODULE_DEVICES)
	LIBYUNI_CONFIG_LIB("display"    "yuni-static-device-display")
	LIBYUNI_CONFIG_LIB("mouse"      "yuni-static-device-mouse")
	LIBYUNI_CONFIG_DEPENDENCY("mouse" "devices") # gfx-core is required
	LIBYUNI_CONFIG_LIB("keyboard"   "yuni-static-device-keyboard")
	LIBYUNI_CONFIG_DEPENDENCY("keyboard" "devices") # gfx-core is required

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
ENDIF(YUNI_MODULE_GFX3D)

IF(YUNI_MODULE_SCRIPT)
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/script.cmake")
ENDIF(YUNI_MODULE_SCRIPT)






#
# Module : Network
#
If(YUNI_MODULE_NET)
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/net.cmake")
EndIf(YUNI_MODULE_NET)



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




IF(YUNI_TESTS)
	Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/test.cmake")
ENDIF(YUNI_TESTS)


# Generating yuni.h
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/yuni.h.cmake ${CMAKE_CURRENT_SOURCE_DIR}/yuni.h)
# Generating version
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.cmake ${CMAKE_CURRENT_SOURCE_DIR}/yuni.version)


#
# Misc
#
Add_definitions("-DYUNI_LIBRARY_STATIC")
LIBYUNI_CONFIG_DEFINITION("core" "YUNI_LIBRARY_STATIC")
Include_directories(${YUNI_INCLUDE})



Message(STATUS "")

IF("${YUNI_CMAKE_ERROR}" GREATER 0)
	Message(STATUS "")
	MESSAGE(SEND_ERROR "An error has occured. Aborting.")
	Message(STATUS "")
ENDIF("${YUNI_CMAKE_ERROR}" GREATER 0)
