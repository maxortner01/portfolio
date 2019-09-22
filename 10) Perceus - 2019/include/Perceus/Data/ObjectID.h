#pragma once

#include <ctime>
#include <bitset>

namespace pcs
{
namespace Data
{
    typedef unsigned long long int U64;

    /**
     * @brief Class that handles an object's unique ID.
     * 
     * @tparam T Class of which the object is declared
     */
    template<typename T, typename R = unsigned int>
    class ObjectID
    {
    protected:

        /**
         * @brief Get the next ID
         * 
         * @return unsigned int Incremented ID
         */
        virtual R getNext()
        {
            static R _id;
            return _id++;
        }

        /// Current ID
        R id;

    public:
        /**
         * @brief Constructs a new ObjectID
         */
        ObjectID() :
            id(getNext())
        {
            
        }

        /// Gets the ID
        R &getID() { return id; }
        
    };

    /**
     * @brief Base class that creates a 64-bit unique ID
     */
    class ObjectUID : public ObjectID<ObjectUID, U64>
    {
        // Generate a unique ID
        U64 getNext() override
        {
            std::bitset<64> bits;

            // Set the random seed equal to the clock ticks
            srand((int)clock());
            for (int i = 0; i < 64; i++)
            {
                // Time based
                if (i % 2 == 0)
                {
                    time_t time = std::time(0);
                    struct tm* now = localtime(&time);
                    bits[i] = (int)(now->tm_hour + now->tm_min + now->tm_mday + now->tm_sec) % 2;
                }
                // Random number based
                else
                    bits[i] = rand() % 2;
                
            }

            return bits.to_ullong();
        }

    public:
        ObjectUID()
        {
            id = getNext();
        }

        void overrideID(U64 uid)
        {
            id = uid;
        }
    };
}
}