#ifndef PACMATH_H
#define	PACMATH_H

#include "CommonMath.h"

struct VecI2
{
    int x;
    int y;
};

struct VecF2
{
	float x;
	float y;

	VecF2()
	{
		x = 0;
		y = 0;
	}

	VecF2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

struct VecF3
{
    float x;
    float y;
    float z;

    VecF3()
    {
    }
    VecF3(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

	VecF3& operator+=(const VecF3& r)
    {
        x += r.x;
        y += r.y;
        z += r.z;

        return *this;
    }
    VecF3& operator-=(const VecF3& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;

        return *this;
    }
    VecF3& operator*=(float f)
    {
        x *= f;
        y *= f;
        z *= f;

        return *this;
    }

	VecF3	cross(const VecF3& vec) const;
    VecF3&	normalize();
    void	rotate(float angle, const VecF3& axis);
	float	dot(VecF3 vec);
};
inline VecF3 operator+(const VecF3& left, const VecF3& right)
{
	VecF3 ret(
		left.x + right.x,
		left.y + right.y,
		left.z + right.z);
    return ret;
}
inline VecF3 operator-(const VecF3& left, const VecF3& right)
{
    VecF3 ret(
		left.x - right.x,
		left.y - right.y,
		left.z - right.z);
    return ret;
}
inline VecF3 operator*(const VecF3& left, float scalar)
{
    VecF3 ret(left.x * scalar,
                 left.y * scalar,
                 left.z * scalar);
    return ret;
}

class MatF4
{
public:
    float m[4][4];

    MatF4()
    {        
    }

    inline void identity()
    {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
    }

    inline MatF4 operator*(const MatF4& right) const
    {
		MatF4 ret;
        for (unsigned int i = 0 ; i < 4 ; i++) {
            for (unsigned int j = 0 ; j < 4 ; j++) {
				ret.m[i][j] = 
					m[i][0] * right.m[0][j] +
					m[i][1] * right.m[1][j] +
					m[i][2] * right.m[2][j] +
					m[i][3] * right.m[3][j];
            }
        }
        return ret;
    }

	void scaling(float x, float y, float z);
	void rotation(float x, float y, float z);
	void translation(float x, float y, float z);
};

struct Quaternion
{
    float x, y, z, w;

    Quaternion(float _x, float _y, float _z, float _w);

    void normalize();
    Quaternion conjugate();  
 };
Quaternion operator*(const Quaternion& left, const Quaternion& right);
Quaternion operator*(const Quaternion& quaternion, const VecF3& vec);

#endif //PACMATH_H

