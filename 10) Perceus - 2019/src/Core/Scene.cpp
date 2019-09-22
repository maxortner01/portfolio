#include "Perceus/Core/Scene.h"

#include "Perceus/Core/Graphics/Rendering/Events/EventHandler.h"

#include "Perceus/Core/Application.h"

#include <iostream>

#include "Perceus/Util/Memory/RegTable.h"

namespace pcs
{
    using namespace Util::Mem;

    void Scene::_render()
    {
        setStatus(SceneState::Running);
        render();
    }

    bool Scene::pollEvent(Event*& event)
    {
        Event* e = EventHandler::get().getEvent();

        if (e == nullptr) return false;
        
        event = e;
        return true;
    }

    Scene::Scene(Application* app, float FOV, const unsigned int size) : 
        Data::Status<SceneState>(SceneState::None),
        current_application(app)
    {
        PS_CORE_DEBUG("Constructing Scene");

        getValues() = {
            "Running",
            "Error",
            "Finished",
            "None"
        };

        camera = new Camera( &app->getCurrentWindow(), FOV );
        models.reserve(size);

        std::cout << "disabling cursor\n";
        rendAPI()->disableCursor(Window::get(0));
    }

    Scene::~Scene()
    {
        for (int i = 0; i < models.size(); i++)
            if (models[i]) delete models[i];

        delete camera;
    }

    Application& Scene::getApplication() const
    {
        return *current_application;
    }
}