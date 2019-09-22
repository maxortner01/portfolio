#pragma once

#include "Perceus/Data/Matrix.h"
#include "Buffer.h"

namespace pcs
{
namespace rend
{
    /**
     * @brief Class that contains 16 buffer objects.
     * In OpenGL this class represents the OOP version of a VAO.
     */
    class PERC_API BufferArray : 
        public RenderObject, public Data::ObjectID<BufferArray>
    {
        Buffer** buffers;

    protected:
        /**
         * @brief Bind a type of data to a specific buffer.
         * 
         * @tparam T Type of data that is to be bound to the buffer
         * @param buffer Buffer index that the data is to be bound to
         * @param members The amount of members that represent one object of type T
         * @param data List of actual data
         */
        template<typename T>
        void bindBuffer(BufferIndex buffer, unsigned int members, const std::vector<T> &data)
        {
            Buffer* &buff = *(buffers + (int)buffer);
            if (!buff)
                buff = new Buffer((int)buffer, data, members);
            else
                buff->bindData(data, members);
        }
        
        /**
         * @brief Overload of the main bindbuffer function just for matrices.
         * 
         * @param data List of matrices to bind
         */
        void bindBuffer(const std::vector<Mat4f> &data)
        {
            unsigned int index = (int)BufferIndex::ModelMatrix;
            Buffer* &buff = *(buffers + index);
            if (!buff)
                buff = new Buffer(index, data);
            else
                buff->bindData(data);
        }

    public:
        /**
         * @brief Constructs a new Buffer Array object with ARRAY_SIZE buffers.
         */
        BufferArray();

        /**
         * @brief Destroys the Buffer Array object as well as the buffers themselves.
         */
        virtual ~BufferArray();

        /**
         * @brief Gets the Buffer object from the specified index
         * 
         * @param buffer Index which to pull the buffer
         * @return Buffer& Reference to the buffer object
         */
        Buffer &getBuffer(BufferIndex buffer) { return *buffers[(int)buffer]; }

        /**
         * @brief Binds the buffer array.
         */
        void bind() const   { rendAPI()->bindBufferArray(id); }
        /**
         * @brief Unbinds the buffer array.
         */
        void unbind() const { rendAPI()->bindBufferArray(0);  }

        /**
         * @brief Get the stringified version of the buffer.
         * 
         * @param index Index of the buffer
         * @return const char* String version of the buffer
         */
        static const char* getBufferName(unsigned int index)
        {
			const char* r[]{
				"Vertices",
				"Normal",
				"TexCoords",
				"Color",
				"Tangents",
				"ModelMatrix",
				"Indices"
			};

            return r[index];
        }
    };
}
}