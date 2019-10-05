#pragma once

#include "../../Data/Vector.h"

#include "Event.h"

namespace age
{
	class MouseEvent : public _Event
	{
		friend class Event;

		Vec2f last_position;
		Vec2f pos;

	protected:
		void setCallbacks() override;
		void updateMouseState();

	public:
		ANSEL_API MouseEvent(void* window);

		ANSEL_API Vec2f getDelta();

		Vec2f getPosition() { return pos; }
		ANSEL_API void setPosition(Vec2f position);
	};
}