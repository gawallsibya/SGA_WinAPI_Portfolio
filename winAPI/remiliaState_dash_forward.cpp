#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_dash_forward_ready
void remiliaState_dash_forward_ready::enter(remilia* pCha)
{
	pCha->releaseDamagedRects();

	pCha->setImage(IMAGEMANAGER->findImage("remilia_dash_forward"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_dash_forward_ready")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_dash_forward_ready"));
	pCha->isArrStateInfo()[remilia::SI_DASH] = true;
	pCha->getAnimation()->start();
}
void remiliaState_dash_forward_ready::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_dash_forward_start);
		return;
	}
}
void remiliaState_dash_forward_ready::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_DASH] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_dash_forward_start
void remiliaState_dash_forward_start::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_dash_forward"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_dash_forward_start")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_dash_forward_start"));
	pCha->isArrStateInfo()[remilia::SI_DASH] = true;
	pCha->getAnimation()->start();
}
void remiliaState_dash_forward_start::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_dash_forward_end);
		return;
	}

	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->moveTo(pCha->getSpeed() * 3.5f * TIMEMANAGER->getElapsedTime(), 0.f) :
		pCha->moveTo(-(pCha->getSpeed() * 3.5f * TIMEMANAGER->getElapsedTime()), 0.f);
}
void remiliaState_dash_forward_start::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_DASH] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_dash_forward_end
void remiliaState_dash_forward_end::enter(remilia* pCha)
{
	pCha->addDamagedRects(pCha->getPos().x, pCha->getPos().y, 45.f, 85.f, 0.5f, 1.0f);

	pCha->setImage(IMAGEMANAGER->findImage("remilia_dash_forward"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_dash_forward_end")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_dash_forward_end"));
	pCha->isArrStateInfo()[remilia::SI_DASH] = true;
	pCha->getAnimation()->start();
}
void remiliaState_dash_forward_end::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_idle);
		return;
	}

}
void remiliaState_dash_forward_end::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_DASH] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======