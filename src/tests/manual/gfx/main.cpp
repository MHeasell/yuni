/*
 * WARNING: this file uses bare irrlicht calls for now, and until Application::Gfx3D and/or friends implements
 * methods to display something on the devices.
 *
 * This is mainly a sample to enable Loomchild to test his Poligonizers algorithms.
 *
 */
#include <stdexcept>
#include <vector>
#include <yuni/yuni.h>
#include <yuni/application/gfx3d.h>
#include <yuni/gfx/mesh.h>
#include <yuni/gfx/marchingcubes.h>
#include <yuni/gfx/metaball.h>


#include <irrlicht.h>



using namespace Yuni;
using namespace Yuni::Gfx;
using namespace irr;

/*
 * TODO: Remove this ASAP.
 */
class IrrMetaballNode : public irr::scene::ISceneNode
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
public:
	IrrMetaballNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
		: scene::ISceneNode(parent, mgr, id)
	{
		pMaterial.Wireframe = true;
		pMaterial.Lighting = false;

		// We use the Metaball algorithm
		ImplicitSurface surf;
		surf.addSubSurface(new MetaBall(Point3D<float>(0.0f, 0.0f, 0.0f), 1.0f));

		// Create a mesh using marchingcubes with an isovalue of 4, and a 1.0 mesh size
		Mesh* mesh2 = MarchingCubes(surf)(4.0f, 1.0f);
		if (!mesh2)
			throw std::runtime_error("Poligonization failed.");

		const Mesh::TriangleList& tList = mesh2->triangles();

		int vertexCount = 0;
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
	// Create a stupid mesh with only one triangle
	Mesh mesh;
	SharedPtr<Triangle> tri(new Triangle(Vertex(0.0f, 0.0f, 0.0f),
										 Vertex(0.0f, 4.0f, 0.0f), Vertex(3.0f, 0.0f, 0.0f)));
	mesh.addTriangle(tri);
	//	mesh.print(std::cout);

	// Create an implicitsurface containing one metaball centered on (0,0,0), density=1.0f
	ImplicitSurface surf;
	surf.addSubSurface(new MetaBall(Point3D<float>(1.0f, 0.0f, 0.0f), 2.0f));

	// Create a mesh using marchingcubes with an isovalue of 4, and a 1.0 mesh size
	Mesh* mesh2 = MarchingCubes(surf)(4.0f, 1.0f);
	if (!mesh2)
		return 1;
	//mesh2->print(std::cout);
	//	mesh2->update();

	//	mesh2->glPrint(std::cout);

	// Create another mesh using marchingcubes with an isovalue of 7, and a 0.2 mesh size
	// 	mesh2 = MarchingCubes(surf)(7.0f, 0.2f);
	// 	if (!mesh2)
	// 		return 1;
	// 	mesh2->print(std::cout);

	{ /* Bare irrlicht calls. TODO: remove them ASAP. */
		using namespace irr;

		IrrlichtDevice *device =
#ifdef _IRR_OSX_PLATFORM_
			createDevice(video::EDT_OPENGL, core::dimension2d<s32>(640, 480), 16,
						 false, false, false, 0);
#else
		createDevice(video::EDT_SOFTWARE, core::dimension2d<s32>(640, 480), 16,
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

		smgr->addCameraSceneNode(0, core::vector3df(0, -8, 0), core::vector3df(0,0,0));

		IrrMetaballNode *myNode = new IrrMetaballNode(smgr->getRootSceneNode(), smgr, 666);

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
