#pragma once

#include "Color.h"
#include "Vector.h"

namespace pcs
{
    struct Vertex
    {
        friend class ParserOBJ;

        Vec3f vertex, normal, tangent;
        Vec2f tex;
        Color color = Color(1.f, 1.f, 1.f);

    private:
        unsigned int _tan_count;
    };
}