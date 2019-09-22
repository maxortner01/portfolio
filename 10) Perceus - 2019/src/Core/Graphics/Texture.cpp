#include "Perceus/Core/Graphics/Texture.h"
#include "Perceus/Util/Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace pcs
{
    Texture::Texture()
    {
        rendAPI()->makeTexture(this);
    }
    
    Texture::Texture(const char* location) :
        Texture()
    {
        loadFromFile(location);
    }

    Texture::~Texture()
    {
        destroy();
    }

    void Texture::destroy()
    {
        rendAPI()->destroyTexture(this);
    }

    void Texture::bind(unsigned int layer)
    {
        current_layer = layer;
        rendAPI()->bindTexture(id, layer);
    }

    void Texture::unbind() const
    {
        rendAPI()->bindTexture(0, current_layer);
    }
    
    void Texture::loadFromFile(const char* location)
    {
        PS_CORE_DEBUG("Loading file '{0}'", location);

        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* image = stbi_load(location, &width, &height, &channels, STBI_rgb_alpha);

        if (rendAPI()->loadImageToTexture(this, image, width, height))
            PS_CORE_INFO("Texture [ {0} ] loaded successfully", location);
        else
            PS_CORE_WARN("Loading texture [ {0} ] failed!", location);

        stbi_image_free(image);
    }
}