#include "Perceus/Core/Graphics/Entities/Buffer.h"
#include "Perceus/Core/Graphics/Entities/BufferArray.h"

namespace pcs
{
namespace rend
{
    Buffer::Buffer(unsigned int index) :
        _index(index)
    {
        rendAPI()->makeBuffer(this);
    }

    Buffer::~Buffer()
    {
        PS_CORE_DEBUG("Destroying Buffer {0}", _index);
        rendAPI()->destroyBuffer(this);
        PS_CORE_DEBUG("Buffer Destroyed");
    }

    void Buffer::bind() 
    { 
        if (_index != (int)BufferIndex::Indices)
            rendAPI()->bindBuffer(this);
        else
            rendAPI()->bindBuffer(this, BufferType::Index);
    }

    void Buffer::unbind() const 
    { 
        if (_index != (int)BufferIndex::Indices)
            rendAPI()->unbindBuffer();
        else
            rendAPI()->unbindBuffer(BufferType::Index);
    }
}
}