#include "Perceus/Core/Graphics/Rendering/Events/EventHandler.h"
#include "Perceus/Core/Graphics/Rendering/OpenAPI.h"
#include "Perceus/Core/Graphics/Rendering/Events.h"
#include "Perceus/Core/Graphics/Window.h"
#include "Perceus/Core/Graphics/Entities/BufferArray.h"
#include "Perceus/Core/Graphics/Rendering/Shaders/ShaderProgram.h"
#include "Perceus/Core/Graphics/Texture.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace pcs
{
namespace rend
{
    /* CALL BACKS */
    void window_close_callback(GLFWwindow* window)
    {
        EventHandler::get().pushEvent<WindowClosedEvent>();
    }

    void window_resize_callback(GLFWwindow* window, int width, int height)
    {
        Window* win = Window::get((void* const)window);
        if (!win) return;

        win->resize(width, height);
        
        EventHandler::get().pushEvent<WindowResizeEvent>();
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        /**/ if (action == GLFW_PRESS)
            EventHandler::get().pushEvent<KeyPressEvent>(key);
        else if (action == GLFW_RELEASE)
            EventHandler::get().pushEvent<KeyReleaseEvent>(key);
        else if (action == GLFW_REPEAT)
            EventHandler::get().pushEvent<KeyDownEvent>(key);
    }

    void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        EventHandler::get().pushEvent<Mouse>(xpos, ypos);
    }

    /* FUNCTION DEFINITIONS */
    bool OpenAPI::initialize() const
    {
        if (!glfwInit())
            return false;

        return true;
    }

    bool OpenAPI::terminate() const
    {
        glfwTerminate();

        return true;
    }

    double OpenAPI::getTime() const
    {
        return glfwGetTime();
    }

    bool OpenAPI::renderInstanced(unsigned int vertexCount, unsigned int count)
    {
        renderCalls++;

        glDrawElementsInstanced(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr, count);

        PS_CORE_DEBUG("Rendering {0} objects ({1} vertices)", count, vertexCount * count);

        getObjectCount()  += count;
        getVertexCount()  += vertexCount * count;
        getPolygonCount() += (int)((float)vertexCount * (float)count / 3.f);

        return true;
    }

    int OpenAPI::makeWindow(Window* window)
    {
        *window->getAPILoc() = (void*)glfwCreateWindow(window->getSize().x, window->getSize().y, "Test", NULL, NULL);

        if (!window)
        {
            return (int)WindowStatus::CreationFailure;
        }

        glfwWindowHint(GLFW_REFRESH_RATE, 60);

        glfwMakeContextCurrent((GLFWwindow*)*window->getAPILoc());
        current_contex = window->getID();

        if (glewInit() != GLEW_OK)
        {
            PS_CORE_ERROR("Failure to initialize OpenGL");
            return (int)WindowStatus::APIInitFailure;
        }

        PS_CORE_INFO("OpenGL Initialized Successfully");
        PS_CORE_INFO("Running OpenGL version {0}", glGetString(GL_VERSION));
        
        // Setting Callbacks
        glfwSetWindowCloseCallback((GLFWwindow*)*window->getAPILoc(), window_close_callback);
        glfwSetWindowSizeCallback((GLFWwindow*)*window->getAPILoc(), window_resize_callback);
        glfwSetKeyCallback((GLFWwindow*)*window->getAPILoc(), key_callback);
        glfwSetCursorPosCallback((GLFWwindow*)*window->getAPILoc(), mouse_callback);

        glfwSetWindowUserPointer((GLFWwindow*)window->getAPILoc(), &window->getID());


        return (int)WindowStatus::Ok;
    }

    int OpenAPI::destroyWindow(Window* window) const
    {
        glfwDestroyWindow((GLFWwindow*)*window->getAPILoc());

        return true;
    }

    bool OpenAPI::shouldClose(Window* window) const
    {

        return glfwWindowShouldClose((GLFWwindow*)*window->getAPILoc());
    }

    bool OpenAPI::swapBuffers(Window* window) const
    {
        glfwSwapBuffers((GLFWwindow*)*window->getAPILoc());

        return true;
    }

    bool OpenAPI::pollEvents(Window* window) const
    {
        glfwPollEvents();

        return true;
    }

    bool OpenAPI::resizeWindow(Window* window, unsigned int width, unsigned int height) const
    {
        glfwSetWindowSize((GLFWwindow*)*window->getAPILoc(), width, height);
        glViewport(0, 0, width, height); 

        return true;
    }

    bool OpenAPI::clear(Color color) const
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        return true;
    }

    void OpenAPI::makeContextCurrent(Window* window)
    {
        GLFWwindow* w = (GLFWwindow*)*window->getAPILoc();
        glfwMakeContextCurrent(w);
        current_contex = window->getID();
    } 

    u_int64_t OpenAPI::getCurrentContext() const 
    {
        return current_contex;
    }
    
    bool OpenAPI::isKeyDown(Window* window, const char c) const 
    {
        GLFWwindow* w = (GLFWwindow*)*(window->getAPILoc());
        if (glfwGetKey(w, c) == GLFW_PRESS) return true;

        return false;
    }
    
    void OpenAPI::setMousePos(Window* window, const Vec2d position) const
    {
        GLFWwindow* w = (GLFWwindow*)*(window->getAPILoc());
        glfwSetCursorPos(w, position.x, position.y);
    }

    void OpenAPI::disableCursor(Window* window) const
    {
        GLFWwindow* w = (GLFWwindow*)*(window->getAPILoc());
        glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    void OpenAPI::makeBuffer(Buffer* buffer) const
    {
        glGenBuffers(1, &buffer->getID());

        PS_CORE_DEBUG("Vertex Buffer ({0}) created", buffer->getID());
    }

    void OpenAPI::destroyBuffer(Buffer* buffer) const
    {
        glDeleteBuffers(1, &buffer->getID());

        PS_CORE_DEBUG("Vertex Buffer ({0}) destroyed", buffer->getID());
    }

    void rawDataBind(unsigned int bytesize, const void* data)
    {
        glBufferData(GL_ARRAY_BUFFER, bytesize, data, GL_DYNAMIC_DRAW);
    }

    void OpenAPI::bindBufferMatrixData(Buffer* buffer, const std::vector<Mat4f> &matrices) const
    {
        buffer->bind();
        rawDataBind(matrices.size() * 4 * 4 * sizeof(float), &matrices[0]);
        buffer->unbind();

        unsigned int index = buffer->getIndex();
        
        glEnableVertexAttribArray(index + 0);
        glEnableVertexAttribArray(index + 1);
        glEnableVertexAttribArray(index + 2);
        glEnableVertexAttribArray(index + 3);

        buffer->bind();
        glVertexAttribPointer(index + 0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4 * 4, (void*)(0));
        glVertexAttribPointer(index + 1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4 * 4, (void*)(sizeof(float) * 4));
        glVertexAttribPointer(index + 2, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4 * 4, (void*)(sizeof(float) * 8));
        glVertexAttribPointer(index + 3, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4 * 4, (void*)(sizeof(float) * 12)); 

        glVertexAttribDivisor(index + 0, 1);
        glVertexAttribDivisor(index + 1, 1);
        glVertexAttribDivisor(index + 2, 1);
        glVertexAttribDivisor(index + 3, 1);
        PS_CORE_DEBUG("Loaded {0} model matrices to vertex attributes {1}-{2}", matrices.size(), index, index + 3);
        
    }

    void OpenAPI::unbindBuffer(BufferType type) const
    {
        GLenum t = GL_ARRAY_BUFFER;
        
        if (type == BufferType::Index) 
        {
            PS_CORE_DEBUG("Unbinding index buffer"); 
            t = GL_ELEMENT_ARRAY_BUFFER;
        }
        else
        {
            PS_CORE_DEBUG("Unbinding vertex buffer");
        }
        
        glBindBuffer(t, 0);
    }

    void OpenAPI::bindBuffer(Buffer* buffer, BufferType type) const
    {
        GLenum t = GL_ARRAY_BUFFER;
        
        if (type == BufferType::Index) t = GL_ELEMENT_ARRAY_BUFFER;

        PS_CORE_DEBUG("Binding buffer {0}: {1}", buffer->getID(), BufferArray::getBufferName(buffer->getIndex()));

        glBindBuffer(t, buffer->getID());
    }

    void OpenAPI::bindBufferData(unsigned int bytesize, const void* data, unsigned int members, unsigned int index, bool divided, BufferType type) const
    {
        GLenum t = GL_ARRAY_BUFFER;

        if (type == BufferType::Index) 
        {
            t = GL_ELEMENT_ARRAY_BUFFER;
            PS_CORE_DEBUG("Binding {0} indicies to buffer {2}", bytesize / 4, members, index);
        }
        else
        {
            PS_CORE_DEBUG("Binding {0} bytes of data with {1} members to buffer {2}", bytesize, members, index);
        }

        glBufferData(t, bytesize, data, GL_STATIC_DRAW);

        if (type != BufferType::Index)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, members, GL_FLOAT, GL_FALSE, 0, 0);
        }

        if (!divided)
        {
            glVertexAttribDivisor(index, 1);
        }
    }

    void OpenAPI::makeBufferArray(BufferArray* array) const
    {
        glGenVertexArrays(1, &array->getID());

        PS_CORE_INFO("Buffer Array ({0}) created", array->getID());
    }

    void OpenAPI::destroyBufferArray(BufferArray* array) const
    {
        glDeleteVertexArrays(1, &array->getID());

        PS_CORE_WARN("Buffer Array ({0}) destroyed", array->getID());
    }

    void OpenAPI::bindBufferArray(unsigned int ID) const
    {
        glBindVertexArray(ID);
    }

    bool OpenAPI::makeProgram(ShaderProgram* program) const
    {
        program->getID() = glCreateProgram();
        PS_CORE_INFO("Created shader program ({0}) successfully", program->getID());

        return true;
    }
    
    bool OpenAPI::linkProgram(ShaderProgram* program) const
    {
        int result = 0;
        int infoLogLength;

        unsigned int vertexID   = program->getShader(ShaderType::Vertex  ).getID();
        unsigned int fragmentID = program->getShader(ShaderType::Fragment).getID();

        for (int i = 0; i < (int)ShaderType::Count; i++)
        {
            Shader* shader = &program->getShader( (ShaderType)i );
            if (shader->getStatus() != ShaderStatus::CompileSucceeded)
            {
                PS_CORE_ERROR("Shader Status Error! Status {0}: {1}", (int)shader->getStatus(), shader->getStatusValue());
            }
        }

        // Attach shaders and link program
        glAttachShader(program->getID(), vertexID);
        glAttachShader(program->getID(), fragmentID);
        glLinkProgram(program->getID());

        // Check the info log
        glGetProgramiv(program->getID(), GL_LINK_STATUS, &result);
        glGetProgramiv(program->getID(), GL_INFO_LOG_LENGTH, &infoLogLength);
        
        if (infoLogLength > 0)
        {
            std::vector<char> errorMessage(infoLogLength + 1);
            glGetProgramInfoLog(program->getID(), infoLogLength, nullptr, &errorMessage[0]);
            PS_CORE_ERROR("Error linking shader program ({0}): {1}", program->getID(), std::string(&errorMessage[0]));
            return false;
        }

        PS_CORE_INFO("Shader program ({0}) linked successfully", program->getID());

        // Finally detach the shaders from the program
        glDetachShader(program->getID(), vertexID);
        glDetachShader(program->getID(), fragmentID);

        return true;
    }

    void OpenAPI::useProgram(unsigned int id) const
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glUseProgram(id);
        PS_CORE_DEBUG("Using shader program {0}", id);
    }

    bool OpenAPI::destroyProgram(ShaderProgram* program) const
    {
        glDeleteProgram(program->getID());
        PS_CORE_WARN("Shader program ({0}) destroyed", program->getID());
        return true;
    }
    
    bool OpenAPI::setUniform(ShaderProgram* program, const char* uniform_name, const Mat4f &matrix) const
    {
        unsigned int location = glGetUniformLocation(program->getID(), uniform_name);

        if (location != -1)
        {
            glUniformMatrix4fv(location, 1, GL_FALSE, &matrix.m[0][0]);
            return true;
        }

        return false;
    }
    
    bool OpenAPI::setUniform(ShaderProgram* program, const char* uniform_name, const Vec3f &var) const
    {
        unsigned int location = glGetUniformLocation(program->getID(), uniform_name);

        if (location != -1)
        {
            glUniform3f(location, var.x, var.y, var.z);
            return true;
        }

        return false;
    }
    
    bool OpenAPI::setUniform(ShaderProgram* program, const char* uniform_name, const int &var) const
    {
        unsigned int location = glGetUniformLocation(program->getID(), uniform_name);

        if (location != -1)
        {
            glUniform1i(location, var);
            return true;
        }

        return false;
    }

    bool OpenAPI::makeShader(Shader* shader) const
    {
        GLenum type;

        switch (shader->getType())
        {
            case ShaderType::Vertex:
                type = GL_VERTEX_SHADER;
                break;

            case ShaderType::Fragment:
                type = GL_FRAGMENT_SHADER;
                break;
        }

        shader->getID() = glCreateShader(type);

        PS_CORE_INFO("{0} Shader ({1}) Created Successfully", shader->getStatusFromEnum((int)shader->getType()), shader->getID());

        return true;
    }

    bool OpenAPI::compileShader(Shader* shader, const char* source) const
    {
        glShaderSource(shader->getID(), 1, &source, nullptr);
        glCompileShader(shader->getID());

        int result = 0;
        int infoLogLength;

        glGetShaderiv(shader->getID(), GL_COMPILE_STATUS,  &result);
        glGetShaderiv(shader->getID(), GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0)
        {
            std::vector<char> errorMessage(infoLogLength + 1);
            glGetShaderInfoLog(shader->getID(), infoLogLength, nullptr, &errorMessage[0]);
            PS_CORE_ERROR("Error compiling {0} shader ({1}): {2}", 
                shader->getStatusFromEnum((int)shader->getType()), shader->getID(), std::string(&errorMessage[0]));

            return false;
        }

        PS_CORE_INFO("Successfully compiledshader ({0})",
            shader->getID());

        return true;
    }

    bool OpenAPI::destroyShader(Shader* shader) const
    {
        PS_CORE_DEBUG("{0} shader ({1}) destroyed", shader->getStatusFromEnum((int)shader->getType()), shader->getID());
        glDeleteShader(shader->getID());
        return true;
    }

    bool OpenAPI::makeTexture(Texture* texture) const
    {
        glGenTextures(1, &texture->getID());
        return true;
    }

    bool OpenAPI::destroyTexture(Texture* texture) const
    {
        glDeleteTextures(1, &texture->getID());
        PS_CORE_WARN("Texture ({0}) destroyed", texture->getID());
        return true;
    }
    
    void OpenAPI::bindTexture(unsigned id, unsigned int layer) const
    {
        glActiveTexture(GL_TEXTURE0 + layer);
        glBindTexture(GL_TEXTURE_2D, id);
    }

    bool OpenAPI::loadImageToTexture(Texture* texture, unsigned char* img, unsigned int width, unsigned int height) const
    {
        if (!img) return false;

        bindTexture(texture->getID());

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

        // Bounding
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Filtering
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);

        bindTexture(0);

        return true;
    }
}
}