#pragma once
#include "gungnir.h"
#include "shot_b.h"
#include <list>

class stage;
class missileManager : public singletonBase<missileManager>
{
	typedef list<missile*> lMissile;
	typedef list<missile*>::iterator liMissile;

public:
	missileManager();
	~missileManager();

	void init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	inline list<missile*>& getLMissileList(void) { return _lMissileList; }
	inline list<missile*>::iterator& getLIMissileList(void) { return _liMissileList; }

	void createMissile(character* master, missile* missileType, float x, float y, VECTOR2D vMovePos, bool reverse, stage* _curStage);

	void removeMissile(int arrNum);
	void setTarget(object* target);

	void setMapMemoryAddressLink(stage* const sg);

private: 
	// update
	void missileUpdate();
	void missileCheckUpdate();

public:
	lMissile _lMissileList;
	liMissile _liMissileList;

	//주소값 받아오는 포인터변수, delete하면 안됨.
	stage* _stage;
	object* _target;
};

