#include "Perceus/Core/Graphics/Rendering/RenderObject.h"

#include "Perceus/Core/Graphics/Rendering/OpenAPI.h"

#include "Perceus/Core/Graphics/Rendering/ForwardRenderer.h"

namespace pcs
{
namespace rend
{
    RenderSettings   RenderObject::settings;

    RenderAPI* RenderObject::rendAPI()
    {
        switch (settings.api)
        {
            case OpenGL:
                return &OpenAPI::get();
        }

        return nullptr;
    }
}
}