#include "Perceus/Core/Graphics/Window.h"

#include "Perceus/Core/Graphics/Entities/Camera.h"
#include "Perceus/Core/Engine.h"
#include "Perceus/Util/Log.h"
#include "Perceus/Util/Memory/RegTable.h"


namespace pcs
{
    List<Window*> Window::windows;

    // Window constructor

    Window::Window(const unsigned int width, const unsigned int height) :
        RenderSurface(width, height), ObjectUID()
    {
        PS_CORE_DEBUG("Constructing Window");

        getValues() = {
			"Ok",
			"API failed to initialize",
			"Window failed to create",
            "None"
        };

        setSize({ width, height });
        
        int windowStatus = rendAPI()->makeWindow(this);
        setStatus((WindowStatus)windowStatus);
    }

	// Window destructor	

    Window::~Window()
    {
        rendAPI()->destroyWindow(this);
        PS_CORE_WARN("Window ({0}) destroyed", getID());

        //camera_directory.empty();
        //unsigned int size = camera_directory.size();
        //for (int i = 0; i < size; i++)
        //{
        //    if (camera_directory.top())
        //        std::free(camera_directory.top());
        //        
        //    camera_directory.pop();
        //}

        camera_directory.clear();
    }

	// Static window creation method

    Window* Window::Create(const unsigned int width, const unsigned int height)
    {
        using namespace Util::Mem;

        Window* win = new Window(width, height);
        windows.push(win);
        //RegTable::get().registerObject<Window>(win->getID(), win);

        if (win->getStatus() > WindowStatus::Ok)
            PS_CORE_ERROR("Window ({0}) failed to initialize with status {1}: {2}", 
                win->getID(), (int)win->getStatus(), win->getStatusValue());
        else
            PS_CORE_INFO("Initialized window ({0}). Status {1}: {2}", 
                win->getID(), (int)win->getStatus(), win->getStatusValue());

        return win;
    }

    Window* Window::get(void* const ptr)
    {
        for (int i = 0; i < windows.size(); i++)
            if (windows[i]->apiPTR == ptr)
                return windows[i];

		return nullptr;
    }
        
    Window* Window::get(const int index)
    {
        return windows[index];
    }

	// Window is open method

    bool Window::isOpen()
    {
        return !rendAPI()->shouldClose(this);
    }

    bool Window::render()
    {
        return rendAPI()->swapBuffers(this);
    }

    void Window::bind() 
    {
        rendAPI()->makeContextCurrent(this);
    }

    void Window::unbind() const 
    {   }

    bool Window::pollEvents()
    {
        return rendAPI()->pollEvents(this);
    }

	// Resize window method

    bool Window::resize(unsigned int width, unsigned int height)
    {
        using namespace Util::Mem;

        setSize({ width, height });
        
        // Need to recompute projection matrices on window resize
        PS_CORE_INFO("Recomputing Projections for {0} camera(s) for window size {1}x{2}", camera_directory.size(), width, height);

        //for (int i = 0; i < camera_directory.size(); i++)
        //    std::cout << camera_directory[i]->getID() << "\n";

        unsigned int size = camera_directory.size();
        for (int i = 0; i < size; i++)
            camera_directory[i]->makeProjection();
                    
        return rendAPI()->resizeWindow(this, width, height);
    }

    void Window::pushCamera(Camera* camera)
    {
        std::cout << "pushing camera " << camera << " to list,";
        std::cout << " so far of size " << camera_directory.size() << "\n";
        camera_directory.push(camera);
        std::cout << "Done!\n";
    }
}
