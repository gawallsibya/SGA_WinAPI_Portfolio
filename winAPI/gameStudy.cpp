#include "stdafx.h"
#include "gameStudy.h"
#include "gameScene.h"
#include "remilia.h"
#include "loadScene.h"
#include "titleScene.h"
#include "gameoverScene.h"
#include "clearScene.h"

gameStudy::gameStudy(void)
{
}

gameStudy::~gameStudy(void)
{
}

//초기화는 여기서~
HRESULT gameStudy::init(void)
{
	ShowCursor(false);
	gameNode::init(true);
	
	SCENEMANAGER->addScene("titleScene", new titleScene);
	SCENEMANAGER->addScene("gameScene", new gameScene);
	SCENEMANAGER->addScene("loadingScene", new loadScene);
	SCENEMANAGER->addScene("clearScene", new clearScene);
	SCENEMANAGER->addScene("gameoverScene", new gameoverScene);
	SCENEMANAGER->changeScene("titleScene");
	
	return S_OK;
}

void gameStudy::release(void)
{
	gameNode::release();

}

//움직여야 하는 코드들...
void gameStudy::update(void)
{
	SCENEMANAGER->update();
	KEYANIMANAGER->update();
	//EFFECTMANAGER->update();
}

void gameStudy::render(void)
{
	gameNode::render();

	SCENEMANAGER->render();
	//EFFECTMANAGER->render();

	//타임매니져 렌더
	//TIMEMANAGER->render(getMemDC());
	
	//백버퍼 내용을 hdc에 그린다 (렌더에 그냥 놔둘것)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}