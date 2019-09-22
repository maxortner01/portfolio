#include "Perceus/Core/Graphics/Rendering/Events/EventHandler.h"

namespace pcs
{
    void EventHandler::clearEvents()
    {
        events.empty();
    }

    EventHandler::EventHandler()
    {
        
    }   

    Event* EventHandler::getEvent()
    {
        if (events.size() == 0)
            return nullptr;

        Event* top = events.top();
        events.pop();
        return top;
    }
}