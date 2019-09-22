#include "Perceus/Core/Graphics/Window.h"

namespace pcs
{
    Vec2d Mouse::position = { 0, 0 };

    Mouse::Mouse(const double posx, const double posy)
    {
        position.x = posx;
        position.y = posy;
    }

    Vec2d Mouse::getPosition()
    {
        return position;
    }

    void Mouse::setPosition(const Vec2d& pos)
    {
        rend::RenderObject::rendAPI()->setMousePos(Window::get(0), pos);
    }
}