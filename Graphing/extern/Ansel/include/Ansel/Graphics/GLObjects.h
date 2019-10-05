#pragma once

#include "../DLL/dll.h"

namespace age
{
	class GLObject
	{
		unsigned int _ID;

	public:
		virtual ~GLObject() { }

		unsigned int &id() { return _ID; }

		virtual void bind()		    { }
		virtual void unbind() const { }
	};

	struct ContextSettings
	{
		ContextSettings(unsigned int _width = 640, unsigned int _height = 480, bool normal = true, unsigned int depth = 0, unsigned int stencil = 0, unsigned int aliasing = 0) :
			width(_width), height(_height), normalized(normal), depthBits(depth), stencilBits(stencil), antialiasing(aliasing)
		{

		}

		bool normalized;
		unsigned int width;
		unsigned int height;

		unsigned int depthBits;
		unsigned int stencilBits;
		unsigned int antialiasing;
	};
}