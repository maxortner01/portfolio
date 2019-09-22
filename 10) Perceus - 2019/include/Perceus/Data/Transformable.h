#pragma once

#include "Sizable.h"
#include "Vector.h"

namespace pcs
{
    /**
     * @brief Class that handles rotation, translation, and scale.
     * 
     * @tparam T Type to store values as
     */
    template<typename T>
    class Transformable
    {
        T location;
        T rotation;
        T scale;

    public:
        /// Gets the current locations
        T      &getLocation()    { return location; }
        // Sets the current location
        void    setLocation(T l) { location = l;    }

        /// Gets the current rotation
        T      &getRotation()    { return rotation; }
        // Sets the current rotation
        void    setRotation(T r) { rotation = r;    }

        /// Gets the current scale
        T      &getScale()       { return scale; }
        // Sets the current scale
        void    setScale(T s)    { scale = s;    }
    };

    /**
     * @brief Class that handles 2-Dimensional Transformations
     * 
     * @tparam T Type to store values as
     */
    template<typename T>
    class Transformable2D : public Transformable<Vec2<T>>
    {

    };

    /**
     * @brief Class that handles 3-Dimensional Transformations
     * 
     * @tparam T Type to store values as
     */
    template<typename T>
    class Transformable3D : public Transformable<Vec3<T>>
    {

    };
}