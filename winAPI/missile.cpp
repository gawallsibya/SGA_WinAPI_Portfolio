#include "stdafx.h"
#include "missile.h"
#include "stage.h"

missile::missile():
_speed(0.f),
_range(0.f),
_bReverse(false),
_deltaTime(0.f),
_bOnEffect(false),
_effectMgr(new effectManager),
_bLife(true)
{
}

missile::~missile()
{
	release();
}

void missile::release(void)
{
	object::release();
	_attackRt.clear();
	_speed = 0.f;

	_deltaTime = 0.f;
	_bOnEffect = false;
	_damage = 0.f;

	_bLife = false;

	ENEMYMANAGER->releaseDamagedFromObjectAdress(this->getAttackRects());
	_effectMgr->release();
	SAFE_DELETE(_effectMgr);
}

void missile::update(void)
{
	moveUpdate();
	animationUpdate();
}

void missile::animationUpdate()
{
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void missile::moveUpdate()
{
	_vMovePos.Normalize();

	//정규화된 벡터에 속도를 더해 좌표값을 수정한다.
	_vMovePos = _vMovePos * _speed * TIMEMANAGER->getElapsedTime();	//임시 스피드
	this->moveTo(_vMovePos.x, _vMovePos.y);

	checkRangeUpdate();
}

void missile::checkRangeUpdate()
{
	// 사거리보다 발사된 미사일의 거리가 더 큰경우 죽음, 아니면 삶.
	if (_range < getDistance(_vStartPos.x, _vStartPos.y, this->getPos().x, this->getPos().y))
	{
		_bLife = false;
	}
}

void missile::moveFromAttackRect(float x, float y)
{
	for (MYRECT& temp : _attackRt)
	{
		temp.setPos(x, y);
	}
}

void missile::addAttackRects(float x, float y, float width, float height, float pivotX, float pivotY)
{
	MYRECT rt;
	rt.setPos(x, y);
	rt.setSize(width, height);
	rt.setPivot(pivotX, pivotY);
	_attackRt.push_back(rt);
}


void missile::pixelCollisionTopAndBottom()
{
	// 세로 맵 끝 충돌 체크
	//mapOutCollsionTopAndBottom();

	// 위나 아래가 닿으면 충돌
	image* img = this->getStageMemoryAddressLink()->getCollisionBackground();
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;

	COLORREF color = NULL;
	bool bHeightCollision = false;
	int r = 0, g = 0, b = 0;
	
	HDC collisionDC = img->getMemDC();

	for (MYRECT& temp : *this->getAttackRects())
	{
		left = (int)(temp.getMinX() + 5);
		top = (int)(temp.getMinY() + img->getHeight() - WINSIZEY);
		right = (int)(temp.getMaxX() - 5);
		bottom = (int)(temp.getMaxY() + img->getHeight() - WINSIZEY);

		// 왼쪽  위
		if (!bHeightCollision)
		{
			for (int i = 20; i >= 0; i--)
			{
				color = GetPixel(collisionDC, left, top + i);
				r = GetRValue(color);
				g = GetGValue(color);
				b = GetBValue(color);
				if ((r == 255 && g == 255 && b == 255))
				{
					_bLife = false;
					break;
				}
				// 오른쪽 위
				else
				{
					color = GetPixel(collisionDC, right, top + i);
					r = GetRValue(color);
					g = GetGValue(color);
					b = GetBValue(color);
					if ((r == 255 && g == 255 && b == 255))
					{
						_bLife = false;
						break;
					}
				}
			}
		}

		//==============================
		// 왼쪽이나 오른쪽이 닿으면 충돌
		left = (int)(temp.getMinX() + 5);
		top = (int)(temp.getMinY() + img->getHeight() - WINSIZEY);
		right = (int)(temp.getMaxX() - 5);
		bottom = (int)(temp.getMaxY() + img->getHeight() - WINSIZEY);
		// 왼쪽 아래

		bHeightCollision = false;
		color = NULL;

		for (int i = -20; i <= 0; i++)
		{
			color = GetPixel(collisionDC, left, bottom + i);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);
			if ((r == 255 && g == 255 && b == 255))
			{
				_bLife = false;
				break;
			}
			// 오른쪽 아래
			else
			{
				color = GetPixel(collisionDC, right, bottom + i);
				r = GetRValue(color);
				g = GetGValue(color);
				b = GetBValue(color);
				if ((r == 255 && g == 255 && b == 255))
				{
					_bLife = false;
					break;
				}
			}
		}
	}
}

void missile::pixelCollisionLeftAndRight()
{
	// 가로 맵 끝 충돌 체크
	//mapOutCollsionLeftAndRight();

	// 왼쪽 위나 아래가 닿으면 충돌
	image* img = this->getStageMemoryAddressLink()->getCollisionBackground();
	
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom  = 0;

	COLORREF color = NULL;
	bool bWidthCollision = false;
	int r = 0, g = 0, b = 0;

	HDC collisionDC = img->getMemDC();

	for (MYRECT& temp : *this->getAttackRects())
	{
		left = (int)(temp.getMinX());
		top = (int)((temp.getMinY() + img->getHeight() + 5) - WINSIZEY);
		right = (int)(temp.getMaxX());
		bottom = (int)((temp.getMaxY() + img->getHeight() - 10) - WINSIZEY);
		
		// 왼쪽 위

		for (int i = 20; i >= 0; i--)
		{
			color = GetPixel(collisionDC, left + i, top);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);
			if ((r == 255 && g == 255 && b == 255))
			{
				bWidthCollision = true;
				_bLife = false;
				break;
			}
			// 왼쪽 아래
			else
			{
				color = GetPixel(collisionDC, left + i, bottom);
				r = GetRValue(color);
				g = GetGValue(color);
				b = GetBValue(color);
				if ((r == 255 && g == 255 && b == 255))
				{
					bWidthCollision = true;
					_bLife = false;
					break;
				}
			}
		}

		//==============================
		// 오른쪽 위나 아래가 닿으면 충돌
		left = (int)(temp.getMinX());
		top = (int)((temp.getMinY() + img->getHeight() + 5) - WINSIZEY);
		right = (int)(temp.getMaxX());
		bottom = (int)((temp.getMaxY() + img->getHeight() - 10) - WINSIZEY);
		// 오른쪽 위

		bWidthCollision = false;
		for (int i = -20; i <= 0; i++)
		{
			color = GetPixel(collisionDC, right + i, top);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if ((r == 255 && g == 255 && b == 255))
			{
				bWidthCollision = true;
				_bLife = false;
				break;
			}
			// 오른쪽 아래
			else
				color = GetPixel(collisionDC, right + i, bottom);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if ((r == 255 && g == 255 && b == 255))
			{
				bWidthCollision = true;
				_bLife = false;
				break;
			}
		}
	}
}
