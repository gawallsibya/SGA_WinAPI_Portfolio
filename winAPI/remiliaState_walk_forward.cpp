#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_walk_forward
void remiliaState_walk_forward::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_walk_forward"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_walk_forward")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_walk_forward"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.5f);
	pCha->isArrStateInfo()[remilia::SI_MOVE] = true;
	pCha->getAnimation()->start();
}
void remiliaState_walk_forward::execute(remilia* pCha)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		pCha->moveTo(pCha->getSpeed() * TIMEMANAGER->getElapsedTime(), 0.f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		pCha->moveTo(-(pCha->getSpeed() * TIMEMANAGER->getElapsedTime()), 0.f);
	}
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_walk_forward);
		return;
	}
}
void remiliaState_walk_forward::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_MOVE] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======