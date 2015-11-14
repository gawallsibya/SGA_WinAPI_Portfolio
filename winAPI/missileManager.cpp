#include "stdafx.h"
#include "missileManager.h"

missileManager::missileManager() : _target(nullptr)
{
}

missileManager::~missileManager()
{
	release();
}

void missileManager::init(void)
{
	_lMissileList.clear();
}

void missileManager::createMissile(character* master, missile* missileType, float x, float y, VECTOR2D vMovePos, bool reverse, stage* _curStage)
{
	missileType->init(master, x, y, vMovePos, reverse);
	missileType->setStageMemoryAddressLink(_curStage);
	_lMissileList.push_back(missileType);
	missileType->setMyIterator(_lMissileList.end());
}

void missileManager::release(void)
{
	for (_liMissileList = _lMissileList.begin(); _liMissileList != _lMissileList.end(); ++_liMissileList)
	{
		SAFE_DELETE(*_liMissileList);
	}

	_stage = nullptr;
	_target = nullptr;
}

void missileManager::setTarget(object* target)
{
	_target = target;
}

void missileManager::update(void)
{
	for (_liMissileList = _lMissileList.begin(); _liMissileList != _lMissileList.end(); ++_liMissileList)
	{
		missileUpdate();
		
		missileCheckUpdate();

		// �浹�����ʾҴٸ� ++iterator	(�����ϸ鼭 ����iterator�� �ѱ�⶧����)
		if (_liMissileList == _lMissileList.end()) break;
			
	}
}

void missileManager::render(HDC hdc)
{
	for (_liMissileList = _lMissileList.begin(); _liMissileList != _lMissileList.end(); ++_liMissileList)
	{
		(*_liMissileList)->render(hdc);
	}
}

// update
void missileManager::missileUpdate()
{
	(*_liMissileList)->update();
}

void missileManager::missileCheckUpdate()
{	
	// �׾��� ���..
	if (!(*_liMissileList)->isLife())
	{
		missile* temp = (*_liMissileList);
		_liMissileList = _lMissileList.erase(_liMissileList);
		SAFE_DELETE(temp);
		if (_liMissileList != _lMissileList.begin()) 
			--_liMissileList;
		return;
	}
}

void missileManager::setMapMemoryAddressLink(stage* const sg)
{
	_stage = sg;
}