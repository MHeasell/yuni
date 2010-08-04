
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

# Audio
Set(YUNI_MODULE_AUDIO                     FALSE)

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



# The list of all available modules
# There is no need for `core` and `gfx-core`, which are implicit
Set(YUNI_MODULE_LIST
	algorithms
	audio
	devices display keyboard mouse
	gfx3d
	script lua
	ui uidummy ui3d
	db psql
	net
	)




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
			YMESSAGE("[!!] Module: Impossible to disable the core module")
			Set(KeywordError TRUE)
		EndIf("${it}" STREQUAL "-core")

		# all
		If("${it}" STREQUAL "all")
			Set(YUNI_MODULE_CORE TRUE)
			Set(YUNI_MODULE_DEVICES TRUE)
			Set(YUNI_MODULE_GFX3D TRUE)
			Set(YUNI_MODULE_AUDIO TRUE)
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
		# -mouse
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


		# audio
		If("${it}" STREQUAL "audio")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_AUDIO TRUE)
		EndIf("${it}" STREQUAL "audio")
		# -audio
		If("${it}" STREQUAL "-audio")
			Set(KeywordIsKnown TRUE)
			Set(YUNI_MODULE_AUDIO FALSE)
		EndIf("${it}" STREQUAL "-audio")


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
		# -ui3d
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
			YMESSAGE("[!!] Unknown module from command line: `${it}` (ignored)")
			Set(KeywordError TRUE)
		EndIf(NOT KeywordIsKnown)

	EndForEach(it {MODULES})

	IF(KeywordError)
		YMESSAGE("")
		YMESSAGE("Errors on modules. Here is the list of all available modules :")
		YMESSAGE("(+ : Enable the module,  - disable the module)")
		YMESSAGE(" Main and virtual modules")
		YMESSAGE("    +core          : The core module (needed)")
		YMESSAGE("    -/+tests       : Atomic Tests for the yuni framework")
		YMESSAGE("    -/+samples     : Samples for the yuni framework")
		YMESSAGE("    +all           : Enable all main modules (gfx,script,tests,samples)")
		YMESSAGE(" The algorithms")
		YMESSAGE("    -/+algorithms  : Standard algorithms")
		YMESSAGE(" The device modules")
		YMESSAGE("    -/+devices     : All devices (display,keyboard,mouse...)")
		YMESSAGE("    -/+display     : The Display device")
		YMESSAGE("    -/+keyboard    : The Keyboard device")
		YMESSAGE("    -/+mouse       : The Mouse device")
		YMESSAGE(" The gfx modules")
		YMESSAGE("    -/+gfx3d       : The Gfx3D module (default: disabled)")
		YMESSAGE(" The audio modules")
		YMESSAGE("    -/+audio       : The Audio module (default: disabled)")
		YMESSAGE(" The scripting modules")
		YMESSAGE("    -/+script      : The script module (default: disabled)")
		YMESSAGE("    -/+lua         : The Lua extension (default: enabled)")
		YMESSAGE(" The ui modules")
		YMESSAGE("    -/+ui          : The ui module (default: disabled)")
		YMESSAGE("    -/+uidummy     : The dummy ui manager (default: enabled)")
		YMESSAGE("    -/+ui3d        : The 3D ui manager (default: enabled)")
		YMESSAGE("")
		Message(FATAL_ERROR "Errors on module names")
	EndIF(KeywordError)
ENDIF(MODULES)


IF(NOT YUNI_MODULE_GFX3D)
	IF(YUNI_MODULE_UI_3D)
		YMESSAGE("[!!] Warning: The Gfx3D module is disabled. The module `ui3d` can not be enabled.")
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
		YMESSAGE("[!!] Warning: No external extension for the `script` module. The module has been disabled.")
		Set(YUNI_MODULE_SCRIPT FALSE)
	ENDIF(NOT YUNI_EXTERNAL_SCRIPT_LUA)
ENDIF(YUNI_MODULE_SCRIPT)

IF(YUNI_MODULE_DATABASE)
	IF(NOT YUNI_MODULE_DB_PSQL)
		YMESSAGE("[!!] Warning: No external extension for the `database` module. The module has been disabled.")
		Set(YUNI_MODULE_DATABASE FALSE)
	ENDIF(NOT YUNI_MODULE_DB_PSQL)
ENDIF(YUNI_MODULE_DATABASE)





#
# We have to keep a list of all available modules
#
Set(YUNI_MODULE_AVAILABLE)

IF(YUNI_MODULE_ALGORITHMS)
	LIST(APPEND YUNI_MODULE_AVAILABLE algorithms)
ENDIF(YUNI_MODULE_ALGORITHMS)

IF(YUNI_MODULE_DEVICES)
	LIST(APPEND YUNI_MODULE_AVAILABLE devices)
	IF(YUNI_MODULE_DEVICE_DISPLAY)
		LIST(APPEND YUNI_MODULE_AVAILABLE display)
	ENDIF(YUNI_MODULE_DEVICE_DISPLAY)
	IF(YUNI_MODULE_DEVICE_MOUSE)
		LIST(APPEND YUNI_MODULE_AVAILABLE mouse)
	ENDIF(YUNI_MODULE_DEVICE_MOUSE)
	IF(YUNI_MODULE_DEVICE_KEYBOARD)
		LIST(APPEND YUNI_MODULE_AVAILABLE keyboard)
	ENDIF(YUNI_MODULE_DEVICE_KEYBOARD)
ENDIF(YUNI_MODULE_DEVICES)

IF(YUNI_MODULE_NET)
	LIST(APPEND YUNI_MODULE_AVAILABLE net)
ENDIF(YUNI_MODULE_NET)

IF(YUNI_MODULE_GFX3D)
	LIST(APPEND YUNI_MODULE_AVAILABLE gfx3d)
ENDIF(YUNI_MODULE_GFX3D)

IF(YUNI_MODULE_AUDIO)
	LIST(APPEND YUNI_MODULE_AVAILABLE audio)
ENDIF(YUNI_MODULE_AUDIO)

IF(YUNI_MODULE_SCRIPT)
	LIST(APPEND YUNI_MODULE_AVAILABLE script)
	IF(YUNI_EXTERNAL_SCRIPT_LUA)
		LIST(APPEND YUNI_MODULE_AVAILABLE lua)
	ENDIF(YUNI_EXTERNAL_SCRIPT_LUA)
ENDIF(YUNI_MODULE_SCRIPT)


IF(YUNI_MODULE_UI)
	LIST(APPEND YUNI_MODULE_AVAILABLE ui)
	IF(YUNI_MODULE_UI_DUMMY)
		LIST(APPEND YUNI_MODULE_AVAILABLE uidummy)
	ENDIF(YUNI_MODULE_UI_DUMMY)
	IF(YUNI_MODULE_UI_3D)
		LIST(APPEND YUNI_MODULE_AVAILABLE ui3d)
	ENDIF(YUNI_MODULE_UI_3D)
ENDIF(YUNI_MODULE_UI)

IF(YUNI_MODULE_DB)
	LIST(APPEND YUNI_MODULE_AVAILABLE db)
	IF(YUNI_MODULE_DB_PSQL)
		LIST(APPEND YUNI_MODULE_AVAILABLE psql)
	ENDIF(YUNI_MODULE_DB_PSQL)
ENDIF(YUNI_MODULE_DB)

