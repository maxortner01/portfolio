#pragma once

#include "Inc.h"

namespace pcs
{
    class String
    {
        size_t size;
        void* buffer;

    public:
        String();
        String(const char* str);
        String(const String& str);
    };
}