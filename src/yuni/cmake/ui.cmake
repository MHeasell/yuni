
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
	ui/id.h ui/id.cpp
	ui/queueservice.h
	ui/queueservice.hxx
	ui/ui.h
	ui/fwd.h

	# Window Systems
	ui/windowsystem.h
	ui/windowsystem/windows.h
	ui/windowsystem/x11.h
	ui/windowsystem/cocoa.h
	ui/windowsystem/native.h

	# Local representations
	ui/local/window.h ui/local/window.hxx ui/local/window.cpp
	ui/local/windows/wingdiwindow.h
	ui/local/windows/cairowindow.h ui/local/windows/cairowindow.hxx
	ui/local/x11/x11yuni.h
	ui/local/x11/cairowindow.h ui/local/x11/cairowindow.hxx

	# Window
	ui/window.h ui/window.hxx ui/window.cpp

	# Standard Components
	ui/button.h ui/button.hxx ui/button.cpp
)


#
# Cairo
#
DEVPACK_IMPORT_CAIROPANGO()
if (CAIRO_FOUND)
	# We Have Cairo
	YMESSAGE("Added Support for Cairo")
	add_definitions("-DYUNI_USE_CAIRO")
	target_link_libraries("${YUNI_EXT_CAIROPANGO_LIB}")
	list(APPEND SRC_UI gfx/surface/cairo.h gfx/surface/cairo.cpp)

	if (WIN32 OR WIN64)
		# Cairo under Windows
		list(APPEND SRC_UI ui/local/windows/cairowindow.cpp)
	else(WIN32 OR WIN64)
		if (UNIX AND NOT APPLE)
			list(APPEND SRC_UI ui/local/x11/cairowindow.cpp)
		endif (UNIX AND NOT APPLE)
	endif (WIN32 OR WIN64)

	# yuni-config
	LIBYUNI_CONFIG_DEFINITION("ui"  "YUNI_USE_CAIRO")
	LIBYUNI_CONFIG_INCLUDE_PATH("ui"  "${YUNI_EXT_CAIROPANGO_INCLUDE}")
	LIBYUNI_CONFIG_LIB_RAW_COMMAND("ui"  "${YUNI_EXT_CAIROPANGO_LIB}")

else (CAIRO_FOUND)
	YERROR("[!!] Impossible to find Cairo")
endif (CAIRO_FOUND)


#
# Pango
#
if (PANGO_FOUND)
	YMESSAGE("Added Support for Pango")
	add_definitions("-DYUNI_USE_PANGO")
	LIBYUNI_CONFIG_DEFINITION("ui"  "YUNI_USE_PANGO")
else (PANGO_FOUND)
	YERROR("[!!] Impossible to find Pango")
endif (PANGO_FOUND)


#
# Platform-dependent
#
if (WIN32 OR WIN64)
   	list(APPEND SRC_UI ui/local/windows/wingdiwindow.cpp)
endif ()


add_library(yuni-static-ui-core STATIC ${SRC_UI})

