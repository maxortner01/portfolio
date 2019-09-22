#pragma once

namespace pcs
{
namespace Data
{
    template<typename T>
    class Singleton
    {
    public:
        static T &get()
        {
            static T* t;

            if (t == nullptr)
                t = new T();

            return *t;
        }
    };
}
}