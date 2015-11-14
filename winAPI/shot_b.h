#pragma once
#include "missile.h"
class shot_b : public missile
{
public:
	shot_b();
	~shot_b();

	virtual void init(character* master, float x, float y, VECTOR2D vMovePos, bool reverse);
	virtual void update();
	virtual void render(HDC hdc);
	virtual void release();

};

