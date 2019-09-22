#pragma once

#include "Vector.h"

namespace pcs
{
    template<typename T>
    struct Sizable
    {
        Vec2<T> size;

    public:
        Sizable() { }
        Sizable(Vec2<T> s) :
            size(s)
        {
            
        }

        Vec2<T> getSize() const { return size; }
        bool    setSize(Vec2<T> s) { size = s; return true; }
    };
}