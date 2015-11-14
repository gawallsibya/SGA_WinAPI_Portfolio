#include "stdafx.h"
#include "stage_1.h"
#include "remilia.h"
#include "stage_2.h"

stage_1::stage_1()
{
}


stage_1::~stage_1()
{
}

void stage_1::init()
{
	IMAGEMANAGER->addImage("bg_stage_1", "ImageResource/bg_stage_1.bmp", 2846, 1287, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bg_stage_1_collision", "ImageResource/bg_stage_1_collision.bmp", 2846, 1287, false, RGB(255, 0, 255));
	_bg = IMAGEMANAGER->findImage("bg_stage_1");
	_bg_collision = IMAGEMANAGER->findImage("bg_stage_1_collision");

	this->setPos(0.f, (float)WINSIZEY);
	this->setSize((float)(_bg->getWidth()), (float)(_bg->getHeight()));
	this->setPivot(0.0f, 1.f);

	_groundY = WINSIZEY - 78.f;

	_nextStagePortal = new portal;
	_nextStagePortal->init(this->getMaxX(), this->getMaxY() - 112.f, 1.f, 1.f, new stage_2);
	
	_remi = remilia::getSingleton();
	_remi->moveFrom(100.f, _groundY);
	_remi->changeState(new remiliaState_idle);
	_remi->setStageMemoryAddressLink(this);

	ENEMYMANAGER->init();

	CAMERAMANAGER->init(this->getMinX(), this->getMinY(), this->getMaxX(), this->getMaxY());
	CAMERAMANAGER->setTargetAddressLink(_remi);

	snake* minion_snake = new snake;
	minion_snake->init(snake::WAY_LEFT, 1000.f, _groundY);
	minion_snake->setTargetMemoryAddressLink(_remi);
	minion_snake->setStageMemoryAddressLink(this);

	ENEMYMANAGER->addEnemy(minion_snake);
	minion_snake->setMyIterator(ENEMYMANAGER->_lEnemyList.end());

	minion_snake = new snake;
	minion_snake->init(snake::WAY_LEFT, 1200.f, _groundY);
	minion_snake->setTargetMemoryAddressLink(_remi);
	minion_snake->setStageMemoryAddressLink(this);

	ENEMYMANAGER->addEnemy(minion_snake);
	minion_snake->setMyIterator(ENEMYMANAGER->_lEnemyList.end());

	minion_snake = new snake;
	minion_snake->init(snake::WAY_LEFT, 1500.f, _groundY);
	minion_snake->setTargetMemoryAddressLink(_remi);
	minion_snake->setStageMemoryAddressLink(this);

	ENEMYMANAGER->addEnemy(minion_snake);
	minion_snake->setMyIterator(ENEMYMANAGER->_lEnemyList.end());

	minion_snake = new snake;
	minion_snake->init(snake::WAY_LEFT, 1700.f, _groundY);
	minion_snake->setTargetMemoryAddressLink(_remi);
	minion_snake->setStageMemoryAddressLink(this);

	ENEMYMANAGER->addEnemy(minion_snake);
	minion_snake->setMyIterator(ENEMYMANAGER->_lEnemyList.end());

	minion_snake = new snake;
	minion_snake->init(snake::WAY_LEFT, 1900.f, _groundY);
	minion_snake->setTargetMemoryAddressLink(_remi);
	minion_snake->setStageMemoryAddressLink(this);

	ENEMYMANAGER->addEnemy(minion_snake);
	minion_snake->setMyIterator(ENEMYMANAGER->_lEnemyList.end());

	minion_snake = new snake;
	minion_snake->init(snake::WAY_LEFT, 2000.f, _groundY);
	minion_snake->setTargetMemoryAddressLink(_remi);
	minion_snake->setStageMemoryAddressLink(this);

	ENEMYMANAGER->addEnemy(minion_snake);
	minion_snake->setMyIterator(ENEMYMANAGER->_lEnemyList.end());

	minion_snake = new snake;
	minion_snake->init(snake::WAY_LEFT, 2300.f, _groundY);
	minion_snake->setTargetMemoryAddressLink(_remi);
	minion_snake->setStageMemoryAddressLink(this);

	ENEMYMANAGER->addEnemy(minion_snake);
	minion_snake->setMyIterator(ENEMYMANAGER->_lEnemyList.end());

	minion_snake = new snake;
	minion_snake->init(snake::WAY_LEFT, 2600.f, _groundY);
	minion_snake->setTargetMemoryAddressLink(_remi);
	minion_snake->setStageMemoryAddressLink(this);

	ENEMYMANAGER->addEnemy(minion_snake);
	minion_snake->setMyIterator(ENEMYMANAGER->_lEnemyList.end());

	_blindImg = IMAGEMANAGER->findImage("stage_blind_black");
	_blindAlpha = 255.f;
}

void stage_1::update()
{
	if (_blindAlpha > 0.f) _blindAlpha -= 3.f;
	else _blindAlpha = 0.f;
	
	_remi->update();
	ENEMYMANAGER->update();
	_nextStagePortal->update();
}

void stage_1::render(HDC hdc)
{
	POINT cameraPos = { 0, WINSIZEY - _bg->getHeight() };
	cameraPos = CAMERAMANAGER->ConvertWorldToScreenPos(&cameraPos);
	_bg->render(hdc, cameraPos.x, cameraPos.y);

	_nextStagePortal->render(hdc);

	ENEMYMANAGER->render(hdc);
	_remi->render(hdc);
	
	if (_blindAlpha != 0.f) _blindImg->alphaRender(hdc, 0, 0, 0, 0, WINSIZEX, WINSIZEY, false, (BYTE)_blindAlpha, false);
}