#include "../../include/Ansel/Main/Scene3D.h"

#include "../../include/Ansel/Graphics/Context.h"

#include <GL/glew.h>

namespace age
{
	Scene3D::Scene3D()
	{
		Context &context = Context::getCurrentContext();
		camera.generateProjection(.005f, 1000.f,65.f, (float)context.getSettings().height / (float)context.getSettings().width);
	}

	void Scene3D::renderObjects(age::Surface surface, RenderType type)
	{
		surface.bind();
		renderObjects(type);
		surface.unbind();
	}
	
	void Scene3D::clear(Color color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Scene3D::renderObjects(RenderType type)
	{
		shader.bind();

		shader.setUniform(camera.getView(), "view");
		shader.setUniform(camera.getProjection(), "projection");

		std::vector<Vec4f> translations, rotations, scales, origins;

		for (int i = 0; i < models.size(); i++) {

			translations.push_back( models.at(i)->getPosition() );
			rotations   .push_back( models.at(i)->getRotation() );
			origins     .push_back( models.at(i)->getOrigin()   );
			scales      .push_back( models.at(i)->getScale()    );
		}

		RawModel* rawModel = &models.at(0)->getRawModel();

		rawModel->loadTransformation(translations, rotations, scales, origins);

		rawModel->getVAO().bind();

		Buffer &index = rawModel->getVAO().getBuffer(Buffer::INDICES);
		index.bind(); 

		GLenum render = GL_TRIANGLES;

		if (type == POINTS) render = GL_POINTS;
		if (type == LINES)  render = GL_LINES;

		glDrawElementsInstanced(render, index.getData().count(), GL_UNSIGNED_INT, 0, models.size());
		//glDrawArrays(GL_TRIANGLES, 0, index.getData().count());

		rawModel->getVAO().unbind();

		shader.unbind();
	}
}