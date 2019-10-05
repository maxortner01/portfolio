#pragma once

#include "../../DLL/dll.h"

#include "../Renderable.h"
#include "../GLObjects.h"
#include "../Texture.h"

namespace age
{
	class Surface : public GLObject, public Target
	{
		struct RenderBuffer : public GLObject
		{
			void create(unsigned int width, unsigned int height);

			void bind() override;
			void unbind() const override;
		};

		RenderBuffer renderbuffer;
		Texture texture;

	public:
		ANSEL_API  Surface();
		ANSEL_API  Surface(unsigned int width, unsigned int height);
		ANSEL_API ~Surface();

		ANSEL_API void clear(Color color = Color()) override;
		ANSEL_API void draw(Renderable &object) override;

		ANSEL_API void bind() override;
		ANSEL_API void unbind() const override;

		ANSEL_API void create(unsigned int width, unsigned int height);
		/*******/ Texture &getTexture() { return texture; }
	};
}