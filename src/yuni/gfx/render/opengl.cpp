
# include <algorithm>
# include "../api/gl.h"
# include "opengl.h"

namespace Yuni
{
namespace Gfx
{
namespace Render
{

	void OpenGL::drawFrame(const Yuni::Gfx::Scene& scene)
	{
		if (pPaused)
			return;

		pCounter.addFrames(1);

		// A floating cube - For testing purposes only
		if (1)
		{
			static float rotQuad = 0.1f;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();
			glTranslatef(0.0f, 0.0f, -7.0f);
			glRotatef(rotQuad, 1.0f, 0.5f, 0.25f);
			glBegin(GL_QUADS);
				/* top of cube */
				glColor3f(0.0f, 1.0f, 0.0f);
				glVertex3f(1.0f, 1.0f, -1.0f);
				glVertex3f(-1.0f, 1.0f, -1.0f);
				glVertex3f(-1.0f, 1.0f, 1.0f);
				glVertex3f(1.0f, 1.0f, 1.0f);
				/* bottom of cube */
				glColor3f(1.0f, 0.5f, 0.0f);
				glVertex3f(1.0f, -1.0f, 1.0f);
				glVertex3f(-1.0f, -1.0f, 1.0f);
				glVertex3f(-1.0f, -1.0f, -1.0f);
				glVertex3f(1.0f, -1.0f, -1.0f);
				/* front of cube */
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(1.0f, 1.0f, 1.0f);
				glVertex3f(-1.0f, 1.0f, 1.0f);
				glVertex3f(-1.0f, -1.0f, 1.0f);
				glVertex3f(1.0f, -1.0f, 1.0f);
				/* back of cube */
				glColor3f(1.0f, 1.0f, 0.0f);
				glVertex3f(-1.0f, 1.0f, -1.0f);
				glVertex3f(1.0f, 1.0f, -1.0f);
				glVertex3f(1.0f, -1.0f, -1.0f);
				glVertex3f(-1.0f, -1.0f, -1.0f);
				/* right side of cube */
				glColor3f(1.0f, 0.0f, 1.0f);
				glVertex3f(1.0f, 1.0f, -1.0f);
				glVertex3f(1.0f, 1.0f, 1.0f);
				glVertex3f(1.0f, -1.0f, 1.0f);
				glVertex3f(1.0f, -1.0f, -1.0f);
				/* left side of cube */
				glColor3f(0.0f, 1.0f, 1.0f);
				glVertex3f(-1.0f, 1.0f, 1.0f);
				glVertex3f(-1.0f, 1.0f, -1.0f);
				glVertex3f(-1.0f, -1.0f, -1.0f);
				glVertex3f(-1.0f, -1.0f, 1.0f);
			glEnd();
			rotQuad += 0.1f;
		}

		// All objects
		const Gfx::Scene::Objects& objects = scene.objects();

		// Foreach object
		const Gfx::Scene::Objects::const_iterator endObj = objects.end();
		for (Gfx::Scene::Objects::const_iterator it = objects.begin(); it != endObj; ++it)
		{
			// The skeleton
			const Gfx::Skeleton::Ptr& skel = it->second->skeleton();

			// Reset to identity
			glLoadIdentity();

			// Translation
			const Gfx::Vector3D<float> pos = skel->position();
			glTranslatef(pos.x, pos.y, pos.z);

			// Rotation
			const Gfx::Vector3D<float> rot = skel->rotation();
			// Does this work or must we have a single rotate call?
			glRotatef(rot.x, 1.0f, 0.0f, 0.0f);
			glRotatef(rot.y, 0.0f, 1.0f, 0.0f);
			glRotatef(rot.z, 0.0f, 0.0f, 1.0f);

			// Foreach triangle
			const Gfx::Mesh::TriangleList& triangles = skel->mesh()->triangles();
			const Gfx::Mesh::TriangleList::const_iterator endtr = triangles.end();
			for (Gfx::Mesh::TriangleList::const_iterator it2 = triangles.begin(); it2 != endtr; ++it2)
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
			} // foreach triangle
		} // foreach object
	}




} // namespace Render
} // namespace Gfx3D
} // namespace Yuni
