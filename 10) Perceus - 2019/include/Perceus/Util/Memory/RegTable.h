#pragma once

#include "Perceus/Data/Singleton.h"
#include "Perceus/Util/Log.h"

#include <iostream>
#include <stdexcept>
#include <unordered_map>

namespace pcs
{
namespace Util
{
namespace Mem
{
    typedef unsigned long long int U64;

    struct DataPoint
    {
        void* ptr;
        size_t size;
    };

    class RegTable : public Data::Singleton<RegTable>
    {
        std::unordered_map<U64, DataPoint> table;

        void registerDataPoint(U64 uid, DataPoint data)
        {
            table.insert(std::pair<U64, DataPoint>(uid, data));
        }

    public:
        RegTable() {}
        RegTable(const RegTable&) = delete;
        RegTable &operator=(const RegTable&) = delete;

        template<typename T>
        T* collect(U64 uid)
        { 
            PS_CORE_DEBUG("Collecting item from regtable: {0}. Size: {1}", uid, table.size());
            DataPoint &p = table[uid];
            
            if (p.size != sizeof(T*)) 
                throw std::runtime_error("Registered type doesn't match");

            return (T*)p.ptr;
        }

        template<typename T>
        void registerObject(U64 uid, const T* obj)
        {
            DataPoint data = { (void*)obj, sizeof(T*) };
            
            registerDataPoint(uid, data);
        }

        template<typename T>
        void registerObject(U64 uid, const T& obj)
        {
            std::cout << "Window Obj: " << &obj << std::endl;
            registerObject(uid, &obj);
        }
    };
}
}
}