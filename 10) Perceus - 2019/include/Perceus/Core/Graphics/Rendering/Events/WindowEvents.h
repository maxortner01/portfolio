#pragma once

#include "Event.h"

namespace pcs
{
    class PERC_API WindowClosedEvent : public Event
    {
    public:
        EVENT_CATEGORY(WindowEvent);
        EVENT_TYPE(WindowClosed);
    };

    class PERC_API WindowResizeEvent : public Event
    {
    public:
        EVENT_CATEGORY(WindowEvent);
        EVENT_TYPE(WindowResize);
    };
}