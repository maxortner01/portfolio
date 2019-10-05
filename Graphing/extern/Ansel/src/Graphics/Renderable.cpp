#include "../../include/Ansel/Graphics/Renderable.h"

#include <GL/glew.h>

namespace age
{
	void Target::clear(Color color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Target::draw(Renderable &object)
	{
		object.draw();
	}

	void Target3D::clear(Color color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Target3D::render(Object3D &object, Shader &shader, Camera &camera)
	{
		object.render(shader, camera);
	}
}