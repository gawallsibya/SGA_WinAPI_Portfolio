#include "stdafx.h"
#include "utils.h"

namespace MY_UTIL
{
	//시작점부터 끝점까지의 각을 라디안으로 구한다...
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		float d = sqrtf(x * x + y * y);
		float angle = acos(x / d);
		if (y > 0) angle = PI2 - angle;

		return angle;
	}

	//두 점 사이의 거리 구한다
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	//곡선의 방정식
	float getParabolaY(float x, float elasticity)
	{
		float VERT_X = 1.0f;
		float VERT_Y = 1.0f * elasticity;

		float a = VERT_Y / (-VERT_X * -VERT_X);
		float y = a *((x - VERT_X)*(x - VERT_X)) - VERT_Y;
		return y;
	}

	


}

