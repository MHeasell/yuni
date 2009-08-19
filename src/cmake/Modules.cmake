
#
# --- Modules - Default settings ---
#

# Core
Set(YUNI_MODULE_CORE                      TRUE) # Must be equals to True
Set(YUNI_MODULE_GFX_CORE                  TRUE)

# Devices
Set(YUNI_MODULE_DEVICES                   FALSE)
	Set(YUNI_MODULE_DEVICE_DISPLAY        TRUE)
	Set(YUNI_MODULE_DEVICE_KEYBOARD       TRUE)
	Set(YUNI_MODULE_DEVICE_MOUSE          TRUE)

# Gfx3D
Set(YUNI_MODULE_GFX3D                     FALSE)

# Scripts
Set(YUNI_MODULE_SCRIPT                    FALSE)
	Set(YUNI_EXTERNAL_SCRIPT_LUA          TRUE)

# Network
Set(YUNI_MODULE_NET                       TRUE)

# UI (User Interface)
Set(YUNI_MODULE_UI                        FALSE)
	Set(YUNI_MODULE_UI_DUMMY              TRUE)
	Set(YUNI_MODULE_UI_3D                 TRUE)

# Database
Set(YUNI_MODULE_DATABASE                  FALSE)
	Set(YUNI_MODULE_DB_PSQL               TRUE)

# Algorithms
Set(YUNI_MODULE_ALGORITHMS                TRUE)


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
	String(REPLACE " " ";" MODULES "${MODULES}")
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
			Set(YUNI_MODULE_DEVICES TRUE)
			Set(YUNI_MODULE_GFX3D TRUE)
			Set(YUNI_MODULE_NET TRUE)
			Set(YUNI_MODULE_SCRIPT TRUE)
			Set(YUNI_MODULE_UI TRUE)
			Set(YUNI_MODULE_UI_DUMMY TRUE)
			Set(YUNI_MODULE_UI_3D TRUE)
			Set(YUNI_MODULE_DATABASE TRUE)
			Set(YUNI_MODULE_ALGORITHMS TRUE)
			Set(YUNI_SAMPLES TRUE)
			Set(YUNI_TESTS TRUE)
			Set(KeywordIsKnown TRUE)
		EndIf("${it}" STREQUAL "all")

		# algorithms
		If("${it}" STREQUAL "algorithms")
			Set(YUNI_MODULE_ALGORITHMS TRUE)
			Set(KeywordIsKnown TRUE)
		EndIf("${it}" STREQUAL "algorithms")
		# -algorithms
		If("${it}" STREQUAL "-algorithms")
			Set(YUNI_MODULE_ALGORITHMS TRUE)
			Set(KeywordIsKnown TRUE)
		EndIf("${it}" STREQUAL "-algorithms")


		# display
		If("${it}" STREQUAL "display")
			Set(YUNI_MODULE_DEVICE_DISPLAY TRUE)
			Set(KeywordIsKnown TRUE)
		EndIf("${it}" STREQUAL "display")
		# -display
		If("${it}" STREQUAL "-display")
			Set(YUNI_MODULE_DEVICE_DISPLAY FALSE)
			Set(KeywordIsKnown TRUE)
		EndIf("${it}" STREQUAL "-display")

		# keyboard
		If("${it}" STREQUAL "keyboard")
			Set(YUNI_MODULE_DEVICE_KEYBOARD TRUE)
			Set(KeywordIsKnown TRUE)
		EndIf("${it}" STREQUAL "keyboard")
		# -keyboard
		If("${it}" STREQUAL "-keyboard")
			Set(YUNI_MODULE_DEVICE_KEYBOARD FALSE)
			Set(KeywordIsKnown TRUE)
		EndIf("${it}" STREQUAL "-keyboard")

		# mouse
		If("${it}" STREQUAL "mouse")
			Set(YUNI_MODULE_DEVICE_MOUSE TRUE)
			Set(KeywordIsKnown TRUE)
		EndIf("${it}" STREQUAL "mouse")
		# -keyboard
		If("${it}" STREQUAL "-mouse")
			Set(YUNI_MODULE_DEVICE_MOUSE FALSE)
			Set(KeywordIsKnown TRUE)
		EndIf("${it}" STREQUAL "-mouse")

		# devices
		If("${it}" STREQUAL "devices")
			Set(YUNI_MODULE_DEVICES TRUE)
			Set(KeywordIsKnown TRUE)
		EndIf("${it}" STREQUAL "devices")
		# -devices
		If("${it}" STREQUAL "-devices")
			Set(YUNI_MODULE_DEVICES FALSE)
			Set(KeywordIsKnown TRUE)
		EndIf("${it}" STREQUAL "-devices")


		# net
		If("${it}" STREQUAL "net")
			Set(YUNI_MODULE_NET TRUE)
			Set(KeywordIsKnown TRUE)
		EndIf("${it}" STREQUAL "net")
		# -net
		If("${it}" STREQUAL "-net")
			Set(YUNI_MODULE_NET FALSE)
			Set(KeywordIsKnown TRUE)
		EndIf("${it}" STREQUAL "-net")

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

		# ui (User Interface)
		If("${it}" STREQUAL "ui")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_UI TRUE)
		EndIf("${it}" STREQUAL "ui")
		# -ui
		If("${it}" STREQUAL "-ui")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_UI FALSE)
		EndIf("${it}" STREQUAL "-ui")

		# uidummy (User Interface)
		If("${it}" STREQUAL "uidummy")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_UI_DUMMY TRUE)
		EndIf("${it}" STREQUAL "uidummy")
		# -ui
		If("${it}" STREQUAL "-uidummy")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_UI_DUMMY FALSE)
		EndIf("${it}" STREQUAL "-uidummy")

		# ui3d (User Interface)
		If("${it}" STREQUAL "ui3d")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_UI_3D TRUE)
		EndIf("${it}" STREQUAL "ui3d")
		# -ui
		If("${it}" STREQUAL "-ui3d")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_UI_3D FALSE)
		EndIf("${it}" STREQUAL "-ui3d")


		# db (Database)
		If("${it}" STREQUAL "db")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_DATABASE TRUE)
		EndIf("${it}" STREQUAL "db")
		# -db
		If("${it}" STREQUAL "-db")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_DATABASE FALSE)
		EndIf("${it}" STREQUAL "-db")

		# PostgreSQL (Database)
		If("${it}" STREQUAL "psql")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_DB_PSQL TRUE)
		EndIf("${it}" STREQUAL "psql")
		# -psql
		If("${it}" STREQUAL "-psql")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_DB_PSQL FALSE)
		EndIf("${it}" STREQUAL "-psql")


		If(NOT KeywordIsKnown)
			Message(STATUS "[!!] Unknown module from command line: `${it}` (ignored)")
			Set(KeywordError TRUE)
		EndIf(NOT KeywordIsKnown)

	EndForEach(it {MODULES})

	IF(KeywordError)
		Message(STATUS "")
		Message(STATUS "Errors on modules. Here is the list of all available modules :")
		Message(STATUS "(+ : Enable the module,  - disable the module)")
		Message(STATUS " Main and virtual modules")
		Message(STATUS "    +core          : The core module (needed)")
		Message(STATUS "    -/+tests       : Atomic Tests for the yuni framework")
		Message(STATUS "    -/+samples     : Samples for the yuni framework")
		Message(STATUS "    +all           : Enable all main modules (gfx,script,tests,samples)")
		Message(STATUS " The algorithms")
		Message(STATUS "    -/+algorithms  : Standard algorithms")
		Message(STATUS " The device modules")
		Message(STATUS "    -/+devices     : All devices (display,keyboard,mouse...)")
		Message(STATUS "    -/+display     : The Display device")
		Message(STATUS "    -/+keyboard    : The Keyboard device")
		Message(STATUS "    -/+mouse       : The Mouse device")
		Message(STATUS " The gfx modules")
		Message(STATUS "    -/+gfx3d       : The Gfx3D module (default: disabled)")
		Message(STATUS " The scripting modules")
		Message(STATUS "    -/+script      : The script module (default: disabled)")
		Message(STATUS "    -/+lua         : The Lua extension (default: enabled)")
		Message(STATUS " The ui modules")
		Message(STATUS "    -/+ui          : The ui module (default: disabled)")
		Message(STATUS "    -/+uidummy     : The dummy ui manager (default: enabled)")
		Message(STATUS "    -/+ui3d        : The 3D ui manager (default: enabled)")
		Message(STATUS "")
		Message(FATAL_ERROR "Errors on module names")
	EndIF(KeywordError)
ENDIF(MODULES)


IF(NOT YUNI_MODULE_GFX3D)
	IF(YUNI_MODULE_UI_3D)
		Message(STATUS "[!!] Warning: The Gfx3D module is disabled. The module `ui3d` can not be enabled.")
		Set(YUNI_MODULE_UI_3D FALSE)
	ENDIF(YUNI_MODULE_UI_3D)
ENDIF(NOT YUNI_MODULE_GFX3D)

IF(YUNI_MODULE_DEVICE_DISPLAY AND YUNI_MODULE_DEVICES)
	SET(TMP_DISPLAY_DEV_FOR_GFX3D_IS_ENABLED TRUE)
ELSE(YUNI_MODULE_DEVICE_DISPLAY AND YUNI_MODULE_DEVICES)
	SET(TMP_DISPLAY_DEV_FOR_GFX3D_IS_ENABLED FALSE)
ENDIF(YUNI_MODULE_DEVICE_DISPLAY AND YUNI_MODULE_DEVICES)

IF(YUNI_MODULE_GFX3D AND NOT TMP_DISPLAY_DEV_FOR_GFX3D_IS_ENABLED)
	SET(YUNI_MODULE_DEVICES TRUE)
	SET(YUNI_MODULE_DEVICE_DISPLAY TRUE)
ENDIF(YUNI_MODULE_GFX3D AND NOT TMP_DISPLAY_DEV_FOR_GFX3D_IS_ENABLED)

IF(YUNI_MODULE_SCRIPT)
	IF(NOT YUNI_EXTERNAL_SCRIPT_LUA)
		Message(STATUS "[!!] Warning: No external extension for the `script` module. The module has been disabled.")
		Set(YUNI_MODULE_SCRIPT FALSE)
	ENDIF(NOT YUNI_EXTERNAL_SCRIPT_LUA)
ENDIF(YUNI_MODULE_SCRIPT)

IF(YUNI_MODULE_SCRIPT)
	IF(NOT YUNI_EXTERNAL_SCRIPT_LUA)
		Message(STATUS "[!!] Warning: No external extension for the `script` module. The module has been disabled.")
		Set(YUNI_MODULE_SCRIPT FALSE)
	ENDIF(NOT YUNI_EXTERNAL_SCRIPT_LUA)
ENDIF(YUNI_MODULE_SCRIPT)

IF(YUNI_MODULE_DATABASE)
	IF(NOT YUNI_MODULE_DB_PSQL)
		Message(STATUS "[!!] Warning: No external extension for the `database` module. The module has been disabled.")
		Set(YUNI_MODULE_DATABASE FALSE)
	ENDIF(NOT YUNI_MODULE_DB_PSQL)
ENDIF(YUNI_MODULE_DATABASE)


