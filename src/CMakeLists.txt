Project(Yuni-Framework)

CMake_minimum_required(VERSION 2.6)

Message(STATUS "")
Message(STATUS "The Yuni Framework")
Message(STATUS "")



#
# Informations about the system
#
Message(STATUS "System: ${CMAKE_SYSTEM} (${CMAKE_SYSTEM_PROCESSOR})")
If(MSVC)
    Message(STATUS "Compiler: Visual Studio")
EndIF(MSVC)
If(MINGW)
    Message(STATUS "Compiler: MinGW")
EndIf(MINGW)
If(XCODE)
    Message(STATUS "Compiler: XCode")
EndIf(XCODE)
If(CMAKE_COMPILER_IS_GNUCXX)
	If(NOT GNUCXX_VERSION)
		# -dumpversion might be used
		Execute_process(COMMAND ${CMAKE_CXX_COMPILER} "--version" OUTPUT_VARIABLE GNUCXX_VERSION_N ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
		String(REGEX REPLACE "Copyright.*" "" GNUCXX_VERSION_N "${GNUCXX_VERSION_N}")
		String(STRIP "${GNUCXX_VERSION_N}" GNUCXX_VERSION_N)
		SET(GNUCXX_VERSION "${GNUCXX_VERSION_N}" CACHE INTERNAL "Version of the Gnu Gxx compiler")
	EndIf(NOT GNUCXX_VERSION)
	Message(STATUS "g++ Variant : ${GNUCXX_VERSION}")
EndIf(CMAKE_COMPILER_IS_GNUCXX)

#
# The target directory for static libs
#
Set(TARGET_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/../bin/static/")
Set(LIBRARY_OUTPUT_PATH "${TARGET_LIBS}")
Set(ARCHIVE_OUTPUT_DIRECTORY "${TARGET_LIBS}")

Message(STATUS "Root folder: `${CMAKE_CURRENT_SOURCE_DIR}`")
Message(STATUS "Libraries output: `${TARGET_LIBS}`")



# DevPacks utilities
Include("${CMAKE_CURRENT_SOURCE_DIR}/DevPack.cmake")
Include("${CMAKE_CURRENT_SOURCE_DIR}/DevPackStandardImports.cmake")


# Sub Directories
Add_SubDirectory(yuni)
Add_SubDirectory(tests)
Add_SubDirectory(samples)

