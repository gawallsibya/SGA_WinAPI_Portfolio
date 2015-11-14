#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_stand_up_forward_ready
void remiliaState_stand_up_forward_ready::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_stand_up_back"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_stand_up_back_ready")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_stand_up_back_ready"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.2f);
	pCha->isArrStateInfo()[remilia::SI_HITDOWN] = true;
	pCha->getAnimation()->start();
}
void remiliaState_stand_up_forward_ready::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_stand_up_forward_start);
		return;
	}
}
void remiliaState_stand_up_forward_ready::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_HITDOWN] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_stand_up_forward_start
void remiliaState_stand_up_forward_start::enter(remilia* pCha)
{
	pCha->setVelocityY(-300.f);

	pCha->setImage(IMAGEMANAGER->findImage("remilia_stand_up_back"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_stand_up_back_start")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_stand_up_back_start"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.4f);
	pCha->isArrStateInfo()[remilia::SI_HITDOWN] = true;
	pCha->getAnimation()->start();
}
void remiliaState_stand_up_forward_start::execute(remilia* pCha)
{
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->moveTo(-100.f * TIMEMANAGER->getElapsedTime(), 0.f) :
		pCha->moveTo(100.f * TIMEMANAGER->getElapsedTime(), 0.f);

	if (pCha->getVelocityY() == 0.f)
	{
		pCha->changeState(new remiliaState_idle);
		return;
	}
	
}
void remiliaState_stand_up_forward_start::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_HITDOWN] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======