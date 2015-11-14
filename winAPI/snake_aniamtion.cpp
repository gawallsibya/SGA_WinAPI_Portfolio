#include "stdafx.h"
#include "snake.h"


void snake::animationInit()
{
	// snake right
	KEYANIMANAGER->addCoordinateFrameAnimation("r_snake_walk_forward", "snake_walk_forward", 5, 0, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_snake_idle", "snake_idle", 9, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_snake_die", "snake_die", 4, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_snake_attack_ready", "snake_attack", 5, 5, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_snake_attack_start", "snake_attack", 4, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_snake_attack_end", "snake_attack", 1, 5, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_snake_hit_forward", "snake_hit_forward", 0, 0, 10, false, false);
	
	// snake left
	KEYANIMANAGER->addCoordinateFrameAnimation("l_snake_walk_forward", "snake_walk_forward", 0, 5, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_snake_idle", "snake_idle", 0, 9, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_snake_die", "snake_die", 0, 4, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_snake_attack_ready", "snake_attack", 0, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_snake_attack_start", "snake_attack", 1 ,5, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_snake_attack_end", "snake_attack", 5, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_snake_hit_forward", "snake_hit_forward", 0, 0, 10, false, false);

}