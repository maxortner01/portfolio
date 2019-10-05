#pragma once

#include "Scene.h"

namespace age
{
	class Scene2D : public Scene, public Target
	{
	protected:
		virtual void create() {}
		virtual void destroy() {}
	};
}