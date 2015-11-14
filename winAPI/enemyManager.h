#pragma once
#include "goldCatfish.h"
#include "snake.h"
#include "blueBoogie.h"
#include "missileManager.h"
class remilia;
class enemyManager : public singletonBase<enemyManager>
{
public:

	typedef list<enemy*> lEnemy;
	typedef list<enemy*>::iterator liEnemy;

public:
	enemyManager();
	~enemyManager();

	void init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	inline lEnemy& getLEnemyList(void) { return _lEnemyList; }
	inline liEnemy& getLIEnemyList(void) { return _liEnemyList; }

	inline void releaseDamagedFromObjectAdress(void* damagedFromObjectAdress) { for (enemy* temp : _lEnemyList) temp->releaseDamagedFromObjectAdress(damagedFromObjectAdress); }
	void addEnemy(enemy* pEnemy);
	
	void eraseEnemy(liEnemy iter);


private:
	void enemyUpdate();
	void enemyCheckUpdate();

public:
	lEnemy _lEnemyList;
	liEnemy _liEnemyList;

	missileManager* _missileMgr;

};