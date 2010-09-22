
# Minimum CMake version check
CMake_minimum_required(VERSION 2.8)
Message(STATUS "${CMAKE_CXX_FLAGS}")
include("cmake/message.cmake")

YMESSAGE("")
YMESSAGE("The Yuni Framework")
YMESSAGE("")
Project(Yuni-Framework) 


# Package informations
SET(YUNI_URL_WEBSITE             "http://www.libyuni.org")
SET(YUNI_MAILING_LIST            "dev@libyuni.org")
# Version
SET(YUNI_VERSION_HI              0)
SET(YUNI_VERSION_LO              1)
SET(YUNI_VERSION                 "${YUNI_VERSION_HI}.${YUNI_VERSION_LO}")
SET(YUNI_VERSION_REV             0) # Svn Revision - see below
SET(YUNI_TARGET                  "debug") # Target : debug/release - see Target.cmake
SET(YUNI_URL_DEVPACK_REPOSITORY  "http://devpacks.libyuni.org/")
SET(YUNI_URL_DEVPACK_SOURCE      "http://devpacks.libyuni.org/downloads")








#
# -----------------------------------------------------------------------------
#

# CMake special variables
SET(VS_KEYWORD                   "YuniVS${YUNI_VERSION}")
SET(VERSION                      "${YUNI_VERSION}")
SET(VS_SCC_PROJECTNAME           "Yuni Framework")
SET(PROJECT_LABEL                "Yuni Framework")


#
# CMake policies
#
# Preprocessor definition values are now escaped automatically
IF(POLICY CMP0005)
	CMake_Policy(SET CMP0005 NEW)
ENDIF(POLICY CMP0005)
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
# Various output directories
#
Set(YUNI_VERSIONED_INST_PATH "yuni/${YUNI_VERSION}")
Set(YUNI_OUTPUT_DIRECTORY    "${CMAKE_CURRENT_BINARY_DIR}/build/${YUNI_TARGET}/")
Set(YUNI_SOURCE_TREE         "${CMAKE_CURRENT_SOURCE_DIR}/yuni/")

YMESSAGE("Folders")
YMESSAGE("       Source: ${CMAKE_CURRENT_SOURCE_DIR}")
YMESSAGE("   Build into: ${CMAKE_CURRENT_BINARY_DIR}")


# Custom settings
IF("${PROFILE}" STREQUAL "")
	FILE(GLOB ProfileFilename "ProfileBuild.*")
	IF("${ProfileFilename}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}/ProfileBuild.cmake")
		Include("${ProfileFilename}")
	ELSE("${ProfileFilename}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}/ProfileBuild.cmake")
		CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProfileBuild.template.cmake
			${CMAKE_CURRENT_SOURCE_DIR}/ProfileBuild.cmake)
		YMESSAGE("A default profile has been created (`./ProfileBuild.cmake`)")
		YMESSAGE("Please edit this file to override the default settings")
		Include(${CMAKE_CURRENT_SOURCE_DIR}/ProfileBuild.cmake)
	ENDIF("${ProfileFilename}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}/ProfileBuild.cmake")
ELSE("${PROFILE}" STREQUAL "")
	Include("${PROFILE}")
ENDIF("${PROFILE}" STREQUAL "")

YMESSAGE("[Profile] ${YUNI_PROFILE_NAME}")
# (Re)Check the target
Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Target.cmake")


# DevPacks utilities
Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/DevPack.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/DevPackStandardImports.cmake")

# Modules
Include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules.cmake")



# Sub Directories
Add_SubDirectory(yuni)

# tools (especially for yuni-config)
Add_SubDirectory(tools)



#
# Compiling yuni-config if required
#
IF(YUNI_AUTO_COMPILE_YUNI_CONFIG)
	YMESSAGE("[yuni-config] Bootstraping")
	IF(YUNI_TESTS)
		YMESSAGE("The bootstrapping is required to compile the testsuite")
	ENDIF(YUNI_TESTS)
	# --
	YMESSAGE("Configuring yuni-config...")
	YMESSAGE("(in ${CMAKE_CURRENT_SOURCE_DIR}/tools/yuni-config)")
	# Create the yuni-config bootstrap directory.
	execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory
		"${CMAKE_CURRENT_BINARY_DIR}/tools/yuni-config-bootstrap"
		WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
	# Configure yuni-config like us.
	execute_process(COMMAND "${CMAKE_COMMAND}"
			${CMAKE_CURRENT_SOURCE_DIR}/tools/yuni-config
			"-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
			"-DYUNI_OUTPUT_DIRECTORY=${YUNI_OUTPUT_DIRECTORY}"
			"-DYUNI_BOOTSTRAP_YUNI_CONFIG=1}"
			-G "${CMAKE_GENERATOR}"
			WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tools/yuni-config-bootstrap")
	# Compile it.
	YMESSAGE("Compiling yuni-config...")
	execute_process(COMMAND "${CMAKE_COMMAND}" --build
                              "${CMAKE_CURRENT_BINARY_DIR}/tools/yuni-config-bootstrap"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tools/yuni-config-bootstrap")
ENDIF(YUNI_AUTO_COMPILE_YUNI_CONFIG)

