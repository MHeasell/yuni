
#
# CMake Stuff
#
#Set(CMAKE_VERBOSE_MAKEFILE ON)
# Policy
IF(NOT CMAKE_MINOR_VERSION EQUAL 4 OR NOT CMAKE_MAJOR_VERSION EQUAL 2 )
	cmake_policy(SET CMP0004 OLD)
	cmake_policy(SET CMP0003 NEW)
ENDIF(NOT CMAKE_MINOR_VERSION EQUAL 4 OR NOT CMAKE_MAJOR_VERSION EQUAL 2 )
Include(CheckIncludeFile)

#
# Getting the folder where this file is located
#
SET(CurrentFolder "${CMAKE_CURRENT_LIST_FILE}")
STRING(REPLACE "\\CommonSettings.cmake" "" CurrentFolder "${CurrentFolder}")
STRING(REPLACE "/CommonSettings.cmake" "" CurrentFolder "${CurrentFolder}")
# Current Folder : ${CurrentFolder}

#
# Detect Special Instructions Set (SSE, MMX...)
#
Include("${CurrentFolder}/DetectInstructionsSets.cmake")


IF(NOT WIN32)
	Set(CMAKE_CXX_FLAGS_RELEASE         "-O3 -fomit-frame-pointer -Wall  -Wextra -mfpmath=sse -msse -msse2 -Wuninitialized -Wunused-parameter -Winit-self -Wwrite-strings")
	Set(CMAKE_CXX_FLAGS_DEBUG           "-g -ggdb3 -Wall -Woverloaded-virtual -Wextra -Wconversion -Wredundant-decls -Wundef -Wcast-align -Wcast-qual -Wfloat-equal -Wunused-parameter -Wwrite-strings")
	Set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-O3 -fomit-frame-pointer -Wall  -Wextra -mfpmath=sse -msse -msse2 -Wuninitialized -Wunused-parameter -Winit-self -Wwrite-strings")
ENDIF(NOT WIN32)
IF(MINGW)
	Set(CMAKE_CXX_FLAGS_RELEASE         "-mthreads -Wall -Wextra -Wconversion -O3 -fomit-frame-pointer -Wwrite-strings")
	Set(CMAKE_CXX_FLAGS_DEBUG           "-mthreads -Wall -Wextra -Wconversion -g2 -Woverloaded-virtual -Wwrite-strings")
	Set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-mthreads -Wall -Wextra -Wconversion -g2 -Woverloaded-virtual -Wwrite-strings")
ENDIF(MINGW)
IF(MSVC)
	Set(CMAKE_CXX_FLAGS_RELEASE         "/Ox /Ob2 /Ot /O2 /Oy /MD /GS- /Gy /arch:SSE2")
	Set(CMAKE_CXX_FLAGS_DEBUG           "/GR /Ob1 /Ot /MDd /fp:except /W3")
	Set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/Ox /Ob2 /Ot /O2 /Oy /MDd /GS- /Gy")
ENDIF(MSVC)
IF(APPLE)
	Set(CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_CXX_FLAGS_DEBUG} -gfull -fvisibility=hidden")
	Set(CMAKE_CXX_FLAGS_RELEASE         "${CMAKE_CXX_FLAGS_RELEASE} -fvisibility=hidden")
	Set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELEASE} -fvisibility=hidden")
Endif(APPLE)

Set(CMAKE_CXX_FLAGS_RELEASE       "${CMAKE_CXX_FLAGS_RELEASE} ${YUNI_PROFILE_CXX_FLAGS_INSTRUCTIONS_SETS}")
Set(CMAKE_CXX_FLAGS_DEBUG         "${CMAKE_CXX_FLAGS_DEBUG} ${YUNI_PROFILE_CXX_FLAGS_INSTRUCTIONS_SETS}")
Set(CMAKE_CXX_FLAGS_RELWITHDEBUG  "${CMAKE_CXX_FLAGS_RELWITHDEBUG} ${YUNI_PROFILE_CXX_FLAGS_INSTRUCTIONS_SETS}")

IF(NOT "${YUNI_CXX_FLAGS_OVERRIDE_ADD_DEBUG}" STREQUAL "")
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${YUNI_CXX_FLAGS_OVERRIDE_ADD_DEBUG}")
ENDIF(NOT "${YUNI_CXX_FLAGS_OVERRIDE_ADD_DEBUG}" STREQUAL "")
IF(NOT "${YUNI_CXX_FLAGS_OVERRIDE_ADD_RELEASE}" STREQUAL "")
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} ${YUNI_CXX_FLAGS_OVERRIDE_ADD_RELEASE}")
ENDIF(NOT "${YUNI_CXX_FLAGS_OVERRIDE_ADD_RELEASE}" STREQUAL "")
IF(NOT "${YUNI_CXX_FLAGS_OVERRIDE_ADD_RELWITHDEBINFO}" STREQUAL "")
	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${YUNI_CXX_FLAGS_OVERRIDE_ADD_RELWITHDEBINFO}")
ENDIF(NOT "${YUNI_CXX_FLAGS_OVERRIDE_ADD_RELWITHDEBINFO}" STREQUAL "")






#
# Extra - Bundles
#
SET(MACOSX_BUNDLE_COPYRIGHT "Yuni Framework - 2008/2010")


IF(APPLE)
#	YMESSAGE("Enabled universal binaries (i386, x86_64)")
#	Set(CMAKE_OSX_ARCHITECTURES "i686;x86_64") # ppc;i386;ppc64;x86_64
ENDIF(APPLE)


