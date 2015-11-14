#pragma once
#include "singletonBase.h"
#include "stage_boss.h"
#include "stage_1.h"

class stage;
class stageManager : public singletonBase<stageManager>
{
public:
	stageManager();
	~stageManager();

	void init();
	void update();
	void render(HDC hdc);
	void changeStage(stage* newStage);

private:
	stage* _curStage;
};

