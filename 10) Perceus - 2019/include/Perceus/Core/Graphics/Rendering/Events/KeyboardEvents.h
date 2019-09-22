#pragma once

#include "Perceus/Data/Inc.h"
#include "Event.h"

namespace pcs
{
    enum class KeyState
    {
        Pressed,
        Released,
        Down,
        None
    };

    class KeyEvent : public Event
    {
        static const unsigned int _keycount;
        static bool* key_states;

        char ch;

    public:
        PERC_API KeyEvent(const char c, KeyState state);

        EVENT_CATEGORY(KeyboardEvent);

        char getKey() const { return ch; }

        static PERC_API bool isKeyDown(const char c);
    };

    class PERC_API KeyPressEvent : public KeyEvent
    {
    public:
        KeyPressEvent(const char c) : KeyEvent(c, KeyState::Pressed) { }
        
        EVENT_TYPE(KeyPress);
    };

    class PERC_API KeyReleaseEvent : public KeyEvent
    {
    public:
        KeyReleaseEvent(const char c) : KeyEvent(c, KeyState::Released) { }
        
        EVENT_TYPE(KeyRelease);
    };

    class PERC_API KeyDownEvent : public KeyEvent
    {
    public:
        KeyDownEvent(const char c) : KeyEvent(c, KeyState::Down) { }
        
        EVENT_TYPE(KeyDown);
    };
}