
Message(STATUS ":: [Module] Gfx3D")


LIBYUNI_CONFIG_LIB("gfx3d"      "yuni-static-gfx3d-core")

LIBYUNI_CONFIG_DEPENDENCY("gfx3d" "core") # gfx-core is required
LIBYUNI_CONFIG_DEPENDENCY("gfx3d" "gfx") # gfx-core is required
LIBYUNI_CONFIG_DEPENDENCY("gfx3d" "display") # gfx-core is required
LIBYUNI_CONFIG_LIB("gfx3d"  "yuni-static-device-display")

IF(APPLE)
	# Frameworks
	LIBYUNI_CONFIG_FRAMEWORK("gfx3d" CoreFoundation)
	LIBYUNI_CONFIG_FRAMEWORK("gfx3d" Cocoa)
	LIBYUNI_CONFIG_FRAMEWORK("gfx3d" IOKit)
	LIBYUNI_CONFIG_FRAMEWORK("gfx3d" OpenGL)
ENDIF(APPLE)




Set(SRC_GFX3D
		application/gfx3d.h application/gfx3d.cpp
		gfx/engine.h gfx/engine.cpp

		# Window
		gfx/window/window.h
		gfx/window/window.hxx
		gfx/window/window.cpp
		gfx/window/msw/msw.h
		gfx/window/msw/directx.h
		gfx/window/msw/opengl.h
		gfx/window/x11/opengl.h
		gfx/window/x11/x11yuni.h
		gfx/window/cocoa/opengl.h

		# Renderer
		gfx/render/renderer.h gfx/render/renderer.cpp
		gfx/render/opengl.h gfx/render/opengl.cpp

		# Font
		gfx/text/font.h gfx/text/label.h
	)

IF(WIN32 OR WIN64)
	LIST(APPEND SRC_GFX3D gfx/text/wgl.h gfx/text/wgl.cpp)
ENDIF(WIN32 OR WIN64)


Include(CheckIncludeFile)

#
# OpenGL
#
Message(STATUS "Added Support for OpenGL")
find_package(OpenGL)
Set(YUNI_COMPILED_WITH_SUPPORT_FOR_OPENGL  1)
LIBYUNI_CONFIG_INCLUDE_PATH("gfx3d"  "${OPENGL_INCLUDE_DIR}")



#
# X11
#
IF(UNIX AND NOT APPLE)
	find_package(X11)
	IF(X11_FOUND)
		Set(YUNI_HAS_X11_XLIB_HEADER 1)
		LIBYUNI_CONFIG_INCLUDE_PATH("gfx3d"  "${X11_INCLUDE_DIR}")
	ENDIF(X11_FOUND)
	IF(NOT "${YUNI_HAS_X11_HEADER}" GREATER 0 OR NOT "${YUNI_HAS_X11_XLIB_HEADER}" GREATER 0)
		Set(YUNI_CMAKE_ERROR 1)
		Message(STATUS     "[!!] Impossible to find X11/X.h or Xlib.h")
		Message(STATUS     " * Packages needed on Debian: libx11.dev")
		Message(STATUS     " * Packages needed on Fedora: libX11-devel")
	ENDIF(NOT "${YUNI_HAS_X11_HEADER}" GREATER 0 OR NOT "${YUNI_HAS_X11_XLIB_HEADER}" GREATER 0)

	IF(X11_Xrandr_FOUND)
		Set(YUNI_HAS_X11_EXT_RANDR_HEADER 1)
		LIBYUNI_CONFIG_INCLUDE_PATH("gfx3d"  "${X11_Xrandr_INCLUDE_PATH}")
	ENDIF(X11_Xrandr_FOUND)
	IF(NOT "${YUNI_HAS_X11_EXT_RANDR_HEADER}" GREATER 0)
		Set(YUNI_CMAKE_ERROR 1)
		Message(STATUS     "[!!] Impossible to find X11/extensions/Xrandr.h")
		Message(STATUS     " * Packages needed on Debian: libxrandr-dev")
		Message(STATUS     " * Packages needed on Fedora: libXrandr-devel.i686")
	ENDIF(NOT "${YUNI_HAS_X11_EXT_RANDR_HEADER}" GREATER 0)

	CHECK_INCLUDE_FILE("GL/glx.h" YUNI_HAS_GLX_HEADER)
	IF(NOT "${YUNI_HAS_GLX_HEADER}" GREATER 0)
		Set(YUNI_CMAKE_ERROR 1)
		Message(STATUS     "[!!] Impossible to find GL/glx.h.h")
		Message(STATUS     " * Packages needed on Debian: mesa-common-dev")
		Message(STATUS     " * Packages needed on Debian: mesa-libGLU-devel.i686")
	ENDIF(NOT "${YUNI_HAS_GLX_HEADER}" GREATER 0)
	
	IF(OPENGL_GLU_FOUND)
		Set(YUNI_HAS_GLU_HEADER 1)
	ENDIF(OPENGL_GLU_FOUND)
	IF(NOT "${YUNI_HAS_GLU_HEADER}" GREATER 0)
		Set(YUNI_CMAKE_ERROR 1)
		Message(STATUS     "[!!] Impossible to find GL/glu.h")
		Message(STATUS     " * Packages needed on Debian: libglu-dev")
		Message(STATUS     " * Packages needed on Fedora: mesa-libGLU-devel.i686")
	ENDIF(NOT "${YUNI_HAS_GLU_HEADER}" GREATER 0)

ENDIF(UNIX AND NOT APPLE)



#
# DirectX
#
# find_package(DirectX)
IF (WIN32)
	FIND_PATH(DX9_INCLUDE_PATH d3d9.h
		PATHS
			"$ENV{DXSDK_DIR}/Include"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK/Include"
		DOC "The directory where D3D9.h resides")

	FIND_LIBRARY(D3D9_LIBRARY d3d9.lib
		PATHS
			"$ENV{DXSDK_DIR}/Lib/x86"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK/Lib/x86"
		DOC "The directory where d3d9.lib resides")

	FIND_LIBRARY(D3DX9_LIBRARY d3dx9.lib
		PATHS
			"$ENV{DXSDK_DIR}/Lib/x86"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK/Lib/x86"
		DOC "The directory where d3dx9.lib resides")

	SET(SRC_GFX3D ${SRC_GFX3D} gfx/window/msw/msw.cpp gfx/window/msw/opengl.cpp)

	IF(D3D9_LIBRARY AND D3DX9_LIBRARY)
		SET(DX9_LIBRARIES "${D3D9_LIBRARY}" "${D3DX9_LIBRARY}")

		IF(DX9_INCLUDE_PATH)
			ADD_DEFINITIONS("-DYUNI_USE_DIRECTX")
			Message(STATUS "Added Support for DirectX")
			Message(STATUS "  DX include: ${DX9_INCLUDE_PATH}")
			Message(STATUS "  DX libs: ${D3X9_LIBRARY} ${D3DX9_LIBRARY}")
			Set(YUNI_COMPILED_WITH_SUPPORT_FOR_DIRECTX 1)
			SET(SRC_GFX3D ${SRC_GFX3D} gfx/window/msw/directx.cpp)
			Include_Directories("${DX9_INCLUDE_PATH}")
			LIBYUNI_CONFIG_INCLUDE_PATH("gfx3d"  "${DX9_INCLUDE_PATH}")
			LIBYUNI_CONFIG_DEFINITION("gfx3d"  "YUNI_USE_DIRECTX")
		ENDIF(DX9_INCLUDE_PATH)
	ENDIF(D3D9_LIBRARY AND D3DX9_LIBRARY)

ELSE(WIN32)
	IF(APPLE)
	ELSE(APPLE)
		Set(SRC_GFX3D ${SRC_GFX3D} gfx/window/x11/opengl.cpp)
		LIBYUNI_CONFIG_LIB("gfx3d" "GL")
		LIBYUNI_CONFIG_LIB("gfx3d" "GLU")
	ENDIF(APPLE)
ENDIF(WIN32)

source_group(Gfx3D FILES ${SRC_GFX3D})

Add_Library(yuni-static-gfx3d-core STATIC ${SRC_GFX3D})

target_link_libraries(yuni-static-gfx3d-core
	# DirectX
	${OPENGL_LIBRARY} ${DX9_LIBRARIES})

