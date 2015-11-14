#pragma once
#include "stage.h"

class goldCatfish;
class goldCatfishState
{
public:
	virtual inline ~goldCatfishState() {}

public:
	// 상태 진입
	virtual void enter(goldCatfish* pCha) = 0;	// = 0  PURE VIRTUAL.
	// 상태 진행중
	virtual void execute(goldCatfish* pCha) = 0;
	// 상태 이탈
	virtual void exit(goldCatfish* pCha) = 0;

	//virtual void change

};

//========== goldCatfishState_idle
class goldCatfishState_idle : public goldCatfishState
{
public:
	inline goldCatfishState_idle(){}
	inline ~goldCatfishState_idle(){}

private:
	virtual void enter(goldCatfish* pCha);
	virtual void execute(goldCatfish* pCha);
	virtual void exit(goldCatfish* pCha);
};
//==========

//========== goldCatfishState_jump_ready
class goldCatfishState_jump_ready : public goldCatfishState
{
public:
	inline goldCatfishState_jump_ready(){}
	inline ~goldCatfishState_jump_ready(){}

private:
	virtual void enter(goldCatfish* pCha);
	virtual void execute(goldCatfish* pCha);
	virtual void exit(goldCatfish* pCha);
};
//==========
//========== goldCatfishState_jump_start
class goldCatfishState_jump_start : public goldCatfishState
{
public:
	inline goldCatfishState_jump_start(){}
	inline ~goldCatfishState_jump_start(){}

private:
	virtual void enter(goldCatfish* pCha);
	virtual void execute(goldCatfish* pCha);
	virtual void exit(goldCatfish* pCha);

private:
	float _disX;
	float _damage;
	bool _bDownAttacked;
};
//==========

//========== goldCatfishState_die
class goldCatfishState_die : public goldCatfishState
{
public:
	inline goldCatfishState_die(){}
	inline ~goldCatfishState_die(){}

private:
	virtual void enter(goldCatfish* pCha);
	virtual void execute(goldCatfish* pCha);
	virtual void exit(goldCatfish* pCha);
	
private:
	bool _bMoveStop;
	float _deltaTime;
};
//==========

//========== goldCatfishState_spark_ready
class goldCatfishState_spark_ready : public goldCatfishState
{
public:
	inline goldCatfishState_spark_ready(){}
	inline ~goldCatfishState_spark_ready(){}

private:
	virtual void enter(goldCatfish* pCha);
	virtual void execute(goldCatfish* pCha);
	virtual void exit(goldCatfish* pCha);
};
//==========
//========== goldCatfishState_spark_start
class goldCatfishState_spark_start : public goldCatfishState
{
public:
	inline goldCatfishState_spark_start(){}
	inline ~goldCatfishState_spark_start(){}

private:
	virtual void enter(goldCatfish* pCha);
	virtual void execute(goldCatfish* pCha);
	virtual void exit(goldCatfish* pCha);

private:
	float _damage;
	bool _bOnEffect;
	float _deltaTime;
};
//==========