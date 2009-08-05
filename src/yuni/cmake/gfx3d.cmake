

Set(SRC_GFX3D
		application/gfx3d.h application/gfx3d.cpp
		gfx/engine.h gfx/engine.cpp
		gfx/window/window.h
		gfx/window/factory.h gfx/window/factory.cpp
		gfx/window/opengl.h gfx/window/opengl.cpp
		gfx/window/openglmsw.h gfx/window/openglmsw.hxx
		gfx/window/openglx11.h gfx/window/openglx11.hxx
		)
source_group(Gfx3D FILES ${SRC_GFX3D})



Add_Library(yuni-static-gfx3d-core STATIC
		${SRC_GFX3D}
	   )





