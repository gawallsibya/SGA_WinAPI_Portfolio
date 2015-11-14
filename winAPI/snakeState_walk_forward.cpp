#include "stdafx.h"
#include "snakeState.h"
#include "snake.h"

//====== snakeState_walk_forward
void snakeState_walk_forward::enter(snake* pCha)
{
	_movingTime = RND->getFromFloatTo(1.f, 2.f);

	pCha->setImage(IMAGEMANAGER->findImage("snake_walk_forward"));
	pCha->getWay() == snake::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_snake_walk_forward")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_snake_walk_forward"));

	pCha->isArrStateInfo()[snake::SI_MOVE] = true;
	
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.5f);
	pCha->getAnimation()->start();
}
void snakeState_walk_forward::execute(snake* pCha)
{
	pCha->getWay() == snake::WAY_RIGHT ?
		pCha->moveTo(pCha->getSpeed() * TIMEMANAGER->getElapsedTime(), 0.f) :
		pCha->moveTo(-(pCha->getSpeed() * TIMEMANAGER->getElapsedTime()), 0.f);

	if (pCha->isAttackMode())
	{
		pCha->getTargetMemoryAddressLink()->getPos().x < pCha->getPos().x ?
			pCha->setWay(snake::WAY_LEFT) : pCha->setWay(snake::WAY_RIGHT);
		
		MYRECT mrt;
		if (isCollisionRect(&mrt, *pCha->getBoundingRect(), *pCha->getTargetMemoryAddressLink()->getBoundingRect()))
		{
			pCha->changeState(new snakeState_idle);
			return;
			
			if (!pCha->getAnimation()->isPlay())
			{
				pCha->changeState(new snakeState_walk_forward);
				return;
			}
		}
		else
		{
			if (pCha->getTargetMemoryAddressLink()->getMinX() <= pCha->getMaxX() && 
				pCha->getTargetMemoryAddressLink()->getMaxX() >= pCha->getMinX())
			{
				pCha->changeState(new snakeState_idle);
				return;
			}
		}
	}
	// 비 전투모드일때..
	else
	{
		if (_movingTime > 0.f)
		{
			_movingTime -= TIMEMANAGER->getElapsedTime();
		}
		else
		{
			_movingTime = RND->getFromFloatTo(1.f, 3.f);
			pCha->changeState(new snakeState_idle);
			return;
		}
	}
}
void snakeState_walk_forward::exit(snake* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[snake::SI_MOVE] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======