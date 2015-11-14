#include "stdafx.h"
#include "gameScene.h"
#include "remilia.h"
#include "ui_state.h"
#include "stageManager.h"

gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}

HRESULT gameScene::init(void)
{
	EFFECTMANAGER->init();

	_remi = remilia::getSingleton();
	_remi->init();

	_stageMgr = stageManager::getSingleton();
	_stageMgr->changeStage(new stage_1);

	_ui_state = ui_state::getSingleton();
	_ui_state->init(_remi);

	return S_OK;
}

void gameScene::release(void)
{
}

//�������� �ϴ� �ڵ��...
void gameScene::update(void)
{
	_stageMgr->update();
	_ui_state->update();
	EFFECTMANAGER->update();
}

void gameScene::render(void)
{
	//Ÿ�ӸŴ��� ����
	//TIMEMANAGER->render(getMemDC());
	
	_stageMgr->render(getMemDC());

	EFFECTMANAGER->render();

	_ui_state->render(getMemDC());

	this->getBackBuffer()->render(getHDC(), 0, 0);
}

