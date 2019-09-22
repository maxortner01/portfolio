#pragma once

#include "Perceus/Data/Color.h"
#include "Perceus/Data/Vector.h"
#include "../Entities/BufferArray.h"

#include "../Texture.h"
#include "../Entities/VertexArray.h"

#include "Perceus/Data/Inc.h"

namespace pcs
{
    class RawModel : public rend::BufferArray
    {
        friend class Engine;

        TextureArray textures;
        static std::vector<RawModel*> rawModels;

        static void flushRawModels();

        RawModel(const VertexArray& vertex);

        bool generateIndices(const std::vector<Vec3f>& vertices, const int start_index = 0);

    public:
        static RawModel PERC_API * Create(const VertexArray& vertex);

        PERC_API ~RawModel();

        TextureArray& getTextures() { return textures; }

        bool PERC_API loadColors(const std::vector<Color>& colors);
        bool PERC_API loadNormals(const std::vector<Vec3f>& normals);
        bool PERC_API loadVertices(const std::vector<Vec3f>& vertices);
        bool PERC_API loadTexCoords(const std::vector<Vec2f>& texCoords);
        bool PERC_API loadModelMatrices(const std::vector<Mat4f>& matrices);
        bool PERC_API loadTangents(const std::vector<Vec3f>& tangents);

        bool PERC_API loadIndices(const std::vector<unsigned int> &indices);
    };
}
