#include "../../../include/Ansel/Graphics/Graphics3D/Model.h"
#include "../../../include/Ansel/Graphics/Context.h"

#include <GL/glew.h>

namespace age
{
	Model::Model(RawModel* model)
	{
		rawModel = model;
	}

	void Model::render(Shader &shader, Camera &camera)
	{
		shader.bind();

		shader.setUniform(camera.getView(), "view");
		shader.setUniform(camera.getProjection(), "projection");

		std::vector<Vec4f> translations, rotations, scales, origins;

		translations.push_back(getPosition());
		rotations.push_back(getRotation());
		origins.push_back(getOrigin());
		scales.push_back(getScale());

		rawModel->loadTransformation(translations, rotations, scales, origins);

		rawModel->getVAO().bind();

		Buffer &index = rawModel->getVAO().getBuffer(Buffer::INDICES);
		index.bind();

		GLenum render = GL_TRIANGLES;

		//render = GL_POINTS;
		render = GL_LINES;

		glDrawElementsInstanced(render, index.getData().count(), GL_UNSIGNED_INT, 0, 1);
		//glDrawArrays(GL_TRIANGLES, 0, index.getData().count());

		rawModel->getVAO().unbind();

		shader.unbind();
	}
}