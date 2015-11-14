#pragma once
#include "stage.h"

class remilia;
class stage_boss : public stage
{
public:
	stage_boss();
	~stage_boss();

	void init();
	void update();
	void render(HDC hdc);

private:
	float _groundY;

	double offsetX;
	image* _fogImg;

	remilia* _remi;
	RECT rt;
	enemyManager* _enemyMgr;
};

