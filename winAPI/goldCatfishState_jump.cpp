#include "stdafx.h"
#include "goldCatfishState.h"
#include "goldCatfish.h"


//====== goldCatfishState_jump_ready
void goldCatfishState_jump_ready::enter(goldCatfish* pCha)
{
	pCha->getTargetMemoryAddressLink()->getPos().x < pCha->getPos().x ?
		pCha->setWay(goldCatfish::WAY_LEFT) : pCha->setWay(goldCatfish::WAY_RIGHT);
	
	pCha->setImage(IMAGEMANAGER->findImage("goldCatfish_jump"));
	pCha->getWay() == goldCatfish::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_goldCatfish_jump_ready")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_goldCatfish_jump_ready"));
	
	pCha->isArrStateInfo()[goldCatfish::SI_JUMP] = true;
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 1.f);
	pCha->getAnimation()->start();
}
void goldCatfishState_jump_ready::execute(goldCatfish* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new goldCatfishState_jump_start);
		return;
	}
}
void goldCatfishState_jump_ready::exit(goldCatfish* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[goldCatfish::SI_JUMP] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== goldCatfishState_jump_start
void goldCatfishState_jump_start::enter(goldCatfish* pCha)
{
	//3.5f
	_bDownAttacked = false;
	_disX = pCha->getTargetMemoryAddressLink()->getPos().x - pCha->getPos().x;
	_damage = 300.f; 
	pCha->setVelocityY(-2000.f);

	pCha->setImage(IMAGEMANAGER->findImage("goldCatfish_jump"));

	pCha->getTargetMemoryAddressLink()->getPos().x < pCha->getPos().x ?
		pCha->setWay(goldCatfish::WAY_LEFT) : pCha->setWay(goldCatfish::WAY_RIGHT);

	if (pCha->getWay() == goldCatfish::WAY_RIGHT)
	{
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_goldCatfish_jump_start"));

		pCha->releaseDamagedRects();
		pCha->addDamagedRects(pCha->getPos().x, pCha->getPos().y, 480.f, 400.f, 0.6f,pCha->getPivot().y);
		pCha->addAttackRects(pCha->getPos().x, pCha->getPos().y, 480.f, 400.f, 0.6f, pCha->getPivot().y);
	}
	else
	{
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_goldCatfish_jump_start"));

		pCha->releaseDamagedRects();
		pCha->addDamagedRects(pCha->getPos().x, pCha->getPos().y, 480.f, 400.f, 0.4f, pCha->getPivot().y);
		pCha->addAttackRects(pCha->getPos().x, pCha->getPos().y, 480.f, 400.f, 0.4f, pCha->getPivot().y);
	}
	pCha->setBoundingRect(480.f, 400.f);

	pCha->isArrStateInfo()[goldCatfish::SI_JUMP] = true;
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 1.f);
	pCha->getAnimation()->start();

	pCha->getEffectBackManager()->play("goldCatfish_jump_start_effect", "goldCatfish_jump_start_effect",
		pCha->getPos().x - 30.f, pCha->getMaxY() + 80.f - IMAGEMANAGER->findImage("goldCatfish_jump_start_effect")->getFrameHeight() / 2,
		(KEYANIMANAGER->findAnimation("goldCatfish_jump_start_effect")->getMaxFrame() + 1) / 0.7f, false, 255, true, true);
	
}
void goldCatfishState_jump_start::execute(goldCatfish* pCha)
{
	pCha->moveTo((_disX / 2.5f) * TIMEMANAGER->getElapsedTime(), 0.f);
	pCha->moveFromAttackRect(pCha->getPos().x, pCha->getPos().y);
	pCha->moveFromDamagedRect(pCha->getPos().x, pCha->getPos().y);

	// 점프 후 내려올때 데미지를 한번 더 입힐 수 있다..
	if (pCha->getVelocityY() >= 0.f && !_bDownAttacked)
	{
		pCha->getTargetMemoryAddressLink()->releaseDamagedFromObjectAdress(pCha->getAttackRects());
		_bDownAttacked = true;
	}

	// 점프하는동안 지속적인 충돌처리로 공격시도중..
	pCha->attackToTarget(pCha->getAttackRects(), _damage);

	if (pCha->getVelocityY() == 0.f)
	{
		pCha->changeState(new goldCatfishState_idle);
		return;
	}
}
void goldCatfishState_jump_start::exit(goldCatfish* pCha)
{
	pCha->getEffectBackManager()->play("goldCatfish_jump_start_effect", "goldCatfish_jump_start_effect",
		pCha->getPos().x - 30.f, pCha->getMaxY() + 80.f - IMAGEMANAGER->findImage("goldCatfish_jump_start_effect")->getFrameHeight() / 2,
		(KEYANIMANAGER->findAnimation("goldCatfish_jump_start_effect")->getMaxFrame() + 1.f) / 0.7f, false, 255, true, true);
	
	pCha->getTargetMemoryAddressLink()->releaseDamagedFromObjectAdress(pCha->getAttackRects());
	pCha->releaseAttackRects();

	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[goldCatfish::SI_JUMP] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======