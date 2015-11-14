#pragma once
#include "character.h"

class enemy : public character
{
public:
	typedef list<enemy*>::iterator liEnemy;

public:
	enemy();
	virtual ~enemy();

	inline void AttackModeStart() { _bAttackMode = true; }
	inline void setAttackModeStop() { _bAttackMode = false; }

	inline const liEnemy getMyIterator() const { return _myIter; }
	inline void setMyIterator(liEnemy iter) { _myIter = iter; }

	inline bool isLife() { return _bLife; }
	inline void setLife(bool life) { _bLife = life; }

	virtual void setDie() = 0;
	virtual void setDamaged(float damage) = 0;

	bool attackToTarget(vector<MYRECT>* attackRts, float damage);

public:
	inline bool isAttackMode() { return _bAttackMode; }

protected:
	float _recognitionRange;
	float _attackRange;
	bool _bAttackMode;

	bool _bLife;

	liEnemy _myIter;

	myProgressBar* _hpBar;
};

