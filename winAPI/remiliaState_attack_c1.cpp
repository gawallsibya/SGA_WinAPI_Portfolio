#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_attack_c1_start
void remiliaState_attack_c1_start::enter(remilia* pCha)
{
	_damage = 70.f;
	_bOnEffect = false;
	pCha->setImage(IMAGEMANAGER->findImage("remilia_attack_c1"));
	if (pCha->getWay() == remilia::WAY_RIGHT)
	{
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_attack_c1_start"));
		pCha->addAttackRects(pCha->getPos().x - 20.f, pCha->getPos().y - 130.f, 120.f, 160.f, 0.f, 0.f);
	}
	else
	{
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_attack_c1_start"));
		pCha->addAttackRects(pCha->getPos().x + 20.f, pCha->getPos().y - 130.f, 120.f, 160.f, 1.f, 0.f);
	}
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.2f);
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = true;
	pCha->setAttackStyle(remilia::AS_C1);
	pCha->getAnimation()->start();
}
void remiliaState_attack_c1_start::execute(remilia* pCha)
{	
	// ÀÌÆåÆ® ½ÇÇà..
	if (pCha->getAnimation()->getPlayFrame() == 4 && !_bOnEffect)
	{
		_bOnEffect = true;
		if (pCha->getWay() == remilia::WAY_RIGHT)
		{
			pCha->getEffectManager()->play("remilia_attack_c1_effect", "r_remilia_attack_c1_effect",
				pCha->getPos().x + IMAGEMANAGER->findImage("remilia_attack_c1_effect")->getFrameWidth() * 0.3f,
				pCha->getPos().y - IMAGEMANAGER->findImage("remilia_attack_c1_effect")->getFrameHeight() * 0.3f, 
				(pCha->getAnimation()->getMaxFrame() + 1) / 0.2f, false, 255, true, true);
		}
		else
		{
			pCha->getEffectManager()->play("remilia_attack_c1_effect", "l_remilia_attack_c1_effect",
				pCha->getPos().x - IMAGEMANAGER->findImage("remilia_attack_c1_effect")->getFrameWidth() * 0.3f,
				pCha->getPos().y - IMAGEMANAGER->findImage("remilia_attack_c1_effect")->getFrameHeight() * 0.3f, 
				(pCha->getAnimation()->getMaxFrame() + 1) / 0.2f, true, 255, true, true);
		}
	}

	pCha->attackToEnemys(pCha->getAttackRects(), _damage);

	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_attack_c1_end);
	}
}
void remiliaState_attack_c1_start::exit(remilia* pCha)
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
//====== remiliaState_attack_c1_end
void remiliaState_attack_c1_end::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_attack_c1"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_attack_c1_end")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_attack_c1_end"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.3f);
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = true;
	pCha->isArrStateInfo()[remilia::SI_COMBO] = false;
	pCha->setAttackStyle(remilia::AS_C1);
	pCha->getAnimation()->start();
}
void remiliaState_attack_c1_end::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_idle);
	}
}
void remiliaState_attack_c1_end::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = false;
	pCha->isArrStateInfo()[remilia::SI_COMBO] = false;
	pCha->setAttackStyle(remilia::AS_NULL);
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======