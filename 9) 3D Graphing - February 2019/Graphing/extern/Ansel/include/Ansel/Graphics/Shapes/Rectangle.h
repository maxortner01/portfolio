#pragma once

#include "../../DLL/dll.h"
#include "Shape.h"

namespace age
{
	class Rectangle : public Shape
	{
		Vec2f size;

	public:
		ANSEL_API void draw() override;

		void  setSize(Vec2f s) { size = s;    }
		Vec2f getSize()  const { return size; }
	};
}