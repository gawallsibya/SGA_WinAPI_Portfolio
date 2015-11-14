#pragma once
#include "enemy.h"

class goldCatfishState;
class missileManager;
class goldCatfish : public enemy
{
public:
	enum STATE_INFO { SI_IDLE, SI_JUMP, SI_ATTACK, SI_DIE, SI_MAX };

public:
	goldCatfish();
	~goldCatfish();

	void init(WAY way, float x, float y);
	void update();
	void render(HDC hdc);
	void release();

	void animationInit();

	void stateUpdate();

	void changeState(goldCatfishState* pNewState);
	void deltaTimeUpdate();

	void fireShotB();
	void fireGungnir();

	void boundingRectUpdate();

	void setDie();

	void setDamaged(float damage);

public:
	inline goldCatfishState* getState() { return _pState; }
	inline bool* isArrStateInfo() { return _bArrStateInfo; }
	
	inline effectManager* getEffectFrontManager() { return _effectFrontMgr; }
	inline effectManager* getEffectBackManager() { return _effectBackMgr; }

private:
	bool _bArrStateInfo[SI_MAX];

	// 점프관련
	float _velocityY;
	float _sp;

	float _attackTimer;

	goldCatfishState* _pState;	// 현재 상태
	missileManager* _pMissileMgr;

	effectManager* _effectFrontMgr;
	effectManager* _effectBackMgr;
};