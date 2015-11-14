#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_sit_start
void remiliaState_sit_start::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_sit"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_sit_start")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_sit_start"));
	pCha->getAnimation()->setFPS(pCha->getAnimation()->getMaxFrame() / 0.1f);
	pCha->isArrStateInfo()[remilia::SI_SIT] = true;
	pCha->getAnimation()->start();

	pCha->releaseDamagedRects();
	pCha->addDamagedRects(pCha->getPos().x, pCha->getPos().y, 45.f, 65.f, 0.5f, 1.0f);
	pCha->setBoundingRect(45.f, 65.f);
}
void remiliaState_sit_start::execute(remilia* pCha)
{
	if (!KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		pCha->changeState(new remiliaState_sit_end);
	}
}
void remiliaState_sit_start::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_SIT] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_sit_end
void remiliaState_sit_end::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_sit"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_sit_end")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_sit_end"));
	pCha->getAnimation()->setFPS(pCha->getAnimation()->getMaxFrame() / 0.1f);
	pCha->isArrStateInfo()[remilia::SI_SIT] = true;
	pCha->getAnimation()->start();

	pCha->releaseDamagedRects();
	pCha->addDamagedRects(pCha->getPos().x, pCha->getPos().y, 45.f, 85.f, 0.5f, 1.0f);
	pCha->setBoundingRect(45.f, 85.f);
}
void remiliaState_sit_end::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_idle);
	}
}
void remiliaState_sit_end::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_SIT] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======