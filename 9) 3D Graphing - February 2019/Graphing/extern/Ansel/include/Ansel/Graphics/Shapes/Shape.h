#pragma once

#include "../../Data/Transformation.h"
#include "../../Data/Color.h"
#include "../Renderable.h"

namespace age
{
	class Shape : public Transformation2D, public Renderable
	{
		Color color;

	public:

		void setColor(Color c)  { color = c;    }
		Color getColor()  const { return color; }
	};
}