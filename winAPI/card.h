#pragma once
#include "myRect.h"

class card : public myRect
{
public:
	card();
	~card();

	void init(string imageName, float x, float y, float width, float height, float maxSp, float* targetSp);
	void update();
	void render(HDC hdc);
	void release();

private:
	image* _card;
	image* _blind;
	image* _aura;
	
	animation* _auraAni;

	float _maxSp;
	float* _targetSp;

	float _targetSpHeight;

	bool _bOnAura;
};

