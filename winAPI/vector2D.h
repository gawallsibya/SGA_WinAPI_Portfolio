#pragma once
#include <cmath>

typedef class vector2D
{
public:
	inline vector2D() : x(0.f), y(0.f) {}

	inline vector2D(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	// 없어질때 알아서 초기화
	inline ~vector2D() 
	{
		x = 0.f;
		y = 0.f;
	}

	inline vector2D operator+(const vector2D& vec) const
	{
		return vector2D(x + vec.x, y + vec.y);
	}
	inline vector2D operator-(const vector2D& vec) const
	{
		return vector2D(x - vec.x, y - vec.y);
	}
	inline vector2D operator*(float val) const
	{
		return vector2D(x *val, y*val);
	}

	inline void Normalize()
	{
		float len = sqrtf(x*x + y*y);

		if (len <= 0.f)
		{
			x = 0;
			y = 0;
		}
		else
		{
			x = x / len;
			y = y / len;
		}
	}


public:
	float x;
	float y;

}VECTOR2D;

const vector2D vLeft(-1.f, 0.f);
const vector2D vRight(1, 0);
const vector2D vUp(0, -1);
const vector2D vDown(0, 1);