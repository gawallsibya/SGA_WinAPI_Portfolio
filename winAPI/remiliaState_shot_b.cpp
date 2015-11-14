#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_shot_b_start
void remiliaState_shot_b_start::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_shot_b"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_shot_b_start")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_shot_b_start"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.3f);
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = true;
	pCha->getAnimation()->start();
}
void remiliaState_shot_b_start::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->fireShotB();
		pCha->changeState(new remiliaState_shot_b_end);
		return;
	}
}
void remiliaState_shot_b_start::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_shot_b_end
void remiliaState_shot_b_end::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_shot_b"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_shot_b_end")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_shot_b_end"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.8f);
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = true;
	pCha->getAnimation()->start();
}
void remiliaState_shot_b_end::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_idle);
		return;
	}
}
void remiliaState_shot_b_end::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======