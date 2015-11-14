#include "stdafx.h"
#include "character.h"
#include "stage.h"

character::character() : 
_velocityX(0.f),
_velocityY(0.f),
_speed(0.f),
_hp(0.f),
_maxHp(0.f),
_target(nullptr)
{
}
character::~character()
{
	_velocityY = 0.f;
	_speed = 0.f;
	//SAFE_DELETE(_hpBar);
	_target = nullptr;
}

void character::calcGravity()
{
	float g = 9.8f * 3 / TIMEMANAGER->getElapsedTime();
	float d = _velocityY * TIMEMANAGER->getElapsedTime();
	_velocityY = _velocityY + g * TIMEMANAGER->getElapsedTime();
	this->moveTo(0.f, d);
}

void character::calcKnockBackRight()
{
	float g = 9.8f * 3 / TIMEMANAGER->getElapsedTime();
	float d = _velocityX * TIMEMANAGER->getElapsedTime();
	_velocityX = _velocityX + g * TIMEMANAGER->getElapsedTime();
	this->moveTo(d, 0.f);
}

void character::calcKnockBackLeft()
{
	float g = 9.8f * 3 / TIMEMANAGER->getElapsedTime();
	float d = _velocityX * TIMEMANAGER->getElapsedTime();
	_velocityX = _velocityX + g * TIMEMANAGER->getElapsedTime();
	this->moveTo(-d, 0.f);
}

void character::moveFromDamagedRect(float x, float y)
{
	for (MYRECT& temp : _damagedRt)
	{
		temp.setPos(x, y);
	}
}
void character::moveFromAttackRect(float x, float y)
{
	for (MYRECT& temp : _attackRt)
	{
		temp.setPos(x, y);
	}
}

void character::addDamagedRects(float x, float y, float width, float height, float pivotX, float pivotY)
{
	MYRECT rt;
	rt.setPos(x, y);
	rt.setSize(width, height);
	rt.setPivot(pivotX, pivotY);
	_damagedRt.push_back(rt);
	
}

void character::addAttackRects(float x, float y, float width, float height, float pivotX, float pivotY)
{
	MYRECT rt;
	rt.setPos(x, y);
	rt.setSize(width, height);
	rt.setPivot(pivotX, pivotY);
	_attackRt.push_back(rt);
}

void character::releaseAttackRects() 
{
	_attackRt.clear();
}

const bool character::isDamagedFromObjectAdress(void* damagedFromObjectAdress) 
{
	if (_damagedFromObjectAdress.find(damagedFromObjectAdress) != _damagedFromObjectAdress.end())
	{
		return true;
	}
	return false;
}

void character::addDamagedFromObjectAdress(void* damagedFromObjectAdress) 
{
	if (_damagedFromObjectAdress.find(damagedFromObjectAdress) == _damagedFromObjectAdress.end()) 
	{
		_damagedFromObjectAdress.insert(make_pair(damagedFromObjectAdress, damagedFromObjectAdress));
	}
}

void character::releaseDamagedFromObjectAdress(void* damagedFromObjectAdress) 
{
	if (_damagedFromObjectAdress.find(damagedFromObjectAdress) != _damagedFromObjectAdress.end())
	{
		_damagedFromObjectAdress.erase(_damagedFromObjectAdress.find(damagedFromObjectAdress));
	}
}


void character::pixelCollisionTopAndBottom()
{
	// 세로 맵 끝 충돌 체크
	//mapOutCollsionTopAndBottom();

	// 위나 아래가 닿으면 충돌
	image* img = this->getStageMemoryAddressLink()->getCollisionBackground();

	int left = (int)(this->getBoundingRect()->getMinX() + 5);
	int top = (int)(this->getBoundingRect()->getMinY() + img->getHeight() - WINSIZEY);
	int right = (int)(this->getBoundingRect()->getMaxX() - 5);
	int bottom = (int)(this->getBoundingRect()->getMaxY() + img->getHeight() - WINSIZEY);

	COLORREF color = NULL;
	bool bHeightCollision = false;
	int r = 0, g = 0, b = 0;

	HDC collisionDC = img->getMemDC();
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
				i += 1;
				if (this->getVelocityY() < 0.f) this->setVelocityY(1.f);
				this->setPosY(this->getPos().y + i);
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
					i += 1;
					if (this->getVelocityY() < 0.f) this->setVelocityY(1.f);
					this->setPosY(this->getPos().y + i);
					break;
				}
			}
		}
	}


	//==============================
	// 왼쪽이나 오른쪽이 닿으면 충돌
	left = (int)(this->getBoundingRect()->getMinX() + 5);
	top = (int)(this->getBoundingRect()->getMinY() + img->getHeight() - WINSIZEY);
	right = (int)(this->getBoundingRect()->getMaxX() - 5);
	bottom = (int)(this->getBoundingRect()->getMaxY() + img->getHeight() - WINSIZEY);
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
			i -= 1;
			this->setVelocityY(0.f);
			this->setPosY(this->getPos().y + i);
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
				i -= 1;
				this->setVelocityY(0.f);
				this->setPosY(this->getPos().y + i);
				break;
			}
		}
	}
		
}

void character::pixelCollisionLeftAndRight()
{
	// 가로 맵 끝 충돌 체크
	//mapOutCollsionLeftAndRight();

	// 왼쪽 위나 아래가 닿으면 충돌
	image* img = this->getStageMemoryAddressLink()->getCollisionBackground();

	int left = (int)(this->getBoundingRect()->getMinX());
	int top = (int)((this->getBoundingRect()->getMinY() + img->getHeight() + 5) - WINSIZEY);
	int right = (int)(this->getBoundingRect()->getMaxX());
	int bottom = (int)((this->getBoundingRect()->getMaxY() + img->getHeight() - 10) - WINSIZEY);

	COLORREF color = NULL;
	bool bWidthCollision = false;
	int r = 0, g = 0, b = 0;

	HDC collisionDC = img->getMemDC();

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
			i += 1;
			this->setPosX(this->getPos().x + i);
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
				i += 1;
				this->setPosX(this->getPos().x + i);
				break;
			}
		}
	}

	//==============================
	// 오른쪽 위나 아래가 닿으면 충돌
	left = (int)(this->getBoundingRect()->getMinX());
	top = (int)((this->getBoundingRect()->getMinY() + img->getHeight() + 5) - WINSIZEY);
	right = (int)(this->getBoundingRect()->getMaxX());
	bottom = (int)((this->getBoundingRect()->getMaxY() + img->getHeight() - 10) - WINSIZEY);
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
			i -= 1;
			this->setPosX(this->getPos().x + i);
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
			i -= 1;
			this->setPosX(this->getPos().x + i);
			break;
		}
	}
}