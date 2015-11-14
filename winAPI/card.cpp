#include "stdafx.h"
#include "card.h"


card::card() : 
_card(nullptr),
_blind(nullptr),
_maxSp(0.f),
_targetSp(nullptr),
_targetSpHeight(0.f),
_bOnAura(false)
{
}


card::~card()
{
	release();
}

void card::init(string imageName, float x, float y, float width, float height, float maxSp, float* targetSp)
{
	this->setPos(x, y);
	this->setSize(width, height);

	_maxSp = maxSp;
	_targetSp = targetSp;

	
	char strCardName[128];

	ZeroMemory(strCardName, sizeof(strCardName));

	sprintf_s(strCardName, "ImageResource/%s.bmp", imageName.c_str());
	
	_card = new image;
	_card->init(strCardName, 0.f, 0.f, (int)width, (int)height, false, RGB(255, 0, 255));
	_blind = new image;
	_blind->init("ImageResource/card_blind.bmp", 0.f, 0.f, (int)width, (int)height, false, RGB(255, 0, 255));
	_aura = new image;
	_aura->init("ImageResource/card_aura.bmp", 0.f, 0.f, ((int)width + 23) * 10, ((int)height + 31) * 2, 10, 2, false, RGB(255, 0, 255));
	_auraAni = new animation;
	_auraAni->init(_aura->getWidth(), _aura->getHeight(), _aura->getFrameWidth(), _aura->getFrameHeight());
	_auraAni->setFPS((_auraAni->getMaxFrame() + 1) / 0.5f);
	_auraAni->setDefPlayFrame(false, true);

	_bOnAura = false;

}

void card::update()
{
	*_targetSp > _maxSp ?
		_targetSpHeight = 0.f :
		_targetSpHeight = this->getSize().height - ((*_targetSp / _maxSp) * this->getSize().height);

	_auraAni->frameUpdate(TIMEMANAGER->getElapsedTime());

	if (*_targetSp >= _maxSp && !_bOnAura)
	{
		_bOnAura = true;
		_auraAni->start();
	}
	else if (*_targetSp < _maxSp && _bOnAura)
	{
		_bOnAura = false;
		_auraAni->stop();
	}
}	

void card::render(HDC hdc)
{
	_card->render(hdc, (int)this->getMinX(),
		(int)this->getMinY(), 0, 0, (int)this->getSize().width, (int)this->getSize().height);

	_blind->render(hdc, (int)this->getMinX(),
		(int)this->getMinY(), 0, 0, (int)this->getSize().width, (int)_targetSpHeight);
	
	if (_bOnAura == true)
	{
		_aura->aniAlphaRender(hdc, (int)this->getMinX() - 12,
			(int)this->getMinY() - 16, _auraAni, false, 255, true);
	}
}

void card::release()
{
	SAFE_DELETE(_card);
	SAFE_DELETE(_blind);

	_maxSp = 0.f;
	_targetSp = nullptr;

	_targetSpHeight = 0.f;
}