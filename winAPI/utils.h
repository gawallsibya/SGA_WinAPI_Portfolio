#pragma once
#include "myRect.h"
#include <cmath>

#define DEG_TO_RAD 0.017453F //degree 1�� (���� ��)
#define PI 3.1415902654f
#define PI2 (PI * 2)

#define FLOAT_EPSILON 0.001f
#define FLOAT_TO_INT(f1) static_cast<int>(f1 + FLOAT_EPSILON) //�Ǽ����� ���������� ��ȯ�Ѵ�
#define FLOAT_EQUAL(f1, f2) (fabs(f1, f2) <= FLOAT_EPSILON) //�� �Ǽ��� ����?

namespace MY_UTIL
{
	//���������� ���������� ���� �������� ���Ѵ�
	float getAngle(float startX, float startY, float endX, float endY);
	
	//�� �� ������ �Ÿ��� ���Ѵ�
	float getDistance(float startX, float startY, float endX, float endY);

	//��� ������
	float getParabolaY(float x, float elasticity);

	//������ ����, �ð��� ���� ���� �Ÿ�
	float fallingDistance(float velocityY, float gravity, float time);	


}


