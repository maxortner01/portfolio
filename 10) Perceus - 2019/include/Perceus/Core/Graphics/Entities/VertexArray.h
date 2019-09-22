#pragma once

#include "Perceus/Data/Inc.h"
#include "Perceus/Data/Vertex.h"

namespace pcs
{
    class PERC_API VertexArray
    {
        std::vector<unsigned int> indices;
        std::vector<Vertex> vertices;

    public:
        Vertex&       getVertex (const int index)         { return vertices[index]; }
        void          pushVertex(Vertex vertex  )         { vertices.push_back(vertex); }

        unsigned int& getIndex (const unsigned int index) { return indices[index]; }
        void          pushIndex(const unsigned int index) { indices.push_back(index); }
 
        std::vector<Color> getColors()     const;
        std::vector<Vec3f> getNormals()    const;
        std::vector<Vec3f> getVertices()   const; 
        std::vector<Vec2f> getTexCoords()  const;
        std::vector<Vec3f> getTangents()   const;

        std::vector<unsigned int>& getIndices()             { return indices; }
        const std::vector<unsigned int>& getIndices() const { return indices; }

        std::vector<Vertex> &getVertexArray()             { return vertices; }
        const std::vector<Vertex>& getVertexArray() const { return vertices; }
    };

}