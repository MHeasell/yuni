
Message(STATUS "[Module] Gfx3D::Yuni")

Add_Definitions("-DYUNI_INTERNAL_3D")

# Internal Yuni 3D Lib
Set(SRC_INTERNAL_3D
		private/gfx3d/abstract.h private/gfx3d/abstract.cpp
		private/gfx3d/gl/gl.h
		private/gfx3d/gl/gl.engine.h private/gfx3d/gl/gl.engine.cpp)
source_group("Private\\Gfx3D\\GL" FILES ${SRC_INTERNAL_3D})


find_package(OpenGL)

Add_Library(yuni-static-gfx3d-yuni STATIC ${SRC_INTERNAL_3D})
target_link_libraries(yuni-static-gfx3d-yuni ${OPENGL_LIBRARY})
