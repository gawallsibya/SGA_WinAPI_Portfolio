#include "stdafx.h"
#include "titleScene.h"


titleScene::titleScene() : 
_bg(nullptr),
_startBtn(nullptr),
_exitBtn(nullptr)
{
}


titleScene::~titleScene()
{
	release();
}

HRESULT titleScene::init(void)
{
	_bg = new image;
	_bg->init("ImageResource/bg_title.bmp", 1600, 900, false, RGB(255, 0, 255));

	_startBtn = IMAGEMANAGER->addImage("start_off_btn", "ImageResource/start_off_btn.bmp", 0, 0, 1600, 900, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("start_on_btn", "ImageResource/start_on_btn.bmp", 0, 0, 1600, 900, false, RGB(255, 0, 255));
	
	_exitBtn = IMAGEMANAGER->addImage("exit_off_btn", "ImageResource/exit_off_btn.bmp", 0, 0, 1600, 900, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("exit_on_btn", "ImageResource/exit_on_btn.bmp", 0, 0, 1600, 900, false, RGB(255, 0, 255));

	_stelectedBtn = BTN_START;

	return S_OK;
}

void titleScene::release(void)
{
	SAFE_DELETE(_bg);
	_startBtn = nullptr;
	_exitBtn = nullptr;
}

//움직여야 하는 코드들...
void titleScene::update(void)
{
	buttonStateUpdate();
	buttonImageUpdate();
}

void titleScene::render(void)
{
	//타임매니져 렌더
	//TIMEMANAGER->render(getMemDC());
	_bg->render(getMemDC(), 0, 0);
	_startBtn->alphaRender(getMemDC(), 0, 0, 100, true);
	_exitBtn->alphaRender(getMemDC(), 0, 0, 255, true);

	this->getBackBuffer()->render(getHDC(), 0, 0);
}

void titleScene::buttonStateUpdate()
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_stelectedBtn = (BTN_STYLE)(_stelectedBtn + 1);
		if (_stelectedBtn >= BTN_MAX) _stelectedBtn = (BTN_STYLE)(_stelectedBtn - BTN_MAX);
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_stelectedBtn = (BTN_STYLE)(_stelectedBtn - 1);
		if (_stelectedBtn < 0) _stelectedBtn = (BTN_STYLE)(_stelectedBtn + BTN_MAX);
	}
	
	if (KEYMANAGER->isOnceKeyDown(13))
	{
		switch (_stelectedBtn)
		{
		case titleScene::BTN_START:
			SCENEMANAGER->changeScene("loadingScene");
			break;
		case titleScene::BTN_EXIT:
			PostMessage(_hWnd, WM_DESTROY, 0, 0);
			break;
		default:
			break;
		}
	}
	

}

void titleScene::buttonImageUpdate()
{
	switch (_stelectedBtn)
	{
	case titleScene::BTN_START:
		_startBtn = IMAGEMANAGER->findImage("start_on_btn");
		_exitBtn = IMAGEMANAGER->findImage("exit_off_btn");
		break;
	case titleScene::BTN_EXIT:
		_exitBtn = IMAGEMANAGER->findImage("exit_on_btn");
		_startBtn = IMAGEMANAGER->findImage("start_off_btn");
		break;
	default:
		break;
	}	
}