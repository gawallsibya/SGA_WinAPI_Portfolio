#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_dash_back_air_ready
void remiliaState_dash_back_air_ready::enter(remilia* pCha)
{
	pCha->releaseDamagedRects();

	pCha->setVelocityY(20.f);
	pCha->setImage(IMAGEMANAGER->findImage("remilia_dash_back_air"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_dash_back_air_ready")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_dash_back_air_ready"));

	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.1f);
	pCha->isArrStateInfo()[remilia::SI_DASH] = true;
	pCha->getAnimation()->start();
}
void remiliaState_dash_back_air_ready::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_dash_back_air_start);
	}
}
void remiliaState_dash_back_air_ready::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_DASH] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_dash_back_air_start
void remiliaState_dash_back_air_start::enter(remilia* pCha)
{
	_bSetDamagedRects = false;

	pCha->setImage(IMAGEMANAGER->findImage("remilia_dash_back_air"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_dash_back_air_start")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_dash_back_air_start"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.3f);
	pCha->isArrStateInfo()[remilia::SI_DASH] = true;
	pCha->getAnimation()->start();
}
void remiliaState_dash_back_air_start::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		// 데미지박스 생성 안했다면 생성..
		if (!_bSetDamagedRects)
		{
			pCha->addDamagedRects(pCha->getPos().x, pCha->getPos().y, 45.f, 85.f, 0.5f, 1.0f);
			_bSetDamagedRects = true;
		}

		pCha->getWay() == remilia::WAY_RIGHT ?
			pCha->moveTo(-(pCha->getSpeed() * TIMEMANAGER->getElapsedTime()), 0.f) :
			pCha->moveTo(pCha->getSpeed() * TIMEMANAGER->getElapsedTime(), 0.f);
	}
	else
	{
		pCha->setVelocityY(10.f);

		pCha->getWay() == remilia::WAY_RIGHT ?
			pCha->moveTo(-(pCha->getSpeed() * 2.5f * TIMEMANAGER->getElapsedTime()), 10 * TIMEMANAGER->getElapsedTime()) :
			pCha->moveTo(pCha->getSpeed() * 2.5f * TIMEMANAGER->getElapsedTime(), 10 * TIMEMANAGER->getElapsedTime());
	}

	if (pCha->getVelocityY() == 0.f)
	{
		pCha->changeState(new remiliaState_dash_back_air_end);
		return;
	}
}
void remiliaState_dash_back_air_start::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_DASH] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======
//====== remiliaState_dash_back_air_end
void remiliaState_dash_back_air_end::enter(remilia* pCha)
{
	pCha->setImage(IMAGEMANAGER->findImage("remilia_dash_back_air"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_dash_back_air_end")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_dash_back_air_end"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.1f);
	pCha->isArrStateInfo()[remilia::SI_DASH] = true;
	pCha->getAnimation()->start();
}
void remiliaState_dash_back_air_end::execute(remilia* pCha)
{
	if (!pCha->getAnimation()->isPlay())
	{
		pCha->changeState(new remiliaState_idle);
	}
}
void remiliaState_dash_back_air_end::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_DASH] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======