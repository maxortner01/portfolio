#pragma once

#include "Renderer.h"

namespace pcs
{
    class PERC_API ForwardRenderer : public Renderer, public Data::Singleton<ForwardRenderer>
    {
    public:
        using Renderer::render;
        int render(RawModel* rawModel, ShaderProgram* shader, Camera* camera, unsigned int count = 1) const;
    };
}