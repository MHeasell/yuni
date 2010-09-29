
YMESSAGE(":: [Module] Gfx3D")


LIBYUNI_CONFIG_LIB("gfx3d"      "yuni-static-gfx3d-core")

LIBYUNI_CONFIG_DEPENDENCY("gfx3d" "core") # core is required
LIBYUNI_CONFIG_DEPENDENCY("gfx3d" "gfx") # gfx-core is required
LIBYUNI_CONFIG_DEPENDENCY("gfx3d" "ui") # ui is required
LIBYUNI_CONFIG_DEPENDENCY("gfx3d" "display") # display is required
LIBYUNI_CONFIG_LIB("gfx3d"  "yuni-static-device-display")

if(APPLE)
	# Frameworks
	LIBYUNI_CONFIG_FRAMEWORK("gfx3d" CoreFoundation)
	LIBYUNI_CONFIG_FRAMEWORK("gfx3d" Cocoa)
	LIBYUNI_CONFIG_FRAMEWORK("gfx3d" IOKit)
	LIBYUNI_CONFIG_FRAMEWORK("gfx3d" OpenGL)
endif(APPLE)




set(SRC_GFX3D
		gfx/engine.h gfx/engine.cpp

		# Window
		gfx/window/window.h
		gfx/window/window.hxx
		gfx/window/window.cpp
		gfx/window/msw/msw.h
		gfx/window/msw/directx.h
		gfx/window/msw/opengl.h
		gfx/window/msw/cairo.h
		gfx/window/x11/opengl.h
		gfx/window/x11/x11yuni.h
		gfx/window/cocoa/opengl.h

		# Render surfaces
		gfx/surface/surface.h
		gfx/surface/surface3d.h gfx/surface/surface3d.cpp
		gfx/surface/opengl.h gfx/surface/opengl.cpp
		gfx/surface/cairo.h gfx/surface/cairo.cpp

		# Font
		gfx/text/font.h gfx/text/label.h
	)


if(WIN32 OR WIN64)
	list(APPEND SRC_GFX3D gfx/text/wgl.h gfx/text/wgl.cpp)
endif(WIN32 OR WIN64)


include(CheckIncludeFile)


#
# OpenGL common stuff
#
YMESSAGE("Added Support for OpenGL")
find_package(OpenGL)
set(YUNI_COMPILED_WITH_SUPPORT_FOR_OPENGL  1)
LIBYUNI_CONFIG_INCLUDE_PATH("gfx3d"  "${OPENGL_INCLUDE_DIR}")



#
# X11
#
if(UNIX AND NOT APPLE)
	find_package(X11)
	if(X11_FOUND)
		set(YUNI_HAS_X11_XLIB_HEADER 1)
		LIBYUNI_CONFIG_INCLUDE_PATH("gfx3d"  "${X11_INCLUDE_DIR}")
	endif(X11_FOUND)
	if(NOT "${YUNI_HAS_X11_XLIB_HEADER}" GREATER 0)
		set(YUNI_CMAKE_ERROR 1)
		YMESSAGE(    "[!!] Impossible to find X11/X.h or Xlib.h")
		YMESSAGE(    " * Packages needed on Debian: libx11-dev")
		YMESSAGE(    " * Packages needed on Fedora: libX11-devel")
	endif(NOT "${YUNI_HAS_X11_XLIB_HEADER}" GREATER 0)

	if(X11_Xrandr_FOUND)
		set(YUNI_HAS_X11_EXT_RANDR_HEADER 1)
		LIBYUNI_CONFIG_INCLUDE_PATH("gfx3d"  "${X11_Xrandr_INCLUDE_PATH}")
	endif(X11_Xrandr_FOUND)
	if(NOT "${YUNI_HAS_X11_EXT_RANDR_HEADER}" GREATER 0)
		set(YUNI_CMAKE_ERROR 1)
		YMESSAGE(    "[!!] Impossible to find X11/extensions/Xrandr.h")
		YMESSAGE(    " * Packages needed on Debian: libxrandr-dev")
		YMESSAGE(    " * Packages needed on Fedora: libXrandr-devel")
	endif(NOT "${YUNI_HAS_X11_EXT_RANDR_HEADER}" GREATER 0)

	check_include_file("GL/glx.h" YUNI_HAS_GLX_HEADER)
	if(NOT "${YUNI_HAS_GLX_HEADER}" GREATER 0)
		set(YUNI_CMAKE_ERROR 1)
		YMESSAGE(    "[!!] Impossible to find GL/glx.h")
		YMESSAGE(    " * Packages needed on Debian: mesa-common-dev")
		YMESSAGE(    " * Packages needed on Fedora: mesa-libGLU-devel")
	endif(NOT "${YUNI_HAS_GLX_HEADER}" GREATER 0)

	if(OPENGL_GLU_FOUND)
		set(YUNI_HAS_GLU_HEADER 1)
		LIBYUNI_CONFIG_LIB("gfx3d" "GLU")
	endif(OPENGL_GLU_FOUND)
	if(NOT "${YUNI_HAS_GLU_HEADER}" GREATER 0)
		set(YUNI_CMAKE_ERROR 1)
		YMESSAGE(    "[!!] Impossible to find GL/glu.h")
		YMESSAGE(    " * Packages needed on Debian: libglu-dev")
		YMESSAGE(    " * Packages needed on Fedora: mesa-libGLU-devel")
	endif(NOT "${YUNI_HAS_GLU_HEADER}" GREATER 0)

endif(UNIX AND NOT APPLE)



#
# DirectX and OpenGL
#
if (WIN32)
	# Search for DirectX
	find_path(DX9_INCLUDE_PATH d3d9.h
		PATHS
			"$ENV{DXSDK_DIR}/Include"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK/Include"
		DOC "The directory where d3d9.h resides")

	find_library(D3D9_LIBRARY d3d9.lib
		PATHS
			"$ENV{DXSDK_DIR}/Lib/x86"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK/Lib/x86"
		DOC "The path to where d3d9.lib resides")

	find_library(D3DX9_LIBRARY d3dx9.lib
		PATHS
			"$ENV{DXSDK_DIR}/Lib/x86"
			"$ENV{PROGRAMFILES}/Microsoft DirectX SDK/Lib/x86"
		DOC "The path to where d3dx9.lib resides")

	set(SRC_GFX3D ${SRC_GFX3D} gfx/window/msw/msw.cpp gfx/window/msw/opengl.cpp)
	LIBYUNI_CONFIG_LIB_RAW_COMMAND("gfx3d"  "${OPENGL_LIBRARY}")

	if(D3D9_LIBRARY AND D3DX9_LIBRARY)
		if(DX9_INCLUDE_PATH)
			add_definitions("-DYUNI_USE_DIRECTX")
			YMESSAGE("Added Support for DirectX")
			YMESSAGE("  DX include: ${DX9_INCLUDE_PATH}")
			YMESSAGE("  DX libs: ${D3D9_LIBRARY}")
			set(YUNI_COMPILED_WITH_SUPPORT_FOR_DIRECTX 1)
			set(SRC_GFX3D ${SRC_GFX3D} gfx/window/msw/directx.cpp)
			include_directories("${DX9_INCLUDE_PATH}")
			LIBYUNI_CONFIG_DEFINITION("gfx3d"  "YUNI_USE_DIRECTX")
			LIBYUNI_CONFIG_INCLUDE_PATH("gfx3d"  "${DX9_INCLUDE_PATH}")
			LIBYUNI_CONFIG_LIB_RAW_COMMAND("gfx3d"  "${D3D9_LIBRARY}")
			LIBYUNI_CONFIG_LIB_RAW_COMMAND("gfx3d"  "${D3DX9_LIBRARY}")
		endif(DX9_INCLUDE_PATH)
	endif(D3D9_LIBRARY AND D3DX9_LIBRARY)

else(WIN32)
	if(APPLE)
		# TODO
	else(APPLE)
		set(SRC_GFX3D ${SRC_GFX3D} gfx/window/x11/opengl.cpp)
		LIBYUNI_CONFIG_LIB("gfx3d" "GL")
		LIBYUNI_CONFIG_LIB("gfx3d" "GLU")
	endif(APPLE)
endif(WIN32)

source_group(Gfx3D FILES ${SRC_GFX3D})

add_library(yuni-static-gfx3d-core STATIC ${SRC_GFX3D})

# Setting output path
set_target_properties(yuni-static-gfx3d-core PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${YUNI_OUTPUT_DIRECTORY}/lib")

# Installation
install(TARGETS yuni-static-gfx3d-core ARCHIVE DESTINATION lib/${YUNI_VERSIONED_INST_PATH})

target_link_libraries(yuni-static-gfx3d-core
	${OPENGL_LIBRARY} ${DX9_LIBRARIES})

