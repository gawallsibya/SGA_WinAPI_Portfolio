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
	//����Ʈ �����ֳ�?
	_isRunning = false;
	//����Ʈ ����ֳ�?
	_bLife = true;
	//�̹��� �־��ش�
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
	//Ȱ��ȭ �ȵǾ� ������ ������� �ʴ´�
	if (!_isRunning) return;
	_effectAnimation->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f); //_elapsedTime);

	if (!_effectAnimation->isPlay()) killEffect();
}

void effect::render(void)
{
	//Ȱ��ȭ �ȵǾ� ������ ������� �ʴ´�
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

//����Ʈ ����
void effect::startEffect(float x, float y)
{
	//������ �ʱ�ȭ �Ǿ����� �ʴٸ� �������� �ʴ´�
	if (!_effectImage || !_effectAnimation) return;

	//�Ű������� ��ġ�� effect�� �߾����� ����
	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;
	_effectAnimation->start();
}

//����Ʈ ����
void effect::killEffect(void)
{
	_isRunning = false;
	_bLife = false;
}
