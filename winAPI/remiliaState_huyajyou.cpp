#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_huyajyou_ready
void remiliaState_huyajyou_ready::enter(remilia* pCha)
{
	pCha->subSP(200.f);
	pCha->setVelocityY(-1100.f);
	pCha->setImage(IMAGEMANAGER->findImage("remilia_huyajyou"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_huyajyou_ready")) :	
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_huyajyou_ready"));

	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.2f);
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = true;
	pCha->setAttackStyle(remilia::AS_HUYAJYOU);
	pCha->getAnimation()->start();

	pCha->releaseDamagedRects();
}
void remiliaState_huyajyou_ready::execute(remilia* pCha)
{
	//pCha->calcGravity();

	if (pCha->getVelocityY() >= -400.f)
	{
		pCha->changeState(new remiliaState_huyajyou_start);
		return;
	}
}
void remiliaState_huyajyou_ready::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = false;
	pCha->setAttackStyle(remilia::AS_NULL);
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_huyajyou_start
void remiliaState_huyajyou_start::enter(remilia* pCha)
{
	_deltaTime = 0.f;
	_damage = 250.f;
	_bOnEffect = false;

	pCha->setImage(IMAGEMANAGER->findImage("remilia_huyajyou"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_huyajyou_start")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_huyajyou_start"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 1.5f);
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = true;
	pCha->setAttackStyle(remilia::AS_HUYAJYOU);
	pCha->getAnimation()->start();
}
void remiliaState_huyajyou_start::execute(remilia* pCha)
{
	if ( pCha->getVelocityY() >= 0.f) pCha->setVelocityY(0.f);

	if (!_bOnEffect)
	{
		pCha->getEffectManager()->play("remilia_huyajyou_effect", "remilia_huyajyou_effect",
			pCha->getPos().x, (pCha->getMaxY() + 380.f) - IMAGEMANAGER->findImage("remilia_huyajyou_effect")->getFrameHeight() / 2,
			(KEYANIMANAGER->findAnimation("remilia_huyajyou_effect")->getMaxFrame() + 1) / 2.f, false, 255, true, true);

		pCha->addAttackRects(pCha->getPos().x, pCha->getPos().y + 380.f, 350.f, 987, 0.5f, 1.0f);
		pCha->addAttackRects(pCha->getPos().x, pCha->getPos().y - 60.f, 800.f, 100.f, 0.5f, 1.0f);

		_bOnEffect = true;
	}

	pCha->attackToEnemys(pCha->getAttackRects(), _damage);

	_deltaTime -= TIMEMANAGER->getElapsedTime();
	if (_deltaTime <= 0.f)
	{
		ENEMYMANAGER->releaseDamagedFromObjectAdress(pCha->getAttackRects());
		_deltaTime = 2.f / 19.f;
	}

	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_huyajyou_end);
		return;
	}
}
void remiliaState_huyajyou_start::exit(remilia* pCha)
{
	pCha->releaseAttackRects();

	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = false;
	pCha->setAttackStyle(remilia::AS_NULL);
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_huyajyou_end
void remiliaState_huyajyou_end::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_huyajyou"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_huyajyou_end")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_huyajyou_end"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.2f);
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = true;
	pCha->setAttackStyle(remilia::AS_HUYAJYOU);
	pCha->getAnimation()->start();
}
void remiliaState_huyajyou_end::execute(remilia* pCha)
{
	if (pCha->getVelocityY() == 0.f)
	{
		pCha->changeState(new remiliaState_idle);
		return;
	}
}
void remiliaState_huyajyou_end::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = false;
	pCha->setAttackStyle(remilia::AS_NULL);
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======