#include "../../../include/Ansel/Graphics/Graphics2D/Sprite.h"
#include "../../../include/Ansel/Main/Engine.h"

#include <GL/glew.h>

namespace age
{
	Sprite::Sprite() { }

	Sprite::Sprite(Texture &tex)
	{
		texture = &tex;
	}

	void Sprite::draw()
	{
		if (!texture) return;
		dimensions = texture->getDimensions();
		Vec2f origin = getOrigin();

		glEnable(GL_TEXTURE_2D);
		texture->bind();

		glBegin(GL_QUADS);
			glColor3f(1, 1, 1);

			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(
				getGlobalLocation().x, 
				getGlobalLocation().y
			);

			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(
				getGlobalLocation().x + ((float)texture->getDimensions().x * getScale().x),
				getGlobalLocation().y
			);

			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(
				getGlobalLocation().x + ((float)texture->getDimensions().x * getScale().x),
				getGlobalLocation().y + ((float)texture->getDimensions().y * getScale().y)
			);

			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(
				getGlobalLocation().x,
				getGlobalLocation().y + ((float)texture->getDimensions().y * getScale().y)
			);


		glEnd();

		texture->unbind();
		glDisable(GL_TEXTURE_2D);
	}

	void Sprite::setTexture(Texture &tex)
	{
		dimensions = tex.getDimensions();
		texture = &tex;
	}
}