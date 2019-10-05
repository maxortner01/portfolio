#pragma once

#include "../../DLL/dll.h"
#include "../GLObjects.h"

#include <vector>

namespace age
{
	class DataType
	{
		void* _data = nullptr;
		unsigned int _size   = 0;
		unsigned int _count  = 1;
		unsigned int _amount = 1;

	public:
		DataType(void* d, unsigned int s, unsigned int c = 1, unsigned int a = 1) : 
			_data(d), _size(s), _count(c), _amount(a)
		{

		}

		unsigned int amount() const { return _amount; }
		unsigned int count()  const { return _count;  }
		unsigned int size()   const { return _size;   }
		void*        data()   const { return _data;   }
	};

	class Buffer : public GLObject
	{
		/// Index within the VertexArray
		unsigned int _index = 0;
		bool bound_data = false;
		DataType* data = nullptr;

	public:
		enum BufferTypes
		{
			VERTEX,
			COLOR,
			NORMAL,
			TRANSLATION,
			ROTATION,
			SCALE,
			ORIGIN,
			TEX_COORDS,
			INDICES = 16
		};

		/**
		  * Builds the VBO with OpenGL
		  * @param index Index within the VertexArray
		  */
		ANSEL_API  Buffer(unsigned int index = 1);

		/**
		  * Destroys the VBO with OpenGL
		  */
		ANSEL_API ~Buffer();

		/**
		  * Binds specified data type to the buffer
		  * @param data    Container which describes the data type
		  * @param divisor Whether nor not to tell OpenGL the data shouldn't be divided
		  */
		void ANSEL_API bindData(const DataType &data, bool static_draw = true, bool divisor = false);

		/**
		  * Binds specified data to the buffer
		  * @param data    Pointer to the data to bind
		  * @param amount  Amount of data points per one unit
		  * @param count   Count of all data units
		  * @param divisor Whether or not to tell OpenGL the data shouldn't be divided
		  */
		template<typename T>
		void bindData(const T* data, unsigned int amount = 1, unsigned int count = 1, bool divisor = false)
		{
			bindData(DataType(data, sizeof(T), count, amount), divisor);
		}

		/// Binds the buffer
		ANSEL_API void bind() override;
		/// Unbinds the buffer
		ANSEL_API void unbind() const override;

		/**
		  * Gets the index in the VertexArray
		  * @return VertexArray index
		  */
		unsigned int index() const { return _index; }

		DataType &getData() { if (data) return *data; }
	};
}