#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include <iostream>
#include <GL/glew.h>

#include <glm.hpp>

#include "engine/controllers/camera.h"
#include "engine/controllers/shader.h"

#include "component.h"

using namespace Controllers;
using namespace Components;

namespace Components {
    
    /**
     * @brief Handles vertex data and rendering
     * Once instanciated with vertex data, it loads the GPU buffer and
     * renders that buffer to the screen every frame (when render is called).
     */
    class Model : public Component
    {
    private:
        enum Buffers {VERTICES, INDICES};

        ///Array which holds the buffer IDs
        GLuint buffers[2];

        ///Vector that holds all vertex data for this model
        std::vector<float> vertexData;
        ///Whether or not to outline objects
        bool outlines;
        ///Draw method, default GL_STATIC_DRAW
        int draw_method;

    public:
        /**
         * @brief Construct a new Model object
         * 
         * @param vertices Vector of float data that is passed to GPU.
         * @param colors Vector of float data that is passed as colors to the GPU.
         */
        Model(std::vector<float> vertices, std::vector<float> colors);
        /**
         * @brief Construct a new Model object
         * 
         * @param vertices Vector of float data that is passed to GPU.
         * @param colors Vector of float data that is passed as colors to the GPU.
         * @param draw_method OpenGL draw method (GL_STATIC_DRAW, GL_DYNAMIC_DRAW)
         */
        Model(std::vector<float> vertices, std::vector<float> colors, int draw);

        /**
         * @brief Renders vertices to the screen
         * 
         * @param shader Shader pointer that is to be used during rendering.
         * @param model Matrix object that represents the current model.
         * @param camera Camera pointer for matrix concatenation.
         */
        void render(Shader* shader, glm::mat4 model, Camera* camera);
        /**
         * @brief Used only when vertex data is to be changed
         * 
         * @param vertices Vector of float data that is passed to GPU.
         * @param colors Vector of float data that is passed as colors to the GPU.
         */
        void newVertices(std::vector<float> vertices, std::vector<float> colors);

        ///Toggles rendering outlines
        void toggleOutlines();

        ///Component abstract function
        void update();

        /**
         * @brief Destroy the Model object, clears buffers.
         * 
         */
        ~Model();
    };

}

#endif /* MODEL_H_ */