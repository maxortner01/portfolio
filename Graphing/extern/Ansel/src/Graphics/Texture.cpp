#include "../../include/Ansel/Graphics/Texture.h"

#include <GL/glew.h>

#include "../../include/Ansel/Main/Engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace age
{
	Texture::Texture()
	{
		glGenTextures(1, &id());
	}

	void Texture::setParameters() const
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void Texture::makeEmpty(unsigned int width, unsigned int height)
	{
		bind();

		setParameters();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		dimensions = { width, height };

		unbind();
	}

	void Texture::loadFromFile(std::string directory)
	{
		bind();

		setParameters();

		int width, height, nrChannels;
		unsigned char *data = stbi_load(directory.c_str(), &width, &height, &nrChannels, 0);
		//stbi__vertical_flip(data, width, height, nrChannels);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			dimensions = { (unsigned int)width, (unsigned int)height };
		}

		stbi_image_free(data);
		unbind();
	}

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, id());
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}