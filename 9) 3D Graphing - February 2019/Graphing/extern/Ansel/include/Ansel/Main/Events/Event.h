#pragma once

#include "../../DLL/dll.h"


namespace age
{
	class KeyEvent;
	class MouseEvent;

	class _Event
	{
	protected:
		void* window_ptr;
		virtual void setCallbacks() {}

	public:
		ANSEL_API _Event(void* window);
	};

	class Event : public _Event
	{
		KeyEvent* keyEvent;
		MouseEvent* mouseEvent;

	public:
		ANSEL_API Event(void* window);

		ANSEL_API void update();

		KeyEvent   &getKeyEvent() { return *keyEvent; }
		MouseEvent &getMouse()    { return *mouseEvent; }
	};
}