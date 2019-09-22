#pragma once

#include "Log.h"

#include <fstream>
#include <string>

namespace pcs
{
    class PERC_API File
    {
    protected:
        const char* fileLocation;

    public:
        File(const char* location);

        template<typename... Args>
        const char* getFileContents(void (*f)(const char*, Args...) = nullptr, Args... args) const
        {
            std::fstream file(fileLocation);
            std::string contents;

            if (!file.good()) PS_CORE_WARN("File '{0}' could not be read!", fileLocation);

            for (std::string line; std::getline(file, line);)
            {
                const char* c_line = line.c_str();

                if (f != nullptr) f(c_line, args...);

                contents += line + "\n";
            }

            return contents.c_str();
        }
    };
}