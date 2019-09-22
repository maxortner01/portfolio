#include "Perceus/Core/Graphics/Entities/VertexArray.h"

namespace pcs
{

#define getType(type, name)\
        std::vector<type> v;\
        v.reserve(vertices.size());\
        for (int i = 0; i < vertices.size(); i++)\
            v.push_back(vertices[i].name);\
        return v;

    std::vector<Color> VertexArray::getColors() const
    {
        getType(Color, color);
    }

    std::vector<Vec3f> VertexArray::getNormals()  const
    {
        getType(Vec3f, normal);
    }

    std::vector<Vec3f> VertexArray::getVertices() const
    {
        getType(Vec3f, vertex);
    } 

    std::vector<Vec2f> VertexArray::getTexCoords() const
    {
        getType(Vec2f, tex);
    }

    std::vector<Vec3f> VertexArray::getTangents() const
    {
        getType(Vec3f, tangent);
    }
}