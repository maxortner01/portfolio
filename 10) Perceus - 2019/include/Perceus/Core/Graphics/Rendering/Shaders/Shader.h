#pragma once

#include "Perceus/Data/ObjectID.h"
#include "Perceus/Data/Status.h"
#include "../RenderObject.h"

#include "Perceus/Data/Inc.h"

#include <string>

namespace pcs
{
    enum class ShaderStatus
    {
        CompileFailed,
        CompileSucceeded,
        FileDoesNotExist
    };

    enum class ShaderType
    {
        Vertex,
        Fragment,
        Count
    };

    class PERC_API Shader : 
        public rend::RenderObject, public Data::ObjectID<Shader>, public Data::Status<ShaderStatus>
    {
        ShaderType type;

    public:
        Shader(ShaderType t);
        ~Shader();

        int loadFromFile(std::string filename);
        int loadFromString(const std::string &str);

        ShaderType getType() const { return type; }
    };
}