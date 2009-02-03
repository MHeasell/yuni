/*
 * WARNING: this file uses bare irrlicht calls for now, and until Application::Gfx3D and/or friends implements
 * methods to display something on the devices.
 *
 * This is mainly a sample to enable Loomchild to test his Polygonizers algorithms.
 *
 */
#include <stdexcept>
#include <vector>
#include <yuni/yuni.h>
#include <yuni/application/gfx3d.h>
#include <yuni/gfx/mesh.h>
#include <yuni/gfx/marchingcubes.h>
#include <yuni/gfx/metabox.h>


#include <irrlicht.h>



using namespace Yuni;
using namespace Yuni::Gfx;
using namespace irr;

/*
 * TODO: Remove this ASAP.
 */
class IrrMetaboxNode : public irr::scene::ISceneNode
{
private:
	//! Our vertices
	std::vector<video::S3DVertex> pVertices;
	//! Our indexes
	std::vector<u16> pIndexes;
	//! Our material
	video::SMaterial pMaterial;
	//! Our Bounding box.
	core::aabbox3d<f32> pBox;
	//! The box
	MetaBox* pMetabox;

	const float MAX_DISTANCE;

public:
	IrrMetaboxNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
		: scene::ISceneNode(parent, mgr, id), MAX_DISTANCE(14.0f)
	{
		pMaterial.Wireframe = true;
		pMaterial.Lighting = false;

		pMetabox = new MetaBox(BoundingBox<float>(Point3D<float>(-8.0, -8.0, -8.0), Point3D<float>(8.0, 8.0, 8.0)));
		
		UpdateMesh();
	}


    virtual void OnRegisterSceneNode()
	{
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);

		ISceneNode::OnRegisterSceneNode();
	}


	virtual void render()
	{
		video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setMaterial(pMaterial);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
		driver->drawIndexedTriangleList(&(pVertices[0]), pVertices.size(), &(pIndexes[0]), pIndexes.size() / 3);
	}

	virtual const core::aabbox3d<f32>& getBoundingBox() const
	{
		return pBox;
	}


	virtual u32 getMaterialCount() const
	{
		return 1;
	}

	virtual video::SMaterial& getMaterial(u32 i)
	{
		return pMaterial;
	}    

private:

	void UpdateMesh()
	{
		ImplicitSurface surf;

		// Add the box to the surface
		surf.addSubSurface(pMetabox);

		// Create a mesh using marchingcubes with an isovalue of 0.05, and a 2.0 mesh size
		Mesh* mesh2 = MarchingCubes(surf)(0.05f, 1.0f);
		if (!mesh2)
			throw std::runtime_error("Polygonization failed.");

		const Mesh::TriangleList& tList = mesh2->triangles();

		int vertexCount = 0;
		pIndexes.clear();
		pVertices.clear();
		for (Mesh::TriangleList::const_iterator triangle = tList.begin(); triangle != tList.end(); ++triangle)
		{
			const Gfx::Vertex &tVertex1 = (*triangle)->vertex1();
			video::S3DVertex vx1(tVertex1.position().x, tVertex1.position().y, tVertex1.position().z,
				0, 0, 0, video::SColor(255,255,0,0), 0, 0);

			const Gfx::Vertex &tVertex2 = (*triangle)->vertex2();
			video::S3DVertex vx2(tVertex2.position().x, tVertex2.position().y, tVertex2.position().z,
				0, 0, 0, video::SColor(255,0,255,0), 0, 0);

			const Gfx::Vertex &tVertex3 = (*triangle)->vertex3();
			video::S3DVertex vx3(tVertex3.position().x, tVertex3.position().y, tVertex3.position().z,
				0, 0, 0, video::SColor(255,0,0,255), 0, 0);

			pVertices.push_back(vx1);
			if (vertexCount == 0)
				pBox.reset(vx1.Pos);
			else
				pBox.addInternalPoint(vx1.Pos);
			pIndexes.push_back(vertexCount);

			pVertices.push_back(vx2);
			pIndexes.push_back(vertexCount + 1);
			pBox.addInternalPoint(vx2.Pos);

			pVertices.push_back(vx3);
			pIndexes.push_back(vertexCount + 2);
			pBox.addInternalPoint(vx3.Pos);

			vertexCount += 3;
		}
		delete mesh2;
	}
};


class MeshTestApplication : public Application::Gfx3D
{
public:
	MeshTestApplication(int argc, char* argv[])
		:Application::Gfx3D(argc, argv)
	{
		// We connect our own method to the event
		Gfx::Engine::Instance()->onFPSChanged.connect(this, &MeshTestApplication::onFPSChanged);
	}

	virtual ~MeshTestApplication()
	{
		// It is advised to disconnect all events at this stade
		this->disconnectAllNotifiers();
	}

	void onFPSChanged(int fps)
	{
		// The FPS count has changed
		// We will set the application title according the new value
		this->title(String() << "Hello World ! - " << fps << " fps");
	}
};




int main(int argc, char* argv[])
{
	{ /* Bare irrlicht calls. TODO: remove them ASAP. */
		using namespace irr;

		IrrlichtDevice *device =
#ifdef _IRR_OSX_PLATFORM_
			createDevice(video::EDT_OPENGL, core::dimension2d<s32>(640, 480), 16,
						 false, false, false, 0);
#else
			createDevice(video::EDT_DIRECT3D9, core::dimension2d<s32>(640, 480), 16,
					 false, false, false, 0);
#endif
		if (!device)
			return 1;

		device->setWindowCaption(L"Yuni GFX Hello World!");
		video::IVideoDriver* driver = device->getVideoDriver();
		scene::ISceneManager* smgr = device->getSceneManager();
		gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

		guienv->addStaticText(L"Hello World! (i'm using irrlicht directly, it's bad.)",
							  core::rect<s32>(10,10,260,22), true);

		smgr->addCameraSceneNode(0, core::vector3df(0, 0, -40), core::vector3df(0, 0, 100));

		IrrMetaboxNode *myNode = new IrrMetaboxNode(smgr->getRootSceneNode(), smgr, 666);

		scene::ISceneNodeAnimator* anim =
			smgr->createRotationAnimator(core::vector3df(0.1f, 0, 0.1f));

		if (anim)
		{
			myNode->addAnimator(anim);
			anim->drop();
			anim = 0;
		}
		myNode->drop();
		myNode = 0; 

		u32 frames=0;
		while(device->run())
		{
			driver->beginScene(true, true, video::SColor(0,0,0,0));

			smgr->drawAll();

			driver->endScene();
			if (++frames==100)
			{
				core::stringw str = L"Irrlicht Engine [";
				str += driver->getName();
				str += L"] FPS: ";
				str += (s32)driver->getFPS();

				device->setWindowCaption(str.c_str());
				frames=0;
			}
		}

		device->drop();



	}


	/*
	 * Yuni main loop (disabled)
	 */
	/*
	   MeshTestApplication app(argc, argv);
	   app.execute();
	   return app.exitCode();
	 */
	return 0;
}
