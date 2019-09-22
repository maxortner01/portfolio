#pragma once

#include "../Graphics/Graphics2D/Surface.h"
#include "../Graphics/Renderable.h"

#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace age
{
	class Scene : public Size
	{
		friend class Engine;

	protected:
		virtual void render(age::Event &event)  = 0;
		virtual void create()  = 0;
		virtual void destroy() = 0;
	};
}