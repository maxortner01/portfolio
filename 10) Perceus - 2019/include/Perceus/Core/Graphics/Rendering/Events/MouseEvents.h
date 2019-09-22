#include "Event.h"

#include "Perceus/Data/Vector.h"

namespace pcs
{
    class Mouse : public Event
    {
        static Vec2d position;

    public:
        PERC_API Mouse(const double posx, const double posy);

        EVENT_TYPE(MousePosition);
        EVENT_CATEGORY(MouseEvent);

        static PERC_API Vec2d getPosition();
        static PERC_API void  setPosition(const Vec2d& pos);
    };
}