#pragma once

#include "../../DLL/dll.h"

#include "../GLObjects.h"
#include "Buffer.h"

#include <vector>

namespace age
{
	class VertexArray : public GLObject
	{
		const unsigned int  BUFFER_SIZE = Buffer::INDICES;
		std::vector<Buffer*> buffers;

	public:
		ANSEL_API  VertexArray();
		ANSEL_API ~VertexArray();

		ANSEL_API void bind() override;
		ANSEL_API void unbind() const override;

		ANSEL_API Buffer &getBuffer(const unsigned int index);
	};
}