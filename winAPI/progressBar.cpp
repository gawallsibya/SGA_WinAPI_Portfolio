#include "stdafx.h"
#include "progressBar.h"

progressBar::progressBar(void)
{
}

progressBar::~progressBar(void)
{
}

void progressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarTop = IMAGEMANAGER->addImage("barTop", "hpBarTop.bmp", static_cast<float>(x), static_cast<float>(y), width, height, true, RGB(255, 0, 255));
	_progressBarBottom = IMAGEMANAGER->addImage("barBottom", "hpBarBottom.bmp", static_cast<float>(x), static_cast<float>(y), width, height, true, RGB(255, 0, 255));

	_width = static_cast<float>(_progressBarTop->getWidth());
}

void progressBar::init(string topImageKeyName, string bottomImageKeyName,
	int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMakeCenter(x, y, width, height);

	char strTopName[128];
	char strBottomName[128];

	ZeroMemory(strTopName, sizeof(strTopName));
	ZeroMemory(strBottomName, sizeof(strBottomName));

	sprintf_s(strTopName, "ImageResource/%s.bmp", topImageKeyName.c_str());
	sprintf_s(strBottomName, "ImageResource/%s.bmp", bottomImageKeyName.c_str());

	_progressBarTop = IMAGEMANAGER->addImage(topImageKeyName, strTopName, (float)x, (float)y, width, height, true, RGB(255, 0, 255));
	_progressBarBottom = IMAGEMANAGER->addImage(bottomImageKeyName, strBottomName, (float)x, (float)y, width, height, true, RGB(255, 0, 255));

	_width = static_cast<float>(_progressBarTop->getWidth());
}

void progressBar::release(void)
{
}

void progressBar::update(void)
{
	_rcProgress = RectMakeCenter(_x + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2, _progressBarBottom->getWidth(), _progressBarBottom->getHeight());
}

void progressBar::render(HDC hdc)
{
	_progressBarBottom->render(hdc, _rcProgress.left,
		_y, 0, 0, _progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	_progressBarTop->render(hdc, _rcProgress.left,
		_y, 0, 0, (int)_width, _progressBarTop->getHeight());
}

void progressBar::setGauge(float HP, float maxHP)
{
	_width = (HP / maxHP) * _progressBarBottom->getWidth();
}
