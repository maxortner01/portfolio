#pragma once

#include "Perceus/Data/Inc.h"

#include "Graphics/Entities/Camera.h"
#include "Perceus/Data/Status.h"
#include "Graphics/Rendering/RenderObject.h"
#include "Graphics/Entities/Model.h"
#include "Graphics/Rendering/Shaders/ShaderProgram.h"

namespace pcs
{
    class Application;

    // State flags for scenes
    enum class SceneState {
        Running,
        Error,
        Finished,
        None
    };

    /**
     * @brief Class that represents a context of rendering.
     */
    class PERC_API Scene :
        public Data::Status<SceneState>,
        public rend::RenderObject
    {   
        friend class Engine;

        Camera*       camera;
        Application*  current_application;
        std::vector<Model*> models;

        // Render and handle states
        void _render();

    protected:
        ShaderProgram program;
        
		bool pollEvent(Event*& event);

        template<typename T = pcs::Model, typename... Args>
        Model* makeModel(Args... args)
        {
            models.push_back(new T(args...));
            return models.at(models.size() - 1);
        }

        virtual void render() = 0;

    public:
        /**
         * @brief Constructs a new Scene object
         * 
         * @param FOV Field of View in which to make the camera
         * @param size The default pre-allocation size for storing models
         */
        Scene(Application* app, float FOV = 90.f, const unsigned int size = 256);
        virtual ~Scene();

        Camera& getCamera() const { return *camera; }

        Application& getApplication() const;
    };
}