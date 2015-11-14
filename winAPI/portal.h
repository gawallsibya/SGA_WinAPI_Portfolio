#pragma once
#include "object.h"

class portal : public object
{
public:
	portal();
	~portal();

	void init(float x, float y, float pivotX, float pivotY, stage* nextStage);
	void update();
	void render(HDC hdc);


private:
	stage* _nextStage;
	bool _bOnPortal;
};

