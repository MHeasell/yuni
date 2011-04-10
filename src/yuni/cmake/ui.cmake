
YMESSAGE(":: [Module] UI  (EXPERIMENTAL, FOR ADVANCED USERS ONLY)")

LIBYUNI_CONFIG_LIB("both" "ui"      "yuni-static-ui-core")

LIBYUNI_CONFIG_DEPENDENCY("ui" "core") # core is required
LIBYUNI_CONFIG_DEPENDENCY("ui" "ldo")
LIBYUNI_CONFIG_DEPENDENCY("ui" "net-server")
LIBYUNI_CONFIG_DEPENDENCY("ui" "net")

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

	# Local components
	surface.h
	glsurface.h glsurface.cpp

	# Adapter stuff
	ui/local/adapter/forrepresentation.h
	ui/local/adapter/forrepresentation.cpp
	ui/local/adapter/localforrepresentation.h
	ui/local/adapter/localforrepresentation.cpp
	ui/adapter/forvirtual.h
	ui/adapter/forvirtual.cpp
	ui/adapter/localforvirtual.h
	ui/adapter/localforvirtual.cpp
)


#
# OpenGL
#
find_package(OpenGL)
set(YUNI_HAS_OPENGL  1)
LIBYUNI_CONFIG_INCLUDE_PATH("both" "ui" "${OPENGL_INCLUDE_DIR}")


#
# System-dependent
#
if (WIN32 OR WIN64)
	list(APPEND SRC_UI ui/local/window/wingdi.h ui/local/window/wingdi.cpp)
	if (YUNI_HAS_OPENGL)
		list(APPEND SRC_UI ui/local/controls/wglsurface.h ui/local/controls/wglsurface.cpp)
	endif ()
else ()
	if (APPLE)
		list(APPEND SRC_UI ui/local/window/cocoa.h ui/local/window/cocoa.cpp)
	else ()
		if (UNIX)
			list(APPEND SRC_UI ui/local/window/x11.h ui/local/window/x11.cpp)
			if (YUNI_HAS_OPENGL)
			   list (APPEND SRC_UI ui/local/controls/glxsurface.h ui/local/controls/glxsurface.cpp)
			endif ()
		endif ()
	endif ()
endif ()

add_library(yuni-static-ui-core STATIC ${SRC_UI})

