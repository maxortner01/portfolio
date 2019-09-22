#pragma once

#include <stdexcept>
#include <cstdlib>

namespace pcs
{
    template<typename T>
    class bStack
    {
        size_t _asize;
        size_t _size;
        void* _start;
        T* top;

    public:
        Stack(size_t s) :
            _size(0), _asize(s)
        {
            _start = std::malloc(sizeof(T) * s);
            top = (T*)_start;
        }

        ~Stack()
        {
            std::free(_start);
        }

        size_t size() const;
        void   push(T val);
        T      pop();
    };

    template<typename T>
    size_t Stack<T>::size() const
    {
        return _size;
    }

    template<typename T>
    void Stack<T>::push(T val)
    {
        if (_size < _asize)
        {
            *(top) = T(std::forward<T>(val));
            top++;
            _size++;
        }
        else
            throw std::runtime_error("Cannot push another item");
    }

    template<typename T>
    T Stack<T>::pop()
    {
        T r = *(top - 1);
        delete top;
        top--;
        _size--;

        return r;
    }
}