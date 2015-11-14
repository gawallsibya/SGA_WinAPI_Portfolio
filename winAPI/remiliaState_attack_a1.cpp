#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_attack_a1_start
void remiliaState_attack_a1_start::enter(remilia* pCha)
{
	_damage = 20.f;
	pCha->setImage(IMAGEMANAGER->findImage("remilia_attack_a1"));

	if (pCha->getWay() == remilia::WAY_RIGHT)
	{
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_attack_a1_start"));
		pCha->addAttackRects(pCha->getPos().x, pCha->getPos().y - 70.f, 80.f, 30.f, 0.f, 0.0f);
	}
	else
	{
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_attack_a1_start"));
		pCha->addAttackRects(pCha->getPos().x, pCha->getPos().y - 70.f, 80.f, 30.f, 1.f, 0.0f);
	}

	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.15f);
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = true;
	pCha->setAttackStyle(remilia::AS_A1);
	pCha->getAnimation()->start();
}
void remiliaState_attack_a1_start::execute(remilia* pCha)
{
	pCha->attackToEnemys(pCha->getAttackRects(), _damage);
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_attack_a1_end);
	}
}
void remiliaState_attack_a1_start::exit(remilia* pCha)
{
	ENEMYMANAGER->releaseDamagedFromObjectAdress(pCha->getAttackRects());
	pCha->releaseAttackRects();
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = false;
	pCha->setAttackStyle(remilia::AS_NULL);
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_attack_a1_end
void remiliaState_attack_a1_end::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_attack_a1"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_attack_a1_end")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_attack_a1_end"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.15f);
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = true;
	pCha->isArrStateInfo()[remilia::SI_COMBO] = true;
	pCha->setAttackStyle(remilia::AS_A1);
	pCha->getAnimation()->start();
}
void remiliaState_attack_a1_end::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_idle);
	}
}
void remiliaState_attack_a1_end::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = false;
	pCha->isArrStateInfo()[remilia::SI_COMBO] = false;
	pCha->setAttackStyle(remilia::AS_NULL);
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======