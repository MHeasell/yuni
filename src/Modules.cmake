
#
# --- Modules - Default settings ---
#

# Core
Set(YUNI_MODULE_CORE                      TRUE) # Must be equals to True
# Gfx3D
Set(YUNI_MODULE_GFX3D                     FALSE)
	Set(YUNI_EXTERNAL_3D_IRRLICHT         TRUE)
# Scripts
Set(YUNI_MODULE_SCRIPT                    FALSE)
	Set(YUNI_EXTERNAL_SCRIPT_LUA          TRUE)


# Tests
Set(YUNI_TESTS   FALSE)
# Samples
Set(YUNI_SAMPLES FALSE)







#
# --- Command lines options ---
#
IF(MODULES)
	Set(KeywordError FALSE)
	String(REPLACE "," ";" MODULES "${MODULES}")
	String(REPLACE "+" "" MODULES "${MODULES}")
	ForEach(it ${MODULES})
		Set(KeywordIsKnown FALSE)

		# core
		If("${it}" STREQUAL "core")
			Set(YUNI_MODULE_CORE TRUE)
			Set(KeywordIsKnown TRUE)
		EndIf("${it}" STREQUAL "core")
		# -core
		If("${it}" STREQUAL "-core")
			Set(KeywordIsKnown TRUE)
			Message(STATUS "[!!] Module: Impossible to disable the core module")
			Set(KeywordError TRUE)
		EndIf("${it}" STREQUAL "-core")

		# all
		If("${it}" STREQUAL "all")
			Set(YUNI_MODULE_CORE TRUE)
			Set(YUNI_MODULE_GFX3D TRUE)
			Set(YUNI_MODULE_SCRIPT TRUE)
			Set(YUNI_SAMPLES TRUE)
			Set(YUNI_TESTS TRUE)
			Set(KeywordIsKnown TRUE)
		EndIf("${it}" STREQUAL "all")



		# gfx3d
		If("${it}" STREQUAL "gfx3d")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_GFX3D TRUE)
		EndIf("${it}" STREQUAL "gfx3d")
		# -gfx3d
		If("${it}" STREQUAL "-gfx3d")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_GFX3D FALSE)
		EndIf("${it}" STREQUAL "-gfx3d")

		# irrlicht
		If("${it}" STREQUAL "irrlicht")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_GFX3D TRUE)
			Set(YUNI_EXTERNAL_3D_IRRLICHT TRUE)
		EndIf("${it}" STREQUAL "irrlicht")
		# -irrlicht
		If("${it}" STREQUAL "-irrlicht")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_EXTERNAL_3D_IRRLICHT FALSE)
		EndIf("${it}" STREQUAL "-irrlicht")




		# script
		If("${it}" STREQUAL "script")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_SCRIPT TRUE)
		EndIf("${it}" STREQUAL "script")
		# -lua
		If("${it}" STREQUAL "-script")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_SCRIPT FALSE)
		EndIf("${it}" STREQUAL "-script")

		# lua
		If("${it}" STREQUAL "lua")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_SCRIPT TRUE)
			Set(YUNI_EXTERNAL_SCRIPT_LUA TRUE)
		EndIf("${it}" STREQUAL "lua")
		# -lua
		If("${it}" STREQUAL "-lua")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_EXTERNAL_SCRIPT_LUA FALSE)
		EndIf("${it}" STREQUAL "-lua")


		# Tests
		If("${it}" STREQUAL "tests")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_TESTS TRUE)
		EndIf("${it}" STREQUAL "tests")
		# -tests
		If("${it}" STREQUAL "-tests")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_TESTS FALSE)
		EndIf("${it}" STREQUAL "-tests")

		# samples
		If("${it}" STREQUAL "samples")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_SAMPLES TRUE)
		EndIf("${it}" STREQUAL "samples")
		# -samples
		If("${it}" STREQUAL "-samples")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_SAMPLES FALSE)
		EndIf("${it}" STREQUAL "-samples")


		If(NOT KeywordIsKnown)
			Message(STATUS "[!!] Unknown module from command line: `${it}` (ignored)")
			Set(KeywordError TRUE)
		EndIf(NOT KeywordIsKnown)

	EndForEach(it {MODULES})

	IF(KeywordError)
		Message(STATUS "")
		Message(STATUS "Errors on modules. Here is the list of all available modules :")
		Message(STATUS "(+ : Enable the module,  - disable the module)")
		Message(STATUS " Main and virtual modules :")
		Message(STATUS "    +core        : The core module (needed)")
		Message(STATUS "    -/+tests     : Atomic Tests for the yuni framework")
		Message(STATUS "    -/+samples   : Samples for the yuni framework")
		Message(STATUS "    +all         : Enable all main modules (gfx,script,tests,samples)")
		Message(STATUS " The gfx modules :")
		Message(STATUS "    -/+gfx3d     : The Gfx3D module (default: disabled)")
		Message(STATUS "    -/+irrlicht  : The Irrlicht extension (default: enabled)")
		Message(STATUS " The scripting modules :")
		Message(STATUS "    -/+script    : The script module (default: disabled)")
		Message(STATUS "    -/+lua       : The Lua extension (default: enabled)")
		Message(STATUS "")
		Message(FATAL_ERROR "Errors on module names")
	EndIF(KeywordError)
ENDIF(MODULES)


