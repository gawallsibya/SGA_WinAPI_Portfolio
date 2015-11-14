#include "stdafx.h"
#include "snakeState.h"
#include "snake.h"

//====== snakeState_attack_ready
void snakeState_attack_ready::enter(snake* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("snake_attack"));

	pCha->getWay() == snake::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_snake_attack_ready")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_snake_attack_ready"));
	
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.3f);
	pCha->isArrStateInfo()[snake::SI_ATTACK] = true;
	pCha->getAnimation()->start();
}
void snakeState_attack_ready::execute(snake* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new snakeState_attack_start);
	}
}
void snakeState_attack_ready::exit(snake* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[snake::SI_ATTACK] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== snakeState_attack_start
void snakeState_attack_start::enter(snake* pCha)
{
	_damage = 20.f;
	_dlayTime = 0.3f;
	pCha->setImage(IMAGEMANAGER->findImage("snake_attack"));

	if (pCha->getWay() == snake::WAY_RIGHT)
	{
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_snake_attack_start"));
		pCha->releaseDamagedRects();
		pCha->addDamagedRects(pCha->getPos().x, pCha->getPos().y, 268.f, 74.f, 0.25f, pCha->getPivot().y);
	}
	else
	{
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_snake_attack_start"));
		pCha->releaseDamagedRects();
		pCha->addDamagedRects(pCha->getPos().x, pCha->getPos().y, 268.f, 74.f, 0.75f, pCha->getPivot().y);
	}
	
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.1f);
	pCha->isArrStateInfo()[snake::SI_ATTACK] = true;
	pCha->getAnimation()->start();
}
void snakeState_attack_start::execute(snake* pCha)
{
	if (_dlayTime <= 0.f)
	{
		pCha->changeState(new snakeState_attack_end);
		return;
	}
	else
	{
		_dlayTime -= TIMEMANAGER->getElapsedTime();
	}

	if (!pCha->getAnimation()->isPlay())
	{
		pCha->getWay() == snake::WAY_RIGHT ?
		pCha->addAttackRects(pCha->getPos().x + 20, pCha->getPos().y, 177.f, 74.f, 0.f, 1.0f) : 
		pCha->addAttackRects(pCha->getPos().x - 20, pCha->getPos().y, 177.f, 74.f, 1.f, 1.0f);

		pCha->attackToTarget(pCha->getAttackRects(), _damage);
	}
}
void snakeState_attack_start::exit(snake* pCha)
{
	pCha->getTargetMemoryAddressLink()->releaseDamagedFromObjectAdress(pCha->getAttackRects());
	pCha->releaseAttackRects();

	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[snake::SI_ATTACK] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== snakeState_attack_end
void snakeState_attack_end::enter(snake* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("snake_attack"));
	pCha->getWay() == snake::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_snake_attack_end")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_snake_attack_end"));

	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.1f);
	pCha->isArrStateInfo()[snake::SI_ATTACK] = true;
	pCha->getAnimation()->start();
}
void snakeState_attack_end::execute(snake* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new snakeState_idle);
	}
}
void snakeState_attack_end::exit(snake* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[snake::SI_ATTACK] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======