#pragma once
#include "stage.h"
#include "portal.h"

class remilia;
class stage_1 : public stage
{
public:
	stage_1();
	~stage_1();

	void init();
	void update();
	void render(HDC hdc);

private:
	float _groundY;
	
	remilia* _remi;
	enemyManager* _enemyMgr;

	portal* _nextStagePortal;

};

