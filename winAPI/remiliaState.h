#pragma once
#include "stage.h"
class remilia;
class remiliaState
{
public:
	virtual inline ~remiliaState() {}

public:
	// 상태 진입
	virtual void enter(remilia* pCha) = 0;	// = 0  PURE VIRTUAL.
	// 상태 진행중
	virtual void execute(remilia* pCha) = 0;
	// 상태 이탈
	virtual void exit(remilia* pCha) = 0;
};

//========== remiliaState_idle
class remiliaState_idle : public remiliaState
{
public:
	inline remiliaState_idle(){}
	inline ~remiliaState_idle(){}

private:
	virtual void enter(remilia* pCha);	
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//==========

//========== remiliaState_walk_forward
class remiliaState_walk_forward : public remiliaState
{

public:
	inline remiliaState_walk_forward(){}
	inline ~remiliaState_walk_forward(){}

private:
	virtual void enter(remilia* pCha);	
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========

//=========== remiliaState_dash_forward_ready
class remiliaState_dash_forward_ready : public remiliaState
{
public:
	inline remiliaState_dash_forward_ready(){}
	inline ~remiliaState_dash_forward_ready(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

};
//===========
//=========== remiliaState_dash_forward_start
class remiliaState_dash_forward_start : public remiliaState
{
public:
	inline remiliaState_dash_forward_start(){}
	inline ~remiliaState_dash_forward_start(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

};
//===========
//=========== remiliaState_dash_forward_end
class remiliaState_dash_forward_end : public remiliaState
{
public:
	inline remiliaState_dash_forward_end(){}
	inline ~remiliaState_dash_forward_end(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

};
//===========

//=========== remiliaState_dash_back_ready
class remiliaState_dash_back_ready : public remiliaState
{
public:
	inline remiliaState_dash_back_ready(){}
	inline ~remiliaState_dash_back_ready(){}

private:
	virtual void enter(remilia* pCha);	
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========
//=========== remiliaState_dash_back_start
class remiliaState_dash_back_start : public remiliaState
{
public:
	inline remiliaState_dash_back_start(){}
	inline ~remiliaState_dash_back_start(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========
//=========== remiliaState_dash_back_end
class remiliaState_dash_back_end : public remiliaState
{
public:
	inline remiliaState_dash_back_end(){}
	inline ~remiliaState_dash_back_end(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========

//=========== remiliaState_attack_a1_start
class remiliaState_attack_a1_start : public remiliaState
{
public:
	inline remiliaState_attack_a1_start(){}
	inline ~remiliaState_attack_a1_start(){}
	
private:
	virtual void enter(remilia* pCha);	
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
	
private:
	float _damage;
};
//===========
//=========== remiliaState_attack_a1_end
class remiliaState_attack_a1_end : public remiliaState
{
public:
	inline remiliaState_attack_a1_end(){}
	inline ~remiliaState_attack_a1_end(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========

//=========== remiliaState_attack_a3_start1
class remiliaState_attack_a3_start1 : public remiliaState
{
public:
	inline remiliaState_attack_a3_start1(){}
	inline ~remiliaState_attack_a3_start1(){}

private:
	virtual void enter(remilia* pCha);	
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bOnEffect;
	float _damage;
};
//===========
//=========== remiliaState_attack_a3_start2
class remiliaState_attack_a3_start2 : public remiliaState
{
public:
	inline remiliaState_attack_a3_start2(){}
	inline ~remiliaState_attack_a3_start2(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bOnEffect;
	float _damage;
};
//===========
//=========== remiliaState_attack_a3_end
class remiliaState_attack_a3_end : public remiliaState
{
public:
	inline remiliaState_attack_a3_end(){}
	inline ~remiliaState_attack_a3_end(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========

//=========== remiliaState_attack_c1_start
class remiliaState_attack_c1_start : public remiliaState
{
public:
	inline remiliaState_attack_c1_start(){}
	inline ~remiliaState_attack_c1_start(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bOnEffect;
	float _damage;
};
//===========
//=========== remiliaState_attack_c1_end
class remiliaState_attack_c1_end : public remiliaState
{
public:
	inline remiliaState_attack_c1_end(){}
	inline ~remiliaState_attack_c1_end(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========

//=========== remiliaState_shot_b_start
class remiliaState_shot_b_start : public remiliaState
{
public:
	inline remiliaState_shot_b_start(){}
	inline ~remiliaState_shot_b_start(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========
//=========== remiliaState_shot_b_end
class remiliaState_shot_b_end : public remiliaState
{
public:
	inline remiliaState_shot_b_end(){}
	inline ~remiliaState_shot_b_end(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========

//========== remiliaState_jump_ready
class remiliaState_jump_ready : public remiliaState
{
public:
	inline remiliaState_jump_ready(){}
	inline ~remiliaState_jump_ready(){}

private:
	virtual void enter(remilia* pCha);	
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========
//========== remiliaState_jump_start
class remiliaState_jump_start : public remiliaState
{
public:
	inline remiliaState_jump_start(){}
	inline ~remiliaState_jump_start(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========
//========== remiliaState_jump_end
class remiliaState_jump_end : public remiliaState
{
public:
	inline remiliaState_jump_end(){}
	inline ~remiliaState_jump_end(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========

//========== remiliaState_dash_forward_air_ready
class remiliaState_dash_forward_air_ready : public remiliaState
{
public:
	inline remiliaState_dash_forward_air_ready(){}
	inline ~remiliaState_dash_forward_air_ready(){}

private:
	virtual void enter(remilia* pCha);	
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========
//========== remiliaState_dash_forward_air_start
class remiliaState_dash_forward_air_start : public remiliaState
{
public:
	inline remiliaState_dash_forward_air_start(){}
	inline ~remiliaState_dash_forward_air_start(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bSetDamagedRects;
};
//===========
//========== remiliaState_dash_forward_air_end
class remiliaState_dash_forward_air_end : public remiliaState
{
public:
	inline remiliaState_dash_forward_air_end(){}
	inline ~remiliaState_dash_forward_air_end(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========

//========== remiliaState_dash_back_air_ready
class remiliaState_dash_back_air_ready : public remiliaState
{
public:
	inline remiliaState_dash_back_air_ready(){}
	inline ~remiliaState_dash_back_air_ready(){}

private:
	virtual void enter(remilia* pCha);	
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========
//========== remiliaState_dash_back_air_start
class remiliaState_dash_back_air_start : public remiliaState
{
public:
	inline remiliaState_dash_back_air_start(){}
	inline ~remiliaState_dash_back_air_start(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bSetDamagedRects;
};
//===========
//========== remiliaState_dash_back_air_end
class remiliaState_dash_back_air_end : public remiliaState
{
public:
	inline remiliaState_dash_back_air_end(){}
	inline ~remiliaState_dash_back_air_end(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========

//========== remiliaState_sit_start
class remiliaState_sit_start : public remiliaState
{
public:
	inline remiliaState_sit_start(){}
	inline ~remiliaState_sit_start(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========
//========== remiliaState_sit_end
class remiliaState_sit_end : public remiliaState
{
public:
	inline remiliaState_sit_end(){}
	inline ~remiliaState_sit_end(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========

//========== remiliaState_gungnir_create
class remiliaState_gungnir_create : public remiliaState
{
public:
	inline remiliaState_gungnir_create(){}
	inline ~remiliaState_gungnir_create(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bOnEffect;
};
//===========
//========== remiliaState_gungnir_ready
class remiliaState_gungnir_ready : public remiliaState
{
public:
	inline remiliaState_gungnir_ready(){}
	inline ~remiliaState_gungnir_ready(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bOnEffect;
};
//===========
//========== remiliaState_gungnir_start
class remiliaState_gungnir_start : public remiliaState
{
public:
	inline remiliaState_gungnir_start(){}
	inline ~remiliaState_gungnir_start(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========

//========== remiliaState_huyajyou_ready
class remiliaState_huyajyou_ready : public remiliaState
{
public:
	inline remiliaState_huyajyou_ready(){}
	inline ~remiliaState_huyajyou_ready(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

};
//===========
//========== remiliaState_huyajyou_start
class remiliaState_huyajyou_start : public remiliaState
{
public:
	inline remiliaState_huyajyou_start(){}
	inline ~remiliaState_huyajyou_start(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bOnEffect;
	float _damage;
	float _deltaTime;
};
//===========
//========== remiliaState_huyajyou_end
class remiliaState_huyajyou_end : public remiliaState
{
public:
	inline remiliaState_huyajyou_end(){}
	inline ~remiliaState_huyajyou_end(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);
};
//===========

//========== remiliaState_hit_down_back
class remiliaState_hit_down_back : public remiliaState
{
public:
	inline remiliaState_hit_down_back(){}
	inline ~remiliaState_hit_down_back(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bOnEffect;
	bool _bMoveStop;
	float _deltaTime;
};
//===========

//========== remiliaState_stand_up_back_ready
class remiliaState_stand_up_back_ready : public remiliaState
{
public:
	inline remiliaState_stand_up_back_ready(){}
	inline ~remiliaState_stand_up_back_ready(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bOnEffect;
	float _deltaTime;
};
//===========
//========== remiliaState_stand_up_back_start
class remiliaState_stand_up_back_start : public remiliaState
{
public:
	inline remiliaState_stand_up_back_start(){}
	inline ~remiliaState_stand_up_back_start(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bOnEffect;
	float _deltaTime;
};
//===========

//========== remiliaState_hit_down_forward
class remiliaState_hit_down_forward : public remiliaState
{
public:
	inline remiliaState_hit_down_forward(){}
	inline ~remiliaState_hit_down_forward(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bOnEffect;
	bool _bMoveStop;
	float _deltaTime;
};
//===========

//========== remiliaState_stand_up_forward_ready
class remiliaState_stand_up_forward_ready : public remiliaState
{
public:
	inline remiliaState_stand_up_forward_ready(){}
	inline ~remiliaState_stand_up_forward_ready(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bOnEffect;
	float _deltaTime;
};
//===========
//========== remiliaState_stand_up_forward_start
class remiliaState_stand_up_forward_start : public remiliaState
{
public:
	inline remiliaState_stand_up_forward_start(){}
	inline ~remiliaState_stand_up_forward_start(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bOnEffect;
	float _deltaTime;
};
//===========

//========== remiliaState_hit_forward
class remiliaState_hit_forward : public remiliaState
{
public:
	inline remiliaState_hit_forward(){}
	inline ~remiliaState_hit_forward(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bOnEffect;
	float _deltaTime;
};
//===========

//========== remiliaState_die
class remiliaState_die : public remiliaState
{
public:
	inline remiliaState_die(){}
	inline ~remiliaState_die(){}

private:
	virtual void enter(remilia* pCha);
	virtual void execute(remilia* pCha);
	virtual void exit(remilia* pCha);

private:
	bool _bOnEffect;
	bool _bMoveStop;
	float _deltaTime;
};
//===========