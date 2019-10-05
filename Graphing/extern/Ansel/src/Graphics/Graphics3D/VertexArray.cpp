#include "../../../include/Ansel/Graphics/Graphics3D/VertexArray.h"

#include <GL/glew.h>

namespace age
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &id());

		bind();

		for (int i = 0; i < BUFFER_SIZE; i++)
			buffers.push_back(new Buffer(i));

		Buffer* index_buffer = new Buffer(Buffer::INDICES);
		buffers.push_back(index_buffer);

		unbind();
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &id());
	}

	void VertexArray::bind()
	{
		glBindVertexArray(id());
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	Buffer &VertexArray::getBuffer(const unsigned int index)
	{
		return *buffers.at(index);
	}
}