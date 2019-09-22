#pragma once

#include <math.h>

#include "Vector.h"

namespace age
{
	struct Mat4f
	{
		float m[4][4] = { 0 };

		Mat4f(bool identity = true)
		{
			if (identity) setIdentity();
		}

		/**
		  * Sets matrix to an identity matrix. (modifies only center
		  * four.
		  */
		void setIdentity()
		{
			m[0][0] = 1.f;
			m[1][1] = 1.f;
			m[2][2] = 1.f;
			m[3][3] = 1.f;
		}

		/**
		  * Makes the matrix into a translation matrix for (x, y, z)
		  * @param x x-coordinate of the translation
		  * @param y y-coordinate of the translation
		  * @param z z-coordinate of the translation
		  */
		static Mat4f makeTranslation(float x, float y, float z) { return makeTranslation({ x, y, z }); }
		static Mat4f makeTranslation(Vec3f loc)
		{
			Mat4f mat;

			mat.setIdentity();

			mat.m[3][0] = loc.x;
			mat.m[3][1] = loc.y;
			mat.m[3][2] = loc.z;

			return mat;
		}

		/**
		  * Make the matrix into a rotation matrix.
		  * @param x Rotation relative to the x-axis (radians)
		  * @param y Rotation relative to the y-axis (radians)
		  * @param z Rotation relative to the z-axis (radians)
		  */
		static Mat4f makeRotation(float x, float y, float z) { return makeRotation({ x, y, z }); }
		static Mat4f makeRotation(Vec3f rot)
		{
			Mat4f rot_x, rot_y, rot_z;

			rot_x.m[0][0] = 1.f;
			rot_x.m[1][1] =  cosf(rot.x);
			rot_x.m[1][2] = -sinf(rot.x);
			rot_x.m[2][2] =  cosf(rot.x);
			rot_x.m[2][1] =  sinf(rot.x);
			rot_x.m[3][3] = 1.f;

			rot_y.m[0][0] =  cosf(rot.y);
			rot_y.m[0][2] =  sinf(rot.y);
			rot_y.m[1][1] = 1.f;
			rot_y.m[2][0] = -sinf(rot.y);
			rot_y.m[2][2] =  cosf(rot.y);
			rot_y.m[3][3] = 1.f;

			return rot_x * rot_y;
		}

		/**
		  * Multiply two matrices together.
		  * @param mat Independant matrix
		  */
		Mat4f operator*(Mat4f mat) {
			Mat4f nmat;

			for (int c = 0; c < 4; c++)
				for (int r = 0; r < 4; r++)
					nmat.m[c][r] = m[0][r] * mat.m[0][c] + m[1][r] * mat.m[1][c] + m[2][r] * mat.m[2][c] + m[3][r] * mat.m[3][c];

			return nmat;
		}
		
	};

}