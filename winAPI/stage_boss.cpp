#include "stdafx.h"
#include "stage_boss.h"
#include "remilia.h"
#include "ui_state.h"

stage_boss::stage_boss() : 
_groundY(0.f),
offsetX(0),
_fogImg(nullptr),
_remi(nullptr),
rt({}),
_enemyMgr(nullptr)
{
}


stage_boss::~stage_boss()
{
}

void stage_boss::init()
{
	_bg = IMAGEMANAGER->addImage("bg_stage_boss", "ImageResource/bg_stage_boss.bmp", 2100, 1875, false, RGB(255, 0, 255));
	_bg_collision = IMAGEMANAGER->addImage("bg_stage_boss_collision", "ImageResource/bg_stage_boss_collision.bmp", 2100, 1875, false, RGB(255, 0, 255));
	_fogImg = IMAGEMANAGER->addImage("bg_stage_boss_fog", "ImageResource/bg_stage_boss_fog.bmp", 2100, 1875, false, RGB(255, 0, 255));

	this->setPos(0.f, (float)WINSIZEY);
	this->setSize((float)(_bg->getWidth()), (float)(_bg->getHeight()));
	this->setPivot(0.f, 1.f);

	_groundY = WINSIZEY - 117.f;

	_remi = remilia::getSingleton();
	_remi->moveFrom(100.f, _groundY);
	_remi->changeState(new remiliaState_idle);
	_remi->setStageMemoryAddressLink(this);

	ENEMYMANAGER->init();

	CAMERAMANAGER->init(this->getMinX(), this->getMinY(), this->getMaxX(), this->getMaxY());
	CAMERAMANAGER->setTargetAddressLink(_remi);

	goldCatfish* goldCatfishBoss = new goldCatfish;
	goldCatfishBoss->init(goldCatfish::WAY_LEFT, 1200.f, _groundY);
	goldCatfishBoss->setTargetMemoryAddressLink(_remi);
	goldCatfishBoss->setStageMemoryAddressLink(this);
	//ui_state::getSingleton()->setBossMemoryAddressLink(goldCatfishBoss);

	ENEMYMANAGER->addEnemy(goldCatfishBoss);
	goldCatfishBoss->setMyIterator(ENEMYMANAGER->_lEnemyList.end());
	
	_blindImg = IMAGEMANAGER->findImage("stage_blind_black");
	_blindAlpha = 255;
}

void stage_boss::update()
{
	if (_blindAlpha > 0.f) _blindAlpha -= 3.f;
	else _blindAlpha = 0.f;

	_remi->update();
	ENEMYMANAGER->update();

	rt = { (int)this->getMinX(), (int)this->getMinY(), (int)this->getMaxX(), (int)this->getMaxY() };
	offsetX += 150 * TIMEMANAGER->getElapsedTime();
	if ((int)offsetX % _fogImg->getWidth() == 0) offsetX = 0;

	// 보스방의 모든 적이 죽으면 클리어
	if (ENEMYMANAGER->_lEnemyList.size() == 0) SCENEMANAGER->changeScene("clearScene");
}

void stage_boss::render(HDC hdc)
{
	POINT cameraPos = { 0, WINSIZEY - _bg->getHeight() };
	cameraPos = CAMERAMANAGER->ConvertWorldToScreenPos(&cameraPos);
	_bg->render(hdc, cameraPos.x, cameraPos.y);

	ENEMYMANAGER->render(hdc);
	_remi->render(hdc);

	_fogImg->loopAlphaRender(hdc, &rt, -(int)offsetX, 0, false, 180, true);

	if (_blindAlpha != 0) _blindImg->alphaRender(hdc, 0, 0, 0, 0, WINSIZEX, WINSIZEY, false, (BYTE)_blindAlpha, false);
	
}