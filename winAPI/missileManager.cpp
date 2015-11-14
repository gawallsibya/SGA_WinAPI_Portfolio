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

		// 충돌하지않았다면 ++iterator	(삭제하면서 다음iterator로 넘기기때문에)
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
	// 죽었을 경우..
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