#include "stdafx.h"
#include "snakeState.h"
#include "snake.h"

//====== snakeState_idle
void snakeState_idle::enter(snake* pCha)
{
	//pCha->setPivot(0.5f, 0.95f);

	pCha->setImage(IMAGEMANAGER->findImage("snake_idle"));
	pCha->getWay() == snake::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_snake_idle")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_snake_idle"));
	pCha->isArrStateInfo()[snake::SI_IDLE] = true;
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.8f);
	pCha->getAnimation()->start();

	pCha->releaseDamagedRects();
	pCha->addDamagedRects(pCha->getPos().x, pCha->getPos().y, 133.f, 99.f, 0.5f, pCha->getPivot().y);
	pCha->setBoundingRect(133.f, 99.f);
}
void snakeState_idle::execute(snake* pCha)
{
	if (pCha->isAttackMode())
	{
		MYRECT mrt;
		if (isCollisionRect(&mrt, *pCha->getBoundingRect(), *pCha->getTargetMemoryAddressLink()->getBoundingRect()))
		{
			if (pCha->getAttackTimer() <= 0.f)
			{
				pCha->getTargetMemoryAddressLink()->getPos().x < pCha->getPos().x ?
					pCha->setWay(snake::WAY_LEFT) : pCha->setWay(snake::WAY_RIGHT);

				pCha->setAttackTimer(0.5f);
				pCha->changeState(new snakeState_attack_ready);
				return;
			}
		}
		else if (pCha->getTargetMemoryAddressLink()->getMinX() <= pCha->getMaxX() &&
			pCha->getTargetMemoryAddressLink()->getMaxX() >= pCha->getMinX())
		{
			if (!pCha->getAnimation()->isPlay())
			{
				pCha->changeState(new snakeState_idle);
				return;
			}
		}
		else
		{
			pCha->changeState(new snakeState_walk_forward);
			return;
		}
	}
	
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new snakeState_idle);
		return;
	}
}
void snakeState_idle::exit(snake* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[snake::SI_IDLE] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======