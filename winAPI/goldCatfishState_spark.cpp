#include "stdafx.h"
#include "goldCatfishState.h"
#include "goldCatfish.h"


//====== goldCatfishState_spark_ready
void goldCatfishState_spark_ready::enter(goldCatfish* pCha)
{
	//pCha->setPivot(0.5f, 0.94f);

	pCha->getTargetMemoryAddressLink()->getPos().x < pCha->getPos().x ?
		pCha->setWay(goldCatfish::WAY_LEFT) : pCha->setWay(goldCatfish::WAY_RIGHT);

	pCha->setImage(IMAGEMANAGER->findImage("goldCatfish_spark"));
	pCha->getWay() == goldCatfish::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_goldCatfish_spark")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_goldCatfish_spark"));

	pCha->isArrStateInfo()[goldCatfish::SI_ATTACK] = true;
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 1.f);
	pCha->getAnimation()->start();
}
void goldCatfishState_spark_ready::execute(goldCatfish* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new goldCatfishState_spark_start);
		return;
	}
}
void goldCatfishState_spark_ready::exit(goldCatfish* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[goldCatfish::SI_ATTACK] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== goldCatfishState_spark_start
void goldCatfishState_spark_start::enter(goldCatfish* pCha)
{
	_bOnEffect = false;
	
	_damage = 50.f;
	_deltaTime = 0.f;

	pCha->setImage(IMAGEMANAGER->findImage("goldCatfish_spark"));

	// 공격 방향 설정.
	pCha->getTargetMemoryAddressLink()->getPos().x < pCha->getPos().x ?
		pCha->setWay(goldCatfish::WAY_LEFT) : pCha->setWay(goldCatfish::WAY_RIGHT);

	pCha->getWay() == goldCatfish::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_goldCatfish_spark")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_goldCatfish_spark"));

	//pCha->addAttackRects(pCha->getPos().x, pCha->getPos().y + 150.f, 600.f, 600.f, 0.5f, pCha->getPivot().y);

	pCha->isArrStateInfo()[goldCatfish::SI_ATTACK] = true;
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 2.f);
	pCha->getAnimation()->start();

}
void goldCatfishState_spark_start::execute(goldCatfish* pCha)
{
	if (!_bOnEffect)
	{
		pCha->getEffectFrontManager()->play("goldCatfish_spark_effect2", "goldCatfish_spark_effect2",
			pCha->getPos().x, pCha->getPos().y + 150.f - IMAGEMANAGER->findImage("goldCatfish_spark_effect2")->getFrameHeight() / 2,
			(KEYANIMANAGER->findAnimation("goldCatfish_spark_effect2")->getMaxFrame() + 1) / 2.f, false, 255, true, true);

			pCha->getEffectFrontManager()->play("goldCatfish_spark_effect1", "goldCatfish_spark_effect1",
				pCha->getPos().x, pCha->getMidY() + 150.f - IMAGEMANAGER->findImage("goldCatfish_spark_effect1")->getFrameHeight() / 2,
				(KEYANIMANAGER->findAnimation("goldCatfish_spark_effect1")->getMaxFrame() + 1) / 2.f, false, 255, true, true);
		
		_bOnEffect = true;
	}

	if (_deltaTime <= 0.f)
	{
		pCha->addAttackRects(pCha->getPos().x, pCha->getPos().y + 150.f, 600.f, 600.f, 0.5f, pCha->getPivot().y);
		pCha->attackToTarget(pCha->getAttackRects(), _damage);

		pCha->getTargetMemoryAddressLink()->releaseDamagedFromObjectAdress(pCha->getAttackRects());
		pCha->releaseAttackRects();
		_deltaTime = 2.f / 10.f;
	}
	else
	{
		_deltaTime -= TIMEMANAGER->getElapsedTime();
	}

	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new goldCatfishState_idle);
		return;
	}
}
void goldCatfishState_spark_start::exit(goldCatfish* pCha)
{
	pCha->getTargetMemoryAddressLink()->releaseDamagedFromObjectAdress(pCha->getAttackRects());
	pCha->releaseAttackRects();

	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[goldCatfish::SI_ATTACK] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======