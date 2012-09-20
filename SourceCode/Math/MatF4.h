#ifndef MATF4_H
#define MATF4_H

#include "CommonMath.h"

struct MatF4
{
	float m[4][4];

	MatF4() {}
	~MatF4() {}

	/*Operators*/
	MatF4 operator*(const MatF4& mat) const
	{
		MatF4 ret;

		for (unsigned int i = 0 ; i < 4; i++)
		{
			for (unsigned int j = 0 ; j < 4; j++)
			{
				ret.m[i][j] = 
				m[i][0]		* mat.m[0][j]
				+ m[i][1]	* mat.m[1][j]
				+ m[i][2]	* mat.m[2][j]
				+ m[i][3]	* mat.m[3][j];
			}
		}

		return ret;
	}

	/*Helper funcs*/
	MatF4& identity()
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;

		return *this;
	}

	/*Transform funcs*/
	void scaling(float x, float y, float z)
	{
		m[0][0] = x;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0.0f;
		m[1][0] = 0.0f;	m[1][1] = y;	m[1][2] = 0.0f;	m[1][3] = 0.0f;
		m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = z;	m[2][3] = 0.0f;
		m[3][0] = 0.0f;	m[3][1] = 0.0f;	m[3][2] = 0.0f;	m[3][3] = 1.0f;
	}
	void rotation(float x, float y, float z)
	{
		MatF4 rx, ry, rz;

		const float radianX = (float)RADIAN(x);
		const float radianY = (float)RADIAN(y);
		const float radianZ = (float)RADIAN(z);

		rx.m[0][0] = 1.0f; rx.m[0][1] = 0.0f;			rx.m[0][2] = 0.0f;				rx.m[0][3] = 0.0f;
		rx.m[1][0] = 0.0f; rx.m[1][1] = cosf(radianX);	rx.m[1][2] = -sinf(radianX);	rx.m[1][3] = 0.0f;
		rx.m[2][0] = 0.0f; rx.m[2][1] = sinf(radianX);	rx.m[2][2] = cosf(radianX);		rx.m[2][3] = 0.0f;
		rx.m[3][0] = 0.0f; rx.m[3][1] = 0.0f;			rx.m[3][2] = 0.0f;				rx.m[3][3] = 1.0f;

		ry.m[0][0] = cosf(radianY);	ry.m[0][1] = 0.0f; ry.m[0][2] = -sinf(radianY);	ry.m[0][3] = 0.0f;
		ry.m[1][0] = 0.0f;			ry.m[1][1] = 1.0f; ry.m[1][2] = 0.0f;			ry.m[1][3] = 0.0f;
		ry.m[2][0] = sinf(radianY);	ry.m[2][1] = 0.0f; ry.m[2][2] = cosf(radianY);	ry.m[2][3] = 0.0f;
		ry.m[3][0] = 0.0f;			ry.m[3][1] = 0.0f; ry.m[3][2] = 0.0f;			ry.m[3][3] = 1.0f;

		rz.m[0][0] = cosf(radianZ);	rz.m[0][1] = -sinf(radianZ);	rz.m[0][2] = 0.0f; rz.m[0][3] = 0.0f;
		rz.m[1][0] = sinf(radianZ);	rz.m[1][1] = cosf(radianZ);		rz.m[1][2] = 0.0f; rz.m[1][3] = 0.0f;
		rz.m[2][0] = 0.0f;			rz.m[2][1] = 0.0f;				rz.m[2][2] = 1.0f; rz.m[2][3] = 0.0f;
		rz.m[3][0] = 0.0f;			rz.m[3][1] = 0.0f;				rz.m[3][2] = 0.0f; rz.m[3][3] = 1.0f;

		*this = rz * ry * rx;
	}
	void translation(float x, float y, float z)
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = x;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = y;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = z;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	}
};

#endif //MATF4_H