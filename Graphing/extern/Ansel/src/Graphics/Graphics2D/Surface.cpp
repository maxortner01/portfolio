#include "../../../include/Ansel/Graphics/Graphics2D/Surface.h"

#include <iostream>

#include <GL/glew.h>

namespace age
{
	Surface::Surface() {}

	Surface::Surface(unsigned int width, unsigned int height)
	{
		create(width, height);
	}

	Surface::~Surface()
	{
		glDeleteFramebuffers(1, &id());
	}

	void Surface::create(unsigned int width, unsigned int height)
	{
		glGenFramebuffers(1, &id());

		bind();

		texture.makeEmpty(width, height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id(), 0);

		renderbuffer.create(width, height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer.id());

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Error: Framebuffer not complete!" << std::endl;

		unbind();
	}

	void Surface::clear(Color color) 
	{
		bind();
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		unbind();
	}

	void Surface::draw(Renderable &object)
	{
		bind();
		object.draw();
		unbind();
	}

	void Surface::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, id());
	}

	void Surface::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Surface::RenderBuffer::create(unsigned int width, unsigned int height)
	{
		glGenRenderbuffers(1, &id());
		bind();
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		unbind();
	}

	void Surface::RenderBuffer::bind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, id());
	}

	void Surface::RenderBuffer::unbind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}