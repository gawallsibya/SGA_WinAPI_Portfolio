#pragma once
#include "singletonBase.h"
#include "character.h"
#include "missileManager.h"
#include "remiliaState.h"

class remilia : public character, public singletonBase<remilia>
{
public:
	enum STATE_INFO { SI_IDLE, SI_MOVE, SI_DASH, SI_JUMP, SI_SIT, SI_ATTACK, SI_HITDOWN, SI_COMBO, SI_MAX };
	enum COMBO_A1 { CA1_NULL, CA1_1, CA1_2, CA1_3, CA1_4 };
	enum ATTACK_STYLE { AS_NULL, AS_A1, AS_A3, AS_C1, AS_HUYAJYOU, AS_MAX };
private:

public:
	remilia();
	~remilia();

	void init();
	void update();
	void render(HDC hdc);
	void release();

	void animationInit();

	void stateUpdate();
	void commandUpdate();

	void changeState(remiliaState* pNewState);
	void deltaTimeUpdate();
	
	void fireShotB();
	void fireGungnir();

	bool attackToEnemys(vector<MYRECT>* attackRts, float damage);

	virtual void boundingRectUpdate();
	virtual void setDie();
	virtual void setDamaged(float damage);

public:
	inline remiliaState* getState() { return _pState; }
	inline bool* isArrStateInfo() { return _bArrStateInfo; }
	inline WAY getWay() { return _way; }

	inline missileManager* getMissileManager() { return _pMissileMgr; }
	inline effectManager* getEffectManager() { return _effectMgr; }

	inline float* getSPAdress() { return &_sp; }
	inline const float& getMaxSP() const { return _maxSp; }
	inline const float getSP() const { return _sp; }
	inline void setSP(float sp) { _sp = sp; }

	inline void addSP(float sp) { _sp += sp; if (_sp > _maxSp) _sp = _maxSp; }
	inline void subSP(float sp) { _sp -= sp; if (_sp < 0.f) _sp = 0.f; }

	inline const ATTACK_STYLE getAttackStyle() const { return _attackStyle; }
	inline void setAttackStyle(ATTACK_STYLE attackStyle) { _attackStyle = attackStyle; }

private:
	bool _bArrStateInfo[SI_MAX];

	// 콤보관련
	COMBO_A1 _combo_a1;
	float _comboTimer;

	float _sp;
	float _maxSp;

	float _dashTimer;
	WAY _prevWay;

	BYTE _prevKey;

	ATTACK_STYLE _attackStyle;

	remiliaState* _pState;	// 현재 상태
	missileManager* _pMissileMgr;

	effectManager* _effectMgr;

	myProgressBar* _spBar;

};
