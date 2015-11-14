#include "stdafx.h"
#include "blueBoogie.h"


void blueBoogie::animationInit()
{
	// blueBoogie right
	KEYANIMANAGER->addCoordinateFrameAnimation("r_blueBoogie_walk_forward", "blueBoogie_walk_forward", 7, 0, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_blueBoogie_idle", "blueBoogie_idle", 7, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_blueBoogie_die", "blueBoogie_die", 4, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_blueBoogie_attack_ready1", "blueBoogie_attack", 11, 10, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_blueBoogie_attack_start1", "blueBoogie_attack", 9, 8, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_blueBoogie_attack_ready2", "blueBoogie_attack", 7, 7, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_blueBoogie_attack_start2", "blueBoogie_attack", 6, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("r_blueBoogie_hit_forward", "blueBoogie_hit_forward", 0, 0, 10, false, false);

	// blueBoogie left
	KEYANIMANAGER->addCoordinateFrameAnimation("l_blueBoogie_walk_forward", "blueBoogie_walk_forward", 0, 7, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_blueBoogie_idle", "blueBoogie_idle", 0, 7, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_blueBoogie_die", "blueBoogie_die", 0, 4, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_blueBoogie_attack_ready1", "blueBoogie_attack", 0, 1, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_blueBoogie_attack_start1", "blueBoogie_attack", 2, 3, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_blueBoogie_attack_ready2", "blueBoogie_attack", 4, 4, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_blueBoogie_attack_start2", "blueBoogie_attack", 5, 11, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("l_blueBoogie_hit_forward", "blueBoogie_hit_forward", 0, 0, 10, false, false);

}