#include "Perceus/Data/String.h"

#include <cstring>

namespace pcs
{
    String::String()
    {

    }

    String::String(const char* str) :
        size(std::strlen(str))
    {
        buffer = std::malloc(size + 1);
        std::memcpy(buffer, str, size);

        char* last = (char*)buffer + size;
        *last = 0;
    }

    String::String(const String& str)
    {

    }
}