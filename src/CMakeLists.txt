Project(Yuni-Framework)

CMake_minimum_required(VERSION 2.6)

Message(STATUS "")
Message(STATUS "The Yuni Framework")
Message(STATUS "")



#
# Informations about the system
#
IF(APPLE)
	execute_process(COMMAND sw_vers -productName OUTPUT_VARIABLE SW_PN OUTPUT_STRIP_TRAILING_WHITESPACE)
	execute_process(COMMAND sw_vers -productVersion OUTPUT_VARIABLE SW_PV OUTPUT_STRIP_TRAILING_WHITESPACE)
	execute_process(COMMAND sw_vers -buildVersion OUTPUT_VARIABLE SW_BV OUTPUT_STRIP_TRAILING_WHITESPACE)
	execute_process(COMMAND sysctl -n hw.packages OUTPUT_VARIABLE HI_CPU_COUNT OUTPUT_STRIP_TRAILING_WHITESPACE)
	execute_process(COMMAND sysctl -n machdep.cpu.core_count OUTPUT_VARIABLE HI_CPU_CORE_COUNT OUTPUT_STRIP_TRAILING_WHITESPACE)
	execute_process(COMMAND sysctl -n hw.optional.sse OUTPUT_VARIABLE CPU_SSE1 OUTPUT_STRIP_TRAILING_WHITESPACE)
	execute_process(COMMAND sysctl -n hw.optional.sse2 OUTPUT_VARIABLE CPU_SSE2 OUTPUT_STRIP_TRAILING_WHITESPACE)
	execute_process(COMMAND sysctl -n hw.optional.sse3 OUTPUT_VARIABLE CPU_SSE3 OUTPUT_STRIP_TRAILING_WHITESPACE)
	execute_process(COMMAND sysctl -n hw.cpu64bit_capable OUTPUT_VARIABLE HI_CPU_i64 OUTPUT_STRIP_TRAILING_WHITESPACE)
	Message(STATUS "System: ${SW_PN} ${SW_PV} ${SW_BV} - ${CMAKE_SYSTEM} (${CMAKE_SYSTEM_PROCESSOR})")
	Message(STATUS "${HI_CPU_COUNT} CPUs (${HI_CPU_CORE_COUNT}-Core), SSE1:${CPU_SSE1}, SSE2:${CPU_SSE2}, SSE3:${CPU_SSE3}, x86_64:${HI_CPU_i64}")
ELSE(APPLE)
	Message(STATUS "System: ${CMAKE_SYSTEM} (${CMAKE_SYSTEM_PROCESSOR})")
ENDIF(APPLE)
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

# Modules
Include("${CMAKE_CURRENT_SOURCE_DIR}/Modules.cmake")



# Sub Directories
Add_SubDirectory(yuni)
IF(YUNI_TESTS)
	Add_SubDirectory(tests)
EndIF(YUNI_TESTS)
IF(YUNI_SAMPLES)
	Add_SubDirectory(samples)
EndIF(YUNI_SAMPLES)

