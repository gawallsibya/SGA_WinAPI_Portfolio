#include "stdafx.h"
#include "blueBoogieState.h"
#include "blueBoogie.h"

//====== blueBoogieState_hit_forward
void blueBoogieState_hit_forward::enter(blueBoogie* pCha)
{
	_deltaTime = 0.4f;
	pCha->setVelocityX(-150.f);

	pCha->setImage(IMAGEMANAGER->findImage("blueBoogie_hit_forward"));
	pCha->getWay() == blueBoogie::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_blueBoogie_hit_forward")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_blueBoogie_hit_forward"));

	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.5f);
	pCha->isArrStateInfo()[blueBoogie::SI_HIT] = true;

	pCha->releaseDamagedRects();
	pCha->addDamagedRects(pCha->getPos().x, pCha->getPos().y, 54.f, 86.f, pCha->getPivot().x, pCha->getPivot().y);

	pCha->getAnimation()->start();
}
void blueBoogieState_hit_forward::execute(blueBoogie* pCha)
{
	if (pCha->getVelocityX() <= 0.f)
	{
		pCha->setVelocityY(10.f);

		pCha->getTargetMemoryAddressLink()->getPos().x >= pCha->getPos().x ?
			pCha->calcKnockBackRight() : pCha->calcKnockBackLeft();
	}

	if (pCha->getVelocityY() == 0.f)
	{
		if (_deltaTime <= 0.f)
		{
			pCha->changeState(new blueBoogieState_idle);
			return;
		}
	}

	_deltaTime -= TIMEMANAGER->getElapsedTime();

}
void blueBoogieState_hit_forward::exit(blueBoogie* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[blueBoogie::SI_HIT] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======