#include "Perceus/Core/Graphics/Entities/RawModel.h"

#include "Perceus/Data/Matrix.h"

namespace pcs
{
    std::vector<RawModel*> RawModel::rawModels;

    void RawModel::flushRawModels()
    {
        int size = rawModels.size();
        for (int i = 0; i < size; i++)
            delete rawModels[i];

		rawModels.clear();
    }

    RawModel::RawModel(const VertexArray& vertex)
    {
        loadVertices(vertex.getVertices());
        loadNormals(vertex.getNormals());
        loadTexCoords(vertex.getTexCoords());
        loadColors(vertex.getColors());
        loadTangents(vertex.getTangents());

        if (vertex.getIndices().size() == 0)
            generateIndices(vertex.getVertices());

        else if (vertex.getIndices().size() < vertex.getVertices().size())
            generateIndices(vertex.getVertices(), vertex.getIndices().size());

        else
            loadIndices(vertex.getIndices());
    }
    
    bool RawModel::generateIndices(const std::vector<Vec3f>& vertices, const int start_index)
    {
        PS_CORE_DEBUG("Generating indices");
        std::vector<unsigned int> indices(vertices.size());

        for (int i = start_index; i < vertices.size(); i++)
            indices[i] = i;


        loadIndices(indices);
        return true;
    }

    RawModel* RawModel::Create(const VertexArray& vertex)
    {
        rawModels.push_back(new RawModel(vertex));
		RawModel* r = rawModels[rawModels.size() - 1];

		r->getID() = rawModels.size() - 1;
		
		return r;
    }

    RawModel::~RawModel()
    {
        PS_CORE_DEBUG("Destroying RawModel");
        
        for (int i = 0; i < (int)TextureTypes::Count; i++)
        {
            Texture* tex = textures.textures[i];
            if (tex)
                textures.textures[i]->destroy();
        }
    }

    bool RawModel::loadColors(const std::vector<Color>& colors)
    {
        PS_CORE_DEBUG("Binding {0} color(s)", colors.size());
        bindBuffer(rend::BufferIndex::Color, 4, colors);
        return true;
    }

    bool RawModel::loadNormals(const std::vector<Vec3f>& normals)
    {
        PS_CORE_DEBUG("Binding {0} normal(s)", normals.size());
        bindBuffer(rend::BufferIndex::Normal, 3, normals);
        return true;
    }

    bool RawModel::loadVertices(const std::vector<Vec3f>& vertices)
    {
        PS_CORE_DEBUG("Binding {0} vertice(s)", vertices.size());
        bindBuffer(rend::BufferIndex::Vertices, 3, vertices);
        return true;
    }
    
    bool RawModel::loadTexCoords(const std::vector<Vec2f>& texCoords)
    {
        PS_CORE_DEBUG("Binding {0} texture coordinate(s)", texCoords.size());
        bindBuffer(rend::BufferIndex::TexCoords, 2, texCoords);
        return true;
    }

    bool RawModel::loadModelMatrices(const std::vector<Mat4f>& matrices)
    {
        PS_CORE_DEBUG("Binding {0} model matrice(s)", matrices.size());
        bindBuffer(matrices);
        return true;
    }

    bool RawModel::loadTangents(const std::vector<Vec3f>& tangents)
    {
        PS_CORE_DEBUG("Binding {0} tangent(s)", tangents.size());
        bindBuffer(rend::BufferIndex::Tangents, 3, tangents);
        return true;
    }

    bool RawModel::loadIndices(const std::vector<unsigned int>& indices)
    {
        PS_CORE_DEBUG("Binding {0} indices", indices.size());
        bindBuffer(rend::BufferIndex::Indices, 1, indices);
        return true;
    }
}
