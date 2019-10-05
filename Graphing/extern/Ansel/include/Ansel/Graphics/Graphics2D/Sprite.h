#pragma once

#include "../../Data/Transformation.h"
#include "../../DLL/dll.h"
#include "../Texture.h"
#include "../Renderable.h"

namespace age
{
	class Sprite : public Renderable, public Transformation2D
	{
		Texture* texture;

	public:
		ANSEL_API Sprite();
		ANSEL_API Sprite(Texture &tex);

		ANSEL_API void draw() override;

		ANSEL_API void setTexture(Texture &tex);
	};
}