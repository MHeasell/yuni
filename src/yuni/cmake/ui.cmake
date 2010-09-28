
YMESSAGE(":: [Module] UI")

LIBYUNI_CONFIG_LIB("ui"      "yuni-static-ui-core")

LIBYUNI_CONFIG_DEPENDENCY("ui" "core") # core is required
LIBYUNI_CONFIG_DEPENDENCY("ui" "gfx") # gfx-core is required

LIST(APPEND SRC_UI
	ui/application.h ui/application.hxx ui/application.cpp
	ui/button.h ui/button.cpp
	ui/component.h ui/component.hxx
	ui/control.h
	ui/controlcontainer.h
	ui/desktop.h ui/desktop.hxx ui/desktop.cpp
	ui/window.h ui/window.hxx ui/window.cpp
)

#
# Cairo - Pango
#
DEVPACK_IMPORT_CAIROPANGO()
IF(CAIRO_FOUND)
	# We Have Cairo
	YMESSAGE("Added Support for Cairo")
	ADD_DEFINITIONS("-DYUNI_USE_CAIRO")
	target_link_libraries("${YUNI_EXT_CAIROPANGO_LIB}")
	Include_Directories("${YUNI_EXT_CAIROPANGO_INCLUDE}")
	LIST(APPEND SRC_GFX3D gfx/surface/cairo.h gfx/surface/cairo.cpp)
	IF (WIN32 OR WIN64)
		# Cairo under Windows
		LIST(APPEND SRC_GFX3D gfx/window/msw/cairo.cpp)
	ENDIF (WIN32 OR WIN64)
	# yuni-config
	LIBYUNI_CONFIG_DEFINITION("ui"  "YUNI_USE_CAIRO")
	LIBYUNI_CONFIG_INCLUDE_PATH("ui"  "${YUNI_EXT_CAIROPANGO_INCLUDE}")
	LIBYUNI_CONFIG_LIB_RAW_COMMAND("ui"  "${YUNI_EXT_CAIROPANGO_LIB}")

ELSE(CAIRO_FOUND)
	YERROR("[!!] Impossible to find Cairo")
ENDIF(CAIRO_FOUND)
IF(PANGO_FOUND)
	YMESSAGE("Added Support for Pango")
	ADD_DEFINITIONS("-DYUNI_USE_PANGO")
	LIBYUNI_CONFIG_DEFINITION("ui"  "YUNI_USE_PANGO")
ELSE(PANGO_FOUND)
	YERROR("[!!] Impossible to find Pango")
ENDIF(PANGO_FOUND)


Add_Library(yuni-static-ui-core STATIC ${SRC_UI})

