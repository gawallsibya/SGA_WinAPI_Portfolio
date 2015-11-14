#include "stdafx.h"
#include "utils.h"

namespace MY_UTIL
{
	//���������� ���������� ���� �������� ���Ѵ�...
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		float d = sqrtf(x * x + y * y);
		float angle = acos(x / d);
		if (y > 0) angle = PI2 - angle;

		return angle;
	}

	//�� �� ������ �Ÿ� ���Ѵ�
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	//��� ������
	float getParabolaY(float x, float elasticity)
	{
		float VERT_X = 1.0f;
		float VERT_Y = 1.0f * elasticity;

		float a = VERT_Y / (-VERT_X * -VERT_X);
		float y = a *((x - VERT_X)*(x - VERT_X)) - VERT_Y;
		return y;
	}

	


}

