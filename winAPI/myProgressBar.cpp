#include "stdafx.h"
#include "myProgressBar.h"


myProgressBar::myProgressBar() :
_topImg(nullptr),
_bottomImg(nullptr)
{
}

myProgressBar::~myProgressBar()
{
	SAFE_DELETE(_topImg);
	SAFE_DELETE(_bottomImg);
}

void myProgressBar::init(string progressTopImageName, string progressBottomImageName, float x, float y, float width, float height,
	float maxHp, float* hpAdress, BYTE alpha1, BYTE alpha2, bool bCamera)
{
	this->setPos(x, y);
	this->setSize(width, height);

	_maxHp = maxHp;
	_targetHp = hpAdress;

	_alpha1 = alpha1;
	_alpha2 = alpha2;

	char strTopName[128];
	char strBottomName[128];

	ZeroMemory(strTopName, sizeof(strTopName));
	ZeroMemory(strBottomName, sizeof(strBottomName));

	sprintf_s(strTopName, "ImageResource/%s.bmp", progressTopImageName.c_str());
	sprintf_s(strBottomName, "ImageResource/%s.bmp", progressBottomImageName.c_str());

	_topImg = new image;
	_bottomImg = new image;
	_topImg->init(strTopName, 0.f, 0.f, (int)width, (int)height, true, RGB(255, 0, 255));
	_bottomImg->init(strBottomName, 0.f, 0.f, (int)width, (int)height, true, RGB(255, 0, 255));

	_bCamera = bCamera;
}

void myProgressBar::update()
{	
	_targetHpWidth = (*_targetHp / _maxHp) * this->getSize().width;
}

void myProgressBar::render(HDC hdc)
{
	POINT pos = { (int)this->getMinX(), (int)this->getMinY() };

	if (_bCamera) pos = CAMERAMANAGER->ConvertWorldToScreenPos(&pos);

	_bottomImg->alphaRender(hdc, pos.x, pos.y, 0, 0, (int)this->getSize().width, (int)this->getSize().height, _alpha2);
	_topImg->alphaRender(hdc, pos.x, pos.y, 0, 0, (int)_targetHpWidth, (int)this->getSize().height, _alpha1);
	
}

