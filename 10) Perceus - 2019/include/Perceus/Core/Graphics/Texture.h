#pragma once

#include "Perceus/Data/Inc.h"
#include "Perceus/Data/ObjectID.h"
#include "Perceus/Core/Graphics/Rendering/RenderObject.h"

namespace pcs
{
    /**
     * @brief Represents a texture
     */
    class Texture : 
        public Data::ObjectID<Texture>, public rend::RenderObject
    {
        unsigned int current_layer;

    public:
        /**
         * @brief Constructs a new Texture object.
         */
        Texture();
        /**
         * @brief Constructs a new Texture object and loads from a file location.
         * 
         * @param location Location of file to load from
         */
        Texture(const char* location);
        /**
         * @brief Destroys the Texture object
         */
        ~Texture();

        /**
         * @brief Destroys the Texture object
         */
        void destroy();

        /**
         * @brief Binds the texture at specified layer.
         * 
         * @param layer Layer on which to bind this texture
         */
        void bind(unsigned int layer = 0);
        /**
         * @brief Unbinds the Texture object
         */
        void unbind() const;

        /**
         * @brief Loads the image from a given file.
         * 
         * @param location Location of the image file
         */
        void loadFromFile(const char* location);
    };

    /**
     * @brief Types of textures that go into a RawModel.
     */
    enum class TextureTypes
    {
        Albedo,
        Normal,
        Count
    };

    /**
     * @brief Array of textures that follows TextureTypes.
     */
    union TextureArray
    {
		TextureArray() {
			for (int i = 0; i < (int)TextureTypes::Count; i++)
				textures[i] = nullptr;
		}

        Texture* textures[(int)TextureTypes::Count];

        struct 
        {
            Texture* albedo;
            Texture* normal;
        };
    };
}