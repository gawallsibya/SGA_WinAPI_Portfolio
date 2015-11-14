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

//�ʱ�ȭ�� ���⼭~
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

//�������� �ϴ� �ڵ��...
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

	//Ÿ�ӸŴ��� ����
	//TIMEMANAGER->render(getMemDC());
	
	//����� ������ hdc�� �׸��� (������ �׳� ���Ѱ�)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}