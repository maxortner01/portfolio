#pragma once

namespace age
{
	template<typename T>
	class List
	{
	public:
		class Iterator
		{
			T* ptr;
		public:

			Iterator() {}
			Iterator(T* p) { ptr = p; }

			void operator=(T* p) { ptr = p; }

			T &operator*() { return *ptr; }
			T &operator++(int) { T &b = *ptr;  ptr++; return b; }
			T &operator--(int) { T &b = *ptr;  ptr--; return b; }
			T* operator+(int i) { return ptr + i; }

			bool operator==(void* p) const { return p == (void*)ptr; }
			bool operator!=(void* p) const { return p != (void*)ptr; }

			T* pointer() const { return ptr; }
		};

	private:
		void* _first_addr = nullptr;
		unsigned int _allocated_size;
		unsigned int _used_space;

		Iterator _last_item;

		void scaleSize()
		{
			_allocated_size = (unsigned int)((float)_allocated_size * 1.5f);
		}

	public:
		List(unsigned int size = 2) :
			_allocated_size(size), _used_space(0)
		{
			reserve(size);
		}

		~List()
		{
			free(_first_addr);
		}
		
		T* begin()
		{
			return (T*)_first_addr;
		}
		
		T* end()
		{
			return ((T*)_first_addr) + _allocated_size;
		}

		void push(const T &item)
		{
			if (_last_item == end())
			{
				scaleSize();
				reserve(_allocated_size);
			}

			memcpy((void*)(_last_item + 1), (void*)&item, sizeof(T));

			_last_item++;
			_used_space++;
		}

		void pop()
		{

		}

		void reserve(int count)
		{
			_allocated_size = count;
			void* new_addr = malloc(sizeof(T) * count);

			if (_first_addr)
			{
				Iterator new_it = (T*)new_addr;
				for (Iterator it = begin(); it != end(); it++)
				{
					memcpy((void*)new_it.pointer(), (void*)it.pointer(), sizeof(T));
					new_it++;
				}

				free(_first_addr);
			}


			_first_addr = new_addr;
		}

		void resize(int count)
		{
			_allocated_size = count;
			_used_space = count;
			reserve(count);

			for (Iterator it = begin(); it != end(); it++)
			{
				*it = T();
			}
		}

		T &at(int index)
		{
			return *((T*)_first_addr + index);
		}

		T &operator[](int index)
		{
			return at(index);
		}

		unsigned int size() const { return _used_space; }
	};
}