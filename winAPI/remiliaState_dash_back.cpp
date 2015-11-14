#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_dash_back_ready
void remiliaState_dash_back_ready::enter(remilia* pCha)
{
	pCha->releaseDamagedRects();

	pCha->setImage(IMAGEMANAGER->findImage("remilia_dash_back"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_dash_back_ready")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_dash_back_ready"));
	pCha->isArrStateInfo()[remilia::SI_DASH] = true;
	pCha->getAnimation()->start();
}
void remiliaState_dash_back_ready::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_dash_back_start);
		return;
	}
}
void remiliaState_dash_back_ready::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_DASH] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_dash_back_start
void remiliaState_dash_back_start::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_dash_back"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_dash_back_start")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_dash_back_start"));
	pCha->isArrStateInfo()[remilia::SI_DASH] = true;
	pCha->getAnimation()->start();
}
void remiliaState_dash_back_start::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_dash_back_end);
		return;
	}
	if (pCha->getWay() == remilia::WAY_RIGHT)
	{
		pCha->moveTo(-(pCha->getSpeed() * 3.5f * TIMEMANAGER->getElapsedTime()), 0.f);
	}
	else
	{
		pCha->moveTo(pCha->getSpeed() * 3.5f * TIMEMANAGER->getElapsedTime(), 0.f);
	}
}
void remiliaState_dash_back_start::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_DASH] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_dash_back_end
void remiliaState_dash_back_end::enter(remilia* pCha)
{
	pCha->addDamagedRects(pCha->getPos().x, pCha->getPos().y, 45.f, 85.f, 0.5f, 1.0f);

	pCha->setImage(IMAGEMANAGER->findImage("remilia_dash_back"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_dash_back_end")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_dash_back_end"));
	pCha->isArrStateInfo()[remilia::SI_DASH] = true;
	pCha->getAnimation()->start();
}
void remiliaState_dash_back_end::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_idle);
		return;
	}
}
void remiliaState_dash_back_end::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_DASH] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======