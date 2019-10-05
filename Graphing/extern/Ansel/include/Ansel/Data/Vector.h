#pragma once

#include <math.h>

namespace age
{
	template<typename T>
	struct Vec2
	{
		T x, y;

		Vec2(T _x = 0, T _y = 0) :
			x(_x), y(_y)
		{

		}

		template<typename N>
		Vec2<T> operator-(Vec2<N> v)
		{
			return Vec2<T>(x - v.x, y - v.y);
		}

		template<typename N>
		Vec2<T> operator+(Vec2<N> v)
		{
			return Vec2<T>(x + v.x, y + v.y);
		}

		template<typename N>
		Vec2<T> operator*(Vec2<N> v)
		{
			return Vec2<T>(x * v.x, y * v.y);
		}

		template<typename N>
		Vec2<T> operator*(N k)
		{
			return Vec2<T>(k * x, k * y);
		}

		template<typename N>
		Vec2<T> operator/(N k)
		{
			return Vec2<T>(x / k, y / k);
		}

		template<typename N>
		operator Vec2<N>()
		{
			return { (N)x, (N)y };
		}
	};

	// Forward declare Vec4 for conversion
	template<typename T>
	struct Vec4;

	template<typename T>
	struct Vec3
	{
		T x, y, z;

		Vec3(T _x = 0, T _y = 0, T _z = 0) :
			x(_x), y(_y), z(_z)
		{

		}

		template<typename N>
		Vec3<T> operator-(Vec3<N> v)
		{
			return Vec3<T>(x - v.x, y - v.y, z - v.z);
		}

		template<typename N>
		Vec3<T> operator+(Vec3<N> v)
		{
			return Vec3<T>(x + v.x, y + v.y, z + v.z);
		}

		template<typename N>
		Vec3<T> operator*(Vec3<N> v)
		{
			return Vec3<T>(x * v.x, y * v.y, z * v.z);
		}

		template<typename N>
		Vec3<T> operator*(N k)
		{
			return Vec3<T>(k * x, k * y, k * z);
		}

		template<typename N>
		const Vec3<T> operator/(N k) const
		{
			return Vec3<T>(x / k, y / k, z / k);
		}

		template<typename N>
		operator Vec3<N>()
		{
			return { (N)x, (N)y, (N)z };
		}

		template<typename N>
		bool operator==(const Vec3<N> &v) const
		{
			return (x == v.x && y == v.y && z == v.z);
		}

		template<typename N>
		operator Vec4<N>()
		{
			return { (N)x, (N)y, (N)z, 1 };
		}
	};

	template<typename T>
	struct Vec4
	{
		T x, y, z, w;

		Vec4(T _x = 0, T _y = 0, T _z = 0, T _w = 1) :
			x(_x), y(_y), z(_z), w(_w)
		{

		}

		template<typename N>
		Vec4<T> operator-(Vec4<N> v)
		{
			return Vec4<T>(x - v.x, y - v.y, z - v.z);
		}

		template<typename N>
		Vec4<T> operator+(Vec4<N> v)
		{
			return Vec4<T>(x + v.x, y + v.y, z + v.z);
		}

		template<typename N>
		Vec4<T> operator*(Vec4<N> v)
		{
			return Vec4<T>(x * v.x, y * v.y, z * v.z);
		}

		template<typename N>
		Vec4<T> operator*(N k)
		{
			return Vec4<T>(k * x, k * y, k * z);
		}

		template<typename N>
		Vec4<T> operator/(N k)
		{
			return Vec4<T>(x / k, y / k, z / k);
		}

		template<typename N>
		operator Vec4<N>()
		{
			return { (N)x, (N)y, (N)z, (N)w };
		}

		template<typename N>
		operator Vec3<N>()
		{
			return { (N)x, (N)y, (N)z };
		}

	};

	typedef Vec4<int>          Vec4i;
	typedef Vec4<float>        Vec4f;
	typedef Vec4<double>       Vec4d;
	typedef Vec4<unsigned int> Vec4u;

	typedef Vec3<int>          Vec3i;
	typedef Vec3<float>        Vec3f;
	typedef Vec3<double>       Vec3d;
	typedef Vec3<unsigned int> Vec3u;

	typedef Vec2<int>          Vec2i;
	typedef Vec2<float>        Vec2f;
	typedef Vec2<double>       Vec2d;
	typedef Vec2<unsigned int> Vec2u;

	template<typename T>
	float dotProduct(const Vec3<T> &v1, const Vec3<T> &v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	template<typename T>
	Vec3<T> normalize(const Vec3<T> &v)
	{
		return v / sqrtf(dotProduct(v, v));
	}
}