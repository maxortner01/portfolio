#pragma once

#include "../DLL/dll.h"

#include <vector>

#include "Scene.h"
#include "Window.h"
#include "Singleton.h"

namespace age
{
	class Engine : public Singleton<Engine>
	{
		ANSEL_API static std::vector<Window*> windows;

		Scene*  current_scene;
		Window* window;

	public:
		ANSEL_API Engine(Window* _window, Scene* scene);

		ANSEL_API void run();

		ANSEL_API static Window &getWindow(unsigned int index);
	};
}