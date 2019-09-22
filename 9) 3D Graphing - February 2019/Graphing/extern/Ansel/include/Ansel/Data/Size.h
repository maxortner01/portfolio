#pragma once

#include "../DLL/dll.h"
#include "Vector.h"

namespace age
{
	class Size
	{
		friend class Engine;

	protected:
		Vec2u dimensions;

	public:
		virtual Vec2u getDimensions() const { return dimensions; }
	};
}