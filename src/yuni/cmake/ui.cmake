
YMESSAGE(":: [Module] UI  (EXPERIMENTAL, FOR ADVANCED USERS ONLY)")

LIBYUNI_CONFIG_LIB("both" "ui"      "yuni-static-ui-core")

LIBYUNI_CONFIG_DEPENDENCY("ui" "core") # core is required

add_definitions("-DYUNI_MODULE_UI")


list(APPEND SRC_UI
	ui/local/queueservice.h
	ui/local/window
	ui/local/window/types.h
	ui/local/window/window.h
	ui/local/window/window.hxx
	ui/local/window.h

	ui/application.h
	ui/application.hxx
	ui/application.cpp
	ui/component.h
	ui/component.hxx
	ui/component.cpp
	ui/control.h
	ui/control.hxx
	ui/control.cpp
	ui/controlcontainer.h
	ui/controlcontainer.hxx
	ui/controlcontainer.cpp
	ui/desktop.h
	ui/desktop.hxx
	ui/desktop.cpp
	ui/id.h
	ui/id.cpp
	ui/ui.h
	ui/fwd.h

	# Window
	ui/window.h
	ui/window.hxx
	ui/window.cpp

	# Standard Components
	ui/button.h
	ui/button.hxx
	ui/button.cpp
)

if (WIN32 OR WIN64)
	list(APPEND SRC_UI ui/local/window/wingdi.h ui/local/window/wingdi.cpp)
else ()
	if (APPLE)
		list(APPEND SRC_UI ui/local/window/cocoa.h ui/local/window/cocoa.cpp)
	else ()
		if (UNIX)
			list(APPEND SRC_UI ui/local/window/x11.h ui/local/window/x11.cpp)
		endif ()
	endif ()
endif ()

add_library(yuni-static-ui-core STATIC ${SRC_UI})

