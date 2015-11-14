#include "stdafx.h"
#include "blueBoogieState.h"
#include "blueBoogie.h"

//====== blueBoogieState_idle
void blueBoogieState_idle::enter(blueBoogie* pCha)
{
	//pCha->setPivot(0.5f, 0.95f);

	pCha->setImage(IMAGEMANAGER->findImage("blueBoogie_idle"));
	pCha->getWay() == blueBoogie::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_blueBoogie_idle")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_blueBoogie_idle"));
	pCha->isArrStateInfo()[blueBoogie::SI_IDLE] = true;
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.8f);
	pCha->getAnimation()->start();

	pCha->releaseDamagedRects();
	pCha->addDamagedRects(pCha->getPos().x, pCha->getPos().y, 54.f, 86.f, pCha->getPivot().x, pCha->getPivot().y);
	pCha->setBoundingRect(54.f, 86.f);
}
void blueBoogieState_idle::execute(blueBoogie* pCha)
{
	if (pCha->isAttackMode())
	{
		MYRECT mrt;
		if (isCollisionRect(&mrt, *pCha->getBoundingRect(), *pCha->getTargetMemoryAddressLink()->getBoundingRect()))
		{
			if (pCha->getAttackTimer() <= 0.f)
			{
				pCha->getTargetMemoryAddressLink()->getPos().x < pCha->getPos().x ?
					pCha->setWay(blueBoogie::WAY_LEFT) : pCha->setWay(blueBoogie::WAY_RIGHT);

				pCha->setAttackTimer(0.5f);
				pCha->changeState(new blueBoogieState_attack_ready1);
				return;
			}
		}
		else if (pCha->getTargetMemoryAddressLink()->getMinX() <= pCha->getMaxX() &&
			pCha->getTargetMemoryAddressLink()->getMaxX() >= pCha->getMinX())
		{
			if (!pCha->getAnimation()->isPlay())
			{
				pCha->changeState(new blueBoogieState_idle);
				return;
			}
		}
		else
		{
			pCha->changeState(new blueBoogieState_walk_forward);
			return;
		}
	}
	
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new blueBoogieState_idle);
		return;
	}
}
void blueBoogieState_idle::exit(blueBoogie* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[blueBoogie::SI_IDLE] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======