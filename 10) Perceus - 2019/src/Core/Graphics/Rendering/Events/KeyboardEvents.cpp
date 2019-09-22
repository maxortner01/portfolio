#include "Perceus/Core/Graphics/Rendering/Events/KeyboardEvents.h"

#include "Perceus/Core/Graphics/Rendering/RenderObject.h"
#include "Perceus/Core/Graphics/Window.h"

#include "Perceus/Data/Inc.h"

#include <cctype>

namespace pcs
{
    const unsigned int KeyEvent::_keycount = 128;
    bool* KeyEvent::key_states = new bool[KeyPressEvent::_keycount];

    KeyEvent::KeyEvent(const char c, KeyState state) :
        ch(c)
    {
        switch (state)
        {
            case KeyState::Released:
                key_states[c] = 0;
                break;

            default:
                key_states[c] = 1;
                break;
        }
    }

    bool KeyEvent::isKeyDown(const char c)
    {
        return key_states[toupper(c)];
    }
}