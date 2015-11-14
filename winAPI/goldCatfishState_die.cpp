#include "stdafx.h"
#include "goldCatfishState.h"
#include "goldCatfish.h"

//====== goldCatfishState_die
void goldCatfishState_die::enter(goldCatfish* pCha)
{
	_bMoveStop = false;
	_deltaTime = 5.f;
	pCha->setVelocityY(-100.f);
	pCha->setImage(IMAGEMANAGER->findImage("goldCatfish_die"));
	pCha->getWay() == goldCatfish::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_goldCatfish_die")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_goldCatfish_die"));
		
	pCha->isArrStateInfo()[goldCatfish::SI_DIE] = true;
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 5.f);
	pCha->getAnimation()->start();

	pCha->releaseDamagedRects();
}
void goldCatfishState_die::execute(goldCatfish* pCha)
{
	if (!_bMoveStop)
	{
		pCha->getWay() == goldCatfish::WAY_RIGHT ?
			pCha->moveTo(-500.f * TIMEMANAGER->getElapsedTime(), 0.f) :
			pCha->moveTo(500.f * TIMEMANAGER->getElapsedTime(), 0.f);
	}
	else
	{
		_deltaTime -= TIMEMANAGER->getElapsedTime();		
	}

	if (pCha->getVelocityY() == 0.f)
	{
		_bMoveStop = true;
	}
	
	

	if (_deltaTime <= 0.f)
	{
		pCha->setLife(false);
	}
}
void goldCatfishState_die::exit(goldCatfish* pCha)
{
	pCha->setLife(false);

	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[goldCatfish::SI_DIE] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======