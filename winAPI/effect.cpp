#include "StdAfx.h"
#include "effect.h"
#include "image.h"
#include "animation.h"

effect::effect(void) : _effectImage(NULL), _effectAnimation(NULL), _isRunning(false), _x(0), _y(0), _bLife(true), _bReverse(false), _bAlphaFormat(false)
{
}

effect::~effect(void)
{
	release();
}

HRESULT effect::init(image* effectImage, animation* effectAnimation, bool reverse, BYTE alpha, bool bAlphaFormat, bool bCamera)
{
	//이펙트 돌고있냐?
	_isRunning = false;
	//이펙트 살아있나?
	_bLife = true;
	//이미지 넣어준다
	_effectImage = effectImage;
	_effectAnimation = new animation(*effectAnimation);
	_bReverse = reverse;
	_alpha = alpha;
	_bAlphaFormat = bAlphaFormat;
	_bCamera = bCamera;

	return S_OK;
}

void effect::release(void)
{
	_effectImage = NULL;
	SAFE_DELETE(_effectAnimation);
}

void effect::update(void)
{
	//활성화 안되어 있으면 실행되지 않는다
	if (!_isRunning) return;
	_effectAnimation->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f); //_elapsedTime);

	if (!_effectAnimation->isPlay()) killEffect();
}

void effect::render(void)
{
	//활성화 안되어 있으면 실행되지 않는다
	if (!_isRunning) return;

	POINT pos = { (int)_x, (int)_y };
	
	if (_bCamera) pos = CAMERAMANAGER->ConvertWorldToScreenPos(&pos);
	
	
	if (_bAlphaFormat)
	{
		_effectImage->aniAlphaRender(getMemDC(), pos.x, pos.y, _effectAnimation, _bReverse, _alpha, _bAlphaFormat);
	}
	else if (_alpha != 255)
	{
		_effectImage->alphaRender(getMemDC(), pos.x, pos.y, _effectAnimation->getFramePos().x, _effectAnimation->getFramePos().y,
			_effectAnimation->getFrameWidth(), _effectAnimation->getFrameHeight(), _bReverse, _alpha);
	}
	else
	{
		_effectImage->aniRender(getMemDC(), pos.x, pos.y, _effectAnimation, _bReverse);
	}
}

//이펙트 시작
void effect::startEffect(float x, float y)
{
	//정보가 초기화 되어있지 않다면 실행하지 않는닫
	if (!_effectImage || !_effectAnimation) return;

	//매개변수의 위치를 effect의 중앙으로 본다
	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;
	_effectAnimation->start();
}

//이펙트 살인
void effect::killEffect(void)
{
	_isRunning = false;
	_bLife = false;
}
