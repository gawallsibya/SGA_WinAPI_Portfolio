#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_idle
void remiliaState_idle::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_idle"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_idle")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_idle"));
	pCha->isArrStateInfo()[remilia::SI_IDLE] = true;
	pCha->getAnimation()->start();

	pCha->releaseDamagedRects();
	pCha->addDamagedRects(pCha->getPos().x, pCha->getPos().y, 45.f, 85.f, 0.5f, 1.0f);
	pCha->setBoundingRect(45.f, 85.f);
	
}
void remiliaState_idle::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_idle);
		return;
	}

}
void remiliaState_idle::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_IDLE] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======