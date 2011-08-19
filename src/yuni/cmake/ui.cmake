
YMESSAGE_MODULE("UI  (EXPERIMENTAL, FOR ADVANCED USERS ONLY)")

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
	ui/local/window/window.cpp
	ui/local/window.h

	ui/application.h
	ui/application.hxx
	ui/application.cpp
	ui/component.h
	ui/component.hxx
	ui/component.cpp
	ui/desktop.h
	ui/desktop.hxx
	ui/desktop.cpp
	ui/id.h
	ui/id.cpp
	ui/fwd.h

	# Window
	ui/window.h
	ui/window.hxx
	ui/window.cpp

	# Standard Components
	ui/control.h
	ui/control/control.h
	ui/control/control.hxx
	ui/control/control.cpp
	ui/control/controlcontainer.h
	ui/control/controlcontainer.hxx
	ui/control/controlcontainer.cpp
	# Button
	ui/control/button.h
	ui/control/button.hxx
	ui/control/button.cpp

	# Local components
	ui/local/controls/surface.h
	ui/local/controls/glsurface.h

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
set(YUNI_HAS_OPENGL  OPENGL_FOUND)

# Found
if (YUNI_HAS_OPENGL)
	YMESSAGE("      Using OpenGL from system")
	YMESSAGE("      -> OpenGL Libraries : ${OPENGL_INCLUDE_DIR}")

	# yuni-config
	LIBYUNI_CONFIG_INCLUDE_PATH("both" "audio" "${OPENGL_INCLUDE_DIR}")
	LIBYUNI_CONFIG_LIB("both" "audio" "${OPENGL_LIBRARY}")
	if (APPLE)
		# Frameworks
		LIBYUNI_CONFIG_FRAMEWORK("both" "ui" OpenGL)
	endif ()
	# Includes
	set(CMAKE_REQUIRED_INCLUDES "${OPENGL_INCLUDE_DIR}")
	# Check everything is in order
	check_include_files("gl.h" YUNI_HAS_GL_GL_H)
	check_include_files("GL/gl.h" YUNI_HAS_GL_GL_H)
	check_include_files("OpenGL/gl.h" YUNI_HAS_GL_GL_H)
	if (NOT YUNI_HAS_AL_AL_H)
		set(YUNI_CMAKE_ERROR 1)
		YMESSAGE(    "[!!] Impossible to find gl.h. Please check your profile.")
		YMESSAGE(    " * Packages needed on Debian: libopengl-dev")
		YMESSAGE(    " * Packages needed on Fedora: opengl-devel")
	endif ()

	# Our files that require GL to compile
	list(APPEND SRC_UI ui/local/controls/glsurface.cpp)

# Not found
else ()
	YFATAL("[!!] OpenGL support was not found !")
endif ()


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
		#list(APPEND SRC_UI ui/local/window/cocoa.h ui/local/window/cocoa.cpp)
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

