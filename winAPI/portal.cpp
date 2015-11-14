#include "stdafx.h"
#include "portal.h"
#include "remilia.h"
#include "stageManager.h"

portal::portal()
{
}


portal::~portal()
{
}

void portal::init(float x, float y, float pivotX, float pivotY, stage* nextStage)
{
	this->setPos(x, y);
	this->setSize((float)IMAGEMANAGER->findImage("stage_portal_on")->getFrameWidth(), (float)IMAGEMANAGER->findImage("stage_portal_on")->getFrameHeight());
	this->setPivot(pivotX, pivotY);
	
	_bOnPortal = false;

	_bOnPortal ?
		_img = IMAGEMANAGER->findImage("stage_portal_on") :
		_img = IMAGEMANAGER->findImage("stage_portal_off");

	KEYANIMANAGER->addDefaultFrameAnimation("stage_portal", "stage_portal_on", 10, false, true);
	_ani = KEYANIMANAGER->findAnimation("stage_portal");
	_ani->setFPS((_ani->getMaxFrame() + 1) / 1.f);
	_ani->start();
	_nextStage = nextStage;
}

void portal::update()
{
	if (_bOnPortal)
	{
		MYRECT halfRt = *dynamic_cast<MYRECT*>(this);
		halfRt.setSize(halfRt.getSize().width * 0.5f, halfRt.getSize().height);

		MYRECT mrt;
		if (isCollisionRect(&mrt, *remilia::getSingleton()->getBoundingRect(), halfRt))
		{
			stageManager::getSingleton()->changeStage(_nextStage);
		}
	}

	if (ENEMYMANAGER->_lEnemyList.size() == 0)
	{
		_bOnPortal = true;
	}

	_bOnPortal ?
		_img = IMAGEMANAGER->findImage("stage_portal_on") :
		_img = IMAGEMANAGER->findImage("stage_portal_off");
}

void portal::render(HDC hdc)
{
	POINT cameraPos = { (int)this->getMinX(), (int)this->getMinY() };
	cameraPos = CAMERAMANAGER->ConvertWorldToScreenPos(&cameraPos);
	_img->aniAlphaRender(hdc, cameraPos.x, cameraPos.y, _ani, false, 255, true);
}