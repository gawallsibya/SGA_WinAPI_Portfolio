#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_hit_forward
void remiliaState_hit_forward::enter(remilia* pCha)
{
	_deltaTime = 0.4f;
	pCha->setVelocityX(-150.f);

	pCha->setImage(IMAGEMANAGER->findImage("remilia_hit_forward"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_hit_forward")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_hit_forward"));

	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.5f);
	pCha->isArrStateInfo()[remilia::SI_HITDOWN] = true;
	pCha->getAnimation()->start();
}
void remiliaState_hit_forward::execute(remilia* pCha)
{
	if (pCha->getVelocityX() <= 0.f)
	{
		pCha->setVelocityY(10.f);

		pCha->getWay() == remilia::WAY_RIGHT ?
			pCha->calcKnockBackRight() : pCha->calcKnockBackLeft();
	}
	
	if (pCha->getVelocityY() == 0.f)
	{
		if (_deltaTime <= 0.f)
		{
			pCha->changeState(new remiliaState_idle);
			return;
		}
	}
	
	_deltaTime -= TIMEMANAGER->getElapsedTime();
	
}
void remiliaState_hit_forward::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_HITDOWN] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======