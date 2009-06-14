
Message(STATUS "[Module] Gfx3D::Ogre")

# Headers for Ogre
DEVPACK_IMPORT_OGRE()


Set(SRC_EXTERNAL_3D_OGRE
	private/gfx3d/ogre/ogre.h
		private/gfx3d/ogre/ogre.engine.h private/gfx3d/ogre/ogre.engine.cpp
		private/gfx3d/ogre/ogre.mesh.h private/gfx3d/ogre/ogre.mesh.cpp)
source_group("Private\\Gfx3D\\Ogre" FILES ${SRC_EXTERNAL_3D_OGRE})


Set(SRC_EXTERNAL_3D
	private/gfx3d/abstract.h private/gfx3d/abstract.cpp
	${YUNI_EXT_OGRE_SRC}  # From DevPack 'ogre-headers'
	${SRC_EXTERNAL_3D_OGRE})

Set(SRC_EXTERNAL_3D
		${SRC_EXTERNAL_3D}
		${YUNI_EXT_OGRE_SRC}  # From DevPack 'ogre-headers'
	)

Add_Library(yuni-static-gfx3d-ogre STATIC ${SRC_EXTERNAL_3D})


