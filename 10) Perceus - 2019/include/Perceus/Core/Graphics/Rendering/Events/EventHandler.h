#pragma once

#include "Perceus/Util/Log.h"
#include "Perceus/Data/Singleton.h"
#include "Event.h"
#include <stack>
#include <iostream>

namespace pcs
{
    class PERC_API EventHandler : public Data::Singleton<EventHandler>
    {
        friend class Engine;

        std::stack<Event*> events;

        void clearEvents();

    public:
        EventHandler();

        Event* getEvent();

        template<typename T, typename... Args>
        void pushEvent(Args... args)
        {
            Event* t = new T(args...);

            PS_CORE_DEBUG("{0} event caught: {1}", t->getCategory(), t->getName());
            events.push(t);
        }
    };
}