#include "stdafx.h"
#include "blueBoogieState.h"
#include "blueBoogie.h"

//====== blueBoogieState_die
void blueBoogieState_die::enter(blueBoogie* pCha)
{
	pCha->setVelocityY(-100.f);
	pCha->setImage(IMAGEMANAGER->findImage("blueBoogie_die"));
	pCha->getWay() == blueBoogie::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_blueBoogie_die")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_blueBoogie_die"));

	pCha->isArrStateInfo()[blueBoogie::SI_DIE] = true;
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.5f);
	pCha->getAnimation()->start();

	pCha->releaseDamagedRects();
}
void blueBoogieState_die::execute(blueBoogie* pCha)
{
	if (!_bMoveStop)
	{
		pCha->getWay() == blueBoogie::WAY_RIGHT ?
			pCha->moveTo(-500.f * TIMEMANAGER->getElapsedTime(), 0.f) :
			pCha->moveTo(500.f * TIMEMANAGER->getElapsedTime(), 0.f);
	}
	if (pCha->getVelocityY() == 0.f)
	{
		_bMoveStop = true;
	}

	if (!pCha->getAnimation()->isPlay())
	{
		pCha->setLife(false);
	}
}
void blueBoogieState_die::exit(blueBoogie* pCha)
{
	pCha->setLife(false);

	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[blueBoogie::SI_DIE] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======