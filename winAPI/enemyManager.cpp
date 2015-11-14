#include "stdafx.h"
#include "enemyManager.h"


enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
	release();
}

void enemyManager::init(void)
{
	for (enemy* temp : _lEnemyList) SAFE_DELETE(temp);
	_lEnemyList.clear();
}

void enemyManager::addEnemy(enemy* pEnemy)
{
	_lEnemyList.push_back(pEnemy);
}

void enemyManager::release(void)
{
	for (_liEnemyList = _lEnemyList.begin(); _liEnemyList != _lEnemyList.end(); ++_liEnemyList)
	{
		SAFE_DELETE(*_liEnemyList);
	}
}

void enemyManager::update(void)
{
	for (_liEnemyList = _lEnemyList.begin(); _liEnemyList != _lEnemyList.end(); ++_liEnemyList)
	{
		enemyUpdate();

		enemyCheckUpdate();

		// �浹�����ʾҴٸ� ++iterator	(�����ϸ鼭 ����iterator�� �ѱ�⶧����)
		if (_liEnemyList == _lEnemyList.end()) break;
	}
}

void enemyManager::render(HDC hdc)
{
	for (_liEnemyList = _lEnemyList.begin(); _liEnemyList != _lEnemyList.end(); ++_liEnemyList)
	{
		(*_liEnemyList)->render(hdc);
	}
}

// update
void enemyManager::enemyUpdate()
{
	(*_liEnemyList)->update();
}

void enemyManager::eraseEnemy(liEnemy iter)
{
	enemy* dieEnemy = (*iter);
	_lEnemyList.erase(iter);
	SAFE_DELETE(dieEnemy);
}


void enemyManager::enemyCheckUpdate()
{
	// �� �浹��.
	if (!(*_liEnemyList)->isLife())
	{
		enemy* temp = (*_liEnemyList);
		_liEnemyList = _lEnemyList.erase(_liEnemyList);
		SAFE_DELETE(temp);
		if (_liEnemyList != _lEnemyList.begin())
			--_liEnemyList;
		return;
	}
}

//void enemyManager::setMapMemoryAddressLink(stage* const sg)
//{
//	_stage = sg;
//}