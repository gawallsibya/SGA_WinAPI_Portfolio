#include "stdafx.h"
#include "blueBoogieState.h"
#include "blueBoogie.h"

//====== blueBoogieState_walk_forward
void blueBoogieState_walk_forward::enter(blueBoogie* pCha)
{
	_movingTime = RND->getFromFloatTo(1.f, 2.f);

	pCha->setImage(IMAGEMANAGER->findImage("blueBoogie_walk_forward"));
	pCha->getWay() == blueBoogie::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_blueBoogie_walk_forward")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_blueBoogie_walk_forward"));

	pCha->isArrStateInfo()[blueBoogie::SI_MOVE] = true;
	
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.5f);
	pCha->getAnimation()->start();
}
void blueBoogieState_walk_forward::execute(blueBoogie* pCha)
{
	pCha->getWay() == blueBoogie::WAY_RIGHT ?
		pCha->moveTo(pCha->getSpeed() * TIMEMANAGER->getElapsedTime(), 0.f) :
		pCha->moveTo(-(pCha->getSpeed() * TIMEMANAGER->getElapsedTime()), 0.f);

	if (pCha->isAttackMode())
	{
		pCha->getTargetMemoryAddressLink()->getPos().x < pCha->getPos().x ?
			pCha->setWay(blueBoogie::WAY_LEFT) : pCha->setWay(blueBoogie::WAY_RIGHT);
		
		MYRECT mrt;
		if (isCollisionRect(&mrt, *pCha->getBoundingRect(), *pCha->getTargetMemoryAddressLink()->getBoundingRect()))
		{
			pCha->changeState(new blueBoogieState_idle);
			return;
			
			if (!pCha->getAnimation()->isPlay())
			{
				pCha->changeState(new blueBoogieState_walk_forward);
				return;
			}
		}
		else
		{
			if (pCha->getTargetMemoryAddressLink()->getMinX() <= pCha->getMaxX() && 
				pCha->getTargetMemoryAddressLink()->getMaxX() >= pCha->getMinX())
			{
				pCha->changeState(new blueBoogieState_idle);
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
			pCha->changeState(new blueBoogieState_idle);
			return;
		}
	}
}
void blueBoogieState_walk_forward::exit(blueBoogie* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[blueBoogie::SI_MOVE] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======