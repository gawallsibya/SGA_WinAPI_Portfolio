#include "stdafx.h"
#include "gungnir.h"
#include "remilia.h"

gungnir::gungnir()
{
}

gungnir::~gungnir()
{
	release();
}

void gungnir::init(character* master, float x, float y, VECTOR2D vMoveToPos, bool reverse)
{
	_img = IMAGEMANAGER->findImage("remilia_gungnir");

	if (reverse == false)
	{
		_ani = new animation(*KEYANIMANAGER->findAnimation("r_remilia_gungnir"));
		_ani->setFPS((KEYANIMANAGER->findAnimation("r_remilia_gungnir")->getMaxFrame() + 1) / 1.0f);
	}
	else
	{
		_ani = new animation(*KEYANIMANAGER->findAnimation("l_remilia_gungnir"));
		_ani->setFPS((KEYANIMANAGER->findAnimation("l_remilia_gungnir")->getMaxFrame() + 1) / 1.0f);
	}
	
	_ani->start();

	this->setPos(x, y);
	this->setPivot(0.5f, 0.5f);
	this->setSize(static_cast<float>(_ani->getFrameWidth()), static_cast<float>(_ani->getFrameHeight()));

	//정점기준(?) 이동방향좌표설정
	_vStartPos = this->getPos();
	_vMovePos = vMoveToPos;

	_master = master;

	_speed = 2500.f;
	_range = 1600.f;
	_bReverse = reverse;

	_damage = 1500.f;

	_bOnEffect = true;

	_effectMgr->init();

	this->addAttackRects(this->getMinX() + 315.f, this->getMinY() + 187.f, 100.f, 70.f, 0.f, 0.f);
}

void gungnir::update()
{
	missile::update();

	_effectMgr->update();

	this->moveFromAttackRect(this->getMinX() + 315.f, this->getMinY() + 187.f);

	dynamic_cast<remilia*>(_master)->attackToEnemys(this->getAttackRects(), _damage);

	_deltaTime += TIMEMANAGER->getElapsedTime();
	if (_deltaTime >= 0.04f)
	{
		_deltaTime = 0.f;
		_bOnEffect = true;
	}
}

void gungnir::render(HDC hdc)
{
	if (_bOnEffect)
	{
		!_bReverse ? this->getEffectManager()->play("remilia_gungnir_effect", "r_remilia_gungnir_effect", this->getPos().x, this->getPos().y,
			(KEYANIMANAGER->findAnimation("r_remilia_gungnir_effect")->getMaxFrame() + 1) / 0.3f, _bReverse, 180, true, true) :
			this->getEffectManager()->play("remilia_gungnir_effect", "l_remilia_gungnir_effect", this->getPos().x, this->getPos().y,
			(KEYANIMANAGER->findAnimation("l_remilia_gungnir_effect")->getMaxFrame() + 1) / 0.3f, _bReverse, 180, true, true);
		_bOnEffect = false;
	}

	_effectMgr->render();

	POINT cameraPos = { (int)this->getMinX(), (int)this->getMinY() };
	cameraPos = CAMERAMANAGER->ConvertWorldToScreenPos(&cameraPos);
	_img->aniAlphaRender(hdc, cameraPos.x, cameraPos.y, _ani, _bReverse, 255, true);

	/*HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	
	MYRECT cameraRect;
	for (MYRECT& temp : *this->getAttackRects())
	{
		cameraRect = CAMERAMANAGER->ConvertWorldToScreenPos(&temp);
		Rectangle(hdc, (int)cameraRect.getMinX(), (int)cameraRect.getMinY(), (int)cameraRect.getMaxX(), (int)cameraRect.getMaxY());
	}

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);*/
}

void gungnir::release()
{
	missile::release();
}