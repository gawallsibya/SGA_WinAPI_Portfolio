#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_jump_ready
void remiliaState_jump_ready::enter(remilia* pCha)
{
	pCha->setVelocityY(-800.f);

	pCha->setImage(IMAGEMANAGER->findImage("remilia_jump"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_jump_ready")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_jump_ready"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.05f);
	pCha->isArrStateInfo()[remilia::SI_JUMP] = true;
	pCha->getAnimation()->start();
}
void remiliaState_jump_ready::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay() || !pCha->isArrStateInfo()[remilia::SI_JUMP])
	{
		pCha->changeState(new remiliaState_jump_start);
		return;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		pCha->moveTo(pCha->getSpeed() * TIMEMANAGER->getElapsedTime(), 0.f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		pCha->moveTo(-(pCha->getSpeed() * TIMEMANAGER->getElapsedTime()), 0.f);
	}
}
void remiliaState_jump_ready::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_JUMP] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_jump_start
void remiliaState_jump_start::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_jump"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_jump_start")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_jump_start"));
	pCha->isArrStateInfo()[remilia::SI_JUMP] = true;
	pCha->getAnimation()->start();
}
void remiliaState_jump_start::execute(remilia* pCha)
{
	if (pCha->getVelocityY() == 0.f)
	{
		pCha->changeState(new remiliaState_jump_end);
		return;
	}
	
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		pCha->moveTo(pCha->getSpeed() * TIMEMANAGER->getElapsedTime(), 0.f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		pCha->moveTo(-(pCha->getSpeed() * TIMEMANAGER->getElapsedTime()), 0.f);
	}



}
void remiliaState_jump_start::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_JUMP] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_jump_end
void remiliaState_jump_end::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_jump"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_jump_end")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_jump_end"));
	pCha->isArrStateInfo()[remilia::SI_JUMP] = true;
	pCha->getAnimation()->start();
}
void remiliaState_jump_end::execute(remilia* pCha)
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
		pCha->changeState(new remiliaState_idle);
		return;
	}
}
void remiliaState_jump_end::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_JUMP] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======