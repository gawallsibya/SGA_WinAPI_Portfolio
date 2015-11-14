#include "stdafx.h"
#include "remiliaState.h"
#include "remilia.h"

//====== remiliaState_die
void remiliaState_die::enter(remilia* pCha)
{
	_deltaTime = 0.5f;
	_bMoveStop = false;
	pCha->setVelocityY(-700.f);

	pCha->setImage(IMAGEMANAGER->findImage("remilia_hit_down_back"));
	pCha->getWay() == remilia::WAY_RIGHT ?
		pCha->setAnimation(KEYANIMANAGER->findAnimation("r_remilia_hit_down_back")) :
		pCha->setAnimation(KEYANIMANAGER->findAnimation("l_remilia_hit_down_back"));
	pCha->getAnimation()->setFPS((pCha->getAnimation()->getMaxFrame() + 1) / 0.5f);
	pCha->isArrStateInfo()[remilia::SI_HITDOWN] = true;
	pCha->getAnimation()->start();

	pCha->releaseDamagedRects();
}
void remiliaState_die::execute(remilia* pCha)
{
	if (!_bMoveStop)
	{
		pCha->getWay() == remilia::WAY_RIGHT ?
			pCha->moveTo(-500.f * TIMEMANAGER->getElapsedTime(), 0.f) :
			pCha->moveTo(500.f * TIMEMANAGER->getElapsedTime(), 0.f);
	}
	if (pCha->getVelocityY() == 0.f)
	{
		_bMoveStop = true;
		_deltaTime -= TIMEMANAGER->getElapsedTime();
	}
	
	// 지정한 시간 후에 일어나게..
	if (_deltaTime <= 0.f)
	{
		SCENEMANAGER->changeScene("gameoverScene");
		return;
	}

}
void remiliaState_die::exit(remilia* pCha)
{
	pCha->getAnimation()->stop();
	pCha->isArrStateInfo()[remilia::SI_HITDOWN] = false;
	pCha->setAnimation(nullptr);
	pCha->setImage(nullptr);
}
//======