#include "Perceus/Core/Engine.h"

#include "Perceus/Util/Log.h"

#include "Perceus/Core/Graphics/Rendering/Renderer.h"
#include "Perceus/Core/Graphics/Rendering/OpenAPI.h"
#include "Perceus/Core/Graphics/Rendering/Events/EventHandler.h"

#include "Perceus/Core/Graphics/Rendering/ForwardRenderer.h"
#include "Perceus/Util/Profiler.h"

#if !defined(WIN32) || !defined(_WIN32)
	#include <unistd.h>
#endif

#include <string>

namespace pcs
{
    std::string commaFormat(float val)
    {
        int v = (int)val;
        std::string sVal = std::to_string(v);
        std::string fin;

        int decimal_index = sVal.size();

        for (int i = 0; i < sVal.size(); i++)
            if (sVal[i] == '.')
            {
                decimal_index = i;
                break;
            }

        int count = 0;
        for (int i = decimal_index - 1; i >= 0; i--)
        {
            fin.push_back(sVal.at(i));

            if (count == 2 && i != 0)
            {
                fin.push_back(',');
                count = -1;
            }

            count++;
        }

        std::reverse(fin.begin(), fin.end());
        fin += std::string(sVal.begin() + decimal_index, sVal.end());

        return fin;
    }

    Renderer* Engine::renderer() const
    {
        switch (currentRenderer()) 
        {
            case CurrentRenderer::ForwardRenderer:
                return &ForwardRenderer::get();
        }

        return nullptr;
    }

    Engine::Engine() :
        fpsLimit(60.0)
    {
        PS_CORE_DEBUG("Constructing Engine");
        getValues() = {
            "Good",
            "Failed"
        };

        PS_CORE_INFO("Engine initialized");

        Window::rendAPI()->initialize();

        // Make variable size
        window = Window::Create(400, 400);
    }
    
    Engine::~Engine()
    {
        RawModel::flushRawModels();

        delete window;
        
        Window::rendAPI()->terminate();

        PS_CORE_WARN("Engine shutdown");
    }

    RenderStatus Engine::renderScene(Scene* scene) const
    {
        static int frame;

        const double needed_frame_time = 1.0 / fpsLimit;
        const double start_time = rendAPI()->getTime();

        // Clear the render api draw count
        rendAPI()->getVertexCount() = 0;
        rendAPI()->getObjectCount() = 0;

        // render the scene
        EventHandler::get().clearEvents();
        window->pollEvents();
        window->clear(Color(0.f, 0.f, 0.f));
        scene->_render();
        
        renderer()->render(scene->models, &scene->program, &scene->getCamera());

        window->render();

        // Accomodate for the frame rate limit
        const double render_time = start_time - rendAPI()->getTime();
        const double needed_wait = needed_frame_time - render_time;

        if (needed_wait > 0.0)
        {
            timespec time;
            time.tv_sec  = 0;
            time.tv_nsec = (unsigned long long int)(pow(10, 9) * needed_wait);

#if !defined(WIN32) || !defined(_WIN32)
            nanosleep(&time, NULL);        
#endif
        }

        // Frame calculations
        {
            const  int seconds = 2;
            static int drawCalls = 0;
            static int polysRendered = 0;
            static int objectsRendered = 0;
            static double totalElapsed = 0;
            static double processElapsed = 0;
            static int threadsUsed = 0;

            double elapsed = rendAPI()->getTime() - start_time;

            processElapsed += Renderer::getProcessTime();            
            totalElapsed += elapsed;
            polysRendered += rendAPI()->getPolygonCount();
            objectsRendered  += rendAPI()->getObjectCount();
            threadsUsed += Renderer::getThreadCount();

            if (totalElapsed >= seconds)
            {
                float fps = (float)frame / totalElapsed;

                commaFormat(fps);

                PS_CORE_INFO("{0} frames passed in {2} second(s) with an average fps of {1}", frame, fps, seconds, 1.f / fps);
                PS_CORE_INFO("RAPI: {0}  |  Avg. draw per frame: {2} |  Avg. Polys: {3}  |  Avg. Objs: {4}  |  Avg. Process Time: {5} ms  |  Avg. Threads: {6}", 
                    settings.getAPIName(settings.api), rendAPI()->getRenderCalls() - drawCalls, (float)(rendAPI()->getRenderCalls() - drawCalls) / (float)frame,
                    commaFormat((float)polysRendered / (float)frame), commaFormat((float)objectsRendered / (float)frame), (float)processElapsed / (float)frame,
                    (float)threadsUsed / (float)frame);
                PS_CORE_INFO("{0}\% CPU Usage  |  Memory Usage: {1} mb", Profiler::get().getCPUPercent(), (float)(Profiler::get().getMemoryUsage()) / 10000.f);

                frame = 0;
                totalElapsed = 0;
                processElapsed = 0;
                polysRendered = 0;
                objectsRendered = 0;
                threadsUsed = 0;
                drawCalls = rendAPI()->getRenderCalls();
            }
        }

        frame++;

        return RenderStatus::Good;
    }
}