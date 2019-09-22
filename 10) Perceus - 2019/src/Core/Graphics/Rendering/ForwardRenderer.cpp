#include "Perceus/Core/Graphics/Rendering/ForwardRenderer.h"

#include <string>
#include <iostream>

namespace pcs
{
    int ForwardRenderer::render(RawModel* rawModel, ShaderProgram* shader, Camera* camera, unsigned int count) const
    {
        //static Texture* texture;
        
        //if (!texture)
        //{
        //    texture = new Texture("Client/res/Sword1/color.png");
        //}

        rend::Buffer* vertexBuff = &rawModel->getBuffer(rend::BufferIndex::Indices);

        vertexBuff->bind();
        //PS_CORE_DEBUG(" -- {0} --", rawModel->getBuffer(rend::BufferIndex::Vertices).getCount());

        const char* textures[] = {
            "texAlbedo", "texNormal"
        };

        shader->use();
        
        for (int i = 0; i < (int)TextureTypes::Count; i++)
        {
            Texture* tex = rawModel->getTextures().textures[i];

            std::string s_name(textures[i]);
            std::string s_exists(textures[i]);
            s_name += ".texture";
            s_exists += ".exists";

            const char* name = s_name.c_str();
            const char* exists = s_exists.c_str();

            if (tex != nullptr)
            {
                tex->bind(i);
                shader->setUniform(name, i);
                shader->setUniform(exists, 1);
            }
            else
            {
                shader->setUniform(exists, 0);
            }
        }

        shader->setUniform("camera_position", camera->getLocation());
        shader->setUniform("projection", camera->getProjection());
        shader->setUniform("view",       camera->getView()); 

        rendAPI()->renderInstanced(vertexBuff->getCount(), count);

        shader->close();

        vertexBuff->unbind();

        return (int)RenderFlag::Good;
    }
}