#include "stdafx.h"
#include "gameoverScene.h"


gameoverScene::gameoverScene() :
_bg(nullptr)
{
}


gameoverScene::~gameoverScene()
{
	release();
}

HRESULT gameoverScene::init(void)
{
	_bg = new image;
	_bg->init("ImageResource/bg_gameover.bmp", 1600, 900, false, RGB(255, 0, 255));

	_blindImg = IMAGEMANAGER->findImage("stage_blind_black");
	_blindAlpha = 255.f;

	return S_OK;
}

void gameoverScene::release(void)
{
	SAFE_DELETE(_bg);
	
}

//움직여야 하는 코드들...
void gameoverScene::update(void)
{
	if (_blindAlpha > 0.f) _blindAlpha -= 3.f;
	else _blindAlpha = 0.f;

	if (KEYMANAGER->isOnceKeyDown(13))
	{
		SCENEMANAGER->changeScene("titleScene");
	}
}

void gameoverScene::render(void)
{
	//타임매니져 렌더
	//TIMEMANAGER->render(getMemDC());
	_bg->render(getMemDC(), 0, 0);
	
	if (_blindAlpha != 0.f) _blindImg->alphaRender(getMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY, false, (BYTE)_blindAlpha, false);


	this->getBackBuffer()->render(getHDC(), 0, 0);
}
