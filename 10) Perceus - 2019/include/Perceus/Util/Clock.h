#pragma once

#include "Perceus/Core/Graphics/Rendering/RenderObject.h"

namespace pcs
{
    class Clock : public pcs::rend::RenderObject
    {
        double _starttime;

        struct _time
        {
            double seconds;
            double milliseconds;
        };

    public:
        Clock()
        {
            restart();
        }

        void restart()
        {
            _starttime = rendAPI()->getTime();
        }

        _time elapsed()
        {
            double e = rendAPI()->getTime() - _starttime;
            return { e, e / 1000.0 };
        }
    };
}