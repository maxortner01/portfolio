#pragma once

#include <iostream>
#include "Perceus/Data/Inc.h"
#include "../Rendering/RenderObject.h"

#include "Perceus/Data/ObjectID.h"
#include "Perceus/Util/Log.h"

namespace pcs
{
namespace rend
{
    /**
     * @brief Index of each buffer type.
     */
    enum class BufferIndex
    {
        Vertices,
        Normal,
        TexCoords,
        Color,
        Tangents,
        ModelMatrix,
        Indices,
        BufferCount
    };

    /**
     * @brief Handles transportation of vector-based data into the render api.
     */
    class PERC_API Buffer : 
        public RenderObject, public Data::ObjectID<Buffer>
    {
        unsigned int _index, _count;

    public:
        /**
         * @brief Constructs a new Buffer object
         * 
         * @param index Index of the buffer within an array object
         */
        Buffer(unsigned int index);

        /**
         * @brief Constructs a new Buffer object and binds specified data.
         * 
         * @tparam Args Arguments which correspond to a bindData function
         * @param index Index of the buffer within an array object
         * @param args Arguments which correspond to a bindData function
         */
        template<typename... Args>
        Buffer(unsigned int index, Args... args) :
            Buffer(index)
        {
            bindData(args...);
        }

        /**
         * @brief Destroys the Buffer object.
         */
        ~Buffer();

        /**
         * @brief Binds the buffer.
         */
        void bind();
        /**
         * @brief Unbinds the buffer.
         */
        void unbind() const;

        /**
         * @brief Binds the specified data to the gpu-buffer.
         * 
         * @tparam T Type of data to bind
         * @param data Pointer to the data
         * @param count Amount of items in the array
         * @param members Amount of data members per object of type T
         */
        template<typename T>
        void bindData(T* data, unsigned int count, unsigned int members)
        {
            bind();
            rendAPI()->bindBufferData(sizeof(T) * count, data, members,true, _index);
            unbind();

            _count = count;
        }

        /**
         * @brief Binds the specified data to the gpu-buffer.
         * 
         * @tparam T Type of data to bind
         * @param data Vector of data 
         * @param members Amount of data members per object of type T
         */
        template<typename T>
        void bindData(const std::vector<T> &data, const unsigned int members)
        {
            bind();
            BufferType type = BufferType::Vertex;
            bool divided = true;

            if (_index == (int)BufferIndex::Indices)
                type = BufferType::Index;

            rendAPI()->bindBufferData(sizeof(T) * data.size(), &data[0], members, _index, divided, type);
            unbind();

            _count = data.size();
        }

        /**
         * @brief Binds the specified list of matrices to the gpu-buffer.
         * 
         * @param matrices Vector of matrices
         */
        void bindData(const std::vector<Mat4f> &matrices)
        {
            rendAPI()->bindBufferMatrixData(this, matrices);
        }

        /// Gets the current index within an array object
        unsigned int &getIndex() { return _index; }
        /// Gets the data count
        unsigned int &getCount() { return _count; }
    };
}
}