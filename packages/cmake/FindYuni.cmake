#
# Locate the Yuni Framework
#
# This module defines :
#  - Yuni_FOUND    : If the libraries has been found
#  - Yuni_Info     : A string about the selected version of yuni (`Not found` by default)
#  - Yuni_CXXFLAGS : The flags to use for compiling a source file
#  - Yuni_LIBS     : The flags to use to link against the libyuni libraries
#  - Yuni_Config   : Full path to the program 'yuni-config' (empty if not found)
#
# Usage :
# \code
# find_package(Yuni COMPONENTS core gfx3d lua)
# if(Yuni_NOTFOUND)
#	message(ERROR "The yuni framework could not been found.")
# endif(Yuni_NOTFOUND)
# \endcode
#


#
# Init
#
SET(Yuni_CXXFLAGS "")
SET(Yuni_LIBS     "")
SET(Yuni_INFOS    "Not found.")
SET(Yuni_Config   "")









SET(__Yuni_Message "Looking for the Yuni Framework")

#
# Where is yuni-config ?
#
SET(__Yuni_CurrentFolder "${CMAKE_CURRENT_LIST_FILE}")
STRING(REPLACE "\\FindYuni.cmake" "" __Yuni_CurrentFolder "${__Yuni_CurrentFolder}")
STRING(REPLACE "/FindYuni.cmake" "" __Yuni_CurrentFolder "${__Yuni_CurrentFolder}")
IF(WIN32 OR WIN64)
	SET(__Yuni_ProgramSearchPath
		C:/dev/libyuni
		C:/libyuni
		"${__Yuni_CurrentFolder}/../../src/build/release/bin/"
		"${__Yuni_CurrentFolder}/../../src/build/debug/bin/"
		"$ENV{YuniPaths}")
ELSE(WIN32 OR WIN64)
	SET(__Yuni_ProgramSearchPath
		"${__Yuni_CurrentFolder}/../../src/build/release/bin"
		"${__Yuni_CurrentFolder}/../../src/build/debug/bin"
		"$ENV{YuniPaths}")
ENDIF(WIN32 OR WIN64)

FIND_PROGRAM(__Yuni_Config NAMES yuni-config yuni-config.exe PATHS ${__Yuni_ProgramSearchPath})

IF("${__Yuni_Config}" STREQUAL "__Yuni_Config-NOTFOUND")
	MESSAGE(STATUS "${__Yuni_Message} - failed ('yuni-config' not found)")
	SET(Yuni_NOTFOUND TRUE)
ENDIF("${__Yuni_Config}" STREQUAL "__Yuni_Config-NOTFOUND")


IF(NOT Yuni_NOTFOUND)

	# gotcha !
	SET(Yuni_Config   "${__Yuni_Config}")

	#
	# Compiler
	#
	SET(__Yuni_Compiler "gcc")
	IF(MINGW)
		SET(__Yuni_Compiler "mingw")
	ENDIF(MINGW)
	IF(MSVC)
		SET(__Yuni_Compiler "msvc")
	ENDIF(MSVC)
	IF(WATCOM)
		SET(__Yuni_Compiler "watcom")
	ENDIF(WATCOM)
	IF(BORLAND)
		SET(__Yuni_Compiler "borland")
	ENDIF(BORLAND)
	IF(MSYS)
		SET(__Yuni_Compiler "mingw")
	ENDIF(MSYS)
	IF(CYGWIN)
		SET(__Yuni_Compiler "mingw")
	ENDIF(CYGWIN)

	#
	# Building the command line options for the list of components
	#
	SET(__Yuni_ModsMods "")
	FOREACH(COMPONENT ${Yuni_FIND_COMPONENTS})
		STRING(TOLOWER ${COMPONENT} COMPONENT)
		SET(__Yuni_ModsOpts "${__Yuni_ModsOpts} ${COMPONENT}")
	ENDFOREACH(COMPONENT)

	#
	# Checking if the required modules are present
	#
    IF(WIN32)
        IF(NOT MSYS)
            # On Windows (not MSys), a patch like this "C:/path/..." is invalid
            STRING(REPLACE "/" "\\" __Yuni_Config "${__Yuni_Config}")
        ENDIF(NOT MSYS)
    ENDIF(WIN32)
	execute_process(COMMAND "${__Yuni_Config}" -c "${__Yuni_Compiler}"
		-m "${__Yuni_ModsOpts}" --module-deps
		OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE __Yuni_ModsDeps
		RESULT_VARIABLE __Yuni_Config_DepsResult)
	IF(NOT "${__Yuni_Config_DepsResult}" EQUAL 0 OR "${__Yuni_ModsDeps}" STREQUAL "")
		MESSAGE(STATUS "${__Yuni_Message} - Requires: ${Yuni_FIND_COMPONENTS}")
		MESSAGE(STATUS "${__Yuni_Message} - failed - the required modules could not be found")
		SET(Yuni_NOTFOUND TRUE)
	ENDIF(NOT "${__Yuni_Config_DepsResult}" EQUAL 0 OR "${__Yuni_ModsDeps}" STREQUAL "")

	IF(NOT Yuni_NOTFOUND)
		# Infos
		execute_process(COMMAND "${__Yuni_Config}" -c "${__Yuni_Compiler}"
			-m "${__Yuni_ModsOpts}" -l
			OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE Yuni_INFOS)

		# CXX
		execute_process(COMMAND "${__Yuni_Config}" -c "${__Yuni_Compiler}"
			-m "${__Yuni_ModsOpts}" --cxxflags
			OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE Yuni_CXXFLAGS
			RESULT_VARIABLE __Yuni_Config_DepsResult)
		# LIBS
		execute_process(COMMAND "${__Yuni_Config}" -c "${__Yuni_Compiler}"
			-m "${__Yuni_ModsOpts}" --libs
			OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE Yuni_LIBS
			RESULT_VARIABLE __Yuni_Config_DepsResult)

		SET(Yuni_FOUND true)
	ENDIF(NOT Yuni_NOTFOUND)

ENDIF(NOT Yuni_NOTFOUND)

