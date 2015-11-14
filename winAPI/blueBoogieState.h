#pragma once
#include "stage.h"

class blueBoogie;
class blueBoogieState
{
public:
	virtual inline ~blueBoogieState() {}

public:
	// 상태 진입
	virtual void enter(blueBoogie* pCha) = 0;	// = 0  PURE VIRTUAL.
	// 상태 진행중
	virtual void execute(blueBoogie* pCha) = 0;
	// 상태 이탈
	virtual void exit(blueBoogie* pCha) = 0;

	//virtual void change

};

//========== blueBoogieState_idle
class blueBoogieState_idle : public blueBoogieState
{
public:
	inline blueBoogieState_idle(){}
	inline ~blueBoogieState_idle(){}

private:
	virtual void enter(blueBoogie* pCha);
	virtual void execute(blueBoogie* pCha);
	virtual void exit(blueBoogie* pCha);
};
//==========

//========== blueBoogieState_die
class blueBoogieState_die : public blueBoogieState
{
public:
	inline blueBoogieState_die(){}
	inline ~blueBoogieState_die(){}

private:
	virtual void enter(blueBoogie* pCha);
	virtual void execute(blueBoogie* pCha);
	virtual void exit(blueBoogie* pCha);

private:
	bool _bMoveStop;
};
//==========

//========== blueBoogieState_walk_forward
class blueBoogieState_walk_forward : public blueBoogieState
{
public:
	inline blueBoogieState_walk_forward(){}
	inline ~blueBoogieState_walk_forward(){}

private:
	virtual void enter(blueBoogie* pCha);
	virtual void execute(blueBoogie* pCha);
	virtual void exit(blueBoogie* pCha);

private:
	float _movingTime;
};
//==========


//========== blueBoogieState_attack_ready1
class blueBoogieState_attack_ready1 : public blueBoogieState
{
public:
	inline blueBoogieState_attack_ready1(){}
	inline ~blueBoogieState_attack_ready1(){}

private:
	virtual void enter(blueBoogie* pCha);
	virtual void execute(blueBoogie* pCha);
	virtual void exit(blueBoogie* pCha);
};
//==========
//========== blueBoogieState_attack_start1
class blueBoogieState_attack_start1 : public blueBoogieState
{
public:
	inline blueBoogieState_attack_start1(){}
	inline ~blueBoogieState_attack_start1(){}

private:
	virtual void enter(blueBoogie* pCha);
	virtual void execute(blueBoogie* pCha);
	virtual void exit(blueBoogie* pCha);

private:
	float _damage;
};
//==========
//========== blueBoogieState_attack_ready2
class blueBoogieState_attack_ready2 : public blueBoogieState
{
public:
	inline blueBoogieState_attack_ready2(){}
	inline ~blueBoogieState_attack_ready2(){}

private:
	virtual void enter(blueBoogie* pCha);
	virtual void execute(blueBoogie* pCha);
	virtual void exit(blueBoogie* pCha);
};
//==========
//========== blueBoogieState_attack_start2
class blueBoogieState_attack_start2 : public blueBoogieState
{
public:
	inline blueBoogieState_attack_start2(){}
	inline ~blueBoogieState_attack_start2(){}

private:
	virtual void enter(blueBoogie* pCha);
	virtual void execute(blueBoogie* pCha);
	virtual void exit(blueBoogie* pCha);

private:
	float _damage;
	float _deltaTime;
};
//==========
//========== blueBoogieState_hit_forward
class blueBoogieState_hit_forward : public blueBoogieState
{
public:
	inline blueBoogieState_hit_forward(){}
	inline ~blueBoogieState_hit_forward(){}

private:
	virtual void enter(blueBoogie* pCha);
	virtual void execute(blueBoogie* pCha);
	virtual void exit(blueBoogie* pCha);

private:
	bool _bOnEffect;
	float _deltaTime;
};
//===========