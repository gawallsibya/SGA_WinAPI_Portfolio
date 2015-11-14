#include "stdafx.h"
#include "stageManager.h"
#include "stage.h"

stageManager::stageManager() : _curStage(nullptr)
{
}


stageManager::~stageManager()
{
}


void stageManager::init()
{
	_curStage->init();
}

void stageManager::update()
{
	_curStage->update();
}

void stageManager::render(HDC hdc)
{
	_curStage->render(hdc);
}

void stageManager::changeStage(stage* newStage)
{
	if (_curStage != nullptr)
	{
		SAFE_DELETE(_curStage);
	}

	_curStage = newStage;

	_curStage->init();
}