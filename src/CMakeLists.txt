Project(Yuni-Framework)
CMake_minimum_required(VERSION 2.6)

Message(STATUS "")
Message(STATUS "The Yuni Framework")
Message(STATUS "")


# Package informations
SET(YUNI_URL_WEBSITE             "http://www.libyuni.org")
SET(YUNI_MAILING_LIST            "dev@libyuni.org")
# Version
SET(YUNI_VERSION_HI              0)
SET(YUNI_VERSION_LO              1)
SET(YUNI_VERSION_REV             0) # Svn Revision - see below
SET(YUNI_TARGET                  "debug") # Target : debug/release - see Target.cmake
SET(YUNI_URL_DEVPACK_REPOSITORY  "http://devpacks.libyuni.org/")
SET(YUNI_URL_DEVPACK_SOURCE      "http://devpacks.libyuni.org/downloads")










IF(POLICY CMP0011)
	CMake_Policy(SET CMP0011 NEW)
ENDIF(POLICY CMP0011)
Set(YUNI_INSTALL_CXX_FLAGS   "")
Set(YUNI_INSTALL_CXX_DEFINES "")

# Target
Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Target.cmake")

# Getting the latest revision number
Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/SvnRevision.cmake")

# Informations about the system
Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/SystemInformation.cmake")


#
# The target directory for static libs
#
Set(TARGET_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/../bin/static/")
Set(LIBRARY_OUTPUT_PATH "${TARGET_LIBS}")
Set(ARCHIVE_OUTPUT_DIRECTORY "${TARGET_LIBS}")

Message(STATUS "Folders")
Message(STATUS "   root: `${CMAKE_CURRENT_SOURCE_DIR}`")
Message(STATUS "   libs: `${TARGET_LIBS}`")


# Custom settings
IF("${PROFILE}" STREQUAL "")
	FILE(GLOB ProfileFilename "ProfileBuild.*")
	IF("${ProfileFilename}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}/ProfileBuild.cmake")
		Include("${ProfileFilename}")
	ELSE("${ProfileFilename}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}/ProfileBuild.cmake")
		CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProfileBuild.template.cmake
			${CMAKE_CURRENT_SOURCE_DIR}/ProfileBuild.cmake)
		Message(STATUS "A default profile has been created (`./ProfileBuild.cmake`)")
		Message(STATUS "Please edit this file to override the default settings")
		Include(${CMAKE_CURRENT_SOURCE_DIR}/ProfileBuild.cmake)
	ENDIF("${ProfileFilename}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}/ProfileBuild.cmake")
ELSE("${PROFILE}" STREQUAL "")
	Include("${PROFILE}")
ENDIF("${PROFILE}" STREQUAL "")

Message(STATUS "[Profile] ${YUNI_PROFILE_NAME}")
# (Re)Check the target
Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Target.cmake")


# DevPacks utilities
Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/DevPack.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/DevPackStandardImports.cmake")

# Modules
Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules.cmake")

# Tests
#Include("${CMAKE_CURRENT_SOURCE_DIR}/Tests.cmake")


# Sub Directories
Add_SubDirectory(yuni)

# tools (especially for libyuni-config)
Add_SubDirectory(tools)




#
# Compiling libyuni-config if required
#
IF(YUNI_AUTO_COMPILE_LIBYUNI_CONFIG)
	Message(STATUS "[libyuni-config] Bootstraping")
	# --
	Message(STATUS "Configuring libyuni-config...")
	Message(STATUS "(in ${CMAKE_CURRENT_SOURCE_DIR}/tools/libyuni-config)")
	execute_process(COMMAND "${CMAKE_COMMAND}" . -G "${CMAKE_GENERATOR}" "-DCMAKE_BUILD_TYPE=release"
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tools/libyuni-config")
	Message(STATUS "Compiling libyuni-config...")
	execute_process(COMMAND make
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tools/libyuni-config")
ENDIF(YUNI_AUTO_COMPILE_LIBYUNI_CONFIG)
