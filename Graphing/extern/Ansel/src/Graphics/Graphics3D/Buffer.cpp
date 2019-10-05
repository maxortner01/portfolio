#include "Ansel/Graphics/Graphics3D/Buffer.h"

#include <iostream>

#include <GL/glew.h>

namespace age
{
	Buffer::Buffer(unsigned int index) :
		_index(index)
	{
		glGenBuffers(1, &id());
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &id());
	}

	void Buffer::bindData(const DataType &data, bool static_draw, bool divisor)
	{
		bind();

		GLenum type = GL_ARRAY_BUFFER;
		if (_index == INDICES)
			type = GL_ELEMENT_ARRAY_BUFFER;

		glBufferData(type, data.count() * data.size(), data.data(), ((static_draw) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW));

		if (_index != INDICES)
			glVertexAttribPointer(index(), data.amount(), GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(index());

		if (divisor) glVertexAttribDivisor(index(), 1);

		unbind();

		bound_data = true;

		this->data = new DataType(data);
	}

	void Buffer::bind()
	{
		if (_index == INDICES)
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id());
		else
			glBindBuffer(GL_ARRAY_BUFFER, id());
	}

	void Buffer::unbind() const
	{
		if (_index == INDICES)
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		else
			glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}