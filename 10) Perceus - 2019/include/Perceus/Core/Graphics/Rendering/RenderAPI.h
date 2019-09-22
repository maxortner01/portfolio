#pragma once

#include "Perceus/Data/Singleton.h"
#include "Perceus/Data/Matrix.h"
#include "Perceus/Data/Color.h"

#include "Perceus/Data/Inc.h"

#if defined(WIN32) || defined(_WIN32)
    typedef unsigned long long int u_int64_t;
#endif

namespace pcs
{
class Window;
class Shader;
class ShaderProgram;
class Texture;

namespace rend
{
    class Buffer;
    class BufferArray;

    enum class BufferType
    {
        Vertex,
        Index
    };

    // Base methods
    #define BASE_METHODS(bef, aft)\
        bef bool   initialize() const aft;\
        bef bool   terminate() const aft;\
        bef double getTime() const aft;\
        bef bool   renderInstanced(unsigned int vertexCount, unsigned int count) aft;\

    // Window methods
    #define WINDOW_METHODS(bef, aft)\
        bef int   makeWindow(Window* window) aft;\
        bef int   destroyWindow(Window* window) const aft;\
        bef bool  shouldClose(Window* window) const aft;\
        bef bool  swapBuffers(Window* window) const aft;\
        bef bool  pollEvents(Window* window) const aft;\
        bef bool  resizeWindow(Window* window, unsigned int width, unsigned int height) const aft;\
        bef bool  clear(Color color) const aft;\
        bef void  makeContextCurrent(Window* window) aft;\
        bef u_int64_t getCurrentContext() const aft;\
        bef bool  isKeyDown(Window* window, const char c) const aft;\
        bef void  setMousePos(Window* window, const Vec2d position) const aft;\
        bef void  disableCursor(Window* window) const aft;

    #define BUFFER_METHODS(bef, aft)\
        bef void makeBuffer(Buffer* buffer) const aft;\
        bef void destroyBuffer(Buffer* buffer) const aft;\
        bef void bindBufferMatrixData(Buffer* buffer, const std::vector<Mat4f> &matrices) const aft;\
        bef void unbindBuffer(BufferType type = BufferType::Vertex) const aft;\
        bef void bindBuffer(Buffer* buffer, BufferType type = BufferType::Vertex) const aft;\
        bef void bindBufferData(unsigned int bytesize, const void* data, unsigned int members, unsigned int index, bool divided = true, BufferType type = BufferType::Vertex) const aft;

    #define BUFFER_ARRAY_METHODS(bef, aft)\
        bef void makeBufferArray(BufferArray* array) const aft;\
        bef void destroyBufferArray(BufferArray* array) const aft;\
        bef void bindBufferArray(unsigned int ID) const aft;

    #define SHADER_PROGRAM_METHODS(bef, aft)\
        bef bool makeProgram(ShaderProgram* program) const aft;\
        bef bool linkProgram(ShaderProgram* program) const aft;\
        bef void useProgram(unsigned int id) const aft;\
        bef bool destroyProgram(ShaderProgram* program) const aft;

    #define SHADER_METHODS(bef, aft)\
        bef bool setUniform(ShaderProgram* program, const char* uniform_name, const Mat4f &matrix) const aft;\
        bef bool setUniform(ShaderProgram* program, const char* uniform_name, const Vec3f &var) const aft;\
        bef bool setUniform(ShaderProgram* program, const char* uniform_name, const int &var) const aft;\
        bef bool makeShader(Shader* shader) const aft;\
        bef bool compileShader(Shader* shader, const char* source) const aft;\
        bef bool destroyShader(Shader* shader) const aft;

    #define TEXTURE_METHODS(bef, aft)\
        bef bool makeTexture(Texture* texture) const aft;\
        bef bool destroyTexture(Texture* texture) const aft;\
        bef void bindTexture(unsigned id, unsigned int layer = 0) const aft;\
        bef bool loadImageToTexture(Texture* texture, unsigned char* img, unsigned int width, unsigned int height) const aft;

    #define RENDER_API_BODY(bef, aft)\
        BASE_METHODS(bef, aft)\
        WINDOW_METHODS(bef, aft)\
        BUFFER_METHODS(bef, aft)\
        BUFFER_ARRAY_METHODS(bef, aft)\
        SHADER_PROGRAM_METHODS(bef, aft)\
        SHADER_METHODS(bef, aft)\
        TEXTURE_METHODS(bef, aft)

    #define RENDER_API_DERIVATIVE(cls) : public RenderAPI, public Data::Singleton<cls>\
        { RENDER_API_BODY( , override) }

    struct RenderAPI
    {
        RENDER_API_BODY(virtual, = 0);

        unsigned int &getRenderCalls()  { return renderCalls;  }
        unsigned int &getVertexCount()  { return vertexCount;  }
        unsigned int &getObjectCount()  { return objectCount;  }
        unsigned int &getPolygonCount() { return polygonCount; }

    protected:
        unsigned int renderCalls  = 0;
        unsigned int vertexCount  = 0;
        unsigned int objectCount  = 0;
        unsigned int polygonCount = 0;

        unsigned long long int current_contex = 0;
    };
}
}