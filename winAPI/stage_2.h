#pragma once
#include "stage.h"
#include "portal.h"

class remilia;
class stage_2 : public stage
{
public:
	stage_2();
	~stage_2();

	void init();
	void update();
	void render(HDC hdc);

private:
	float _groundY;

	remilia* _remi;
	enemyManager* _enemyMgr;

	portal* _nextStagePortal;

};

