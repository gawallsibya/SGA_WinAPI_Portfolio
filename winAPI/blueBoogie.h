#pragma once
#include "enemy.h"

class blueBoogieState;
class missileManager;
class blueBoogie : public enemy
{
public:
	enum STATE_INFO { SI_IDLE, SI_JUMP, SI_ATTACK, SI_DIE, SI_MOVE, SI_HIT, SI_MAX };

public:
	blueBoogie();
	~blueBoogie();

	void init(WAY way, float x, float y);
	void update();
	void render(HDC hdc);
	void release();

	void animationInit();

	void stateUpdate();

	void changeState(blueBoogieState* pNewState);
	void deltaTimeUpdate();

	void fireShotB();
	void fireGungnir();

	void boundingRectUpdate();

	void setDie();

	void setDamaged(float damage);

public:
	inline blueBoogieState* getState() { return _pState; }
	inline bool* isArrStateInfo() { return _bArrStateInfo; }

	inline effectManager* getEffectFrontManager() { return _effectFrontMgr; }
	inline effectManager* getEffectBackManager() { return _effectBackMgr; }

	inline float getAttackTimer() { return _attackTimer; }
	inline void setAttackTimer(float attackTimer) { _attackTimer = attackTimer; }

private:
	bool _bArrStateInfo[SI_MAX];

	// 점프관련
	float _velocityY;

	float _attackTimer;
	float _moveTimer;

	blueBoogieState* _pState;	// 현재 상태
	missileManager* _pMissileMgr;

	effectManager* _effectFrontMgr;
	effectManager* _effectBackMgr;
};