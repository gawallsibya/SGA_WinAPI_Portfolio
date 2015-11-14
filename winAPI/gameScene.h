#pragma once
#include "gameNode.h"

class remilia;
class enemyManager;
class ui_state;
class stageManager;
class gameScene : public gameNode
{
public:
	gameScene();
	~gameScene();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);



private:
	image* _bg;
	remilia* _remi;
	enemyManager* _enemyMgr;
	ui_state* _ui_state;

	stageManager* _stageMgr;

};

