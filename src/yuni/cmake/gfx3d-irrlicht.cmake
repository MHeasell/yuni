
Message(STATUS "[Module] Gfx3D::Irrlicht")

# Headers for Irrlicht
DEVPACK_IMPORT_IRRLICHT()


# External Lib: Irrlicht
Set(SRC_EXTERNAL_3D_IRRLICHT
		private/gfx3d/irrlicht/irr.h
		private/gfx3d/irrlicht/irr.engine.h private/gfx3d/irrlicht/irr.engine.cpp
		private/gfx3d/irrlicht/irr.mesh.h private/gfx3d/irrlicht/irr.mesh.cpp)
source_group("Private\\Gfx3D\\Irrlicht" FILES ${SRC_EXTERNAL_3D_IRRLICHT})

Set(SRC_EXTERNAL_3D
		private/gfx3d/abstract.h private/gfx3d/abstract.cpp
		${YUNI_EXT_IRRLICHT_SRC}  # From DevPack 'irrlicht-headers'
		${SRC_EXTERNAL_3D_IRRLICHT})


Set(SRC_EXTERNAL_3D
		${SRC_EXTERNAL_3D}
		${YUNI_EXT_IRRLICHT_SRC}  # From DevPack irrlicht-headers
		)

Add_Library(yuni-static-gfx3d-irrlicht STATIC ${SRC_EXTERNAL_3D})
