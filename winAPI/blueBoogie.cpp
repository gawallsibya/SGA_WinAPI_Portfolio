#include "stdafx.h"
#include "blueBoogie.h"
#include "missileManager.h"
#include "blueBoogieState.h"

blueBoogie::blueBoogie()
{
}


blueBoogie::~blueBoogie()
{
}

void blueBoogie::init(WAY way, float x, float y)
{

	this->setPos(x, y);
	this->setPivot(0.5f, 1.0f);

	animationInit();

	memset(_bArrStateInfo, false, (sizeof(bool) * SI_MAX));
	_way = way;

	_maxHp = 500.f;
	_hp = _maxHp;

	this->setSpeed(200.f);

	_attackTimer = 0.f;
	_moveTimer = RND->getFromFloatTo(1.f, 3.f);

	_pState = nullptr;

	_recognitionRange = 1800.f;
	_attackRange = 500.f;

	_bAttackMode = false;
	//===========

	_pState = new blueBoogieState_idle;
	_pState->enter(this);

	_pMissileMgr = new missileManager;
	_pMissileMgr->init();

	_effectFrontMgr = new effectManager;
	_effectFrontMgr->init();

	_effectBackMgr = new effectManager;
	_effectBackMgr->init();

	_hpBar->init("hpBar_top", "hpBar_bottom", this->getMinX(), this->getMaxY() + 5.f, this->getSize().width, 10.f, _maxHp, &_hp, 180, 180, true);

}

void blueBoogie::update()
{
	if (getDistance(_target->getPos().x, 0.f, this->getPos().x, 0.f) <= _recognitionRange)
	{
		stateUpdate();

		this->calcGravity();

		_pMissileMgr->update();
		_effectFrontMgr->update();
		_effectBackMgr->update();


		if (getDistance(_target->getPos().x, 0.f, this->getPos().x, 0.f) <= _attackRange && !_bAttackMode)
		{
			_bAttackMode = true;
			this->changeState(new blueBoogieState_idle);
			return;
		}

		// 전투모드일때..
		if (_bAttackMode)
		{
			if (_bArrStateInfo[SI_IDLE] || _bArrStateInfo[SI_MOVE])
			{
				if (_attackTimer > 0.f)
				{
					_attackTimer -= TIMEMANAGER->getElapsedTime();
				}
			}
		}
		// 비 전투모드일때..
		else
		{
			if (_bArrStateInfo[SI_IDLE] == true)
			{
				if (_moveTimer > 0.f)
				{
					_moveTimer -= TIMEMANAGER->getElapsedTime();
				}
				else
				{
					_way == WAY_LEFT ? _way = WAY_RIGHT : _way = WAY_LEFT;

					_moveTimer = RND->getFromFloatTo(1.f, 3.f);
					this->changeState(new blueBoogieState_walk_forward);
					return;
				}
			}
		}
		boundingRectUpdate();
	}
	else if (_bAttackMode) _bAttackMode = false; 

	if (_maxHp != _hp)
	{
		_hpBar->update();
		_hpBar->setPos(this->getMinX(), this->getMaxY() + 5.f);
	}
}

void blueBoogie::render(HDC hdc)
{
	_effectBackMgr->render();

	POINT cameraPos = { (int)(this->getPos().x - this->getImage()->getFrameWidth() * 0.5f), (int)(this->getPos().y - this->getImage()->getFrameHeight()) };
	cameraPos = CAMERAMANAGER->ConvertWorldToScreenPos(&cameraPos);
	_way == WAY_RIGHT ?
		this->getImage()->aniAlphaRender(hdc, cameraPos.x, cameraPos.y, this->getAnimation(), true, 255, true) :
		this->getImage()->aniAlphaRender(hdc, cameraPos.x, cameraPos.y, this->getAnimation(), false, 255, true);

	_effectFrontMgr->render();
	_pMissileMgr->render(hdc);
	if (_maxHp != _hp) _hpBar->render(hdc);

	/*HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	MYRECT cameraRect;
	for (MYRECT& temp : *this->getDamagedRects())
	{
		cameraRect = CAMERAMANAGER->ConvertWorldToScreenPos(&temp);
		Rectangle(hdc, (int)cameraRect.getMinX(), (int)cameraRect.getMinY(), (int)cameraRect.getMaxX(), (int)cameraRect.getMaxY());
	}
	for (MYRECT& temp : *this->getAttackRects())
	{
		cameraRect = CAMERAMANAGER->ConvertWorldToScreenPos(&temp);
		Rectangle(hdc, (int)cameraRect.getMinX(), (int)cameraRect.getMinY(), (int)cameraRect.getMaxX(), (int)cameraRect.getMaxY());
	}

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

	cameraPos = { (int)this->getPos().x, (int)this->getPos().y };
	cameraPos = CAMERAMANAGER->ConvertWorldToScreenPos(&cameraPos);
	Ellipse(hdc, cameraPos.x - 5, cameraPos.y, cameraPos.x + 5, cameraPos.y + 10);*/
}

void blueBoogie::release()
{
	_bArrStateInfo[SI_MAX] = {};
	_way = {};

	// 점프관련
	_velocityY = 0.f;
	_hp = 0.f;

	SAFE_DELETE(_pState);	// 현재 상태

	_effectFrontMgr->release();
	SAFE_DELETE(_effectFrontMgr);

	_effectBackMgr->release();
	SAFE_DELETE(_effectBackMgr);
}

void blueBoogie::stateUpdate()
{
	_pState->execute(this);
}

void blueBoogie::changeState(blueBoogieState* pNewState)
{
	// 오류체크
	if (_pState == nullptr || pNewState == nullptr)
	{
		// 에러를 어찌 표시할꼬..
		return;
	}
	// 현재 상태 이탈
	_pState->exit(this);
	// 현재 상태 삭제
	delete _pState;

	// 새로운 상태를 현재 상태로 만듦
	_pState = pNewState;
	// 새로운 상태로 진입
	_pState->enter(this);
}

void blueBoogie::boundingRectUpdate()
{
	this->moveFromDamagedRect(this->getPos().x, this->getPos().y);
}

void blueBoogie::setDie()
{
	this->changeState(new blueBoogieState_die);
}

void blueBoogie::setDamaged(float damage)
{
	this->subHP(damage);
	if (this->getHP() <= 0.f)
	{
		this->setDie();
		return;
	}
	else
	{
		this->changeState(new blueBoogieState_hit_forward);
		return;
	}

}