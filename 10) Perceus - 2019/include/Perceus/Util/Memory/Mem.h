#pragma once

#include <cstdlib>
#include <cstring>
#include <stdexcept>

namespace pcs
{
    template<typename T>
    class Array
    {
        void* buffer;

    protected:
        unsigned int _size;

        void* buffermemaddr() const
        {
            return buffer;
        }

    public:
        Array() : _size(0), buffer(nullptr) { }

        Array(const unsigned int size) :
            _size(size), buffer(nullptr)
        {
            resize(size);
        }

        virtual ~Array()
        {
            std::free(buffer);
        }

        void resize(const unsigned int size)
        {
            if (buffer == nullptr || _size == 0)
            {
                buffer = std::calloc(size, sizeof(T));
                return;
            }

            void* newbuff = std::calloc(size, sizeof(T));

            if (newbuff == NULL)
                throw std::runtime_error("Error reallocating data!");

            std::memcpy(newbuff, buffer, sizeof(T) * _size);
            std::free(buffer);

            buffer = newbuff;
        }

        T &operator[](const unsigned int index)
        {
            return *((T*)(buffer) + index);
        }

        void clear()
        {
            std::memset(buffer, 0, sizeof(T) * _size);
        }

        unsigned int size() const { return _size; }

    };

    template<typename T>
    class List : public Array<T>
    {
        bool allocated = false;
        unsigned int _capacity;

        struct it
        {
            T* pos;
            unsigned int index;

            it operator+(const unsigned int index) const
            {
                return { pos + index, index };
            }

            T& operator*() const
            {
                return *pos;
            }
        };

        template<typename C> struct pointer_handler
        {
            static void handle(List<T>* list, const unsigned int index)
            {

            }
        };

        template<typename C> struct pointer_handler<C*>
        {
            static void handle(List<T>* list, const unsigned int index)
            {
                if ((*list)[index])
                    delete (*list)[index];
            }
        };

        it _first, _last;

    public:
        List() :
        _capacity(0)
        {
            
        }

        List(const unsigned int size) :
            Array<T>(size), _capacity(size)
        {
            allocated = true;
        }

        void push(const T& val)
        {
            if (this->_size == _capacity)
            {
                // Calculate the new capacity
                _capacity = (int)(sqrtf(7.f / 4.f * powf(this->_size, 2))) + 1;
                // Resize the memory to fit the capacity
                this->resize(_capacity);
                // Set the 'first' iterator to the location of the first data
                _first = { (T*)this->buffermemaddr(), 0 };
            }

            std::cout << "setting last\n";
            // Set the last item to be the value
            (*this)[this->_size++] = val;

            // Set the 'last' iterator to be the location of the last value
            _last = { &(*this)[this->_size - 1], this->_size - 1 };
        }

        void erase(const it& loc1, const it& loc2, bool conservative_ptr = false)
        {
            int start = loc1.index;
            int end   = loc2.index;
            if (loc1.index > loc2.index)
            {
                start = loc2.index;
                end   = loc1.index;
            }

            if (start < 0 || end >= this->_size) 
            {
                //std::cout << "Start: " << start << " End: " << end << "\n";
                //std::cout << "bad yo\n";
                return;
            }

            const unsigned int bef = this->_size;
            for (int i = start; i <= end; i++)
            {
                if (!conservative_ptr)
                    pointer_handler<T>::handle(this, i);

                this->_size--;
            }
            
            //std::cout << "mem to " << start << " from " << this->_size << " with size of " << (bef - this->_size) * sizeof(T) << "\n";
            std::memcpy(&(*this)[start], &(*this)[end + 1], (bef - end + 1) * sizeof(T));

            // Set the 'last' iterator to be the location of the last value
            _last = { &(*this)[this->_size - 1], this->_size - 1 };
        }

        const it& first() const
        {
            return _first;
        }

        const it& last() const
        {
            return _last;
        }

        void fit()
        {
            this->resize(this->_size);
            _capacity = this->_size;
        }

        unsigned int capacity() const { return _capacity; }
    };

    template<typename T, bool _CONSERVATIVE = false>
    class Stack : protected List<T>
    {
        void* _top;

    public:
        Stack() :
            _top(nullptr)
        {
            
        }

        void push(const T& val)
        { 
            static_cast<List<T>*>(this)->push(val);
            _top = (void*)this->last().pos;
        }

        void pop()
        {
            this->erase(this->last(), this->last(), _CONSERVATIVE);

            if (this->_size != 0)
                _top = (void*)this->last().pos;
            else
                _top = nullptr;
        }

        unsigned int size() const
        {
            return this->_size;
        }

        T& top()
        {
            if (!_top)
                throw std::runtime_error("Attempting to access empty stack!");

            return *(T*)_top;
        }
    };

    template<typename T>
using ConservativeStack = Stack<T, true>;
}