#include "stdafx.h"
#include "clearScene.h"


clearScene::clearScene() :
_bg(nullptr)
{
}


clearScene::~clearScene()
{
	release();
}

HRESULT clearScene::init(void)
{
	_bg = new image;
	_bg->init("ImageResource/bg_clear.bmp", 1600, 900, false, RGB(255, 0, 255));

	_blindImg = IMAGEMANAGER->findImage("stage_blind_white");
	_blindAlpha = 255.f;

	return S_OK;
}

void clearScene::release(void)
{
	SAFE_DELETE(_bg);

}

//움직여야 하는 코드들...
void clearScene::update(void)
{
	if (_blindAlpha > 0.f) _blindAlpha -= 1.f;
	else _blindAlpha = 0.f;

	if (KEYMANAGER->isOnceKeyDown(13))
	{
		SCENEMANAGER->changeScene("titleScene");
	}
}

void clearScene::render(void)
{
	//타임매니져 렌더
	//TIMEMANAGER->render(getMemDC());
	_bg->render(getMemDC(), 0, 0);

	if (_blindAlpha != 0.f) _blindImg->alphaRender(getMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY, false, (BYTE)_blindAlpha, false);


	this->getBackBuffer()->render(getHDC(), 0, 0);
}
