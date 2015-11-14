#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_attack_a3_start1
void remiliaState_attack_a3_start1::enter(remilia* pCha)
{
	_damage = 30.f;
	_bOnEffect = false;
	pCha->setImage(IMAGEMANAGER->findImage("remilia_attack_a3"));
	if (pCha->getWay() == remilia::WAY_RIGHT)
	{
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_attack_a3_start1"));
		pCha->addAttackRects(pCha->getPos().x, pCha->getPos().y - 85.f, 80.f, 85.f, 0.f, 0.f);
	}
	else
	{
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_attack_a3_start1"));
		pCha->addAttackRects(pCha->getPos().x, pCha->getPos().y - 85.f, 80.f, 85.f, 1.f, 0.f);
	}
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.3f);
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = true;
	pCha->setAttackStyle(remilia::AS_A3);
	pCha->getAnimation()->start();
}
void remiliaState_attack_a3_start1::execute(remilia* pCha)
{
	if (!_bOnEffect)
	{
		_bOnEffect = true;
		if (pCha->getWay() == remilia::WAY_RIGHT)
		{
			pCha->getEffectManager()->play("remilia_attack_a3_effect", "r_remilia_attack_a3_effect1",
				pCha->getPos().x + IMAGEMANAGER->findImage("remilia_attack_a3_effect")->getFrameWidth() * 0.1f,
				pCha->getPos().y - IMAGEMANAGER->findImage("remilia_attack_a3_effect")->getFrameHeight() * 0.4f, 
				(KEYANIMANAGER->findAnimation("r_remilia_attack_a3_effect1")->getMaxFrame() + 1) / 0.3f, false, 255, true, true);
		}
		else
		{
			pCha->getEffectManager()->play("remilia_attack_a3_effect", "l_remilia_attack_a3_effect1",
				pCha->getPos().x - IMAGEMANAGER->findImage("remilia_attack_a3_effect")->getFrameWidth() * 0.1f,
				pCha->getPos().y - IMAGEMANAGER->findImage("remilia_attack_a3_effect")->getFrameHeight() * 0.4f,
				(KEYANIMANAGER->findAnimation("l_remilia_attack_a3_effect1")->getMaxFrame() + 1) / 0.3f, true, 255, true, true);
		}
	}
	pCha->attackToEnemys(pCha->getAttackRects(), _damage);

	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_attack_a3_start2);
	}
}
void remiliaState_attack_a3_start1::exit(remilia* pCha)
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
//====== remiliaState_attack_a3_start2
void remiliaState_attack_a3_start2::enter(remilia* pCha)
{
	_damage = 30.f;
	_bOnEffect = false;
	pCha->setImage(IMAGEMANAGER->findImage("remilia_attack_a3"));
	if (pCha->getWay() == remilia::WAY_RIGHT)
	{
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_attack_a3_start2"));
		pCha->addAttackRects(pCha->getPos().x, pCha->getPos().y - 85.f, 80.f, 85.f, 0.f, 0.f);
	}
	else
	{
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_attack_a3_start2"));
		pCha->addAttackRects(pCha->getPos().x, pCha->getPos().y - 85.f, 80.f, 85.f, 1.f, 0.f);
	}
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.3f);
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = true;
	pCha->setAttackStyle(remilia::AS_A3);
	pCha->getAnimation()->start();
}
void remiliaState_attack_a3_start2::execute(remilia* pCha)
{
	if (!_bOnEffect)
	{
		_bOnEffect = true;
		if (pCha->getWay() == remilia::WAY_RIGHT)
		{
			pCha->getEffectManager()->play("remilia_attack_a3_effect", "r_remilia_attack_a3_effect2",
				pCha->getPos().x + IMAGEMANAGER->findImage("remilia_attack_a3_effect")->getFrameWidth() * 0.1f,
				pCha->getPos().y - IMAGEMANAGER->findImage("remilia_attack_a3_effect")->getFrameHeight() * 0.4f,
				(KEYANIMANAGER->findAnimation("r_remilia_attack_a3_effect2")->getMaxFrame() + 1) / 0.3f, false, 255, true, true);
		}
		else
		{
			pCha->getEffectManager()->play("remilia_attack_a3_effect", "l_remilia_attack_a3_effect2",
				pCha->getPos().x - IMAGEMANAGER->findImage("remilia_attack_a3_effect")->getFrameWidth() * 0.1f,
				pCha->getPos().y - IMAGEMANAGER->findImage("remilia_attack_a3_effect")->getFrameHeight() * 0.4f,
				(KEYANIMANAGER->findAnimation("l_remilia_attack_a3_effect2")->getMaxFrame() + 1) / 0.3f, true, 255, true, true);
		}
	}
	pCha->attackToEnemys(pCha->getAttackRects(), _damage);

	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_attack_a1_end);
	}
}
void remiliaState_attack_a3_start2::exit(remilia* pCha)
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
//====== remiliaState_attack_a3_end
void remiliaState_attack_a3_end::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_attack_a3"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_attack_a3_end")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_attack_a3_end"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.3f);
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = true;
	pCha->isArrStateInfo()[remilia::SI_COMBO] = true;
	pCha->setAttackStyle(remilia::AS_A3);
	pCha->getAnimation()->start();
}
void remiliaState_attack_a3_end::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_idle);
	}
}
void remiliaState_attack_a3_end::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = false;
	pCha->isArrStateInfo()[remilia::SI_COMBO] = false;
	pCha->setAttackStyle(remilia::AS_NULL);
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======