#
# Locate the Yuni Framework
#
# This module defines :
#  - LibYuni_FOUND    : If the libraries has been found
#  - LibYuni_Info     : A string about the selected version of yuni (`Not found` by default)
#  - LibYuni_CXXFLAGS : The flags to use for compiling a source file
#  - LibYuni_LIBS     : The flags to use to link against the libyuni libraries
#  - LibYuni_Config   : Full path to the program 'libyuni-config' (empty if not found)
#
# Usage :
# \code
# find_package(LibYuni COMPONENTS core gfx3d lua)
# if(LibYuni_NOTFOUND)
#	message(ERROR "The yuni framework could not been found.")
# endif(LibYuni_NOTFOUND)
# \endcode
#


#
# Init
#
SET(LibYuni_CXXFLAGS "")
SET(LibYuni_LIBS     "")
SET(LibYuni_INFOS    "Not found.")
SET(LibYuni_Config   "")









SET(__LibYuni_Message "Looking for libyuni")

#
# Where is libyuni-config ?
#
STRING(REPLACE "\\FindLibYuni.cmake" "" __LibYuni_CurrentFolder "${CMAKE_CURRENT_LIST_FILE}")
STRING(REPLACE "/FindLibYuni.cmake" "" __LibYuni_CurrentFolder "${CMAKE_CURRENT_LIST_FILE}")
IF(WIN32 OR WIN64)
	SET(__LibYuni_ProgramSearchPath
		C:/dev/libyuni
		C:/libyuni
		"${__LibYuni_CurrentFolder}/../../src/tools/libyuni-config"
		"${__LibYuni_CurrentFolder}/../../src/tools/libyuni-config/Release"
		"${__LibYuni_CurrentFolder}/../../src/tools/libyuni-config/Debug"
		"$ENV{LibYuniPaths}")
ELSE(WIN32 OR WIN64)
	SET(__LibYuni_ProgramSearchPath
		"${__LibYuni_CurrentFolder}/../../src/tools/libyuni-config" "$ENV{LibYuniPaths}")
ENDIF(WIN32 OR WIN64)

FIND_PROGRAM(__LibYuni_Config NAMES libyuni-config PATHS ${__LibYuni_ProgramSearchPath})
IF("${__LibYuni_Config}" STREQUAL "__LibYuni_Config-NOTFOUND")
	MESSAGE(STATUS "${__LibYuni_Message} - failed ('libyuni-config' not found)")
	SET(LibYuni_NOTFOUND TRUE)
ENDIF("${__LibYuni_Config}" STREQUAL "__LibYuni_Config-NOTFOUND")


IF(NOT LibYuni_NOTFOUND)

	# gotcha !
	SET(LibYuni_Config   "${__LibYuni_Config}")

	#
	# Compiler
	#
	SET(__LibYuni_Compiler "gcc")
	IF(MINGW)
		SET(__LibYuni_Compiler "mingw")
	ENDIF(MINGW)
	IF(MSVC)
		IF(MSVC90)
			SET(__LibYuni_Compiler "vs9")
		ELSEIF(MSVC80)
			SET(__LibYuni_Compiler "vs8")
		ELSE(MSVC80)
			SET(__LibYuni_Compiler "vs.unknown")
		ENDIF(MSVC80)
	ENDIF(MSVC)
	IF(WATCOM)
		SET(__LibYuni_Compiler "watcom")
	ENDIF(WATCOM)
	IF(BORLAND)
		SET(__LibYuni_Compiler "borland")
	ENDIF(BORLAND)
	IF(MSYS)
		SET(__LibYuni_Compiler "mingw")
	ENDIF(MSYS)
	IF(CYGWIN)
		SET(__LibYuni_Compiler "mingw")
	ENDIF(CYGWIN)

	#
	# Building the command line options for the list of components
	#
	SET(__LibYuni_ModsMods "")
	FOREACH(COMPONENT ${LibYuni_FIND_COMPONENTS})
		STRING(TOLOWER ${COMPONENT} COMPONENT)
		SET(__LibYuni_ModsOpts "${__LibYuni_ModsOpts} ${COMPONENT}")
	ENDFOREACH(COMPONENT)

	#
	# Checking if the required modules are present
	#
	execute_process(COMMAND "${__LibYuni_Config}" -c "${__LibYuni_Compiler}"
		-m "${__LibYuni_ModsOpts}" --module-deps
		OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE __LibYuni_ModsDeps
		RESULT_VARIABLE __LibYuni_Config_DepsResult)
	IF(NOT "${__LibYuni_Config_DepsResult}" EQUAL 0 OR "${__LibYuni_ModsDeps}" STREQUAL "")
		MESSAGE(STATUS "${__LibYuni_Message} - Requires: ${LibYuni_FIND_COMPONENTS}")
		MESSAGE(STATUS "${__LibYuni_Message} - failed - the required modules could not be found")
		SET(LibYuni_NOTFOUND TRUE)
	ENDIF(NOT "${__LibYuni_Config_DepsResult}" EQUAL 0 OR "${__LibYuni_ModsDeps}" STREQUAL "")

	IF(NOT LibYuni_NOTFOUND)
		# Infos
		execute_process(COMMAND "${__LibYuni_Config}" -c "${__LibYuni_Compiler}"
			-m "${__LibYuni_ModsOpts}" -l
			OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE LibYuni_INFOS)

		# CXX
		execute_process(COMMAND "${__LibYuni_Config}" -c "${__LibYuni_Compiler}"
			-m "${__LibYuni_ModsOpts}" --cxxflags
			OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE LibYuni_CXXFLAGS
			RESULT_VARIABLE __LibYuni_Config_DepsResult)
		# LIBS
		execute_process(COMMAND "${__LibYuni_Config}" -c "${__LibYuni_Compiler}"
			-m "${__LibYuni_ModsOpts}" --libs
			OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE LibYuni_LIBS
			RESULT_VARIABLE __LibYuni_Config_DepsResult)

		SET(LibYuni_FOUND true)
	ENDIF(NOT LibYuni_NOTFOUND)

ENDIF(NOT LibYuni_NOTFOUND)

