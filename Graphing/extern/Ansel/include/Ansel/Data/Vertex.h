#pragma once

#include "Vector.h"
#include "Color.h"

namespace age
{
	struct Vertex2D
	{
		Vec2f position;
		Color color;
	};

	struct Vertex3D
	{
		Vec3f postion;
		Color color;
		Vec2f tex_coords;
		Vec3f normal;
	};
}