#pragma once

#include <cmath>

namespace pcs
{
    template<typename T>
    struct Vec2
    {
        T x, y;
        
        Vec2(T _x = 0, T _y = 0) :
            x(_x), y(_y)
        {

        }

        void operator+(const Vec2<T> &v)
        {
            x += v.x;
            y += v.y;
        }

        Vec2<T> operator-(const Vec2<T> &v) const
        {
            Vec2<T> t = Vec2<T>();

            t.x -= v.x;
            t.y -= v.y;

            return t;
        }
    };
    
    template<typename T>
    struct Vec3
    {
        T x, y, z;

        Vec3(T _x = 0, T _y = 0, T _z = 0) :
            x(_x), y(_y), z(_z)
        {

        }

        Vec3<T> operator+(const Vec3<T> &v) const
        {
            Vec3<T> t = Vec3<T>();

            t.x += v.x;
            t.y += v.y;
            t.z += v.z;

            return t;
        }

        Vec3<T> operator-(const Vec3<T> &v) const
        {
            Vec3<T> t = Vec3<T>();

            t.x -= v.x;
            t.y -= v.y;
            t.z -= v.z;

            return t;
        }

        Vec3<T> operator*(const float &k) const
        {
            Vec3<T> t = Vec3<T>();

            t.x = x * k;
            t.y = y * k;
            t.z = z * k;

            return t;
        }

        Vec3<T> operator/(const float &k) const
        {
            Vec3<T> t = Vec3<T>();

            t.x = x / k;
            t.y = y / k;
            t.z = z / k;

            return t;
        }

        void operator+=(const Vec3<T> &v) 
        {
            x += v.x;
            y += v.y;
            z += v.z;
        }

        void operator/=(const float &v) 
        {
            x /= v;
            y /= v;
            z /= v;
        }

        template<typename R>
        operator Vec3<R>() const
        {
            return Vec3<R>(
                (R)x,
                (R)y,
                (R)z
            );
        }
    };

    template<typename T>
    struct Vec4
    {
        T x, y, z, w;

        Vec4(T _x = 0, T _y = 0, T _z = 0, T _w = 0) :
            x(_x), y(_y), z(_z), w(_w)
        {

        }

        void operator+(const Vec4<T> &v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
        }

        void operator-(const Vec4<T> &v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
        }
    };

    typedef Vec2<double>       Vec2d;
    typedef Vec2<float>        Vec2f;
    typedef Vec2<int>          Vec2i;
    typedef Vec2<unsigned int> Vec2u;

    typedef Vec3<double>       Vec3d;
    typedef Vec3<float>        Vec3f;
    typedef Vec3<int>          Vec3i;
    typedef Vec3<unsigned int> Vec3u;

    typedef Vec4<double>       Vec4d;
    typedef Vec4<float>        Vec4f;
    typedef Vec4<int>          Vec4i;
    typedef Vec4<unsigned int> Vec4u;

    static float length(const Vec3f& vec)
    {
        return sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
    }

    static Vec3f normalize(const Vec3f& vec)
    {
        return vec / length(vec);
    }

	static float dot(const Vec3f& a, const Vec3f& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
}