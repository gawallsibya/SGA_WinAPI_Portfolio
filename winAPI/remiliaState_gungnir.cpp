#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_gungnir_create
void remiliaState_gungnir_create::enter(remilia* pCha)
{
	_bOnEffect = false;

	pCha->subSP(100.f);
	pCha->setImage(IMAGEMANAGER->findImage("remilia_shot_gungnir"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_shot_gungnir_create")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_shot_gungnir_create"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.5f);
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = true;
	pCha->getAnimation()->start();

	pCha->releaseDamagedRects();
}
void remiliaState_gungnir_create::execute(remilia* pCha)
{
	if (!_bOnEffect)
	{
		_bOnEffect = true;
		if (pCha->getWay() == remilia::WAY_RIGHT)
		{
			pCha->getEffectManager()->play("remilia_shot_gungnir_create_effect", "r_remilia_shot_gungnir_create_effect",
				pCha->getPos().x - IMAGEMANAGER->findImage("remilia_shot_gungnir_create_effect")->getFrameWidth() * 0.1f,
				pCha->getPos().y - IMAGEMANAGER->findImage("remilia_shot_gungnir_create_effect")->getFrameHeight() * 0.2f,
				(KEYANIMANAGER->findAnimation("r_remilia_shot_gungnir_create_effect")->getMaxFrame() + 1) / 0.5f, true, 255, true, true);
		}
		else
		{
			pCha->getEffectManager()->play("remilia_shot_gungnir_create_effect", "l_remilia_shot_gungnir_create_effect",
				pCha->getPos().x + IMAGEMANAGER->findImage("remilia_shot_gungnir_create_effect")->getFrameWidth() * 0.1f,
				pCha->getPos().y - IMAGEMANAGER->findImage("remilia_shot_gungnir_create_effect")->getFrameHeight() * 0.2f,
				(KEYANIMANAGER->findAnimation("l_remilia_shot_gungnir_create_effect")->getMaxFrame() + 1) / 0.5f, false, 255, true, true);
		}
	}
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_gungnir_ready);
		return;
	}
}
void remiliaState_gungnir_create::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_gungnir_ready
void remiliaState_gungnir_ready::enter(remilia* pCha)
{
	_bOnEffect = false;
	pCha->setImage(IMAGEMANAGER->findImage("remilia_shot_gungnir"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_shot_gungnir_ready")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_shot_gungnir_ready"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.3f);
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = true;
	pCha->getAnimation()->start();
}
void remiliaState_gungnir_ready::execute(remilia* pCha)
{
	if (!_bOnEffect)
	{
		_bOnEffect = true;
		if (pCha->getWay() == remilia::WAY_RIGHT)
		{
			pCha->getEffectManager()->play("remilia_shot_gungnir_ready_effect", "r_remilia_shot_gungnir_ready_effect",
				pCha->getPos().x + IMAGEMANAGER->findImage("remilia_shot_gungnir_ready_effect")->getFrameWidth() * 0.1f,
				pCha->getPos().y - IMAGEMANAGER->findImage("remilia_shot_gungnir_ready_effect")->getFrameHeight() * 0.05f,
				(KEYANIMANAGER->findAnimation("r_remilia_shot_gungnir_ready_effect")->getMaxFrame() + 1) / 0.3f, false, 255, true, true);
		}
		else
		{
			pCha->getEffectManager()->play("remilia_shot_gungnir_ready_effect", "l_remilia_shot_gungnir_ready_effect",
				pCha->getPos().x + IMAGEMANAGER->findImage("remilia_shot_gungnir_ready_effect")->getFrameWidth() * 0.1f,
				pCha->getPos().y - IMAGEMANAGER->findImage("remilia_shot_gungnir_ready_effect")->getFrameHeight() * 0.05f,
				(KEYANIMANAGER->findAnimation("l_remilia_shot_gungnir_ready_effect")->getMaxFrame() + 1) / 0.3f, true, 255, true, true);
		}
	}
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->fireGungnir();
		pCha->changeState(new remiliaState_gungnir_start);
		return;
	}
	
}
void remiliaState_gungnir_ready::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_gungnir_start
void remiliaState_gungnir_start::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_shot_gungnir"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_shot_gungnir_start")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_shot_gungnir_start"));
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = true;
	pCha->getAnimation()->start();
}
void remiliaState_gungnir_start::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_idle);
		return;
	}
}
void remiliaState_gungnir_start::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_ATTACK] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======