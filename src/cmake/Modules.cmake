
#
# --- Modules - Default settings ---
#

# Core
set(YUNI_MODULE_CORE                      TRUE) # Must be True

# Devices
set(YUNI_MODULE_DEVICES                   FALSE)
	set(YUNI_MODULE_DEVICE_DISPLAY        TRUE)
	set(YUNI_MODULE_DEVICE_KEYBOARD       TRUE)
	set(YUNI_MODULE_DEVICE_MOUSE          TRUE)

# Gfx3D
set(YUNI_MODULE_GFX3D                     FALSE)

# Audio
set(YUNI_MODULE_AUDIO                     FALSE)

# Scripts
set(YUNI_MODULE_SCRIPT                    FALSE)
	set(YUNI_EXTERNAL_SCRIPT_LUA          TRUE)

# Network
set(YUNI_MODULE_NET                       TRUE)

# UI (User Interface)
set(YUNI_MODULE_UI                        FALSE)
	set(YUNI_EXTERNAL_GFX_CAIROPANGO	  TRUE)
	set(YUNI_MODULE_UI_DUMMY              TRUE)

# Database
set(YUNI_MODULE_DATABASE                  FALSE)
	set(YUNI_MODULE_DB_PSQL               TRUE)

# Algorithms
set(YUNI_MODULE_ALGORITHMS                TRUE)


# Tests
set(YUNI_TESTS   FALSE)
# Samples
set(YUNI_SAMPLES FALSE)



# The list of all available modules
# There is no need for `core` and `gfx-core`, which are implicit
set(YUNI_MODULE_LIST
	algorithms
	audio
	devices display keyboard mouse
	gfx3d
	script lua
	ui uidummy
	db psql
	net
	)




#
# --- Command lines options ---
#
if(MODULES)
	set(KeywordError FALSE)
	string(REPLACE "," ";" MODULES "${MODULES}")
	string(REPLACE " " ";" MODULES "${MODULES}")
	string(REPLACE "+" "" MODULES "${MODULES}")
	foreach(it ${MODULES})
		set(KeywordIsKnown FALSE)

		# core
		if("${it}" STREQUAL "core")
			set(YUNI_MODULE_CORE TRUE)
			set(KeywordIsKnown TRUE)
		endif("${it}" STREQUAL "core")
		# -core
		if("${it}" STREQUAL "-core")
			set(KeywordIsKnown TRUE)
			YMESSAGE("[!!] Module: Impossible to disable the core module")
			set(KeywordError TRUE)
		endif("${it}" STREQUAL "-core")

		# all
		if("${it}" STREQUAL "all")
			set(YUNI_MODULE_CORE TRUE)
			set(YUNI_MODULE_DEVICES TRUE)
			set(YUNI_MODULE_GFX3D TRUE)
			set(YUNI_MODULE_AUDIO TRUE)
			set(YUNI_MODULE_NET TRUE)
			set(YUNI_MODULE_SCRIPT TRUE)
			set(YUNI_MODULE_UI TRUE)
			set(YUNI_MODULE_UI_DUMMY TRUE)
			set(YUNI_MODULE_DATABASE TRUE)
			set(YUNI_MODULE_ALGORITHMS TRUE)
			set(YUNI_SAMPLES TRUE)
			set(YUNI_TESTS TRUE)
			set(KeywordIsKnown TRUE)
		endif("${it}" STREQUAL "all")

		# algorithms
		if("${it}" STREQUAL "algorithms")
			set(YUNI_MODULE_ALGORITHMS TRUE)
			set(KeywordIsKnown TRUE)
		endif("${it}" STREQUAL "algorithms")
		# -algorithms
		if("${it}" STREQUAL "-algorithms")
			set(YUNI_MODULE_ALGORITHMS TRUE)
			set(KeywordIsKnown TRUE)
		endif("${it}" STREQUAL "-algorithms")


		# display
		if("${it}" STREQUAL "display")
			set(YUNI_MODULE_DEVICE_DISPLAY TRUE)
			set(KeywordIsKnown TRUE)
		endif("${it}" STREQUAL "display")
		# -display
		if("${it}" STREQUAL "-display")
			set(YUNI_MODULE_DEVICE_DISPLAY FALSE)
			set(KeywordIsKnown TRUE)
		endif("${it}" STREQUAL "-display")

		# keyboard
		if("${it}" STREQUAL "keyboard")
			set(YUNI_MODULE_DEVICE_KEYBOARD TRUE)
			set(KeywordIsKnown TRUE)
		endif("${it}" STREQUAL "keyboard")
		# -keyboard
		if("${it}" STREQUAL "-keyboard")
			set(YUNI_MODULE_DEVICE_KEYBOARD FALSE)
			set(KeywordIsKnown TRUE)
		endif("${it}" STREQUAL "-keyboard")

		# mouse
		if("${it}" STREQUAL "mouse")
			set(YUNI_MODULE_DEVICE_MOUSE TRUE)
			set(KeywordIsKnown TRUE)
		endif("${it}" STREQUAL "mouse")
		# -mouse
		if("${it}" STREQUAL "-mouse")
			set(YUNI_MODULE_DEVICE_MOUSE FALSE)
			set(KeywordIsKnown TRUE)
		endif("${it}" STREQUAL "-mouse")

		# devices
		if("${it}" STREQUAL "devices")
			set(YUNI_MODULE_DEVICES TRUE)
			set(KeywordIsKnown TRUE)
		endif("${it}" STREQUAL "devices")
		# -devices
		if("${it}" STREQUAL "-devices")
			set(YUNI_MODULE_DEVICES FALSE)
			set(KeywordIsKnown TRUE)
		endif("${it}" STREQUAL "-devices")


		# net
		if("${it}" STREQUAL "net")
			set(YUNI_MODULE_NET TRUE)
			set(KeywordIsKnown TRUE)
		endif("${it}" STREQUAL "net")
		# -net
		if("${it}" STREQUAL "-net")
			set(YUNI_MODULE_NET FALSE)
			set(KeywordIsKnown TRUE)
		endif("${it}" STREQUAL "-net")

		# gfx3d
		if("${it}" STREQUAL "gfx3d")
			set(KeywordIsKnown TRUE)
			set(YUNI_MODULE_GFX3D TRUE)
		endif("${it}" STREQUAL "gfx3d")
		# -gfx3d
		if("${it}" STREQUAL "-gfx3d")
			set(KeywordIsKnown TRUE)
			set(YUNI_MODULE_GFX3D FALSE)
		endif("${it}" STREQUAL "-gfx3d")


		# audio
		if("${it}" STREQUAL "audio")
			set(KeywordIsKnown TRUE)
			set(YUNI_MODULE_AUDIO TRUE)
		endif("${it}" STREQUAL "audio")
		# -audio
		if("${it}" STREQUAL "-audio")
			set(KeywordIsKnown TRUE)
			set(YUNI_MODULE_AUDIO FALSE)
		endif("${it}" STREQUAL "-audio")


		# script
		if("${it}" STREQUAL "script")
			set(KeywordIsKnown TRUE)
			set(YUNI_MODULE_SCRIPT TRUE)
		endif("${it}" STREQUAL "script")
		# -lua
		if("${it}" STREQUAL "-script")
			set(KeywordIsKnown TRUE)
			set(YUNI_MODULE_SCRIPT FALSE)
		endif("${it}" STREQUAL "-script")

		# lua
		if("${it}" STREQUAL "lua")
			set(KeywordIsKnown TRUE)
			set(YUNI_MODULE_SCRIPT TRUE)
			set(YUNI_EXTERNAL_SCRIPT_LUA TRUE)
		endif("${it}" STREQUAL "lua")
		# -lua
		if("${it}" STREQUAL "-lua")
			set(KeywordIsKnown TRUE)
			set(YUNI_EXTERNAL_SCRIPT_LUA FALSE)
		endif("${it}" STREQUAL "-lua")


		# Tests
		if("${it}" STREQUAL "tests")
			set(KeywordIsKnown TRUE)
			set(YUNI_TESTS TRUE)
		endif("${it}" STREQUAL "tests")
		# -tests
		if("${it}" STREQUAL "-tests")
			set(KeywordIsKnown TRUE)
			set(YUNI_TESTS FALSE)
		endif("${it}" STREQUAL "-tests")

		# samples
		if("${it}" STREQUAL "samples")
			set(KeywordIsKnown TRUE)
			set(YUNI_SAMPLES TRUE)
		endif("${it}" STREQUAL "samples")
		# -samples
		if("${it}" STREQUAL "-samples")
			set(KeywordIsKnown TRUE)
			set(YUNI_SAMPLES FALSE)
		endif("${it}" STREQUAL "-samples")

		# ui (User Interface)
		if("${it}" STREQUAL "ui")
			set(KeywordIsKnown TRUE)
			set(YUNI_MODULE_UI TRUE)
		endif("${it}" STREQUAL "ui")
		# -ui
		if("${it}" STREQUAL "-ui")
			set(KeywordIsKnown TRUE)
			set(YUNI_MODULE_UI FALSE)
		endif("${it}" STREQUAL "-ui")

		# uidummy (User Interface)
		if("${it}" STREQUAL "uidummy")
			set(KeywordIsKnown TRUE)
			set(YUNI_MODULE_UI_DUMMY TRUE)
		endif("${it}" STREQUAL "uidummy")
		# -ui
		if("${it}" STREQUAL "-uidummy")
			set(KeywordIsKnown TRUE)
			set(YUNI_MODULE_UI_DUMMY FALSE)
		endif("${it}" STREQUAL "-uidummy")

		# db (Database)
		if("${it}" STREQUAL "db")
			set(KeywordIsKnown TRUE)
			set(YUNI_MODULE_DATABASE TRUE)
		endif("${it}" STREQUAL "db")
		# -db
		if("${it}" STREQUAL "-db")
			set(KeywordIsKnown TRUE)
			set(YUNI_MODULE_DATABASE FALSE)
		endif("${it}" STREQUAL "-db")

		# PostgreSQL (Database)
		if("${it}" STREQUAL "psql")
			set(KeywordIsKnown TRUE)
			set(YUNI_MODULE_DB_PSQL TRUE)
		endif("${it}" STREQUAL "psql")
		# -psql
		if("${it}" STREQUAL "-psql")
			set(KeywordIsKnown TRUE)
			set(YUNI_MODULE_DB_PSQL FALSE)
		endif("${it}" STREQUAL "-psql")


		if(NOT KeywordIsKnown)
			YMESSAGE("[!!] Unknown module from command line: `${it}` (ignored)")
			set(KeywordError TRUE)
		endif(NOT KeywordIsKnown)

	EndForEach(it {MODULES})

	if(KeywordError)
		YMESSAGE("")
		YMESSAGE("Errors on modules. Here is the list of all available modules :")
		YMESSAGE("(+ : Enable the module,  - disable the module)")
		YMESSAGE(" Main and virtual modules")
		YMESSAGE("    +core          : The core module (needed)")
		YMESSAGE("    -/+tests       : Atomic Tests for the yuni framework")
		YMESSAGE("    -/+samples     : Samples for the yuni framework")
		YMESSAGE("    +all           : Enable all main modules (gfx3d,script,tests,samples)")
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
		YMESSAGE("")
		Message(FATAL_ERROR "Errors on module names")
	Endif(KeywordError)
endif(MODULES)


if(YUNI_MODULE_DEVICE_DISPLAY AND YUNI_MODULE_DEVICES)
	SET(TMP_DISPLAY_DEV_FOR_GFX3D_IS_ENABLED TRUE)
else(YUNI_MODULE_DEVICE_DISPLAY AND YUNI_MODULE_DEVICES)
	SET(TMP_DISPLAY_DEV_FOR_GFX3D_IS_ENABLED FALSE)
endif(YUNI_MODULE_DEVICE_DISPLAY AND YUNI_MODULE_DEVICES)

if(YUNI_MODULE_GFX3D AND NOT TMP_DISPLAY_DEV_FOR_GFX3D_IS_ENABLED)
	SET(YUNI_MODULE_DEVICES TRUE)
	SET(YUNI_MODULE_DEVICE_DISPLAY TRUE)
endif(YUNI_MODULE_GFX3D AND NOT TMP_DISPLAY_DEV_FOR_GFX3D_IS_ENABLED)

if(YUNI_MODULE_UI)
	if(NOT YUNI_EXTERNAL_GFX_CAIROPANGO)
		YMESSAGE("[!!] Warning: Cairo and Pango are required for the `ui` module. The module has been disabled.")
		set(YUNI_MODULE_UI FALSE)
		set(YUNI_MODULE_UI_3D FALSE)
	endif(NOT YUNI_EXTERNAL_GFX_CAIROPANGO)
endif(YUNI_MODULE_UI)

if(YUNI_MODULE_SCRIPT)
	if(NOT YUNI_EXTERNAL_SCRIPT_LUA)
		YMESSAGE("[!!] Warning: No external extension for the `script` module. The module has been disabled.")
		set(YUNI_MODULE_SCRIPT FALSE)
	endif(NOT YUNI_EXTERNAL_SCRIPT_LUA)
endif(YUNI_MODULE_SCRIPT)

if(YUNI_MODULE_DATABASE)
	if(NOT YUNI_MODULE_DB_PSQL)
		YMESSAGE("[!!] Warning: No external extension for the `database` module. The module has been disabled.")
		set(YUNI_MODULE_DATABASE FALSE)
	endif(NOT YUNI_MODULE_DB_PSQL)
endif(YUNI_MODULE_DATABASE)





#
# We have to keep a list of all available modules
#
set(YUNI_MODULE_AVAILABLE)

if(YUNI_MODULE_ALGORITHMS)
	list(APPEND YUNI_MODULE_AVAILABLE algorithms)
endif(YUNI_MODULE_ALGORITHMS)

if(YUNI_MODULE_DEVICES)
	list(APPEND YUNI_MODULE_AVAILABLE devices)
	if(YUNI_MODULE_DEVICE_DISPLAY)
		list(APPEND YUNI_MODULE_AVAILABLE display)
	endif(YUNI_MODULE_DEVICE_DISPLAY)
	if(YUNI_MODULE_DEVICE_MOUSE)
		list(APPEND YUNI_MODULE_AVAILABLE mouse)
	endif(YUNI_MODULE_DEVICE_MOUSE)
	if(YUNI_MODULE_DEVICE_KEYBOARD)
		list(APPEND YUNI_MODULE_AVAILABLE keyboard)
	endif(YUNI_MODULE_DEVICE_KEYBOARD)
endif(YUNI_MODULE_DEVICES)

if(YUNI_MODULE_NET)
	list(APPEND YUNI_MODULE_AVAILABLE net)
endif(YUNI_MODULE_NET)

if(YUNI_MODULE_GFX3D)
	list(APPEND YUNI_MODULE_AVAILABLE gfx3d)
endif(YUNI_MODULE_GFX3D)

if(YUNI_MODULE_AUDIO)
	list(APPEND YUNI_MODULE_AVAILABLE audio)
endif(YUNI_MODULE_AUDIO)

if(YUNI_MODULE_SCRIPT)
	list(APPEND YUNI_MODULE_AVAILABLE script)
	if(YUNI_EXTERNAL_SCRIPT_LUA)
		list(APPEND YUNI_MODULE_AVAILABLE lua)
	endif(YUNI_EXTERNAL_SCRIPT_LUA)
endif(YUNI_MODULE_SCRIPT)


if(YUNI_MODULE_UI)
	list(APPEND YUNI_MODULE_AVAILABLE ui)
	if(YUNI_MODULE_UI_DUMMY)
		list(APPEND YUNI_MODULE_AVAILABLE uidummy)
	endif(YUNI_MODULE_UI_DUMMY)
endif(YUNI_MODULE_UI)

if(YUNI_MODULE_DB)
	list(APPEND YUNI_MODULE_AVAILABLE db)
	if(YUNI_MODULE_DB_PSQL)
		list(APPEND YUNI_MODULE_AVAILABLE psql)
	endif(YUNI_MODULE_DB_PSQL)
endif(YUNI_MODULE_DB)

