
# include <algorithm>
# include "../../private/gfx3d/gl/gl.h"
# include "opengl.h"

namespace Yuni
{
namespace Gfx3D
{
namespace Render
{

	void OpenGL::drawFrame(const Yuni::Gfx::Scene& scene)
	{
		if (pPaused)
			return;

		pCounter.addFrames(1);

		const Gfx::Scene::Objects& objects = scene.objects();
		for (Gfx::Scene::Objects::const_iterator it = objects.begin();
			it != objects.end(); ++it)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			const Gfx::Skeleton::Ptr& skel = it->second->skeleton();
			glLoadIdentity();
			Gfx::Vector3D<float> pos = skel->position();
			glTranslatef(pos.x, pos.y, pos.z);
			Gfx::Vector3D<float> rot = skel->rotation();
			// Does this work or must we have a single rotate call?
			glRotatef(rot.x, 1.0f, 0.0f, 0.0f);
			glRotatef(rot.y, 0.0f, 1.0f, 0.0f);
			glRotatef(rot.z, 0.0f, 0.0f, 1.0f);
			const Gfx::Mesh::TriangleList& triangles = skel->mesh()->triangles();

			for (Gfx::Mesh::TriangleList::const_iterator it2 = triangles.begin();
				it2 != triangles.end(); ++it2)
			{
				glBegin(GL_TRIANGLES);
				Gfx::Point3D<float> v1 = (*it2)->vertex1().position();
				glVertex3f(v1.x, v1.y, v1.z);
				Gfx::Point3D<float> v2 = (*it2)->vertex2().position();
				glVertex3f(v2.x, v2.y, v2.z);
				Gfx::Point3D<float> v3 = (*it2)->vertex3().position();
				glVertex3f(v3.x, v3.y, v3.z);
				glNormal3f((*it2)->normal().x, (*it2)->normal().y, (*it2)->normal().z);
				glEnd();
			}
		}
	}

} // Render
} // Gfx3D
} // Yuni
