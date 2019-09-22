#pragma once

#include "Events/Event.h"

#include "../Graphics/Graphics2D/Surface.h"
#include "../DLL/dll.h"
#include "../Data/Size.h"
#include "../Graphics/Context.h"
#include "../Graphics/Renderable.h"

namespace age
{
	class Window : public Target, public Size
	{
		friend class Engine;

		Event* event_handler;
		Context context;

		ANSEL_API void pollEvents();

	public:
		ANSEL_API  Window(ContextSettings settings = ContextSettings());
		ANSEL_API ~Window();

		ANSEL_API bool shouldClose() const;
		ANSEL_API void close() const;
		
		Context   &getContext()  { return context; }
	};
}