#include "stdafx.h"
#include "blueBoogieState.h"
#include "blueBoogie.h"

//====== blueBoogieState_attack_ready1
void blueBoogieState_attack_ready1::enter(blueBoogie* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("blueBoogie_attack"));

	pCha->getWay() == blueBoogie::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_blueBoogie_attack_ready1")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_blueBoogie_attack_ready1"));
	
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.2f);
	pCha->isArrStateInfo()[blueBoogie::SI_ATTACK] = true;
	pCha->getAnimation()->start();
}
void blueBoogieState_attack_ready1::execute(blueBoogie* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new blueBoogieState_attack_start1);
	}
}
void blueBoogieState_attack_ready1::exit(blueBoogie* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[blueBoogie::SI_ATTACK] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== blueBoogieState_attack_start1
void blueBoogieState_attack_start1::enter(blueBoogie* pCha)
{
	_damage = 8.f;
	pCha->setImage(IMAGEMANAGER->findImage("blueBoogie_attack"));

	if (pCha->getWay() == blueBoogie::WAY_RIGHT)
	{
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_blueBoogie_attack_start1"));
	}
	else
	{
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_blueBoogie_attack_start1"));
	}
	
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.2f);
	pCha->isArrStateInfo()[blueBoogie::SI_ATTACK] = true;
	pCha->getAnimation()->start();

	pCha->getWay() == blueBoogie::WAY_RIGHT ?
		pCha->addAttackRects(pCha->getPos().x + 5, pCha->getPos().y, 70.f, 57.f, 0.f, 1.0f) :
		pCha->addAttackRects(pCha->getPos().x - 5, pCha->getPos().y, 70.f, 57.f, 1.f, 1.0f);
}
void blueBoogieState_attack_start1::execute(blueBoogie* pCha)
{
	pCha->attackToTarget(pCha->getAttackRects(), _damage);

	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new blueBoogieState_attack_ready2);
	}
}
void blueBoogieState_attack_start1::exit(blueBoogie* pCha)
{
	pCha->getTargetMemoryAddressLink()->releaseDamagedFromObjectAdress(pCha->getAttackRects());
	pCha->releaseAttackRects();

	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[blueBoogie::SI_ATTACK] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== blueBoogieState_attack_ready2
void blueBoogieState_attack_ready2::enter(blueBoogie* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("blueBoogie_attack"));

	pCha->getWay() == blueBoogie::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_blueBoogie_attack_ready2")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_blueBoogie_attack_ready2"));

	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.3f);
	pCha->isArrStateInfo()[blueBoogie::SI_ATTACK] = true;
	pCha->getAnimation()->start();
}
void blueBoogieState_attack_ready2::execute(blueBoogie* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new blueBoogieState_attack_start2);
	}
}
void blueBoogieState_attack_ready2::exit(blueBoogie* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[blueBoogie::SI_ATTACK] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== blueBoogieState_attack_start2
void blueBoogieState_attack_start2::enter(blueBoogie* pCha)
{
	_damage = 8.f;
	_deltaTime = 0.0f;
	pCha->setImage(IMAGEMANAGER->findImage("blueBoogie_attack"));

	pCha->getWay() == blueBoogie::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_blueBoogie_attack_start2")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_blueBoogie_attack_start2"));
	

	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.7f);
	pCha->isArrStateInfo()[blueBoogie::SI_ATTACK] = true;
	pCha->getAnimation()->start();
}
void blueBoogieState_attack_start2::execute(blueBoogie* pCha)
{
	if (_deltaTime <= 0.f)
	{
		pCha->getWay() == blueBoogie::WAY_RIGHT ?
			pCha->addAttackRects(pCha->getPos().x + 5, pCha->getPos().y, 70.f, 57.f, 0.f, 1.0f) :
			pCha->addAttackRects(pCha->getPos().x - 5, pCha->getPos().y, 70.f, 57.f, 1.f, 1.0f);
		pCha->attackToTarget(pCha->getAttackRects(), _damage);

		pCha->getTargetMemoryAddressLink()->releaseDamagedFromObjectAdress(pCha->getAttackRects());
		pCha->releaseAttackRects();
		_deltaTime = 0.7f / 3.f;
	}
	else
	{
		_deltaTime -= TIMEMANAGER->getElapsedTime();
	}

	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new blueBoogieState_idle);
	}
}
void blueBoogieState_attack_start2::exit(blueBoogie* pCha)
{
	pCha->getTargetMemoryAddressLink()->releaseDamagedFromObjectAdress(pCha->getAttackRects());
	pCha->releaseAttackRects();

	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[blueBoogie::SI_ATTACK] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======