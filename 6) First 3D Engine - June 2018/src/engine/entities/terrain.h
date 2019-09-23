#ifndef TERRAIN_H_
#define TERRAIN_H_

/* DIMENSION DEFINITIONS*/

#define WIDTH  50
#define HEIGHT 50

#define SECTOR_WIDTH 100
#define SECTOR_DEPTH 100

//-------------------->

#include <vector>
#include <thread>

#include "engine/util/SimplexNoise.h"
#include "engine/util/vert.h"

#include "engine/components/model.h"

#include "engine/controllers/camera.h"
#include "engine/controllers/shader.h"

#include "engine/entities/entity.h"

using namespace Entities;

namespace Entities {
    
    /**
     * Using predefined dimensions (SECTOR_WIDTH and SECTOR_HEIGHT), Terrain class handles
     * generation of Sector structs which each hold a model that renders that specific sector
     * to the screen.
     */
    class Terrain
    {
        /**
         * @brief Represents a small chunk of terrain data
         * Holds a small chunk of map data and handles rendering.
         */
        struct Sector
        {
            ///Model object used for rendering
            Model*  model;
            ///Model pointer object for rendering trees
            Model*  trees;
            ///Model pointer object for rendering water
            Model*  water;

            ///Shader used to draw terrain
            Shader* shader;
            ///Shader used to draw trees
            Shader* treeshader;
            ///Shader used to draw water
            Shader* watershader;

            ///Camera object used for matrix concatenation
            Camera* camera;
            
            ///Location of sector
            vec2 location;

            /**
             * @brief Construct a new Sector object at SECTOR location (x, y)
             * 
             * @param x First dimension of location in the terrain.
             * @param y Second dimension of location in the terrain.
             * @param s Shader pointer object used to draw terrain.
             * @param c Camera pointer object for projection/view matrices.
             */
            Sector(float x, float y, Shader* s, Shader* t, Shader* w, Camera* c);

            ///Renders current model to the screen
            void render() const;
            /**
             * @brief Generates vertices according to the coordinates.
             * 
             * @param x First dimension of location in the terrain.
             * @param y Second dimension of location in the terrain.
             */
            void generate(float x, float z);

            /**
             * @brief Destroy the Sector object
             */
            ~Sector();
        };        

        ///Shader used to pass onto the sectors
        Shader* shader      = new Shader("terrain");
        Shader* treeshader  = new Shader("tree");
        Shader* watershader = new Shader("water");

        ///Main camera pointer object
        Camera* currentCamera;

        ///Vector of current sectors
        std::vector<Sector*> sectors;

        /**
         * @brief Get the relative tile location of coordinates
         * 
         * @param x First dimensional location of the tile.
         * @param y Second dimensional location of the tile.
         * @return vec2 Relative location of (x, y).
         */
        inline vec2 getTileLocation(float x, float y)   const { return vec2( std::floor(x), std::floor(y) ); }
        inline vec2 getSectorLocation(float x, float y) const { 
            return vec2( std::floor(x / SECTOR_WIDTH), std::floor(y / SECTOR_DEPTH) ); }

    public:
        /**
         * @brief Construct a new Terrain object
         * 
         * @param camera Current camera pointer object.
         */
        Terrain(Camera* camera);

        ///Iterates through sectors and renders them
        void render();

        /**
         * @brief Run position through layered simplex noise algorithm
         * 
         * @param x First dimension of location in the terrain.
         * @param y Second dimension of location in the terrain.
         * @return float Layered simplex noise value at (x, y)
         */
        static float getval(float x, float y);
    };
}

#endif /* TERRAIN_H_ */