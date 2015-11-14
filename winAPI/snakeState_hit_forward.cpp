#include "stdafx.h"
#include "snakeState.h"
#include "snake.h"

//====== snakeState_hit_forward
void snakeState_hit_forward::enter(snake* pCha)
{
	_deltaTime = 0.4f;
	pCha->setVelocityX(-150.f);

	pCha->setImage(IMAGEMANAGER->findImage("snake_hit_forward"));
	pCha->getWay() == snake::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_snake_hit_forward")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_snake_hit_forward"));

	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.5f);
	pCha->isArrStateInfo()[snake::SI_HIT] = true;

	pCha->releaseDamagedRects();
	pCha->addDamagedRects(pCha->getPos().x, pCha->getPos().y, 133.f, 99.f, 0.5f, pCha->getPivot().y);

	pCha->getAnimation()->start();
}
void snakeState_hit_forward::execute(snake* pCha)
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
			pCha->changeState(new snakeState_idle);
			return;
		}
	}

	_deltaTime -= TIMEMANAGER->getElapsedTime();

}
void snakeState_hit_forward::exit(snake* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[snake::SI_HIT] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======