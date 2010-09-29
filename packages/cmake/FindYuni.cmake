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
# - It might be specified.
if(Yuni_YUNICONFIG_PATH AND EXISTS "${Yuni_YUNICONFIG_PATH}")
	# Nothing to do, the binary is there, we'll blindly use it.
	set(__Yuni_Config "${Yuni_YUNICONFIG_PATH}")
elseif(Yuni_YUNICONFIG_PATH AND NOT EXISTS "${Yuni_YUNICONFIG_PATH}")
	# If the specified yuni-config cannot be found, we should not try harder.
	message(STATUS "${__Yuni_Message} - The specified yuni-config (`${Yuni_YUNICONFIG_PATH}`) could not be found.")
	set(Yuni_NOTFOUND TRUE)
else()
	# Try to find it in _reasonable_ places.
	set(__Yuni_CurrentFolder "${CMAKE_CURRENT_LIST_FILE}")
	string(REPLACE "\\FindYuni.cmake" "" __Yuni_CurrentFolder "${__Yuni_CurrentFolder}")
	string(REPLACE "/FindYuni.cmake" "" __Yuni_CurrentFolder "${__Yuni_CurrentFolder}")

	SET(__Yuni_ProgramSearchPath
		# Search in the source tree (if we have a trunk-like tree).
		"${__Yuni_CurrentFolder}/../../src/build/release/bin/"
		"${__Yuni_CurrentFolder}/../../src/build/debug/bin/"
		"$ENV{YuniPaths}")

	find_program(__Yuni_Config NAMES yuni-config yuni-config.exe PATHS ${__Yuni_ProgramSearchPath})

	if("${__Yuni_Config}" STREQUAL "__Yuni_Config-NOTFOUND")
		message(STATUS "${__Yuni_Message} - failed ('yuni-config' not found)")
		set(Yuni_NOTFOUND TRUE)
	endif()
endif()


# FIXME: we should check if yuni-config has any versions configured here, to avoid problems.
# FIXME: we also should give a choice of options to pass to yuni-config (like a secondary version, or so).

if(NOT Yuni_NOTFOUND)

	# Store the config path.
	set(Yuni_Config   "${__Yuni_Config}")

	#
	# Compiler
	#
	set(__Yuni_Compiler "gcc")
	if(MINGW)
		set(__Yuni_Compiler "mingw")
	endif()
	if(MSVC)
		set(__Yuni_Compiler "msvc")
	endif()
	if(WATCOM)
		set(__Yuni_Compiler "watcom")
	endif()
	if(BORLAND)
		set(__Yuni_Compiler "borland")
	endif()
	if(MSYS)
		set(__Yuni_Compiler "mingw")
	endif(MSYS)
	if(CYGWIN)
		set(__Yuni_Compiler "mingw")
	endif(CYGWIN)

	#
	# Building the command line options for the list of components
	#
	set(__Yuni_ModsMods "")
	foreach(COMPONENT ${Yuni_FIND_COMPONENTS})
		string(TOLOWER ${COMPONENT} COMPONENT)
		set(__Yuni_ModsOpts "${__Yuni_ModsOpts} ${COMPONENT}")
	endforeach()

	#
	# Checking if the required modules are present
	#
    if(WIN32)
        if(NOT MSYS)
            # On Windows (not MSys), a patch like this "C:/path/..." is invalid
            string(REPLACE "/" "\\" __Yuni_Config "${__Yuni_Config}")
        endif()
    endif()
	execute_process(COMMAND "${__Yuni_Config}" -c "${__Yuni_Compiler}"
		-m "${__Yuni_ModsOpts}" --module-deps
		OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE __Yuni_ModsDeps
		RESULT_VARIABLE __Yuni_Config_DepsResult)
	if(NOT "${__Yuni_Config_DepsResult}" EQUAL 0 OR "${__Yuni_ModsDeps}" STREQUAL "")
		message(STATUS "${__Yuni_Message} - Requires: ${Yuni_FIND_COMPONENTS}")
		message(STATUS "${__Yuni_Message} - failed - the required modules could not be found")
		set(Yuni_NOTFOUND TRUE)
	endif()

	if(NOT Yuni_NOTFOUND)
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
	endif()

endif()

