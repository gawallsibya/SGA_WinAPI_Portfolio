#include "stdafx.h"
#include "goldCatfishState.h"
#include "goldCatfish.h"

//====== goldCatfishState_idle
void goldCatfishState_idle::enter(goldCatfish* pCha)
{
	//pCha->setPivot(0.5f, 0.95f);

	pCha->setImage(IMAGEMANAGER->findImage("goldCatfish_idle"));
	pCha->getWay() == goldCatfish::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_goldCatfish_idle")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_goldCatfish_idle"));
	pCha->isArrStateInfo()[goldCatfish::SI_IDLE] = true;
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 10.f);
	pCha->getAnimation()->start();

	pCha->releaseDamagedRects();
	pCha->addDamagedRects(pCha->getPos().x, pCha->getPos().y, 533.f, 320.f, 0.5f, pCha->getPivot().y);
	pCha->setBoundingRect(533.f, 320.f);
}
void goldCatfishState_idle::execute(goldCatfish* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new goldCatfishState_idle);
		return;
	}
}
void goldCatfishState_idle::exit(goldCatfish* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[goldCatfish::SI_IDLE] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======