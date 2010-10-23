
#
# CMake Stuff
#
#set(CMAKE_VERBOSE_MAKEFILE ON)
# Policy
if(NOT CMAKE_MINOR_VERSION EQUAL 4 OR NOT CMAKE_MAJOR_VERSION EQUAL 2 )
	cmake_policy(SET CMP0004 OLD)
	cmake_policy(SET CMP0003 NEW)
endif()
include(CheckIncludeFile)

#
# Getting the folder where this file is located
#
set(CurrentFolder "${CMAKE_CURRENT_LIST_FILE}")
string(REPLACE "\\CommonSettings.cmake" "" CurrentFolder "${CurrentFolder}")
string(REPLACE "/CommonSettings.cmake" "" CurrentFolder "${CurrentFolder}")
# Current Folder : ${CurrentFolder}

#
# Detect Special Instructions Set (SSE, MMX...)
#
Include("${CurrentFolder}/DetectInstructionsSets.cmake")


if(NOT WIN32)
	set(CMAKE_CXX_FLAGS_RELEASE         "-O3 -fomit-frame-pointer -Wall  -Wextra -mfpmath=sse -msse -msse2 -Wuninitialized -Wunused-parameter -Winit-self -Wwrite-strings -D_FILE_OFFSET_BITS=64")
	set(CMAKE_CXX_FLAGS_DEBUG           "-g -ggdb3 -Wall -Woverloaded-virtual -Wextra -Wconversion -Wredundant-decls -Wundef -Wcast-align -Wcast-qual -Wfloat-equal -Wunused-parameter -Wwrite-strings -D_FILE_OFFSET_BITS=64")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-O3 -fomit-frame-pointer -Wall  -Wextra -mfpmath=sse -msse -msse2 -Wuninitialized -Wunused-parameter -Winit-self -Wwrite-strings")
endif()
if(MINGW)
	set(CMAKE_CXX_FLAGS_RELEASE         "-mthreads -Wall -Wextra -Wconversion -O3 -fomit-frame-pointer -Wwrite-strings")
	set(CMAKE_CXX_FLAGS_DEBUG           "-mthreads -Wall -Wextra -Wconversion -g2 -Woverloaded-virtual -Wwrite-strings")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-mthreads -Wall -Wextra -Wconversion -g2 -Woverloaded-virtual -Wwrite-strings")
endif()
if(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE         "/Ox /Ob2 /Ot /O2 /Oy /MD /GS- /Gy /arch:SSE2")
	set(CMAKE_CXX_FLAGS_DEBUG           "/GR /Ob1 /Ot /MDd /fp:except /W3")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/Ox /Ob2 /Ot /O2 /Oy /MDd /GS- /Gy")
endif()
if(APPLE)
	set(CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_CXX_FLAGS_DEBUG} -gfull -fvisibility=hidden")
	set(CMAKE_CXX_FLAGS_RELEASE         "${CMAKE_CXX_FLAGS_RELEASE} -fvisibility=hidden")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELEASE} -fvisibility=hidden")
endif()

set(CMAKE_CXX_FLAGS_RELEASE       "${CMAKE_CXX_FLAGS_RELEASE} ${YUNI_PROFILE_CXX_FLAGS_INSTRUCTIONS_SETS}")
set(CMAKE_CXX_FLAGS_DEBUG         "${CMAKE_CXX_FLAGS_DEBUG} ${YUNI_PROFILE_CXX_FLAGS_INSTRUCTIONS_SETS}")
set(CMAKE_CXX_FLAGS_RELWITHDEBUG  "${CMAKE_CXX_FLAGS_RELWITHDEBUG} ${YUNI_PROFILE_CXX_FLAGS_INSTRUCTIONS_SETS}")

if(NOT "${YUNI_CXX_FLAGS_OVERRIDE_ADD_DEBUG}" STREQUAL "")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${YUNI_CXX_FLAGS_OVERRIDE_ADD_DEBUG}")
endif()
if(NOT "${YUNI_CXX_FLAGS_OVERRIDE_ADD_RELEASE}" STREQUAL "")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} ${YUNI_CXX_FLAGS_OVERRIDE_ADD_RELEASE}")
endif()
if(NOT "${YUNI_CXX_FLAGS_OVERRIDE_ADD_RELWITHDEBINFO}" STREQUAL "")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${YUNI_CXX_FLAGS_OVERRIDE_ADD_RELWITHDEBINFO}")
endif()






#
# Extra - Bundles
#
SET(MACOSX_BUNDLE_COPYRIGHT "Yuni Framework - 2010")


if(APPLE)
#	YMESSAGE("Enabled universal binaries (i386, x86_64)")
#	set(CMAKE_OSX_ARCHITECTURES "i686;x86_64") # ppc;i386;ppc64;x86_64
endif()


