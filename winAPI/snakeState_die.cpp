#include "stdafx.h"
#include "snakeState.h"
#include "snake.h"

//====== snakeState_die
void snakeState_die::enter(snake* pCha)
{
	_bMoveStop = false;
	pCha->setVelocityY(-100.f);
	pCha->setImage(IMAGEMANAGER->findImage("snake_die"));
	pCha->getWay() == snake::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_snake_die")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_snake_die"));

	pCha->isArrStateInfo()[snake::SI_DIE] = true;
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 1.0f);
	pCha->getAnimation()->start();

	pCha->releaseDamagedRects();
}
void snakeState_die::execute(snake* pCha)
{
	if (!_bMoveStop)
	{
		pCha->calcGravity();

		pCha->getWay() == snake::WAY_RIGHT ?
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
void snakeState_die::exit(snake* pCha)
{
	pCha->setLife(false);
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[snake::SI_DIE] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======