#pragma once

#include "Shape.h"

namespace age
{
	class Circle : public Shape
	{
		unsigned int points = 32;
		float radius = 1.f;

	public:
		ANSEL_API void draw() override;

		void setPointCount(unsigned int c) { points = c; }
		void setRadius(float r)			   { radius = r; }
	};
}