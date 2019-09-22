#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>

class Animate
{
    float *tValue, tEnd, tStart;
    float fDuration, fDelay;

    sf::Clock start_time;

public:
    enum TYPE {
        EXPONENTIAL,
        LINEAR,
        SIN
    };

    Animate(float *v, float end, float duration, float delay = 0.f) {
        tValue = v; tEnd = end; tStart = *v;
        fDuration = duration;
        fDelay    = delay;

        start_time.restart();
    }

    int update() {
        float time_passed = start_time.getElapsedTime().asSeconds() - fDelay;

        if (time_passed < 0)
            return 0;

        float progress = time_passed / fDuration;
        float difference = tEnd - tStart;

        if (progress >= 1) {
            *tValue = tEnd;

            return 1;
        }
    
    
        *tValue = tStart + (difference * (sinf((3.14159f / 2.f) * progress)));

        return 0;
    }

};