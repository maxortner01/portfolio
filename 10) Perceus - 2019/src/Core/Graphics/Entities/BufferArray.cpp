#include "Perceus/Core/Graphics/Entities/BufferArray.h"

namespace pcs
{
namespace rend
{
    BufferArray::BufferArray()
    {
        rendAPI()->makeBufferArray(this);

        unsigned int count = (unsigned int)BufferIndex::BufferCount;
        buffers = (Buffer**)std::calloc(count, sizeof(void*));
    };

    BufferArray::~BufferArray()
    {
        PS_CORE_DEBUG("Destroying BufferArray");
        rendAPI()->destroyBufferArray(this);

        for (int i = 0; i < (int)BufferIndex::BufferCount; i++)
            if (buffers + i) delete *(buffers + i);

        std::free(buffers);
        PS_CORE_DEBUG("Buffer Array Destroyed");
    }
}
}