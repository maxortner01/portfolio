#pragma once

#include "Vector.h"
#include <math.h>

namespace pcs
{
    struct Mat4f
    {
        float m[4][4];

        void toIdentity()
        {
            for (int i = 0; i < 4; i++)
            {
                m[i][i] = 1;
            }
        }

        float &operator() (const unsigned int r, const unsigned int c)
        {
            return m[r][c];
        }

        static Mat4f makeIdentity()
        {
            Mat4f mat = Mat4f();
            mat.toIdentity();
            return mat;
        }

        // Static function for generating translation matrix
        static Mat4f makeTranslation(const float x, const float y, const float z) 
            { return makeTranslation({ x, y, z });  }
        static Mat4f makeTranslation(const Vec3f &vec)
        {
            Mat4f mat = Mat4f::makeIdentity();   

            mat.m[0][3] = vec.x;
            mat.m[1][3] = vec.y;
            mat.m[2][3] = vec.z;

            return mat;
        }

        // Static function for generating rotation matrix
        static Mat4f makeRotation(const float x, const float y, const float z) 
            { return makeRotation({ x, y, z });  }
        static Mat4f makeRotation(const Vec3f &rot)
        {
            Mat4f matX = Mat4f::makeIdentity();
            Mat4f matY = Mat4f::makeIdentity();
            Mat4f matZ = Mat4f::makeIdentity();

            matX.m[1][1] =  cosf(rot.x);
            matX.m[2][2] =  cosf(rot.x);
            matX.m[2][1] =  sinf(rot.x);
            matX.m[1][2] = -sinf(rot.x);

            matY.m[0][0] =  cosf(rot.y);
            matY.m[0][2] =  sinf(rot.y);
            matY.m[2][0] = -sinf(rot.y);
            matY.m[2][2] =  cosf(rot.y);

            matZ.m[0][0] =  cosf(rot.z);
            matZ.m[0][1] = -sinf(rot.z);
            matZ.m[1][0] =  sinf(rot.z);
            matZ.m[1][1] =  cosf(rot.z);

            return matZ * matX * matY;
        }

        // Static function for generating scale matrix
        static Mat4f makeScale(const float x, const float y, const float z) 
            { return makeScale({ x, y, z });  }
        static Mat4f makeScale(const Vec3f &rot)
        {
            Mat4f mat = Mat4f::makeIdentity();   

            mat.m[0][0] = rot.x;
            mat.m[1][1] = rot.y;
            mat.m[2][2] = rot.z;

            return mat;
        }

        Vec4f getRow(int index)
        {
            return Vec4f(m[index][0], m[index][1], m[index][2], m[index][3]);
        }

        Mat4f operator*(const Mat4f &mat) const
        {
            Mat4f res = Mat4f();

            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                {
                    res.m[i][j] = 0;
                    for (int k = 0; k < 4; k++)
                        res.m[i][j] += m[i][k] * mat.m[k][j];
                }

            return res;
        }

        //void print() const
        //{
        //    for (int i = 0; i < 4; i++)
        //    {
        //        for (int j = 0; j < 4; j++)
        //        {
        //            std::cout << m[i][j] << " ";
        //        }
        //        std::cout << std::endl;
        //    }
        //}
    };
}