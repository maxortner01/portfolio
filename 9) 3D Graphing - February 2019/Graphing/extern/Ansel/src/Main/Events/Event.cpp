#include "../../../include/Ansel/Main/Events/Event.h"

#include "../../../include/Ansel/Main/Events/KeyEvent.h"
#include "../../../include/Ansel/Main/Events/MouseEvent.h"

namespace age
{
	_Event::_Event(void* window) :
		window_ptr(window)
	{
		setCallbacks();
	}

	Event::Event(void* window) :
		_Event(window),
		keyEvent(new KeyEvent(window)),
		mouseEvent(new MouseEvent(window))
	{
		
	}

	void Event::update()
	{
		keyEvent->updateKeyStates();
		mouseEvent->updateMouseState();
	}
}