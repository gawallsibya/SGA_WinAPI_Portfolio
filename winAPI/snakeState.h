#pragma once
#include "stage.h"

class snake;
class snakeState
{
public:
	virtual inline ~snakeState() {}

public:
	// 상태 진입
	virtual void enter(snake* pCha) = 0;	// = 0  PURE VIRTUAL.
	// 상태 진행중
	virtual void execute(snake* pCha) = 0;
	// 상태 이탈
	virtual void exit(snake* pCha) = 0;

	//virtual void change

};

//========== snakeState_idle
class snakeState_idle : public snakeState
{
public:
	inline snakeState_idle(){}
	inline ~snakeState_idle(){}

private:
	virtual void enter(snake* pCha);
	virtual void execute(snake* pCha);
	virtual void exit(snake* pCha);
};
//==========

//========== snakeState_die
class snakeState_die : public snakeState
{
public:
	inline snakeState_die(){}
	inline ~snakeState_die(){}

private:
	virtual void enter(snake* pCha);
	virtual void execute(snake* pCha);
	virtual void exit(snake* pCha);

private:
	bool _bMoveStop;
};
//==========

//========== snakeState_walk_forward
class snakeState_walk_forward : public snakeState
{
public:
	inline snakeState_walk_forward(){}
	inline ~snakeState_walk_forward(){}

private:
	virtual void enter(snake* pCha);
	virtual void execute(snake* pCha);
	virtual void exit(snake* pCha);

private:
	float _movingTime;
};
//==========


//========== snakeState_attack_ready
class snakeState_attack_ready : public snakeState
{
public:
	inline snakeState_attack_ready(){}
	inline ~snakeState_attack_ready(){}

private:
	virtual void enter(snake* pCha);
	virtual void execute(snake* pCha);
	virtual void exit(snake* pCha);
};
//==========
//========== snakeState_attack_start
class snakeState_attack_start : public snakeState
{
public:
	inline snakeState_attack_start(){}
	inline ~snakeState_attack_start(){}

private:
	virtual void enter(snake* pCha);
	virtual void execute(snake* pCha);
	virtual void exit(snake* pCha);

private:
	float _damage;
	float _dlayTime;
};
//==========
//========== snakeState_attack_end
class snakeState_attack_end : public snakeState
{
public:
	inline snakeState_attack_end(){}
	inline ~snakeState_attack_end(){}

private:
	virtual void enter(snake* pCha);
	virtual void execute(snake* pCha);
	virtual void exit(snake* pCha);

};
//==========
//========== snakeState_hit_forward
class snakeState_hit_forward : public snakeState
{
public:
	inline snakeState_hit_forward(){}
	inline ~snakeState_hit_forward(){}

private:
	virtual void enter(snake* pCha);
	virtual void execute(snake* pCha);
	virtual void exit(snake* pCha);

private:
	bool _bOnEffect;
	float _deltaTime;
};
//===========