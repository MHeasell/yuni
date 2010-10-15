
YMESSAGE(":: [Module] UI")

LIBYUNI_CONFIG_LIB("ui"      "yuni-static-ui-core")

LIBYUNI_CONFIG_DEPENDENCY("ui" "core") # core is required

add_definitions("-DYUNI_MODULE_UI")


list(APPEND SRC_UI

	ui/application.h ui/application.hxx ui/application.cpp
	ui/component.h ui/component.hxx ui/component.cpp
	ui/control.h ui/control.hxx ui/control.cpp
	ui/controlcontainer.h ui/controlcontainer.hxx ui/controlcontainer.cpp
	ui/desktop.h ui/desktop.hxx ui/desktop.cpp
	ui/loop.h ui/loop.hxx ui/loop.cpp
	ui/queueservice.h ui/queueservice.hxx ui/queueservice.cpp
	ui/ui.h

	# Window Systems
	ui/windowsystem.h
	ui/windowsystem/windows.h
	ui/windowsystem/x11.h
	ui/windowsystem/cocoa.h
	ui/windowsystem/native.h

	# Window
	ui/window.h ui/window.hxx ui/window.cpp

	# Standard Components
	ui/button.h ui/button.hxx ui/button.cpp
)


#
# Cairo - Pango
#
DEVPACK_IMPORT_CAIROPANGO()
if (CAIRO_FOUND)
	# We Have Cairo
	YMESSAGE("Added Support for Cairo")
	add_definitions("-DYUNI_USE_CAIRO")
	target_link_libraries("${YUNI_EXT_CAIROPANGO_LIB}")
	list(APPEND SRC_GFX3D gfx/surface/cairo.h gfx/surface/cairo.cpp)
	if (WIN32 OR WIN64)
		# Cairo under Windows
		list(APPEND SRC_GFX3D gfx/window/msw/cairo.cpp)
	endif (WIN32 OR WIN64)
	# yuni-config
	LIBYUNI_CONFIG_DEFINITION("ui"  "YUNI_USE_CAIRO")
	LIBYUNI_CONFIG_INCLUDE_PATH("ui"  "${YUNI_EXT_CAIROPANGO_INCLUDE}")
	LIBYUNI_CONFIG_LIB_RAW_COMMAND("ui"  "${YUNI_EXT_CAIROPANGO_LIB}")

else (CAIRO_FOUND)
	YERROR("[!!] Impossible to find Cairo")
endif (CAIRO_FOUND)
if (PANGO_FOUND)
	YMESSAGE("Added Support for Pango")
	add_definitions("-DYUNI_USE_PANGO")
	LIBYUNI_CONFIG_DEFINITION("ui"  "YUNI_USE_PANGO")
else (PANGO_FOUND)
	YERROR("[!!] Impossible to find Pango")
endif (PANGO_FOUND)


add_library(yuni-static-ui-core STATIC ${SRC_UI})

