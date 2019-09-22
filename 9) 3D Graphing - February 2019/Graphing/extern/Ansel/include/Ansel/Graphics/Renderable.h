#pragma once

#include "../DLL/dll.h"
#include "../Data/Vector.h"
#include "../Data/Size.h"
#include "../Data/Color.h"

#include "../Graphics/Shader.h"
#include "../Graphics/Graphics3D/Camera.h"

#include <vector>

namespace age
{
	struct Renderable : public Size
	{
		ANSEL_API virtual void draw() = 0;
	};

	struct Object3D
	{
		ANSEL_API virtual void render(Shader &shader, Camera &camera) = 0;
	};

	struct Target
	{
		ANSEL_API virtual void clear(Color color = Color());
		ANSEL_API virtual void draw(Renderable &object);
	};

	struct Target3D
	{
		ANSEL_API virtual void clear(Color color = Color());
		ANSEL_API virtual void render(Object3D &object, Shader &shader, Camera &camera);
	};
}