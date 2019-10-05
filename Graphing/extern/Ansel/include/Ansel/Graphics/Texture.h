#pragma once

#include <string>

#include "../DLL/dll.h"
#include "../Data/Size.h"
#include "GLObjects.h"
#include "Renderable.h"

namespace age
{
	class Texture : public GLObject, public Size
	{
		void setParameters() const;

	public:
		ANSEL_API Texture();

		ANSEL_API void makeEmpty(unsigned int width, unsigned int height);
		ANSEL_API void loadFromFile(std::string directory);

		ANSEL_API void bind() override;
		ANSEL_API void unbind() const override;
	};
}