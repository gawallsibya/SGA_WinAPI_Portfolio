#include "stdafx.h"
#include "shot_b.h"
#include "remilia.h"

shot_b::shot_b()
{
}


shot_b::~shot_b()
{
	release();
}

void shot_b::init(character* master, float x, float y, VECTOR2D vMoveToPos, bool reverse)
{
	_img = IMAGEMANAGER->findImage("remilia_shot_b_missile");

	if (reverse == false)
	{
		_ani = new animation(*KEYANIMANAGER->findAnimation("r_remilia_shot_b_missile"));
		_ani->setFPS((KEYANIMANAGER->findAnimation("r_remilia_shot_b_missile")->getMaxFrame() + 1) / 0.2f);
	}
	else
	{
		_ani = new animation(*KEYANIMANAGER->findAnimation("l_remilia_shot_b_missile"));
		_ani->setFPS((KEYANIMANAGER->findAnimation("l_remilia_shot_b_missile")->getMaxFrame() + 1) / 0.2f);
	}

	_ani->start();

	this->setPos(x, y);
	this->setPivot(0.5f, 0.5f);
	this->setSize(static_cast<float>(_ani->getFrameWidth()), static_cast<float>(_ani->getFrameHeight()));

	//정점기준(?) 이동방향좌표설정
	_vStartPos = this->getPos();
	_vMovePos = vMoveToPos;

	_master = master;

	_speed = 500.f;
	_range = 1600.f;
	_bReverse = reverse;

	_damage = 30.f;

	this->addAttackRects(this->getMinX() + 23.f, this->getMinY() + 17.f, 35.f, 70.f, 0.f, 0.f);
}

void shot_b::update()
{
	missile::update();
	this->pixelCollisionLeftAndRight();

	this->moveFromAttackRect(this->getMinX() + 23.f, this->getMinY() + 17.f);

	if (dynamic_cast<remilia*>(_master)->attackToEnemys(this->getAttackRects(), _damage))
	{
		_bLife = false;
		dynamic_cast<remilia*>(_master)->addSP(5.f);
	}
}

void shot_b::render(HDC hdc)
{
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

void shot_b::release()
{
	missile::release();
}
